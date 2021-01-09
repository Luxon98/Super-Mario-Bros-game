#include "World.h"

#include "SoundController.h"
#include "CollisionHandling.h"
#include "UtilityFunctions.h"
#include "Camera.h"
#include "AnimatedObject.h"
#include "Player.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Star.h"
#include "FireBall.h"
#include "Turtle.h"
#include "Creature.h"
#include "FireMissle.h"
#include "Boss.h"
#include "JumpingFish.h"
#include "CloudBombardier.h"
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
#include "DestroyedBoss.h"
#include "DestroyedFish.h"
#include "DestroyedBombardier.h"
#include "LayoutStyle.h"
#include "Screen.h"


int World::WORLD_HEIGHT = 480;
LayoutStyle World::LAYOUT_STYLE = LayoutStyle::OpenWorld;

bool World::isTimeToChangeColors() const
{
	auto timePoint = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastColoursUpdateTime).count() >= 750) {
		return true;
	}

	return false;
}

bool World::isPlayerCloseEnough(IndependentMovingObject &npc) const
{
	if (npc.getX() < player->getX() + camera->getReferencePoint() * 1.5) {
		return true;
	}

	return false;
}

bool World::isObjectOutsideWorld(MovingObject &object) const
{
	if (object.getY() > WORLD_HEIGHT + DISTANCE_FROM_WORLD) {
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

void World::deleteTemporaryElements()
{
	for (std::size_t i = 0; i < temporaryElements.size(); ++i) {
		if (temporaryElements[i]->shouldBeRemoved()) {
			if (temporaryElements[i]->isAnimatedCoin()) {
				addAnimatedText(TextType::TWO_HUNDRED, Position(temporaryElements[i]->getPosition()));
			}

			temporaryElements.erase(temporaryElements.begin() + i);
		}
	}

	for (std::size_t j = 0; j < destroyedElements.size(); ++j) {
		if (destroyedElements[j]->shouldBeRemoved()) {
			destroyedElements.erase(destroyedElements.begin() + j);
		}
	}
}

void World::handleFireballStatus()
{
	if (fireballStatus) {
		if (player->isArmed()) {
			SoundController::playFireballPoppedEffect();
			Direction direction = determineDirection(*player);
			fireballs.push_back(FireBall(Position(player->getX() + 5, player->getY() - 15), direction));
		}

		fireballStatus = false;
	}
}

void World::performBonusElementsActions()
{
	for (std::size_t i = 0; i < bonuses.size(); ++i) {
		bonuses[i]->move(*this);
		if (isObjectOutsideWorld(*bonuses[i])) {
			deleteBonus(i);
		}
	}
}

void World::performNpcsActions()
{
	for (std::size_t i = 0; i < npcs.size(); ++i) {
		if (npcs[i]->shouldStartMoving(*player)) {
			npcs[i]->startMoving();
			break;
		}

		if (isObjectOutsideWorld(*npcs[i])) {
			npcs.erase(npcs.begin() + i);
			break;
		}

		npcs[i]->move(*this);
		npcs[i]->performSpecificActions(*this, i);
	}
}

void World::performFireBallsActions()
{
	for (std::size_t i = 0; i < fireballs.size(); ++i) {
		fireballs[i].move(*this);

		if (fireballs[i].shouldBeRemoved()) {
			int shift = determineShift(fireballs[i], 7);
			temporaryElements.push_back(std::make_shared<Explosion>(Explosion(
				Position(fireballs[i].getX() + shift, fireballs[i].getY()))));

			fireballs.erase(fireballs.begin() + i);
		}
		else if (isObjectOutsideWorld(fireballs[i]) || isObjectOutsideCamera(fireballs[i], *camera)) {
			fireballs.erase(fireballs.begin() + i);
		}
	}

	handleFireballStatus();
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

void World::performAnimatedElementsActions()
{
	for (auto &animatedElement : animatedElements) {
		animatedElement->move();
	}
}

void World::performWorldActions(bool playerActionFlag)
{
	if (playerActionFlag) {
		player->move(*this);
	}
	
	performBonusElementsActions();
	performNpcsActions();
	performFireBallsActions();
	performFireSerpentsActions();
	performAnimatedElementsActions();

	if (slidingCounter) {
		slideBlock();
	}

	if (flag != nullptr && flag->isActive()) {
		flag->changePosition();
	}
}

void World::slideTemporaryElements()
{
	for (auto &animatedElement : temporaryElements) {
		animatedElement->slide();
	}

	for (auto &destroyedElement : destroyedElements) {
		destroyedElement->slide();
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
	destroyedElements.push_back(std::make_shared<Shards>(Shards(position)));
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
		bonuses.push_back(std::make_shared<Mushroom>(Mushroom(Position(
			blocks[lastTouchedBlockIndex].getPosition()), false)));
		blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
	}
	else if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithFlower) {
		if (player->isSmall()) {
			bonuses.push_back(std::make_shared<Mushroom>(Mushroom(Position(
				blocks[lastTouchedBlockIndex].getPosition()), false)));
		}
		else {
			bonuses.push_back(std::make_shared<Flower>(Flower(Position(
				blocks[lastTouchedBlockIndex].getPosition()))));
		}
		blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
	}
	else if (blocks[lastTouchedBlockIndex].getType() == BlockType::BonusWithStar) {
		bonuses.push_back(std::make_shared<Star>(Star(Position(blocks[lastTouchedBlockIndex].getPosition()))));
		blocks[lastTouchedBlockIndex].setType(BlockType::AlternativeEmpty);
	}
}

void World::createOneUpMushroom()
{
	bonuses.push_back(std::make_shared<Mushroom>(Mushroom(Position(blocks[lastTouchedBlockIndex].getX(),
		blocks[lastTouchedBlockIndex].getY() - 8), true)));

	blocks[lastTouchedBlockIndex].setType(BlockType::Empty);
}

void World::playBlockSoundEffects()
{
	BlockType blockType = blocks[lastTouchedBlockIndex].getType();
	if ((blockType >= BlockType::BonusWithOneUpMushroom && blockType <= BlockType::BonusWithStar) 
		&& blockType != BlockType::BonusWithCoin) {

		SoundController::playBonusAppearedEffect();
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

void World::drawTemporaryElements(SDL_Surface* display)
{
	for (const auto &animatedElement : temporaryElements) {
		animatedElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
}

void World::drawBonusesAndNpcs(SDL_Surface* display)
{
	for (const auto &bonusElement : bonuses) {
		bonusElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}

	for (const auto &npc : npcs) {
		npc->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
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

void World::drawDestroyedElements(SDL_Surface* display)
{
	for (const auto &destroyedElement : destroyedElements) {
		destroyedElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
	}
}

void World::drawAnimatedElements(SDL_Surface* display)
{
	for (const auto &animatedElement : animatedElements) {
		animatedElement->draw(display, camera->getBeginningOfCamera(), camera->getEndOfCamera());
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
	return bonuses;
}

std::vector<std::shared_ptr<IndependentMovingObject>> const& World::getNpcs() const
{
	return npcs;
}

const Player& World::getPlayer() const
{
	return *player;
}

const Camera& World::getCamera() const
{
	return *camera;
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

bool World::isBridgeDestroyedAlready() const
{
	for (const auto &platform : platforms) {
		if (platform.getPlatformType() == PlatformType::Bridge) {
			return false;
		}
	}

	return true;
}

bool World::areAnimatedElementsEmpty() const
{
	return (temporaryElements.size() == 0);
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

int World::getLastTouchedBlockIndex() const
{
	return lastTouchedBlockIndex;
}

BlockType World::getLastTouchedBlockType() const
{
	return blocks[lastTouchedBlockIndex].getType();
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

void World::spoilBridgeAndBoss()
{
	if (platforms.size() > 0 && (platforms[platforms.size() - 1].getPlatformType() == PlatformType::Bridge)) {
		platforms[platforms.size() - 1].reduceBridge();
		if (platforms[platforms.size() - 1].getBridgeLength() == 0) {
			platforms.pop_back();
		}
	}

	if (npcs.size() > 0 && npcs[npcs.size() - 1]->isBoss()) {
		addDestroyedBoss(npcs[npcs.size() - 1]->getPosition(), npcs[npcs.size() - 1]->getDirection(), false); 
		npcs.pop_back();
		SoundController::playEnemyDestroyedEffect(true);
	}
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

void World::deleteBonus(int index)
{
	bonuses.erase(bonuses.begin() + index);
}

void World::deleteNpc(int index)
{
	npcs.erase(npcs.begin() + index);
}

void World::deleteFireBall(int index)
{
	fireballs.erase(fireballs.begin() + index);
}

void World::addShell(Position position, bool red)
{
	npcs.push_back(std::make_shared<Shell>(Shell(position, red)));
}

void World::addFireBomb(Position position)
{
	npcs.push_back(std::make_shared<FireMissle>(FireMissle(position, MissleType::Bomb)));
}

void World::addTurtle(Position position)
{
	npcs.push_back(std::make_shared<Turtle>(Turtle(Position(position))));
}

void World::addCrushedCreature(Position position)
{
	temporaryElements.push_back(std::make_shared<CrushedCreature>(CrushedCreature(position)));
}

void World::addDestroyedCreature(Position position, Direction slideDirection)
{
	destroyedElements.push_back(std::make_shared<DestroyedCreature>(DestroyedCreature(position, slideDirection)));
}

void World::addDestroyedTurtle(Position position, Direction slideDirection, bool red)
{
	destroyedElements.push_back(std::make_shared<DestroyedTurtle>(DestroyedTurtle(position, slideDirection, red)));
}

void World::addDestroyedBoss(Position position, Direction direction, bool normal)
{
	temporaryElements.push_back(std::make_shared<DestroyedBoss>(DestroyedBoss(position, direction, normal)));
}

void World::addDestroyedFish(Position position, Direction direction)
{
	destroyedElements.push_back(std::make_shared<DestroyedFish>(DestroyedFish(position, direction)));
}

void World::addDestroyedBombardier(Position position, Direction direction)
{
	destroyedElements.push_back(std::make_shared<DestroyedBombardier>(DestroyedBombardier(position, direction)));
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

void World::performActions(bool playerActionFlag)
{
	++gameCounter;
	if (gameCounter % (10 - gameSpeed) == 0) {
		performWorldActions(playerActionFlag);
		deleteTemporaryElements();
		slideTemporaryElements();

		handleBonusesCollecting(*player, *this);
		handleShellsAndNpcsCollisions(*this, *player);
		handleFireBallsAndNpcsCollisions(*this, *player);

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
	drawTemporaryElements(display);
	drawBonusesAndNpcs(display);
	drawAnimatedElements(display);
	drawPlatformsAndFireballs(display);
	drawOtherObjects(display, drawPlayer);
	drawDestroyedElements(display);
}