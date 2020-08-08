#include "CollisionHandling.h"

bool isCharacterHittingBlock(WorldObject* object, Block block, Direction direction, int distance)
{
	if (direction == Right && object->getX() < block.getX() && object->getX() + distance + object->getWidth() / 2
		>= block.getX() - block.getWidth() / 2) {
		return true;
	}
	else if (direction == Left && object->getX() > block.getX() && object->getX() - distance - object->getWidth() / 2
		<= block.getX() + block.getWidth() / 2) {
		return true;
	}
	else if (direction == Up && object->getY() > block.getY() && object->getY() - distance - object->getHeight() / 2
		<= block.getY() + block.getHeight() / 2) {
		return true;
	}
	else if (direction == Down && object->getY() < block.getY() && object->getY() + distance + object->getHeight() / 2
		>= block.getY() - block.getHeight() / 2) {
		return true;
	}
	else {
		return false;
	}
}

bool isCharacterStandingOnTheBlock(WorldObject* object, World& world)
{
	std::vector<Block> blocks = world.getBlocks();
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (object->getY() + object->getHeight() / 2 == it->getY() - it->getHeight() / 2 && areAtTheSameWidth(object, *it)) {
			return true;
		}
	}

	return false;
}

bool isMonsterStandingOnTheBlock(NonControllableLivingObject* object, Block block)
{
	if (abs((object->getY() + object->getHeight() / 2) - (block.getY() - block.getHeight() / 2))
		< (block.getHeight() / 2) && areAtTheSameWidth(object, block)) {
		return true;
	}

	return false;
}

bool isFlowerStandingOnTheBlock(World& world, int index)
{
	std::vector<InanimateObject*> elements = world.getInanimateElements();
	std::vector<Block> blocks = world.getBlocks();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (dynamic_cast<Flower*>(*it)) {
			if (((*it)->getY() + (*it)->getHeight() / 2) + 9 == blocks[index].getY() - blocks[index].getHeight() / 2
				&& areAtTheSameWidth(*it, blocks[index])) {
				return true;
			}
		}
	}
	return false;
}

bool areAtTheSameWidth(WorldObject* object, Block block)
{
	if (object->getX() + object->getWidth() / 2 > block.getX() - block.getWidth() / 2 && object->getX() <= block.getX()) {
		return true;
	}
	else if (object->getX() - object->getWidth() / 2 < block.getX() + block.getWidth() / 2 && object->getX() >= block.getX()) {
		return true;
	}

	return false;
}

bool areAtTheSameHeight(WorldObject* object, Block block)
{
	if (object->getY() >= block.getY() && object->getY() - object->getHeight() / 2 < block.getY() + block.getHeight() / 2) {
		return true;
	}
	else if (object->getY() <= block.getY() && object->getY() + object->getHeight() / 2 > block.getY() - block.getHeight() / 2) {
		return true;
	}

	return false;
}

bool areAtTheSameWidth(WorldObject* firstObject, WorldObject* secondObject)
{
	if (firstObject->getX() + firstObject->getWidth() / 2 > secondObject->getX() - secondObject->getWidth() / 2
		&& firstObject->getX() <= secondObject->getX()) {
		return true;
	}
	else if (firstObject->getX() - firstObject->getWidth() / 2 < secondObject->getX() + secondObject->getWidth() / 2
		&& firstObject->getX() >= secondObject->getX()) {
		return true;
	}

	return false;
}

bool areAtTheSameHeight(WorldObject* firstObject, WorldObject* secondObject)
{
	if (firstObject->getY() >= secondObject->getY() && firstObject->getY() - firstObject->getHeight() / 2
		< secondObject->getY() + secondObject->getHeight() / 2) {
		return true;
	}
	else if (firstObject->getY() <= secondObject->getY() && firstObject->getY() + firstObject->getHeight() / 2
		> secondObject->getY() - secondObject->getHeight() / 2) {
		return true;
	}

	return false;
}

bool isPlayerJumpingOnMonster(Player* player, NonControllableLivingObject* monster)
{
	return (monster->getY() - player->getY() > 25);
}

void handleIfCollisionWithMonsterOccurs(Player* player, World& world)
{
	std::vector<NonControllableLivingObject*> monsters = world.getMonsters();
	int index = 0;
	for (auto it = monsters.begin(); it != monsters.end(); ++it, ++index) {
		if (areAtTheSameWidth(player, *it) && areAtTheSameHeight(player, *it)) {
			if (isPlayerJumpingOnMonster(player, *it)) {
				player->setRejumpFlag();

				if (dynamic_cast<Shell*>(*it)) {
					if (dynamic_cast<Shell*>(*it)->isActive()) {
						world.changeShellMovementParameters(index, None);
					}
					else {
						world.changeShellMovementParameters(index, player->getX() >= dynamic_cast<Shell*>(*it)->getX() ? Left : Right);
					}
					break;
				}

				if (dynamic_cast<Turtle*>(*it)) {
					world.addShell(new Position((*it)->getX(), (*it)->getY() + 6));
				}
				else if (dynamic_cast<Creature*>(*it)) {
					world.addCrushedCreature(new Position(dynamic_cast<Creature*>(*it)->getX(),
						dynamic_cast<Creature*>(*it)->getY() + 8));
				}
				player->addPoints(100);
				world.addAnimatedText(ONE_HUNDRED, new Position(player->getX() - 22, player->getY() - 22));
				world.deleteMonster(index);
				SoundController::playEnemyDestroyedEffect();
			}
			else {
				if (dynamic_cast<Shell*>(*it) && !(dynamic_cast<Shell*>(*it)->isActive())) {
					world.changeShellMovementParameters(index, player->getX() >= dynamic_cast<Shell*>(*it)->getX() ? Left : Right);
					break;
				}

				if (player->isImmortal()) {
					if (dynamic_cast<Turtle*>(*it) || (dynamic_cast<Shell*>(*it) && dynamic_cast<Shell*>(*it)->isActive())) {
						world.addDestroyedTurtle(new Position((*it)->getX(), (*it)->getY()));
					}
					else if (dynamic_cast<Creature*>(*it)) {
						world.addDestroyedCreature(new Position((*it)->getX(), (*it)->getY()));
					}
					player->addPoints(100);
					world.addAnimatedText(ONE_HUNDRED, new Position(player->getX() - 22, player->getY() - 22));
					world.deleteMonster(index);
					SoundController::playEnemyDestroyedEffect();
				}
				else {
					player->loseBonusOrLife();
				}
			}
			break;
		}
	}
}

void handleIfShellCollideWithMonsters(World& world, Player* player)
{
	std::vector<NonControllableLivingObject*> monsters = world.getMonsters();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (dynamic_cast<Shell*>(*it) && dynamic_cast<Shell*>(*it)->isActive()) {
			int index = 0;
			for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2, ++index) {
				if (!(dynamic_cast<Shell*>(*it2)) && (areAtTheSameWidth(*it, *it2) && areAtTheSameHeight(*it, *it2))) {
					if (dynamic_cast<Creature*>(*it2)) {
						world.addDestroyedCreature(new Position((*it2)->getX(), (*it2)->getY()));
					}
					else if (dynamic_cast<Turtle*>(*it2) || dynamic_cast<Shell*>(*it2)) {
						world.addDestroyedTurtle(new Position((*it2)->getX(), (*it2)->getY()));
					}
					world.deleteMonster(index);
					SoundController::playEnemyDestroyedEffect();
					player->addPoints(200);
					world.addAnimatedText(TWO_HUNDRED, new Position((*it)->getX() - 20, (*it)->getY() - 15));
				}
			}
		}
	}
}

void handleIfFireBallCollideWithMonsters(World& world, Player* player)
{
	std::vector<FireBall> fireballs = world.getFireBalls();
	std::vector<NonControllableLivingObject*> monsters = world.getMonsters();
	int i = 0, j = 0;
	for (auto it = fireballs.begin(); it != fireballs.end(); ++it, ++i) {
		for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2, ++j) {
			if (areAtTheSameWidth(&*it, *it2) && areAtTheSameHeight(&*it, *it2)) {
				int alignment = (fireballs[i].getMoveDirection() == Left ? -5 : 5);

				if (dynamic_cast<Creature*>(*it2)) {
					world.addDestroyedCreature(new Position((*it2)->getX() + alignment, (*it2)->getY()));
				}
				else if (dynamic_cast<Turtle*>(*it2) || dynamic_cast<Shell*>(*it2)) {
					world.addDestroyedTurtle(new Position((*it2)->getX() + alignment, (*it2)->getY()));
				}

				world.deleteMonster(j);
				SoundController::playEnemyDestroyedEffect();

				player->addPoints(100);
				world.addAnimatedText(ONE_HUNDRED, new Position(fireballs[i].getX() - 22, fireballs[i].getY() - 22));
				world.addExplosion(new Position(it->getX(), it->getY()));
				world.deleteFireBall(i);
			}
		}
	}
}

void handleIfMonsterCollideWithDestroyedBlock(World& world, Block block, Player* player)
{
	std::vector<NonControllableLivingObject*> monsters = world.getMonsters();
	int index = 0;
	for (auto it = monsters.begin(); it != monsters.end(); ++it, ++index) {
		if (isMonsterStandingOnTheBlock(*it, block)) {
			if (dynamic_cast<Creature*>(*it)) {
				world.addDestroyedCreature(new Position((*it)->getX(), (*it)->getY()));
			}
			else if (dynamic_cast<Turtle*>(*it)) {
				world.addDestroyedTurtle(new Position((*it)->getX(), (*it)->getY()));
			}

			player->addPoints(100);
			world.addAnimatedText(ONE_HUNDRED, new Position((*it)->getX(), (*it)->getY() - 15));
			world.deleteMonster(index);
			SoundController::playEnemyDestroyedEffect();
		}
	}
}

void collectCoinIfPossible(Player* player, World& world)
{
	std::vector<InanimateObject*> elements = world.getInanimateElements();
	int index = 0;
	for (auto it = elements.begin(); it != elements.end(); ++it, ++index) {
		if (areAtTheSameWidth(player, *it) && areAtTheSameHeight(player, *it)) {
			if (dynamic_cast<Coin*>(*it)) {
				player->incrementCoins();
				world.deleteInanimateElement(index);
			}
		}
	}
}

void collectBonusIfPossible(Player* player, World& world)
{
	std::vector<BonusObject*> elements = world.getBonusElements();
	int index = 0;
	for (auto it = elements.begin(); it != elements.end(); ++it, ++index) {
		if (areAtTheSameWidth(player, *it) && areAtTheSameHeight(player, *it)) {
			if (dynamic_cast<Mushroom*>(*it)) {
				if (!(dynamic_cast<Mushroom*>(*it)->isGreen())) {
					player->setCurrentAnimation(DuringGrowingAnimation);
					SoundController::playBonusCollectedEffect();
				}
				else {
					player->incrementLives();
					world.addAnimatedText(ONE_UP, new Position(player->getX(), player->getY() - 20));
					world.deleteLivingElement(index);
					SoundController::play1upCollectedEffect();
					break;
				}
			}
			else if (dynamic_cast<Flower*>(*it)) {
				if (player->getCurrentState() == Tall) {
					player->setCurrentAnimation(DuringArmingAnimation);
				}
				else if (player->getCurrentState() == Small) {
					player->setCurrentAnimation(DuringGrowingAnimation);
				}
				SoundController::playBonusCollectedEffect();
			}
			else if (dynamic_cast<Star*>(*it)) {
				if (player->getCurrentState() == Small) {
					player->setCurrentAnimation(DuringGrowingAnimation);
				}
				else {
					player->setCurrentAnimation(DuringImmortalAnimation);
					SoundController::stopMusic();
					SoundController::playBackgroudStarMusic();
				}
			}
			world.deleteLivingElement(index);
			player->addPoints(1000);
			world.addAnimatedText(ONE_THOUSAND, new Position(player->getX(), player->getY() - 20));
		}
	}
}

int getAlignmentIfCollisionOccursDuringMovement(Direction direction, int distance, WorldObject* object, World& world)
{
	std::vector<Block> blocks = world.getBlocks();
	int alignment = 0;
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (areAtTheSameHeight(object, *it) && isCharacterHittingBlock(object, *it, direction, distance)) {
			if ((object->getX() + distance + object->getWidth() / 2) - (it->getX() - it->getWidth() / 2) > alignment
				&& direction == Right) {
				alignment = (object->getX() + distance + object->getWidth() / 2) - (it->getX() - it->getWidth() / 2);
			}
			else if ((it->getX() + it->getWidth() / 2) - (object->getX() - distance - object->getWidth() / 2) > alignment
				&& direction == Left) {
				alignment = (it->getX() + it->getWidth() / 2) - (object->getX() - distance - object->getWidth() / 2);
			}
		}
	}

	return alignment;
}

int getAlignmentIfCollisionOccursDuringVerticalMovement(Direction direction, int distance, WorldObject* object, World& world)
{
	std::vector<Block> blocks = world.getBlocks();
	int alignment = 0;
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (areAtTheSameWidth(object, *it) && isCharacterHittingBlock(object, *it, direction, distance)) {
			if ((it->getY() + it->getHeight() / 2) - (object->getY() - distance - object->getHeight() / 2) > alignment
				&& direction == Up) {
				world.setLastTouchedBlock(it - blocks.begin());
				alignment = (it->getY() + it->getHeight() / 2) - (object->getY() - distance - object->getHeight() / 2);
			}
			else if ((object->getY() + distance + object->getHeight() / 2) - (it->getY() - it->getHeight() / 2) > alignment
				&& direction == Down && it->getModel() != BonusWithGreenMushroom) {
				alignment = (object->getY() + distance + object->getHeight() / 2) - (it->getY() - it->getHeight() / 2);
			}
		}
	}

	return alignment;
}
