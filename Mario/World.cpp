#include "World.h"

#include "CollisionHandling.h"
#include "UtilityFunctions.h"
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
#include "FireRocket.h"
#include "Boss.h"
#include "Shell.h"
#include "Flag.h"
#include "Button.h"
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
	if (monster.getX() < player->getX() + camera->getReferencePoint() * 1.5) {
		return true;
	}

	return false;
}

bool World::hasLastTouchedBlockCoin() const
{
	BlockType blockType = blocks[lastTouchedBlockIndex].getType();
	if (blockType == BlockType::Monetary || blockType == BlockType::BonusWithCoin) {
		return true;
	}

	return false;
}

bool World::isLastTouchedBlockBonus() const
{
	BlockType blockType = blocks[lastTouchedBlockIndex].getType();
	if (blockType == BlockType::BonusWithRedMushroom || blockType == BlockType::BonusWithFlower
		|| blockType == BlockType::BonusWithStar) {

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
	Button::changeButtonImage();
}

void World::setMovementDirection(LivingObject &monster)
{
	if (dynamic_cast<Turtle*>(&monster)) {
		dynamic_cast<Turtle*>(&monster)->setMoveDirection(Direction::Left);
	}
	else if (dynamic_cast<Creature*>(&monster)) {
		dynamic_cast<Creature*>(&monster)->setMoveDirection(Direction::Left);
	}
	else if (dynamic_cast<FireRocket*>(&monster)) {
		dynamic_cast<FireRocket*>(&monster)->setMoveDirection(Direction::Left);
	}
	else if (dynamic_cast<Boss*>(&monster)) {
		dynamic_cast<Boss*>(&monster)->setMoveDirection(Direction::Left);
	}
}

void World::deleteTemporaryElements()
{
	for (std::size_t i = 0; i < temporaryElements.size(); ++i) {
		if (temporaryElements[i]->shouldBeRemoved()) {
			if (std::dynamic_pointer_cast<AnimatedCoin>(temporaryElements[i])) {
				addAnimatedText(TextType::TWO_HUNDRED, Position(temporaryElements[i]->getPosition()));
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

				monsters.push_back(std::make_shared<Turtle>(Turtle(Position(monsters[i]->getPosition()))));
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

void World::performPlatformsActions()
{
	for (auto &platform : platforms) {
		platform.slide(*player);
	}
}

void World::performFireSerpentsActions()
{
	for (auto &fireSerpent : fireSerpents) {
		fireSerpent.move();
	}
}

void World::performWorldActions()
{
	player->move(*this);
	performBonusElementsActions();
	performMonstersActions();
	performFireBallsActions();
	performFireSerpentsActions();

	if (slidingCounter) {
		slideBlock();
	}

	if (flag != nullptr && flag->isActive()) {
		flag->changePosition();
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
	}

	performBlockSliding();

	if (slidingCounter == 0) {
		if (isLastTouchedBlockBonus()) {
			createNewBonus();
		}

		slideBlockStatus = true;
	}
}

void World::collectCoin()
{
	player->incrementCoins();
	player->addPoints(200);
	addAnimatedCoin();
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
			createOneUpMushroom();
		}
	}

	handleBlockCollisions(*this, blocks[lastTouchedBlockIndex], *player);
}

void World::subtractCoinFromBlock()
{
	if (blocks[lastTouchedBlockIndex].getType() == BlockType::Monetary) {
		blocks[lastTouchedBlockIndex].decrementCoins();
		collectCoin();

		if (!blocks[lastTouchedBlockIndex].hasCoins()) {
			blocks[lastTouchedBlockIndex].setType(BlockType::AlternativeEmpty);
		}
	}
	else if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithCoin) {
		collectCoin();
		blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
	}
}

void World::createNewBonus()
{
	if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithRedMushroom) {
		bonusElements.push_back(std::make_shared<Mushroom>(Mushroom(Position(
			blocks[lastTouchedBlockIndex].getPosition()), false)));
		blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
	}
	else if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithFlower) {
		if (player->isSmall()) {
			bonusElements.push_back(std::make_shared<Mushroom>(Mushroom(Position(
				blocks[lastTouchedBlockIndex].getPosition()), false)));
		}
		else {
			bonusElements.push_back(std::make_shared<Flower>(Flower(Position(
				blocks[lastTouchedBlockIndex].getPosition()))));
		}
		blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
	}
	else if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithStar) {
		bonusElements.push_back(std::make_shared<Star>(Star(Position(blocks[lastTouchedBlockIndex].getPosition()))));
		blocks[lastTouchedBlockIndex].setType(BlockType::AlternativeEmpty);
	}
}

void World::createOneUpMushroom()
{
	bonusElements.push_back(std::make_shared<Mushroom>(Mushroom(Position(blocks[lastTouchedBlockIndex].getX(),
		blocks[lastTouchedBlockIndex].getY() - 8), true)));

	blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
}

void World::playBlockSoundEffects()
{
	BlockType blockType = blocks[lastTouchedBlockIndex].getType();
	if ((blockType >= BlockType::BonusWithOneUpMushroom && blockType <= BlockType::BonusWithStar) 
		&& blockType != BlockType::BonusWithCoin) {

		SoundController::playBonusAppeardEffect();
	}
	else if (blockType == BlockType::Monetary || blockType == BlockType::BonusWithCoin) {
		SoundController::playCoinCollectedEffect();
	}
	else {
		SoundController::playBlockHittedEffect();
	}
}

void World::drawInanimateElements(SDL_Surface* display)
{
	for (const auto &inanimateElement : inanimateElements) {
		inanimateElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
}

void World::drawBonusesAndMonsters(SDL_Surface* display)
{
	for (const auto &bonusElement : bonusElements) {
		bonusElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &monster : monsters) {
		monster->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
}

void World::drawPlatformsAndFireballs(SDL_Surface* display)
{
	for (const auto &fireball : fireballs) {
		fireball.draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &platform : platforms) {
		platform.draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
}

void World::drawOtherObjects(SDL_Surface* display, bool drawPlayer)
{
	if (flag != nullptr) {
		flag->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
	if (button != nullptr) {
		button->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	if (drawPlayer) {
		player->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &block : blocks) {
		block.draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &fireSerpent : fireSerpents) {
		fireSerpent.draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
}

void World::drawTemporaryElements(SDL_Surface* display)
{
	for (const auto &temporaryElement : temporaryElements) {
		temporaryElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
}

World::World()
{
	gameCounter = 0;
	gameSpeed = 7;
	lastColoursUpdateTime = std::chrono::steady_clock::now();
	lastTouchedBlockIndex = -1;
	slidingCounter = 0;
	slideBlockStatus = true;
	fireballStatus = false;
}

std::vector<Block> const& World::getBlocks() const
{
	return blocks;
}

std::vector<Platform> const& World::getPlatforms() const
{
	return platforms;
}

std::vector<FireBall> const& World::getFireBalls() const
{
	return fireballs;
}

std::vector<FireSerpent> const& World::getFireSerpents() const
{
	return fireSerpents;
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
	return flag->isDown();
}

bool World::isPlayerFinishingWorld() const
{
	if (flag != nullptr && flag->isPlayerHittingThisFlag(*player)) {
		return true;
	}
	else if (button != nullptr && button->isPlayerHittingThisButton(*player)) {
		return true;
	}

	return false;
}

int World::getLastReachedCheckPointMark() const
{
	for (const auto &checkPoint : checkPoints) {
		if (checkPoint.isPlayerInRangeOfCheckPoint(*player)) {
			if (checkPoint.isAutomatic() || (!checkPoint.isAutomatic() && player->isGoingToPipe()
				&& isCharacterStandingOnSomething(*player, *this))) {

				return checkPoint.getMark();
			}
		}
	}

	return -1;
}

void World::setGameSpeed(int gameSpeed)
{
	this->gameSpeed = gameSpeed;
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
	if (lastTouchedBlockIndex != -1) {
		BlockType blockType = blocks[lastTouchedBlockIndex].getType();
		if (((blockType >= BlockType::BonusWithOneUpMushroom && blockType <= BlockType::Monetary) 
			|| blockType == BlockType::Destructible) && blocks[lastTouchedBlockIndex].canBeHitted()) {

			slidingCounter = SLIDING_BLOCK_VALUE;
		}
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
	flag->setActiveState();
}

void World::changeShellMovementParameters(int index, Direction direction)
{
	std::dynamic_pointer_cast<Shell>(monsters[index])->setActiveStateParameters(direction);
	std::dynamic_pointer_cast<Shell>(monsters[index])->resetCreationTime();
}

void World::resetImages()
{
	Screen::resetCoinImage();
	Block::resetBlockImage();
	Coin::resetCoinImage();
	Button::resetButtonImage();
}

void World::destroyLastTouchedBlock()
{
	addShards(Position(blocks[lastTouchedBlockIndex].getPosition()));
	handleBlockCollisions(*this, blocks[lastTouchedBlockIndex], *player);
	blocks.erase(blocks.begin() + lastTouchedBlockIndex);
	player->addPoints(50);

	SoundController::playBlockDestroyedEffect();
}

void World::deleteCoin(int index)
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

void World::addAnimatedCoin()
{
	Position position = Position(blocks[lastTouchedBlockIndex].getX(), blocks[lastTouchedBlockIndex].getY() - 50);
	temporaryElements.push_back(std::make_shared<AnimatedCoin>(AnimatedCoin(position)));
}

void World::performActions()
{
	++gameCounter;
	if (gameCounter % (10 - gameSpeed) == 0) {
		performWorldActions();
		deleteTemporaryElements();
		slideTemporaryElements();

		handleBonusCollecting(*player, *this);
		handleShellsAndMonstersCollisions(*this, *player);
		handleFireBallsAndMonstersCollisions(*this, *player);

		if (isTimeToChangeColors()) {
			changeColors();
		}

		if (gameCounter & 1) {
			performPlatformsActions();
		}
	}

	handlePlayerCollisions(*player, *this);
}

void World::draw(SDL_Surface* display, bool drawPlayer)
{
	drawInanimateElements(display);
	drawBonusesAndMonsters(display);
	drawPlatformsAndFireballs(display);
	drawOtherObjects(display, drawPlayer);
	drawTemporaryElements(display);
}