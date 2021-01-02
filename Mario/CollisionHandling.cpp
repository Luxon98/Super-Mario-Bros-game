#include "CollisionHandling.h"

#include <vector>
#include <cmath>
#include "Player.h"
#include "SoundController.h"
#include "Block.h"
#include "Platform.h"
#include "World.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Star.h"
#include "Shell.h"
#include "Turtle.h"
#include "RedTurtle.h"
#include "FireMissle.h"
#include "Creature.h"
#include "Plant.h"
#include "JumpingFish.h"
#include "CloudBombardier.h"
#include "FireBall.h"
#include "Boss.h"
#include "Position.h"
#include "AnimatedText.h"
#include "Screen.h"
#include "UtilityFunctions.h"
#include "WorldInteractionFunctions.h"


bool isCharacterHittingObject(const WorldObject &figure, const WorldObject &block, Direction direction, int distance)
{
	if (direction == Direction::Right && figure.getX() < block.getX()
		&& figure.getX() + distance + figure.getWidth() / 2 >= block.getX() - block.getWidth() / 2) {

		return true;
	}
	else if (direction == Direction::Left && figure.getX() > block.getX()
		&& figure.getX() - distance - figure.getWidth() / 2 <= block.getX() + block.getWidth() / 2) {

		return true;
	}
	else if (direction == Direction::Up && figure.getY() > block.getY()
		&& figure.getY() - distance - figure.getHeight() / 2 <= block.getY() + block.getHeight() / 2) {

		return true;
	}
	else if (direction == Direction::Down && figure.getY() < block.getY()
		&& figure.getY() + distance + figure.getHeight() / 2 >= block.getY() - block.getHeight() / 2) {

		return true;
	}

	return false;
}

bool isCharacterStandingOnSomething(const WorldObject &figure, const World &world)
{
	std::vector<Block> blocks = world.getBlocks();
	for (auto &block : blocks) {
		if (isElementDirectlyAboveObject(figure, block) && areAtTheSameWidth(figure, block) 
			&& !block.isInvisible()) {

			return true;
		}
	}

	std::vector<Platform> platforms = world.getPlatforms();
	for (auto &platform : platforms) {
		if (isElementDirectlyAboveObject(figure, platform) && areAtTheSameWidth(figure, platform)) {
			return true;
		}
	}

	return false;
}

bool isMonsterStandingOnBlock(const LivingObject &monster, const Block &block)
{
	if (isMonsterCloseAboveBlock(monster, block) && areAtTheSameWidth(monster, block)) {
		return true;
	}

	return false;
}

bool isMushroomStandingOnBlock(const World &world, const Block &block)
{
	std::vector<std::shared_ptr<BonusObject>> bonusElements = world.getBonusElements();
	for (auto &bonusElement : bonusElements) {
		if (std::dynamic_pointer_cast<Mushroom>(bonusElement)) {
			if (isElementDirectlyAboveObject(*bonusElement, block) && areAtTheSameWidth(*bonusElement, block)) {
				return true;
			}
		}
	}

	return false;
}

bool isPlayerCloseToFireRocket(const FireMissle &fireRocket, const World &world)
{
	const Player& player = world.getPlayer();

	if (abs(player.getX() - fireRocket.getX()) < 350) {
		return true;
	}

	return false;
}

bool isPlayerCloseToPlant(const Plant &plant, const World &world)
{
	const Player& player = world.getPlayer();
	int yDifference = plant.getY() - player.getY();

	if (abs(player.getX() - plant.getX()) < 40 && (yDifference > 30 && yDifference < 60)) {
		return true;
	}

	return false;
}

bool isPlayerAheadOfMonster(const LivingObject &monster, const World &world)
{
	const Player& player = world.getPlayer();

	if (player.getX() > monster.getX()) {
		return true;
	}

	return false;
}

bool isPlayerStandingOnThisPlatform(const Player &player, const Platform &platform)
{
	if (isElementDirectlyAboveObject(player, platform) && areAtTheSameWidth(player, platform)) {
		return true;
	}

	return false;
}

bool isBlockBlockedByAnother(const Block& block, const World& world)
{
	std::vector<Block> blocks = world.getBlocks();
	for (auto &element : blocks) {
		if (block.getX() == element.getX() && block.getY() == (element.getY() + block.getHeight())) {
			return true;
		}
	}

	return false;
}

bool isPlayerJumpingOnMonster(const Player &player, const LivingObject &monster)
{
	return ((monster.getY() - player.getY() > 25) && player.isNotJumpingUp());
}

bool isBonusStandingOnBlock(const BonusObject &bonus, const Block &block)
{
	return (isElementDirectlyAboveObject(bonus, block) && areAtTheSameWidth(bonus, block));
}

void handleJumpingOnMonster(std::shared_ptr<IndependentLivingObject> monster, World &world, Player &player, int index)
{
	player.performAdditionalJump();
	monster->crush(world, index);

	int points = monster->getPointsForCrushing();
	if (points) {
		addTextAndPoints(player, world, points, Position(monster->getX(), monster->getY() - 15));
	}
}

void handlePlayerAndMonstersCollisions(IndependentLivingObject &monster, World &world, Player &player, int index)
{
	if (player.isImmortal()) {
		if (!monster.isResistantToImmortalPlayer()) {
			Direction direction = determineDirection(player, monster);
			monster.destroy(world, direction);
			addTextAndPoints(player, world, monster.getPointsForDestroying(), Position(monster.getX(), monster.getY() - 15));
			world.deleteMonster(index);
			SoundController::playEnemyDestroyedEffect();
		}
		else if (isInactiveShell(monster)) {
			Direction direction = determineDirection(player, monster);
			dynamic_cast<Shell*>(&monster)->setActiveStateParameters(direction);
			dynamic_cast<Shell*>(&monster)->resetCreationTime();
		}
	}
	else if (isInactiveShell(monster)) {
		Direction direction = determineDirection(player, monster);
		dynamic_cast<Shell*>(&monster)->setActiveStateParameters(direction);
		dynamic_cast<Shell*>(&monster)->resetCreationTime();
	}
	else if (!player.isInsensitive()) {
		player.loseBonusOrLife();
	}
}

void handleCollisionsWithMonsters(Player &player, World &world)
{
	std::vector<std::shared_ptr<IndependentLivingObject>> monsters = world.getMonsters();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (areAtTheSameWidth(player, **it) && areAtTheSameHeight(player, **it)) {
			if (isPlayerJumpingOnMonster(player, **it) && !(*it)->isCrushproof()) {
				handleJumpingOnMonster(*it, world, player, it - monsters.begin());
			}
			else {
				handlePlayerAndMonstersCollisions(**it, world, player, it - monsters.begin());
			}
			break; //
		}
	}
}

void handleCollisionsWithFireSerpents(Player &player, World &world)
{
	std::vector<FireSerpent> fireSerpents = world.getFireSerpents();
	for (const auto &fireSerpent : fireSerpents) {
		if (areAtTheSameWidth(player, fireSerpent) && areAtTheSameHeight(player, fireSerpent)) {
			if (!player.isImmortal() && !player.isInsensitive()) {
				player.loseBonusOrLife();
				return;
			}
		}
	}
}

void handlePlayerCollisions(Player &player, World &world)
{
	handleCollisionsWithMonsters(player, world);
	handleCollisionsWithFireSerpents(player, world);
}

void handleShellsAndMonstersCollisions(World &world, Player &player)
{
	std::vector<std::shared_ptr<IndependentLivingObject>> monsters = world.getMonsters();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if ((*it)->isActiveShell()) {
			for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2) {
				if (!(*it2)->isResistantToCollisionWithShell() && (areAtTheSameWidth(**it, **it2)
					&& areAtTheSameHeight(**it, **it2))) {

					Direction direction = determineDirection(**it, **it2);
					(*it2)->destroy(world, direction);
					addTextAndPoints(player, world, (*it2)->getPointsForDestroying(), (*it2)->getPosition());
					world.deleteMonster(it2 - monsters.begin());
					SoundController::playEnemyDestroyedEffect();					
				}
			}
		}
	}
}

void handleFireBallDestruction(const FireBall &fireball, World &world, int fireballIndex)
{
	int alignment = (fireball.getMovement().getDirection() == Direction::Left ? -5 : 5);

	world.deleteFireBall(fireballIndex);
	world.addExplosion(Position(fireball.getX() + alignment, fireball.getY()));
}

void handleFireBallsAndMonstersCollisions(World &world, Player &player)
{
	std::vector<FireBall> fireballs = world.getFireBalls();
	std::vector<std::shared_ptr<IndependentLivingObject>> monsters = world.getMonsters();
	int index = 0;
	for (auto it = fireballs.begin(); it != fireballs.end(); ++it, ++index) {
		for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2) {
			if (!(*it2)->isResistantToFireBalls() && (areAtTheSameWidth(*it, **it2) 
				&& areAtTheSameHeight(*it, **it2))) {

				handleFireBallDestruction(fireballs[index], world, index);

				(*it2)->decrementHealthPoints();
				if ((*it2)->getHealthPoints() == 0) {
					int points = (*it2)->getPointsForDestroying();
					Direction direction = (*it).getMovement().getDirection();
					(*it2)->destroy(world, direction);
					world.deleteMonster(it2 - monsters.begin());
					addTextAndPoints(player, world, points, Position((*it2)->getX(), (*it2)->getY() - 15));
					bool bossFlag = (points == 5000);
					SoundController::playEnemyDestroyedEffect(bossFlag);
				}
			}
		}
	}
}

void handleBlockAndMonstersCollisions(World &world, const Block &block, Player &player)
{
	std::vector<std::shared_ptr<IndependentLivingObject>> monsters = world.getMonsters();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (!(*it)->isResistantToCollisionWithBlock() && isMonsterStandingOnBlock(**it, block)) {
			int points = (*it)->getPointsForDestroying();
			Direction direction = determineDirection(block, **it);
			(*it)->destroy(world, direction);
			addTextAndPoints(player, world, points, Position((*it)->getX(), (*it)->getY() - 15));
			world.deleteMonster(it - monsters.begin());
			SoundController::playEnemyDestroyedEffect();
		}
	}
}

void handleBlockAndBonusesCollisions(World &world, const Block &block, Player &player)
{
	std::vector<std::shared_ptr<BonusObject>> elements = world.getBonusElements();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (isBonusStandingOnBlock(**it, block) && block.canCollideWithBonuses()) {
			if ((*it)->isCoin()) {
				collectCoinByCollision(player, world, it - elements.begin());
			}
			else {
				(*it)->knockUp();
			}
			return;
		}
	}
}

void handleBlockCollisions(World &world, const Block &block, Player &player)
{
	handleBlockAndMonstersCollisions(world, block, player);
	handleBlockAndBonusesCollisions(world, block, player);
}

void handleBonusesCollecting(Player &player, World &world)
{
	std::vector<std::shared_ptr<BonusObject>> elements = world.getBonusElements();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (areAtTheSameWidth(player, **it) && areAtTheSameHeight(player, **it) && (*it)->isActive()) {
			(*it)->giveBonus(player);
			addTextAndPoints(player, world, (*it)->getPointsForCollecting());
			world.deleteBonusElement(it - elements.begin());
			return;
		}
	}
}

int getAlignmentForCollisionFromRight(int distance, const WorldObject &object, const Block &block, const World &world)
{
	int alignment = 0;

	if (block.getType() == BlockType::TubeLeftEntry) {
		if (!isCharacterStandingOnSomething(object, world)) {
			alignment = (object.getX() + distance + object.getWidth() / 2) - (block.getX() - block.getWidth() / 2);
		}
	}
	else {
		alignment = (object.getX() + distance + object.getWidth() / 2) - (block.getX() - block.getWidth() / 2);
	}
	
	return (alignment > 0 ? alignment : 0);
}

int getHorizontalAlignmentForCollisionWithBlocks(Direction direction, int distance, const WorldObject &object, const World &world)
{
	int alignment = 0;
	std::vector<Block> blocks = world.getBlocks();
	
	for (auto &block : blocks) {
		if (areAtTheSameHeight(object, block) && isCharacterHittingObject(object, block, direction, distance)
			&& !block.isInvisible()) {

			if (direction == Direction::Right) {
				alignment = getAlignmentForCollisionFromRight(distance, object, block, world);
			}
			else if (direction == Direction::Left) {
				alignment = (block.getX() + block.getWidth() / 2) - (object.getX() - distance - object.getWidth() / 2);
			}
			break;
		}
	}

	return (alignment > 0 ? alignment : 0);
}

int getHorizontalAlignmentForCollisionWithPlatforms(Direction direction, int distance, const WorldObject &object, const World &world)
{
	int alignment = 0;
	std::vector<Platform> platforms = world.getPlatforms();

	for (auto &platform : platforms) {
		if (areAtTheSameHeight(object, platform) && isCharacterHittingObject(object, platform, direction, distance)) {
			if (direction == Direction::Right) {
				alignment = (object.getX() + distance + object.getWidth() / 2) - (platform.getX() - platform.getWidth() / 2);
			}
			else if (direction == Direction::Left) {
				alignment = (platform.getX() + platform.getWidth() / 2) - (object.getX() - distance - object.getWidth() / 2);
			}
			break;
		}
	}

	return (alignment > 0 ? alignment : 0);
}

int computeHorizontalAlignment(Direction direction, int distance, const WorldObject &object, const World &world)
{
	int firstAlignment = getHorizontalAlignmentForCollisionWithBlocks(direction, distance, object, world);
	int secondAlignment = getHorizontalAlignmentForCollisionWithPlatforms(direction, distance, object, world);

	return (firstAlignment >= secondAlignment ? firstAlignment : secondAlignment);
}

// this method additionaly set the last touched block's index
int getVerticalAlignmentForCollisionWithBlocks(Direction direction, int distance, const WorldObject &object, World &world)
{
	int alignment = 0;
	std::vector<Block> blocks = world.getBlocks();

	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (areAtTheSameWidth(object, *it) && isCharacterHittingObject(object, *it, direction, distance)) {
			if (direction == Direction::Up) {
				alignment = (it->getY() + it->getHeight() / 2) - (object.getY() - distance - object.getHeight() / 2);

				if (alignment > 0) {
					world.setLastTouchedBlock(it - blocks.begin());	// 
				}
			}
			else if ( direction == Direction::Down && !it->isInvisible()) {
				alignment = (object.getY() + distance + object.getHeight() / 2) - (it->getY() - it->getHeight() / 2);
			}
			break;
		}
	}

	return (alignment > 0 ? alignment : 0);
}

// this method additionaly set the last touched block's index to -1
int getVerticalAlignmentForCollisionWithPlatforms(Direction direction, int distance, const WorldObject &object, World &world)
{
	int alignment = 0;
	std::vector<Platform> platforms = world.getPlatforms();

	for (auto it = platforms.begin(); it != platforms.end(); ++it) {
		if (areAtTheSameWidth(object, *it) && isCharacterHittingObject(object, *it, direction, distance)) {
			if (direction == Direction::Up) {
				alignment = (it->getY() + it->getHeight() / 2) - (object.getY() - distance - object.getHeight() / 2);

				if (alignment > 0) {
					world.setLastTouchedBlock(-1);	// 
				}
			}
			else if (direction == Direction::Down) {
				alignment = (object.getY() + distance + object.getHeight() / 2) - (it->getY() - it->getHeight() / 2);
			}
			break;
		}
	}

	return (alignment > 0 ? alignment : 0);
}

int computeVerticalAlignment(Direction direction, int distance, const WorldObject &object, World &world)
{
	int firstAlignment = getVerticalAlignmentForCollisionWithBlocks(direction, distance, object, world);
	int secondAlignment = getVerticalAlignmentForCollisionWithPlatforms(direction, distance, object, world);

	return (firstAlignment >= secondAlignment ? firstAlignment : secondAlignment);
}