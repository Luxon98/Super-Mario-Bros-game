#include "CollisionHandling.h"

#include <vector>
#include <cmath>
#include <memory>
#include "Player.h"
#include "SoundController.h"
#include "Block.h"
#include "World.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Star.h"
#include "Shell.h"
#include "Turtle.h"
#include "Creature.h"
#include "Plant.h"
#include "FireBall.h"
#include "Position.h"
#include "AnimatedText.h"
#include "Screen.h"


bool isCharacterHittingBlock(const WorldObject &object, const Block &block, Direction direction, int distance)
{
	if (direction == Direction::Right && object.getX() < block.getX()
		&& object.getX() + distance + object.getWidth() / 2 >= block.getX() - block.getWidth() / 2) {

		return true;
	}
	else if (direction == Direction::Left && object.getX() > block.getX()
		&& object.getX() - distance - object.getWidth() / 2 <= block.getX() + block.getWidth() / 2) {

		return true;
	}
	else if (direction == Direction::Up && object.getY() > block.getY()
		&& object.getY() - distance - object.getHeight() / 2 <= block.getY() + block.getHeight() / 2) {

		return true;
	}
	else if (direction == Direction::Down && object.getY() < block.getY()
		&& object.getY() + distance + object.getHeight() / 2 >= block.getY() - block.getHeight() / 2) {

		return true;
	}

	return false;
}

bool isCharacterStandingOnTheBlock(const WorldObject &object, const World &world)
{
	std::vector<Block> blocks = world.getBlocks();
	for (auto &block : blocks) {
		if (object.getY() + object.getHeight() / 2 == block.getY() - block.getHeight() / 2
			&& areAtTheSameWidth(object, block) && !block.isInvisible()) {

			return true;
		}
	}

	return false;
}

bool isMonsterStandingOnTheBlock(const LivingObject& object, const Block& block)
{
	if (abs((object.getY() + object.getHeight() / 2) - (block.getY() - block.getHeight() / 2)) < 2
		&& areAtTheSameWidth(object, block)) {

		return true;
	}

	return false;
}

bool isMushroomStandingOnTheBlock(const World &world, int index)
{
	std::vector<std::shared_ptr<BonusObject>> bonusElements = world.getBonusElements();
	std::vector<Block> blocks = world.getBlocks();
	for (auto bonusElement : bonusElements) {
		if (std::dynamic_pointer_cast<Mushroom>(bonusElement)) {
			if ((bonusElement->getY() + bonusElement->getHeight() / 2) == (blocks[index].getY()
				- blocks[index].getHeight() / 2) && areAtTheSameWidth(*bonusElement, blocks[index])) {

				return true;
			}
		}
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
	else {
		return false;
	}
}

bool areAtTheSameWidth(const WorldObject &firstObject, const WorldObject &secondObject)
{
	if (firstObject.getX() + firstObject.getWidth() / 2 > secondObject.getX() - secondObject.getWidth() / 2
		&& firstObject.getX() <= secondObject.getX()) {

		return true;
	}
	else if (firstObject.getX() - firstObject.getWidth() / 2 < secondObject.getX() + secondObject.getWidth() / 2
		&& firstObject.getX() >= secondObject.getX()) {

		return true;
	}

	return false;
}

bool areAtTheSameHeight(const WorldObject &firstObject, const WorldObject &secondObject)
{
	if (firstObject.getY() >= secondObject.getY() && firstObject.getY() - firstObject.getHeight() / 2
		< secondObject.getY() + secondObject.getHeight() / 2) {

		return true;
	}
	else if (firstObject.getY() <= secondObject.getY() && firstObject.getY() + firstObject.getHeight() / 2
		> secondObject.getY() - secondObject.getHeight() / 2) {

		return true;
	}

	return false;
}

bool isPlayerJumpingOnMonster(const Player &player, const LivingObject &monster)
{
	return (monster.getY() - player.getY() > 25);
}

void handlePlayerCollisions(Player &player, World &world)
{
	std::vector<std::shared_ptr<LivingObject>> monsters = world.getMonsters();
	int i = 0;
	for (auto it = monsters.begin(); it != monsters.end(); ++it, ++i) {
		if (areAtTheSameWidth(player, **it) && areAtTheSameHeight(player, **it)) {
			if (isPlayerJumpingOnMonster(player, **it) && !std::dynamic_pointer_cast<Plant>(*it)) {
				player.performAdditionalJump();

				if (std::dynamic_pointer_cast<Shell>(*it)) {
					if (std::dynamic_pointer_cast<Shell>(*it)->isActive()) {
						world.changeShellMovementParameters(i, Direction::None);
					}
					else {
						Direction direction = (player.getX() >= std::dynamic_pointer_cast<Shell>(*it)->getX()
							? Direction::Left : Direction::Right);

						world.changeShellMovementParameters(i, direction);
					}
					break;
				}

				if (std::dynamic_pointer_cast<Turtle>(*it)) {
					world.addShell(Position((*it)->getX(), (*it)->getY() + 6));
				}
				else if (std::dynamic_pointer_cast<Creature>(*it)) {
					world.addCrushedCreature(Position(std::dynamic_pointer_cast<Creature>(*it)->getX(),
						std::dynamic_pointer_cast<Creature>(*it)->getY() + 8));
				}
				player.addPoints(100);
				world.addAnimatedText(TextType::ONE_HUNDRED, Position(player.getX() - 22, player.getY() - 22));
				world.deleteMonster(i);
				SoundController::playEnemyDestroyedEffect();
			}
			else {
				if (std::dynamic_pointer_cast<Shell>(*it) && !(std::dynamic_pointer_cast<Shell>(*it)->isActive())) {
					Direction direction = (player.getX() >= std::dynamic_pointer_cast<Shell>(*it)->getX()
						? Direction::Left : Direction::Right);

					world.changeShellMovementParameters(i, direction);
					break;
				}

				if (player.isImmortal()) {
					if (std::dynamic_pointer_cast<Turtle>(*it) || (std::dynamic_pointer_cast<Shell>(*it)
						&& std::dynamic_pointer_cast<Shell>(*it)->isActive())) {

						world.addDestroyedTurtle(Position((*it)->getX(), (*it)->getY()));
					}
					else if (std::dynamic_pointer_cast<Creature>(*it)) {
						world.addDestroyedCreature(Position((*it)->getX(), (*it)->getY()));
					}
					player.addPoints(100);
					world.addAnimatedText(TextType::ONE_HUNDRED, Position(player.getX() - 22, player.getY() - 22));
					world.deleteMonster(i);
					SoundController::playEnemyDestroyedEffect();
				}
				else if (!player.isInsensitive()) {
					player.loseBonusOrLife();
				}
			}
			break;
		}
	}
}

void handleShellsAndMonstersCollisions(World &world, Player &player)
{
	std::vector<std::shared_ptr<LivingObject>> monsters = world.getMonsters();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (std::dynamic_pointer_cast<Shell>(*it) && std::dynamic_pointer_cast<Shell>(*it)->isActive()) {
			int i = 0;
			for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2, ++i) {
				if (!(std::dynamic_pointer_cast<Shell>(*it2)) && (areAtTheSameWidth(**it, **it2)
					&& areAtTheSameHeight(**it, **it2)) && ((*it2)->getX()) < world.getScreen()->getEndOfCamera()) {

					if (std::dynamic_pointer_cast<Creature>(*it2)) {
						world.addDestroyedCreature(Position((*it2)->getX(), (*it2)->getY()));
					}
					else if (std::dynamic_pointer_cast<Turtle>(*it2) || std::dynamic_pointer_cast<Shell>(*it2)) {
						world.addDestroyedTurtle(Position((*it2)->getX(), (*it2)->getY()));
					}

					world.deleteMonster(i);
					SoundController::playEnemyDestroyedEffect();
					player.addPoints(200);
					world.addAnimatedText(TextType::TWO_HUNDRED, Position((*it)->getX() - 20, (*it)->getY() - 15));
				}
			}
		}
	}
}

void handleFireBallsAndMonstersCollisions(World &world, Player &player)
{
	std::vector<FireBall> fireballs = world.getFireBalls();
	std::vector<std::shared_ptr<LivingObject>> monsters = world.getMonsters();
	int i = 0;
	for (auto it = fireballs.begin(); it != fireballs.end(); ++it, ++i) {
		int j = 0;
		for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2, ++j) {
			if (areAtTheSameWidth(*it, **it2) && areAtTheSameHeight(*it, **it2)) {
				int alignment = (fireballs[i].getMovement().getDirection() == Direction::Left ? -5 : 5);

				if (std::dynamic_pointer_cast<Creature>(*it2)) {
					world.addDestroyedCreature(Position((*it2)->getX() + alignment, (*it2)->getY()));
				}
				else if (std::dynamic_pointer_cast<Turtle>(*it2) || std::dynamic_pointer_cast<Shell>(*it2)) {
					world.addDestroyedTurtle(Position((*it2)->getX() + alignment, (*it2)->getY()));
				}

				world.deleteMonster(j);
				SoundController::playEnemyDestroyedEffect();

				player.addPoints(100);
				world.addAnimatedText(TextType::ONE_HUNDRED, Position(fireballs[i].getX() - 22,
					fireballs[i].getY() - 22));

				world.addExplosion(Position(it->getX(), it->getY()));
				world.deleteFireBall(i);
			}
		}
	}
}

void handleMonstersAndBlockCollisions(World &world, const Block &block, Player &player)
{
	std::vector<std::shared_ptr<LivingObject>> monsters = world.getMonsters();
	int i = 0;
	for (auto it = monsters.begin(); it != monsters.end(); ++it, ++i) {
		if (isMonsterStandingOnTheBlock(**it, block)) {
			if (std::dynamic_pointer_cast<Creature>(*it)) {
				world.addDestroyedCreature(Position((*it)->getX(), (*it)->getY()));
			}
			else if (std::dynamic_pointer_cast<Turtle>(*it)) {
				world.addDestroyedTurtle(Position((*it)->getX(), (*it)->getY()));
			}

			player.addPoints(100);
			world.addAnimatedText(TextType::ONE_HUNDRED, Position((*it)->getX(), (*it)->getY() - 15));
			world.deleteMonster(i);
			SoundController::playEnemyDestroyedEffect();
		}
	}
}

void collectCoinIfPossible(Player &player, World &world)
{
	std::vector<std::shared_ptr<InanimateObject>> elements = world.getInanimateElements();
	int i = 0;
	for (auto it = elements.begin(); it != elements.end(); ++it, ++i) {
		if (areAtTheSameWidth(player, **it) && areAtTheSameHeight(player, **it)) {
			if (std::dynamic_pointer_cast<Coin>(*it)) {
				player.incrementCoins();
				world.deleteInanimateElement(i);
				SoundController::playCoinCollectedEffect();
			}
		}
	}
}

void collectMushroom(Mushroom &mushroom, int index, Player &player, World &world)
{
	if (!mushroom.isGreen()) {
		if (player.isSmall()) {
			player.setCurrentAnimation(PlayerAnimation::Growing);
		}
		SoundController::playBonusCollectedEffect();
	}
	else {
		player.incrementLives();
		SoundController::playNewLiveAddedEffect();
	}

	TextType type = (!mushroom.isGreen() ? TextType::ONE_THOUSAND : TextType::ONE_UP);
	world.addAnimatedText(type, Position(player.getX(), player.getY() - 20));
	world.deleteLivingElement(index);
	player.addPoints(1000);
}

void collectFlower(Player &player, World &world)
{
	if (player.isSmall()) {
		player.setCurrentAnimation(PlayerAnimation::Growing);
	}
	else if (!player.isImmortal() && !player.isArmed()) {
		player.setCurrentAnimation(PlayerAnimation::Arming);
	}

	SoundController::playBonusCollectedEffect();
}

void collectStar(Player &player, World &world)
{
	if (player.isSmall()) {
		player.setCurrentAnimation(PlayerAnimation::ImmortalSmall);
	}
	else {
		player.setCurrentAnimation(PlayerAnimation::Immortal);
	}
	player.increaseSpeed();

	SoundController::playStarMusic();
}

void collectBonusIfPossible(Player &player, World &world)
{
	std::vector<std::shared_ptr<BonusObject>> elements = world.getBonusElements();
	int i = 0;
	for (auto it = elements.begin(); it != elements.end(); ++it, ++i) {
		if (areAtTheSameWidth(player, **it) && areAtTheSameHeight(player, **it) && (*it)->isActive()) {
			if (std::dynamic_pointer_cast<Mushroom>(*it)) {
				collectMushroom(dynamic_cast<Mushroom&>(**it), i, player, world);
				break;
			}
			else if (std::dynamic_pointer_cast<Flower>(*it)) {
				collectFlower(player, world);
			}
			else if (std::dynamic_pointer_cast<Star>(*it)) {
				collectStar(player, world);
			}

			world.deleteLivingElement(i);
			player.addPoints(1000);
			world.addAnimatedText(TextType::ONE_THOUSAND, Position(player.getX(), player.getY() - 20));
		}
	}
}

int getAlignmentForHorizontalMove(Direction direction, int distance, const WorldObject &object, const World &world)
{
	std::vector<Block> blocks = world.getBlocks();
	int alignment = 0;
	for (auto& block : blocks) {
		if (areAtTheSameHeight(object, block) && isCharacterHittingBlock(object, block, direction, distance)
			&& !block.isInvisible()) {

			if ((object.getX() + distance + object.getWidth() / 2) - (block.getX() - block.getWidth() / 2) > alignment
				&& direction == Direction::Right) {

				alignment = (object.getX() + distance + object.getWidth() / 2) - (block.getX() - block.getWidth() / 2);
			}
			else if ((block.getX() + block.getWidth() / 2) - (object.getX() - distance - object.getWidth() / 2)
	> alignment&& direction == Direction::Left) {

				alignment = (block.getX() + block.getWidth() / 2) - (object.getX() - distance - object.getWidth() / 2);
			}
		}
	}

	return alignment;
}

// this method additionaly set the last touched block
int getAlignmentForVerticalMove(Direction direction, int distance, const WorldObject &object, World &world)
{
	std::vector<Block> blocks = world.getBlocks();
	int alignment = 0;
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (areAtTheSameWidth(object, *it) && isCharacterHittingBlock(object, *it, direction, distance)) {
			if ((it->getY() + it->getHeight() / 2) - (object.getY() - distance - object.getHeight() / 2)
				> alignment&& direction == Direction::Up) {

				world.setLastTouchedBlock(it - blocks.begin());	// 
				alignment = (it->getY() + it->getHeight() / 2) - (object.getY() - distance - object.getHeight() / 2);
			}
			else if ((object.getY() + distance + object.getHeight() / 2) - (it->getY() - it->getHeight() / 2)
				> alignment&& direction == Direction::Down && !it->isInvisible()) {

				alignment = (object.getY() + distance + object.getHeight() / 2) - (it->getY() - it->getHeight() / 2);
			}
		}
	}

	return alignment;
}