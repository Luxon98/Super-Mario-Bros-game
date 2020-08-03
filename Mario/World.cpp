#include "World.h"


void World::changeColoursIfAvailable()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastColoursUpdateTime).count() >= 750) {
		this->lastColoursUpdateTime = timePoint;
		Coin::changeCoinImage();
		Block::changeBlockImage();
		Flower::changeFlowerImage();
	}
}

void World::setMovementDirectionIfPlayerIsCloseEnough(NonControllableLivingObject& monster)
{
	if (monster.getX() < this->player->getX() + 2 * CAMERA_REFERENCE_POINT) {
		if (dynamic_cast<Turtle*>(&monster)) {
			dynamic_cast<Turtle*>(&monster)->setMoveDirection(Left);
		}
		else if (dynamic_cast<Creature*>(&monster)) {
			dynamic_cast<Creature*>(&monster)->setMoveDirection(Left);
		}
	}
}

void World::deleteTemporaryElementsIfTimePassed()
{
	for (unsigned int i = 0; i < this->temporaryElements.size(); ++i) {
		if (this->temporaryElements[i]->shouldBeRemoved()) {
			if (dynamic_cast<AnimatedCoin*>(this->temporaryElements[i])) {
				this->addAnimatedText(TWO_HUNDRED, new Position(this->temporaryElements[i]->getX(),
					this->temporaryElements[i]->getY()));
			}
			this->temporaryElements.erase(this->temporaryElements.begin() + i);
		}
	}
}

void World::performBonusElementsActions()
{
	for (unsigned int i = 0; i < bonusElements.size(); ++i) {
		this->bonusElements[i]->move(this->bonusElements[i]->getMoveDirection(), 1, *this);
		if (this->bonusElements[i]->getY() > WORLD_HEIGHT + 30) {
			this->deleteLivingElement(i);
		}
	}
}

void World::performMonstersActions()
{
	for (unsigned int i = 0; i < monsters.size(); ++i) {
		if (this->monsters[i]->getMoveDirection() == None) {
			this->setMovementDirectionIfPlayerIsCloseEnough(*this->monsters[i]);
		}

		this->monsters[i]->move(this->monsters[i]->getMoveDirection(), 1, *this);

		if (dynamic_cast<Shell*>(this->monsters[i]) && !(dynamic_cast<Shell*>(this->monsters[i])->isActive())
			&& dynamic_cast<Shell*>(this->monsters[i])->shouldTurnIntoTurtle()) {

			this->monsters.push_back(new Turtle(new Position(this->monsters[i]->getX(), this->monsters[i]->getY())));
			this->monsters.erase(this->monsters.begin() + i);
		}

		if (this->monsters[i]->getY() > WORLD_HEIGHT + 30) {
			this->deleteMonster(i, false);
		}
	}
}

void World::performFireBallsActions()
{
	for (unsigned int i = 0; i < fireballs.size(); ++i) {
		this->fireballs[i].move(this->fireballs[i].getMoveDirection(), 1, *this, nullptr);

		if (this->fireballs[i].shouldBeRemoved()) {
			int shift = (this->fireballs[i].getMoveDirection() == Left ? -5 : 5);
			this->temporaryElements.push_back(new Explosion(new Position(this->fireballs[i].getX() + shift,
				this->fireballs[i].getY())));

			this->fireballs.erase(this->fireballs.begin() + i);
		}
		else if (this->fireballs[i].getY() > WORLD_HEIGHT + 30) {
			this->fireballs.erase(this->fireballs.begin() + i);
		}
	}

	if (this->fireballStatus && this->player->isArmed()) {
		SoundController::playFireballPoppedEffect();
		this->fireballs.push_back(FireBall(new Position(this->player->getX() + 5, this->player->getY() - 15),
			this->player->getMovementDirection()));

		this->fireballStatus = false;
	}
}

void World::performWorldActions()
{
	this->performBonusElementsActions();
	this->performMonstersActions();
	this->performFireBallsActions();

	if (this->slidingCounter) {
		this->slideBlock();
	}

	if (this->flag->isActive()) {
		this->flag->changePosition();
	}
}

void World::slideTemporaryElements()
{
	for (unsigned int i = 0; i < this->temporaryElements.size(); ++i) {
		this->temporaryElements[i]->slide();
	}
}

void World::slideBlock()
{
	if (isFlowerStandingOnTheBlock(*this, this->lastTouchedBlockIndex)) {
		this->slidingCounter = 0;
	}
	else {
		if (this->slidingCounter == 124) {
			this->playBlockSoundEffects();
			this->subtractCoinFromBlockIfPossible();
		}

		this->slidingCounter--;

		if (this->slidingCounter % 3 == 0) {
			int height = (this->slidingCounter <= 60 ? 1 : -1);
			this->blocks[lastTouchedBlockIndex].addToPositionY(height);

			if (this->slidingCounter > 60 && this->blocks[lastTouchedBlockIndex].getModel() == BonusWithGreenMushroom) {
				this->createGreenMushroom();
			}
		}
		handleIfMonsterCollideWithDestroyedBlock(*this, this->blocks[this->lastTouchedBlockIndex], this->player);

		if (this->slidingCounter == 0) {
			this->createNewBonusIfPossible();
		}
	}
}

void World::addShards(int x, int y)
{
	this->temporaryElements.push_back(new Shards(x, y));
}

void World::subtractCoinFromBlockIfPossible()
{
	if (this->blocks[this->lastTouchedBlockIndex].getModel() == Monetary) {
		this->blocks[this->lastTouchedBlockIndex].setAvailableCoins(this->blocks[this->lastTouchedBlockIndex].getAvailableCoins() - 1);
		this->player->incrementCoins();
		this->player->addPoints(200);
		this->temporaryElements.push_back(new AnimatedCoin(new Position(this->blocks[this->lastTouchedBlockIndex].getX(),
			this->blocks[this->lastTouchedBlockIndex].getY() - 56)));

		if (!this->blocks[this->lastTouchedBlockIndex].getAvailableCoins()) {
			this->blocks[this->lastTouchedBlockIndex].setModel(Empty);
		}
	}
	else if (this->blocks[this->lastTouchedBlockIndex].getModel() == BonusWithCoin) {
		this->player->incrementCoins();
		this->player->addPoints(200);
		this->temporaryElements.push_back(new AnimatedCoin(new Position(this->blocks[this->lastTouchedBlockIndex].getX(),
			this->blocks[this->lastTouchedBlockIndex].getY() - 50)));
		this->blocks[this->lastTouchedBlockIndex].setModel(Empty);
	}
}

void World::createNewBonusIfPossible()
{
	if (this->blocks[this->lastTouchedBlockIndex].getModel() == BonusWithRedMushroom) {
		this->bonusElements.push_back(new Mushroom(new Position(this->blocks[this->lastTouchedBlockIndex].getX(),
			this->blocks[this->lastTouchedBlockIndex].getY()), false));
		this->blocks[this->lastTouchedBlockIndex].setModel(Empty);
	}
	else if (this->blocks[this->lastTouchedBlockIndex].getModel() == BonusWithFlower) {
		this->bonusElements.push_back(new Flower(new Position(this->blocks[this->lastTouchedBlockIndex].getX(),
			this->blocks[this->lastTouchedBlockIndex].getY())));
		this->blocks[this->lastTouchedBlockIndex].setModel(Empty);
	}
	else if (this->blocks[this->lastTouchedBlockIndex].getModel() == BonusWithStar) {
		this->bonusElements.push_back(new Star(new Position(this->blocks[this->lastTouchedBlockIndex].getX(),
			this->blocks[this->lastTouchedBlockIndex].getY())));
		this->blocks[this->lastTouchedBlockIndex].setModel(Empty);
	}
}

void World::createGreenMushroom()
{
	this->bonusElements.push_back(new Mushroom(new Position(this->blocks[this->lastTouchedBlockIndex].getX(),
		this->blocks[this->lastTouchedBlockIndex].getY()), true));
	this->blocks[lastTouchedBlockIndex].setModel(Empty);
}

void World::playBlockSoundEffects()
{
	if (this->blocks[this->lastTouchedBlockIndex].getModel() >= BonusWithGreenMushroom &&
		this->blocks[this->lastTouchedBlockIndex].getModel() <= BonusWithStar) {
		SoundController::playBonusAppeardEffect();
	}
	else if (this->blocks[this->lastTouchedBlockIndex].getModel() >= Monetary &&
		this->blocks[this->lastTouchedBlockIndex].getModel() <= BonusWithCoin) {
		SoundController::playCoinCollectedEffect();
	}
	else {
		SoundController::playBlockHittedEffect();
	}
}

World::World()
{
	this->lastColoursUpdateTime = std::chrono::steady_clock::now();
	this->lastTouchedBlockIndex = 0;
	this->player = nullptr;
	this->flag = nullptr;
	this->slidingCounter = 0;
	this->fireballStatus = false;
}

std::vector<Block> World::getBlocks() const
{
	return this->blocks;
}

std::vector<InanimateObject*> World::getInanimateElements() const
{
	return this->inanimateElements;
}

std::vector<BonusObject*> World::getBonusElements() const
{
	return this->bonusElements;
}

std::vector<NonControllableLivingObject*> World::getMonsters() const
{
	return this->monsters;
}

std::vector<FireBall> World::getFireBalls() const
{
	return this->fireballs;
}

int World::getLastTouchedBlockIndex() const
{
	return this->lastTouchedBlockIndex;
}

int World::getBlockModel(int index) const
{
	return this->blocks[index].getModel();
}

bool World::isFlagDown() const
{
	return this->flag->isDown();
}

void World::setPlayer(Player* playerPointer)
{
	this->player = playerPointer;
}

void World::setLastTouchedBlock(int index)
{
	if (!this->slidingCounter) {
		this->lastTouchedBlockIndex = index;
	}
}

void World::setSlidingCounter(int ctr)
{
	if (this->blocks[this->lastTouchedBlockIndex].getModel() >= Destructible &&
		this->blocks[this->lastTouchedBlockIndex].getModel() <= BonusWithStar) {
		this->slidingCounter = ctr;
	}
}

void World::setFireballStatus()
{
	if (this->fireballs.size() != 3) {
		this->fireballStatus = true;
	}
}

void World::setActiveFlag()
{
	this->flag->setActiveState();
}

void World::changeShellMovementParameters(int index, Direction direction)
{
	dynamic_cast<Shell*>(this->monsters[index])->setMovementDirectionAndActiveState(direction);
	dynamic_cast<Shell*>(this->monsters[index])->resetCreationTime();
}

void World::deleteBlock(int index)
{
	this->addShards(this->blocks[index].getX(), this->blocks[index].getY());
	handleIfMonsterCollideWithDestroyedBlock(*this, this->blocks[index], this->player);
	this->blocks.erase(this->blocks.begin() + index);
	this->player->addPoints(50);

	SoundController::playBlockDestroyedEffect();
}

void World::deleteInanimateElement(int index)
{
	this->inanimateElements.erase(this->inanimateElements.begin() + index);
}

void World::deleteLivingElement(int index)
{
	this->bonusElements.erase(this->bonusElements.begin() + index);
}

void World::deleteMonster(int index, bool sound)
{
	if (sound) {
		SoundController::playEnemyDestroyedEffect();
	}
	this->monsters.erase(this->monsters.begin() + index);
}

void World::deleteFireBall(int index)
{
	this->fireballs.erase(this->fireballs.begin() + index);
}

void World::addShell(Position* position)
{
	this->monsters.push_back(new Shell(position));
}

void World::addCrushedCreature(Position* position)
{
	this->temporaryElements.push_back(new CrushedCreature(position));
}

void World::addDestroyedCreature(Position* position)
{
	this->temporaryElements.push_back(new DestroyedCreature(position));
}

void World::addDestroyedTurtle(Position* position)
{
	this->temporaryElements.push_back(new DestroyedTurtle(position));
}

void World::addExplosion(Position* position)
{
	this->temporaryElements.push_back(new Explosion(position));
}

void World::addAnimatedText(TextType type, Position* position)
{
	this->temporaryElements.push_back(new AnimatedText(type, position));
}

void World::performActions()
{
	this->performWorldActions();
	this->deleteTemporaryElementsIfTimePassed();
	this->slideTemporaryElements();

	collectBonusIfPossible(this->player, *this);
	handleIfCollisionWithMonsterOccurs(this->player, *this);
	handleIfShellCollideWithMonsters(*this, this->player);
	handleIfFireBallCollideWithMonsters(*this, this->player);

	this->changeColoursIfAvailable();
}

void World::draw(SDL_Surface* screen, int beginningOfScreen, bool playerFlag)
{
	for (unsigned int i = 0; i < inanimateElements.size(); ++i) {
		this->inanimateElements[i]->draw(screen, beginningOfScreen);
	}

	for (unsigned int i = 0; i < bonusElements.size(); ++i) {
		this->bonusElements[i]->draw(screen, beginningOfScreen);
	}

	for (unsigned int i = 0; i < monsters.size(); ++i) {
		this->monsters[i]->draw(screen, beginningOfScreen);
	}

	for (auto it = this->fireballs.begin(); it != this->fireballs.end(); ++it) {
		it->draw(screen, beginningOfScreen);
	}

	for (auto it = this->blocks.begin(); it != this->blocks.end(); ++it) {
		it->draw(screen, beginningOfScreen);
	}

	for (unsigned int i = 0; i < temporaryElements.size(); ++i) {
		this->temporaryElements[i]->draw(screen, beginningOfScreen);
	}

	this->flag->draw(screen, beginningOfScreen);

	if (playerFlag) {
		this->player->draw(screen, this->player->getCameraX());
	}
}

