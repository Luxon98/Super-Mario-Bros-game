#include "World.h"

#include "Screen.h"
#include "CollisionHandling.h"
#include "Block.h"
#include "LivingObject.h"
#include "Player.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Star.h"
#include "FireBall.h"
#include "Turtle.h"
#include "Creature.h"
#include "Shell.h"
#include "Flag.h"
#include "AnimatedText.h"
#include "AnimatedCoin.h"
#include "Shards.h"
#include "Explosion.h"
#include "CrushedCreature.h"
#include "DestroyedCreature.h"
#include "DestroyedTurtle.h"
#include "Position.h"
#include "SoundController.h"


bool World::isTimeToChangeColors()
{
	auto timePoint = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastColoursUpdateTime).count() >= 750) {
		return true;
	}

	return false;
}

bool World::isPlayerCloseEnough(LivingObject& monster)
{
	if (monster.getX() < player->getX() + 2 * CAMERA_REFERENCE_POINT) {
		return true;
	}

	return false;
}

bool World::hasLastTouchedBlockCoin()
{
	if (blocks[lastTouchedBlockIndex].getModel() == Monetary || 
		blocks[lastTouchedBlockIndex].getModel() == BonusWithCoin) {

		return true;
	}

	return false;
}

bool World::isLastTouchedBlockBonus()
{
	if (blocks[lastTouchedBlockIndex].getModel() == BonusWithRedMushroom 
		|| blocks[lastTouchedBlockIndex].getModel() == BonusWithFlower 
		|| blocks[lastTouchedBlockIndex].getModel() == BonusWithStar) {
		
		return true;
	}

	return false;
}

void World::changeColors()
{
	auto timePoint = std::chrono::steady_clock::now();
	lastColoursUpdateTime = timePoint;
	Coin::changeCoinImage();
	Block::changeBlockImage();
	Flower::changeFlowerImage();
}

void World::setMovementDirection(LivingObject& monster)
{
	if (dynamic_cast<Turtle*>(&monster)) {
		dynamic_cast<Turtle*>(&monster)->setMoveDirection(Left);
	}
	else if (dynamic_cast<Creature*>(&monster)) {
		dynamic_cast<Creature*>(&monster)->setMoveDirection(Left);
	}
}

void World::deleteTemporaryElements()
{
	for (unsigned int i = 0; i < temporaryElements.size(); ++i) {
		if (temporaryElements[i]->shouldBeRemoved()) {
			if (dynamic_cast<AnimatedCoin*>(temporaryElements[i])) {
				addAnimatedText(TWO_HUNDRED, Position(temporaryElements[i]->getX(), temporaryElements[i]->getY()));
			}

			temporaryElements.erase(temporaryElements.begin() + i);
		}
	}
}

void World::performBonusElementsActions()
{
	for (unsigned int i = 0; i < bonusElements.size(); ++i) {
		bonusElements[i]->move(*this);
		if (bonusElements[i]->getY() > WORLD_HEIGHT + DISTANCE_FROM_WORLD) {
			deleteLivingElement(i);
		}
	}
}

void World::performMonstersActions()
{
	for (unsigned int i = 0; i < monsters.size(); ++i) {
		if (monsters[i]->getMovement().getDirection() == None && isPlayerCloseEnough(*monsters[i])) {
			setMovementDirection(*monsters[i]);
		}

		monsters[i]->move(*this);

		if (dynamic_cast<Shell*>(monsters[i]) && !(dynamic_cast<Shell*>(monsters[i])->isActive()) 
			&& dynamic_cast<Shell*>(monsters[i])->shouldTurnIntoTurtle()) {

			monsters.push_back(new Turtle(Position(monsters[i]->getX(), monsters[i]->getY())));
			monsters.erase(monsters.begin() + i);
		}

		if (monsters[i]->getY() > WORLD_HEIGHT + DISTANCE_FROM_WORLD) {
			deleteMonster(i);
		}
	}
}

void World::performFireBallsActions()
{
	for (unsigned int i = 0; i < fireballs.size(); ++i) {
		fireballs[i].move(*this);

		if (fireballs[i].shouldBeRemoved()) {
			int shift = (fireballs[i].getMovement().getDirection() == Left ? -5 : 5);
			temporaryElements.push_back(new Explosion(Position(fireballs[i].getX() + shift, fireballs[i].getY())));

			fireballs.erase(fireballs.begin() + i);
		}
		else if (fireballs[i].getY() > WORLD_HEIGHT + DISTANCE_FROM_WORLD) {
			fireballs.erase(fireballs.begin() + i);
		}
	}

	if (fireballStatus && player->isArmed()) {
		SoundController::playFireballPoppedEffect();
		Direction direction = player->isTurnedRight() ? Right : Left;
		fireballs.push_back(FireBall(Position(player->getX() + 5, player->getY() - 15), direction));

		fireballStatus = false;
	}
}

void World::performWorldActions()
{
	player->move(*this);
	performBonusElementsActions();
	performMonstersActions();
	performFireBallsActions();

	if (slidingCounter) {
		slideBlock();
	}

	if (flag.isActive()) {
		flag.changePosition();
	}
}

void World::slideTemporaryElements()
{
	for (unsigned int i = 0; i < temporaryElements.size(); ++i) {
		temporaryElements[i]->slide();
	}
}

void World::slideBlock()
{
	if (isFlowerStandingOnTheBlock(*this, lastTouchedBlockIndex)) {
		slidingCounter = 0;
	}
	else {
		if (slidingCounter == 124) {
			playBlockSoundEffects();

			if (hasLastTouchedBlockCoin()) {
				subtractCoinFromBlock();
			}

			if (isMushroomStandingOnTheBlock(*this, lastTouchedBlockIndex)) {
				raiseUpMushroom();
			}
		}

		performBlockSliding();

		if (slidingCounter == 0) {
			if (isLastTouchedBlockBonus()) {
				createNewBonus();
			}

			slideBlockStatus = true;
		}
	}
}

void World::raiseUpMushroom()
{
	std::vector<BonusObject*> elements = getBonusElements();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (dynamic_cast<Mushroom*>(*it)) {
			if (((*it)->getY() + (*it)->getHeight() / 2) == 
				blocks[lastTouchedBlockIndex].getY() - blocks[lastTouchedBlockIndex].getHeight() / 2 
				&& areAtTheSameWidth(*it, blocks[lastTouchedBlockIndex])) {

				dynamic_cast<Mushroom*>(*it)->decreasePositionY();
				dynamic_cast<Mushroom*>(*it)->setStepsUp(30);
				return;
			}
		}
	}
}

void World::addShards(Position position)
{
	temporaryElements.push_back(new Shards(position));
}

void World::performBlockSliding()
{
	slidingCounter--;
	if (slidingCounter % 3 == 0) {
		int height = (slidingCounter <= 60 ? 1 : -1);
		blocks[lastTouchedBlockIndex].addToPositionY(height);

		if (slidingCounter > 60 && blocks[lastTouchedBlockIndex].getModel() == BonusWithGreenMushroom) {
			createGreenMushroom();
		}
	}

	handleMonstersAndBlockCollisions(*this, blocks[lastTouchedBlockIndex], player);
}

void World::subtractCoinFromBlock()
{
	if (blocks[lastTouchedBlockIndex].getModel() == Monetary) {
		blocks[lastTouchedBlockIndex].setAvailableCoins(blocks[lastTouchedBlockIndex].getAvailableCoins() - 1);
		player->incrementCoins();
		player->addPoints(200);
		temporaryElements.push_back(new AnimatedCoin(Position(blocks[lastTouchedBlockIndex].getX(), 
			blocks[lastTouchedBlockIndex].getY() - 56)));

		if (!blocks[lastTouchedBlockIndex].getAvailableCoins()) {
			blocks[lastTouchedBlockIndex].setModel(Empty);
		}
	}
	else if (blocks[lastTouchedBlockIndex].getModel() == BonusWithCoin) {
		player->incrementCoins();
		player->addPoints(200);
		temporaryElements.push_back(new AnimatedCoin(Position(blocks[lastTouchedBlockIndex].getX(), 
			blocks[lastTouchedBlockIndex].getY() - 50)));

		blocks[lastTouchedBlockIndex].setModel(Empty);
	}
}

void World::createNewBonus()
{
	if (blocks[lastTouchedBlockIndex].getModel() == BonusWithRedMushroom) {
		bonusElements.push_back(new Mushroom(Position(blocks[lastTouchedBlockIndex].getX(), 
			blocks[lastTouchedBlockIndex].getY()), false));
	}
	else if (blocks[lastTouchedBlockIndex].getModel() == BonusWithFlower) {
		if (player->isSmall()) {
			bonusElements.push_back(new Mushroom(Position(blocks[lastTouchedBlockIndex].getX(), 
				blocks[lastTouchedBlockIndex].getY()), false));
		}
		else {
			bonusElements.push_back(new Flower(Position(blocks[lastTouchedBlockIndex].getX(), 
				blocks[lastTouchedBlockIndex].getY())));
		}
	}
	else if (blocks[lastTouchedBlockIndex].getModel() == BonusWithStar) {
		bonusElements.push_back(new Star(Position(blocks[lastTouchedBlockIndex].getX(), 
			blocks[lastTouchedBlockIndex].getY())));
	}

	blocks[lastTouchedBlockIndex].setModel(Empty);
}

void World::createGreenMushroom()
{
	bonusElements.push_back(new Mushroom(Position(blocks[lastTouchedBlockIndex].getX(), 
		blocks[lastTouchedBlockIndex].getY()), true));

	blocks[lastTouchedBlockIndex].setModel(Empty);
}

void World::playBlockSoundEffects()
{
	if (blocks[lastTouchedBlockIndex].getModel() >= BonusWithGreenMushroom &&
		blocks[lastTouchedBlockIndex].getModel() <= BonusWithStar) {
		SoundController::playBonusAppeardEffect();
	}
	else if (blocks[lastTouchedBlockIndex].getModel() >= Monetary &&
		blocks[lastTouchedBlockIndex].getModel() <= BonusWithCoin) {
		SoundController::playCoinCollectedEffect();
	}
	else {
		SoundController::playBlockHittedEffect();
	}
}

World::World()
{
	gameCounter = 0;
	lastColoursUpdateTime = std::chrono::steady_clock::now();
	lastTouchedBlockIndex = 0;
	player = nullptr;
	screen = nullptr;
	flag = Flag();
	slidingCounter = 0;
	slideBlockStatus = true;
	fireballStatus = false;
}

std::vector<Block> World::getBlocks() const
{
	return blocks;
}

std::vector<InanimateObject*> World::getInanimateElements() const
{
	return inanimateElements;
}

std::vector<BonusObject*> World::getBonusElements() const
{
	return bonusElements;
}

std::vector<LivingObject*> World::getMonsters() const
{
	return monsters;
}

std::vector<FireBall> World::getFireBalls() const
{
	return fireballs;
}

int World::getLastTouchedBlockIndex() const
{
	return lastTouchedBlockIndex;
}

int World::getBlockModel(int index) const
{
	return blocks[index].getModel();
}

bool World::isFlagDown() const
{
	return flag.isDown();
}

Screen* World::getScreen() const
{
	return screen;
}

void World::setPlayer(Player* player)
{
	this->player = player;
}

void World::setScreen(Screen* screen)
{
	this->screen = screen;
}

void World::setLastTouchedBlock(int index)
{
	if (!slidingCounter) {
		lastTouchedBlockIndex = index;
	}
}

void World::hitBlock()
{
	if ((blocks[lastTouchedBlockIndex].getModel() >= Destructible && blocks[lastTouchedBlockIndex].getModel()
		<= BonusWithStar) && blocks[lastTouchedBlockIndex].canBeHitted()) {

		slidingCounter = 124;
	}
}

void World::setFireballStatus()
{
	if (fireballs.size() != 3) {
		fireballStatus = true;
	}
}

void World::switchOnFlag()
{
	flag.setActiveState();
}

bool World::isPlayerFinishingWorld()
{
	if (player->getX() >= flag.getX() + 15 && player->getX() <= flag.getX() + 65) {
		return true;
	}

	return false;
}

void World::changeShellMovementParameters(int index, Direction direction)
{
	dynamic_cast<Shell*>(monsters[index])->setMovementDirectionAndActiveState(direction);
	dynamic_cast<Shell*>(monsters[index])->resetCreationTime();
}

void World::performBlockRemovalActions(int index)
{
	addShards(Position(blocks[index].getX(), blocks[index].getY()));
	handleMonstersAndBlockCollisions(*this, blocks[index], player);
	blocks.erase(blocks.begin() + index);
	player->addPoints(50);

	SoundController::playBlockDestroyedEffect();
}

void World::deleteInanimateElement(int index)
{
	inanimateElements.erase(inanimateElements.begin() + index);
}

void World::deleteLivingElement(int index)
{
	bonusElements.erase(bonusElements.begin() + index);
}

void World::deleteMonster(int index)
{
	monsters.erase(monsters.begin() + index);
}

void World::deleteFireBall(int index)
{
	fireballs.erase(fireballs.begin() + index);
}

void World::addShell(Position position)
{
	monsters.push_back(new Shell(position));
}

void World::addCrushedCreature(Position position)
{
	temporaryElements.push_back(new CrushedCreature(position));
}

void World::addDestroyedCreature(Position position)
{
	temporaryElements.push_back(new DestroyedCreature(position));
}

void World::addDestroyedTurtle(Position position)
{
	temporaryElements.push_back(new DestroyedTurtle(position));
}

void World::addExplosion(Position position)
{
	temporaryElements.push_back(new Explosion(position));
}

void World::addAnimatedText(TextType type, Position position)
{
	temporaryElements.push_back(new AnimatedText(type, position));
}

void World::performActions()
{
	gameCounter++;
	if (gameCounter % 3 == 0) {
		performWorldActions();
		deleteTemporaryElements();
		slideTemporaryElements();

		collectBonusIfPossible(player, *this);
		handlePlayerCollisions(player, *this);
		handleShellsAndMonstersCollisions(*this, player);
		handleFireBallsAndMonstersCollisions(*this, player);

		if (isTimeToChangeColors()) {
			changeColors();
		}
	}
}

void World::draw(SDL_Surface* display, int beginningOfScreen, int endOfScreen, bool drawPlayer)
{
	for (auto &inanimateElement : inanimateElements) {
		inanimateElement->draw(display, beginningOfScreen, endOfScreen);
	}

	for (auto &bonusElement : bonusElements) {
		bonusElement->draw(display, beginningOfScreen, endOfScreen);
	}

	for (auto &monster : monsters) {
		monster->draw(display, beginningOfScreen, endOfScreen);
	}

	for (auto &fireball : fireballs) {
		fireball.draw(display, beginningOfScreen, endOfScreen);
	}

	for (auto &block : blocks) {
		block.draw(display, beginningOfScreen, endOfScreen);
	}

	for (auto &temporaryElement : temporaryElements) {
		temporaryElement->draw(display, beginningOfScreen, endOfScreen);
	}

	flag.draw(display, beginningOfScreen, endOfScreen);

	if (drawPlayer) {
		player->draw(display, beginningOfScreen, endOfScreen);
	}
}

World::~World()
{
	player = nullptr;
	screen = nullptr;
}

