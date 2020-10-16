#include "World.h"

#include "CollisionHandling.h"
#include "Block.h"
#include "Camera.h"
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
#include "LayoutStyle.h"
#include "Screen.h"


LayoutStyle World::LAYOUT_STYLE = LayoutStyle::OpenWorld;

bool World::isTimeToChangeColors() const
{
	auto timePoint = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastColoursUpdateTime).count() >= 750) {
		return true;
	}

	return false;
}

bool World::isPlayerCloseEnough(LivingObject &monster) const
{
	if (monster.getX() < player->getX() + Camera::CAMERA_REFERENCE_POINT * 1.5) {
		return true;
	}

	return false;
}

bool World::hasLastTouchedBlockCoin() const
{
	if (blocks[lastTouchedBlockIndex].getType() == BlockType::Monetary ||
		blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithCoin) {

		return true;
	}

	return false;
}

bool World::isLastTouchedBlockBonus() const
{
	if (blocks[lastTouchedBlockIndex].getType() >= BlockType::BonusWithRedMushroom
		&& blocks[lastTouchedBlockIndex].getType() <= BlockType::BonusWithStar) {

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
	Screen::changeCoinImage();
}

void World::setMovementDirection(LivingObject &monster)
{
	if (dynamic_cast<Turtle*>(&monster)) {
		dynamic_cast<Turtle*>(&monster)->setMoveDirection(Direction::Left);
	}
	else if (dynamic_cast<Creature*>(&monster)) {
		dynamic_cast<Creature*>(&monster)->setMoveDirection(Direction::Left);
	}
}

void World::deleteTemporaryElements()
{
	for (std::size_t i = 0; i < temporaryElements.size(); ++i) {
		if (temporaryElements[i]->shouldBeRemoved()) {
			if (std::dynamic_pointer_cast<AnimatedCoin>(temporaryElements[i])) {
				addAnimatedText(TextType::TWO_HUNDRED, Position(temporaryElements[i]->getX(),
					temporaryElements[i]->getY()));
			}

			temporaryElements.erase(temporaryElements.begin() + i);
		}
	}
}

void World::performBonusElementsActions()
{
	for (std::size_t i = 0; i < bonusElements.size(); ++i) {
		bonusElements[i]->move(*this);
		if (bonusElements[i]->getY() > WORLD_HEIGHT + DISTANCE_FROM_WORLD) {
			deleteLivingElement(i);
		}
	}
}

void World::performMonstersActions()
{
	for (std::size_t i = 0; i < monsters.size(); ++i) {
		if (monsters[i]->getMovement().getDirection() == Direction::None && isPlayerCloseEnough(*monsters[i])) {
			setMovementDirection(*monsters[i]);
		}

		monsters[i]->move(*this);

		if (std::dynamic_pointer_cast<Shell>(monsters[i])) {

			if (monsters[i]->getX() < camera->getBeginningOfCamera() 
				|| monsters[i]->getX() > camera->getEndOfCamera()) {

				deleteMonster(i);
				break;
			}

			if (!(std::dynamic_pointer_cast<Shell>(monsters[i])->isActive())
				&& std::dynamic_pointer_cast<Shell>(monsters[i])->shouldTurnIntoTurtle()) {

				monsters.push_back(std::make_shared<Turtle>(Turtle(Position(monsters[i]->getX(), 
					monsters[i]->getY()))));
				monsters.erase(monsters.begin() + i);
			}

			if (monsters[i]->getY() > WORLD_HEIGHT + DISTANCE_FROM_WORLD) {
				deleteMonster(i);
			}
		}
	}
}

void World::performFireBallsActions()
{
	for (std::size_t i = 0; i < fireballs.size(); ++i) {
		fireballs[i].move(*this);

		if (fireballs[i].shouldBeRemoved()) {
			int shift = (fireballs[i].getMovement().getDirection() == Direction::Left ? -7 : 7);
			temporaryElements.push_back(std::make_shared<Explosion>(Explosion(
				Position(fireballs[i].getX() + shift, fireballs[i].getY()))));

			fireballs.erase(fireballs.begin() + i);
		}
		else if (fireballs[i].getY() > WORLD_HEIGHT + DISTANCE_FROM_WORLD) {
			fireballs.erase(fireballs.begin() + i);
		}
		else if (fireballs[i].getX() < camera->getBeginningOfCamera()
			|| fireballs[i].getX() > camera->getEndOfCamera()) {

			fireballs.erase(fireballs.begin() + i);
		}
	}

	if (fireballStatus && player->isArmed()) {
		SoundController::playFireballPoppedEffect();
		Direction direction = (player->isTurnedRight() ? Direction::Right : Direction::Left);
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
	for (auto &temporaryElement : temporaryElements) {
		temporaryElement->slide();
	}
}

void World::slideBlock()
{
	if (isBlockBlockedByAnother(blocks[lastTouchedBlockIndex], *this)) {
		slidingCounter = 0;
		return;
	}

	if (slidingCounter == SLIDING_BLOCK_VALUE) {
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

void World::raiseUpMushroom()
{
	for (auto &bonusElement : bonusElements) {
		if (std::dynamic_pointer_cast<Mushroom>(bonusElement)) {
			if ((bonusElement->getY() + bonusElement->getHeight() / 2) ==
				blocks[lastTouchedBlockIndex].getY() - blocks[lastTouchedBlockIndex].getHeight() / 2
				&& areAtTheSameWidth(*bonusElement, blocks[lastTouchedBlockIndex])) {

				std::dynamic_pointer_cast<Mushroom>(bonusElement)->decreasePositionY();
				std::dynamic_pointer_cast<Mushroom>(bonusElement)->setStepsUp(30);
				return;
			}
		}
	}
}

void World::addShards(Position position)
{
	temporaryElements.push_back(std::make_shared<Shards>(Shards(position)));
}

void World::performBlockSliding()
{
	--slidingCounter;
	if (slidingCounter & 1) {
		int height = (slidingCounter <= 40 ? 1 : -1);
		blocks[lastTouchedBlockIndex].addToPositionY(height);

		if (slidingCounter > 40 && blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithOneUpMushroom) {
			createGreenMushroom();
		}
	}

	handleMonstersAndBlockCollisions(*this, blocks[lastTouchedBlockIndex], *player);
}

void World::subtractCoinFromBlock()
{
	if (blocks[lastTouchedBlockIndex].getType() == BlockType::Monetary) {
		blocks[lastTouchedBlockIndex].decrementCoins();
		player->incrementCoins();
		player->addPoints(200);
		temporaryElements.push_back(std::make_shared<AnimatedCoin>(AnimatedCoin(
			Position(blocks[lastTouchedBlockIndex].getX(), blocks[lastTouchedBlockIndex].getY() - 50))));

		if (!blocks[lastTouchedBlockIndex].hasCoins()) {
			blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
		}
	}
	else if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithCoin) {
		player->incrementCoins();
		player->addPoints(200);
		temporaryElements.push_back(std::make_shared<AnimatedCoin>(AnimatedCoin(
			Position(blocks[lastTouchedBlockIndex].getX(), blocks[lastTouchedBlockIndex].getY() - 56))));

		blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
	}
}

void World::createNewBonus()
{
	if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithRedMushroom) {
		bonusElements.push_back(std::make_shared<Mushroom>(Mushroom(Position(blocks[lastTouchedBlockIndex].getX(),
			blocks[lastTouchedBlockIndex].getY()), false)));
	}
	else if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithFlower) {
		if (player->isSmall()) {
			bonusElements.push_back(std::make_shared<Mushroom>(Mushroom(Position(blocks[lastTouchedBlockIndex].getX(),
				blocks[lastTouchedBlockIndex].getY()), false)));
		}
		else {
			bonusElements.push_back(std::make_shared<Flower>(Flower(Position(blocks[lastTouchedBlockIndex].getX(),
				blocks[lastTouchedBlockIndex].getY()))));
		}
	}
	else if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithStar) {
		bonusElements.push_back(std::make_shared<Star>(Star(Position(blocks[lastTouchedBlockIndex].getX(),
			blocks[lastTouchedBlockIndex].getY()))));
	}

	blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
}

void World::createGreenMushroom()
{
	bonusElements.push_back(std::make_shared<Mushroom>(Mushroom(Position(blocks[lastTouchedBlockIndex].getX(),
		blocks[lastTouchedBlockIndex].getY() - 8), true)));

	blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
}

void World::playBlockSoundEffects()
{
	if (blocks[lastTouchedBlockIndex].getType() >= BlockType::BonusWithOneUpMushroom &&
		blocks[lastTouchedBlockIndex].getType() <= BlockType::BonusWithStar) {
		SoundController::playBonusAppeardEffect();
	}
	else if (blocks[lastTouchedBlockIndex].getType() >= BlockType::Monetary &&
		blocks[lastTouchedBlockIndex].getType() <= BlockType::BonusWithCoin) {
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
	lastTouchedBlockIndex = -1;
	flag = Flag();
	slidingCounter = 0;
	slideBlockStatus = true;
	fireballStatus = false;
}

std::vector<Block> const& World::getBlocks() const
{
	return blocks;
}

std::vector<MovingPlatform> const& World::getPlatforms() const
{
	return platforms;
}

std::vector<FireBall> const& World::getFireBalls() const
{
	return fireballs;
}

std::vector<std::shared_ptr<InanimateObject>> const& World::getInanimateElements() const
{
	return inanimateElements;
}

std::vector<std::shared_ptr<BonusObject>> const& World::getBonusElements() const
{
	return bonusElements;
}

std::vector<std::shared_ptr<LivingObject>> const& World::getMonsters() const
{
	return monsters;
}

const Player& World::getPlayer() const
{
	return *player;
}

int World::getLastTouchedBlockIndex() const
{
	return lastTouchedBlockIndex;
}

BlockType World::getLastTouchedBlockType() const
{
	return blocks[lastTouchedBlockIndex].getType();
}

bool World::isFlagDown() const
{
	return flag.isDown();
}

bool World::isPlayerFinishingWorld() const
{
	if (player->getX() >= flag.getX() + 15 && player->getX() <= flag.getX() + 65) {
		return true;
	}

	return false;
}

void World::setPlayer(std::shared_ptr<Player> player)
{
	this->player = std::move(player);
}

void World::setCamera(std::shared_ptr<Camera> camera)
{
	this->camera = std::move(camera);
}

void World::setLastTouchedBlock(int index)
{
	if (!slidingCounter) {
		lastTouchedBlockIndex = index;
	}
}

void World::hitBlock()
{
	if ((blocks[lastTouchedBlockIndex].getType() >= BlockType::Destructible && blocks[lastTouchedBlockIndex].getType()
		<= BlockType::BonusWithStar) && blocks[lastTouchedBlockIndex].canBeHitted()) {

		slidingCounter = SLIDING_BLOCK_VALUE;
	}
}

void World::setFireballStatus()
{
	if (fireballs.size() != MAX_NUMBER_OF_FIREBALLS) {
		fireballStatus = true;
	}
}

void World::switchOnFlag()
{
	flag.setActiveState();
}

void World::changeShellMovementParameters(int index, Direction direction)
{
	std::dynamic_pointer_cast<Shell>(monsters[index])->setMovementDirectionAndActiveState(direction);
	std::dynamic_pointer_cast<Shell>(monsters[index])->resetCreationTime();
}

void World::resetImages()
{
	Screen::resetCoinImage();
	Block::resetBlockImage();
	Coin::resetCoinImage();
}

void World::destroyLastTouchedBlock()
{
	addShards(Position(blocks[lastTouchedBlockIndex].getX(), blocks[lastTouchedBlockIndex].getY()));
	handleMonstersAndBlockCollisions(*this, blocks[lastTouchedBlockIndex], *player);
	blocks.erase(blocks.begin() + lastTouchedBlockIndex);
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

void World::addShell(Position position, bool red)
{
	monsters.push_back(std::make_shared<Shell>(Shell(position, red)));
}

void World::addCrushedCreature(Position position)
{
	temporaryElements.push_back(std::make_shared<CrushedCreature>(CrushedCreature(position)));
}

void World::addDestroyedCreature(Position position, Direction slideDirection)
{
	temporaryElements.push_back(std::make_shared<DestroyedCreature>(DestroyedCreature(position, slideDirection)));
}

void World::addDestroyedTurtle(Position position, Direction slideDirection, bool red)
{
	temporaryElements.push_back(std::make_shared<DestroyedTurtle>(DestroyedTurtle(position, slideDirection, red)));
}

void World::addExplosion(Position position)
{
	temporaryElements.push_back(std::make_shared<Explosion>(Explosion(position)));
}

void World::addAnimatedText(TextType type, Position position)
{
	temporaryElements.push_back(std::make_shared<AnimatedText>(AnimatedText(type, position)));
}

void World::performActions()
{
	++gameCounter;
	if (gameCounter % 3 == 0) {
		performWorldActions();
		deleteTemporaryElements();
		slideTemporaryElements();

		collectBonusIfPossible(*player, *this);
		handleShellsAndMonstersCollisions(*this, *player);
		handleFireBallsAndMonstersCollisions(*this, *player);

		if (isTimeToChangeColors()) {
			changeColors();
		}

		if (gameCounter & 1) {
			for (auto &platform : platforms) {
				platform.slide(*player);
			}
		}
	}

	handlePlayerCollisions(*player, *this);
}

void World::draw(SDL_Surface* display, bool drawPlayer)
{
	for (const auto &inanimateElement : inanimateElements) {
		inanimateElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &bonusElement : bonusElements) {
		bonusElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &monster : monsters) {
		monster->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &fireball : fireballs) {
		fireball.draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &block : blocks) {
		block.draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &platform : platforms) {
		platform.draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &temporaryElement : temporaryElements) {
		temporaryElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	flag.draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());

	if (drawPlayer) {
		player->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
}