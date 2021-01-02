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

bool isMonsterStandingOnBlock(const IndependentLivingObject &monster, const Block &block)
{
	if (isMonsterCloseAboveBlock(monster, block) && areAtTheSameWidth(monster, block)) {
		return true;
	}

	return false;
}

bool isBonusStandingOnBlock(const BonusObject &bonus, const Block &block)
{
	return (isElementDirectlyAboveObject(bonus, block) && areAtTheSameWidth(bonus, block));
}

bool isBlockBlockedByAnother(const Block &block, const World &world)
{
	std::vector<Block> blocks = world.getBlocks();
	for (auto &element : blocks) {
		if (block.getX() == element.getX() && block.getY() == (element.getY() + block.getHeight())) {
			return true;
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

bool isPlayerAheadOfMonster(const IndependentLivingObject &monster, const World &world)
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

bool isPlayerJumpingOnMonster(const Player &player, const IndependentLivingObject &monster)
{
	return ((monster.getY() - player.getY() > 25) && player.isNotJumpingUp());
}

void handleMonsterDestroying(IndependentLivingObject &npc, World &world, Player &player, Direction direction)
{
	npc.destroy(world, direction);
	addTextAndPoints(player, world, npc.getPointsForDestroying(), Position(npc.getX(), npc.getY() - 15));
}

void handleMonsterDeleting(World &world, int index, bool bossFlag)
{
	world.deleteMonster(index);
	SoundController::playEnemyDestroyedEffect(bossFlag);
}

void handleMonsterHpReducing(IndependentLivingObject &npc, World &world, Player &player, int index)
{
	npc.decrementHealthPoints();
	if (npc.getHealthPoints() == 0) {
		Direction direction = npc.getMovement().getDirection();
		handleMonsterDestroying(npc, world, player, direction);
		handleMonsterDeleting(world, index, (npc.getPointsForDestroying() == 5000));
	}
}

void handleFireBallDeleting(const FireBall &fireball, World &world, int index)
{
	int alignment = (fireball.getMovement().getDirection() == Direction::Left ? -5 : 5);

	world.deleteFireBall(index);
	world.addExplosion(Position(fireball.getX() + alignment, fireball.getY()));
}

void handleJumpingOnMonster(IndependentLivingObject &npc, World &world, Player &player, int index)
{
	player.performAdditionalJump();
	npc.crush(world, index);

	int points = npc.getPointsForCrushing();
	if (points) {
		addTextAndPoints(player, world, points, Position(npc.getX(), npc.getY() - 15));
	}
}

void handlePlayerAndMonsterCollision(IndependentLivingObject &npc, World &world, Player &player, int index)
{
	if (player.isImmortal()) {
		if (!npc.isResistantToImmortalPlayer()) {
			Direction direction = determineDirection(player, npc);
			handleMonsterDestroying(npc, world, player, direction);
			handleMonsterDeleting(world, index);
		}
		else if (isInactiveShell(npc)) {
			Direction direction = determineDirection(player, npc);
			dynamic_cast<Shell*>(&npc)->setActiveState(direction);
		}
	}
	else if (isInactiveShell(npc)) {
		Direction direction = determineDirection(player, npc);
		dynamic_cast<Shell*>(&npc)->setActiveState(direction);
	}
	else if (!player.isInsensitive()) {
		player.loseBonusOrLife();
	}
}

void handleCollisionsWithMonsters(Player &player, World &world)
{
	std::vector<std::shared_ptr<IndependentLivingObject>> monsters = world.getMonsters();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (areColliding(player, **it)) {
			if (isPlayerJumpingOnMonster(player, **it) && !(*it)->isCrushproof()) {
				handleJumpingOnMonster(**it, world, player, it - monsters.begin());
			}
			else {
				handlePlayerAndMonsterCollision(**it, world, player, it - monsters.begin());
			}
			return;
		}
	}
}

void handleCollisionsWithFireSerpents(Player &player, World &world)
{
	std::vector<FireSerpent> fireSerpents = world.getFireSerpents();
	for (const auto &fireSerpent : fireSerpents) {
		if (areColliding(player, fireSerpent) && !player.isImmortal() && !player.isInsensitive()) {
			player.loseBonusOrLife();
			return;
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
				if (!(*it2)->isResistantToCollisionWithShell() && areColliding(**it, **it2)) {
					Direction direction = determineDirection(**it, **it2);
					handleMonsterDestroying(**it2, world, player, direction);
					handleMonsterDeleting(world, it2 - monsters.begin());	
					return;
				}
			}
		}
	}
}

void handleFireBallsAndMonstersCollisions(World &world, Player &player)
{
	std::vector<FireBall> fireballs = world.getFireBalls();
	std::vector<std::shared_ptr<IndependentLivingObject>> monsters = world.getMonsters();
	for (auto it = fireballs.begin(); it != fireballs.end(); ++it) {
		for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2) {
			if (!(*it2)->isResistantToFireBalls() && areColliding(*it, **it2)) {
				handleMonsterHpReducing(**it2, world, player, it2 - monsters.begin());
				handleFireBallDeleting(*it, world, it - fireballs.begin());
				return;
			}
		}
	}
}

void handleBlockAndMonstersCollisions(World &world, const Block &block, Player &player)
{
	std::vector<std::shared_ptr<IndependentLivingObject>> monsters = world.getMonsters();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (!(*it)->isResistantToCollisionWithBlock() && isMonsterStandingOnBlock(**it, block)) {
			Direction direction = determineDirection(block, **it);
			handleMonsterDestroying(**it, world, player, direction);
			handleMonsterDeleting(world, it - monsters.begin());
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

int getAlignmentForCollisionFromRight(int dist, const WorldObject &obj, const Block &block, const World &world)
{
	int alignment = 0;

	if (block.getType() == BlockType::TubeLeftEntry) {
		if (!isCharacterStandingOnSomething(obj, world)) {
			alignment = (obj.getX() + dist + obj.getWidth() / 2) - (block.getX() - block.getWidth() / 2);
		}
	}
	else {
		alignment = (obj.getX() + dist + obj.getWidth() / 2) - (block.getX() - block.getWidth() / 2);
	}
	
	return (alignment > 0 ? alignment : 0);
}

int getHorizontalAlignmentForCollisionWithBlocks(Direction dir, int dist, const WorldObject &obj, const World &world)
{
	int alignment = 0;
	std::vector<Block> blocks = world.getBlocks();

	for (auto &block : blocks) {
		if (areAtTheSameHeight(obj, block) && isCharacterHittingObject(obj, block, dir, dist) && !block.isInvisible()) {
			if (dir == Direction::Right) {
				alignment = getAlignmentForCollisionFromRight(dist, obj, block, world);
			}
			else if (dir == Direction::Left) {
				alignment = (block.getX() + block.getWidth() / 2) - (obj.getX() - dist - obj.getWidth() / 2);
			}
			break;
		}
	}

	return (alignment > 0 ? alignment : 0);
}

int getHorizontalAlignmentForCollisionWithPlatforms(Direction dir, int dist, const WorldObject &obj, const World &world)
{
	int alignment = 0;
	std::vector<Platform> platforms = world.getPlatforms();

	for (auto &platform : platforms) {
		if (areAtTheSameHeight(obj, platform) && isCharacterHittingObject(obj, platform, dir, dist)) {
			if (dir == Direction::Right) {
				alignment = (obj.getX() + dist + obj.getWidth() / 2) - (platform.getX() - platform.getWidth() / 2);
			}
			else if (dir == Direction::Left) {
				alignment = (platform.getX() + platform.getWidth() / 2) - (obj.getX() - dist - obj.getWidth() / 2);
			}
			break;
		}
	}

	return (alignment > 0 ? alignment : 0);
}

int computeHorizontalAlignment(Direction dir, int dist, const WorldObject &obj, const World &world)
{
	int firstAlignment = getHorizontalAlignmentForCollisionWithBlocks(dir, dist, obj, world);
	int secondAlignment = getHorizontalAlignmentForCollisionWithPlatforms(dir, dist, obj, world);

	return (firstAlignment >= secondAlignment ? firstAlignment : secondAlignment);
}

// this method additionaly set the last touched block's index
int getVerticalAlignmentForCollisionWithBlocks(Direction dir, int dist, const WorldObject &obj, World &world)
{
	int alignment = 0;
	std::vector<Block> blocks = world.getBlocks();

	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (areAtTheSameWidth(obj, *it) && isCharacterHittingObject(obj, *it, dir, dist)) {
			if (dir == Direction::Up) {
				alignment = (it->getY() + it->getHeight() / 2) - (obj.getY() - dist - obj.getHeight() / 2);

				if (alignment > 0) {
					world.setLastTouchedBlock(it - blocks.begin());	// 
				}
			}
			else if ( dir == Direction::Down && !it->isInvisible()) {
				alignment = (obj.getY() + dist + obj.getHeight() / 2) - (it->getY() - it->getHeight() / 2);
			}
			break;
		}
	}

	return (alignment > 0 ? alignment : 0);
}

// this method additionaly set the last touched block's index to -1
int getVerticalAlignmentForCollisionWithPlatforms(Direction dir, int dist, const WorldObject &obj, World &world)
{
	int alignment = 0;
	std::vector<Platform> platforms = world.getPlatforms();

	for (auto it = platforms.begin(); it != platforms.end(); ++it) {
		if (areAtTheSameWidth(obj, *it) && isCharacterHittingObject(obj, *it, dir, dist)) {
			if (dir == Direction::Up) {
				alignment = (it->getY() + it->getHeight() / 2) - (obj.getY() - dist - obj.getHeight() / 2);

				if (alignment > 0) {
					world.setLastTouchedBlock(-1);	// 
				}
			}
			else if (dir == Direction::Down) {
				alignment = (obj.getY() + dist + obj.getHeight() / 2) - (it->getY() - it->getHeight() / 2);
			}
			break;
		}
	}

	return (alignment > 0 ? alignment : 0);
}

int computeVerticalAlignment(Direction dir, int dist, const WorldObject &obj, World &world)
{
	int firstAlignment = getVerticalAlignmentForCollisionWithBlocks(dir, dist, obj, world);
	int secondAlignment = getVerticalAlignmentForCollisionWithPlatforms(dir, dist, obj, world);

	return (firstAlignment >= secondAlignment ? firstAlignment : secondAlignment);
}