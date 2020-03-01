#include "CollisionHandling.h"

bool isCharacterHittingBlock(WorldObject* object, Block block, Direction direction, int distance) {
	if (direction == Right && object->getPositionX() < block.getPositionX()
		&& object->getPositionX() + distance + object->getWidth() / 2 >= block.getPositionX() - block.getWidth() / 2) {
		return true;
	}
	else if (direction == Left && object->getPositionX() > block.getPositionX()
		&& object->getPositionX() - distance - object->getWidth() / 2 <= block.getPositionX() + block.getWidth() / 2) {
		return true;
	}
	else if (direction == Up && object->getPositionY() > block.getPositionY()
		&& object->getPositionY() - distance - object->getHeight() / 2 <= block.getPositionY() + block.getHeight() / 2) {
		return true;
	}
	else if (direction == Down && object->getPositionY() < block.getPositionY()
		&& object->getPositionY() + distance + object->getHeight() / 2 >= block.getPositionY() - block.getHeight() / 2) {
		return true;
	}
	else {
		return false;
	}
}

bool isCharacterStandingOnTheBlock(WorldObject* object, World& world) {
	std::vector<Block> blocks = world.getBlocks();
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (object->getPositionY() + object->getHeight() / 2 == it->getPositionY() - it->getHeight() / 2
			&& areAtTheSameWidth(object, *it)) {
			return true;
		}
	}
	return false;
}

bool isFlowerStandingOnTheBlock(World& world, int index) {
	std::vector<InanimateObject*> elements = world.getInanimateElements();
	std::vector<Block> blocks = world.getBlocks();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (dynamic_cast<Flower*>(*it)) {
			if (((*it)->getPositionY() + (*it)->getHeight() / 2) + 9 == blocks[index].getPositionY()
				- blocks[index].getHeight() / 2 && areAtTheSameWidth(*it, blocks[index])) {

				return true;
			}
		}
	}
	return false;
}

bool areAtTheSameWidth(WorldObject* object, Block block) {
	if (object->getPositionX() + object->getWidth() / 2 > block.getPositionX() - block.getWidth() / 2
		&& object->getPositionX() <= block.getPositionX()) {
		return true;
	}
	else if (object->getPositionX() - object->getWidth() / 2 < block.getPositionX() + block.getWidth() / 2
		&& object->getPositionX() >= block.getPositionX()) {
		return true;
	}
	return false;
}

bool areAtTheSameHeight(WorldObject* object, Block block) {
	if (object->getPositionY() >= block.getPositionY()
		&& object->getPositionY() - object->getHeight() / 2 < block.getPositionY() + block.getHeight() / 2) {
		return true;
	}
	else if (object->getPositionY() <= block.getPositionY()
		&& object->getPositionY() + object->getHeight() / 2 > block.getPositionY() - block.getHeight() / 2) {
		return true;
	}
	return false;
}

bool areAtTheSameWidth(WorldObject* firstObject, WorldObject* secondObject) {
	if (firstObject->getPositionX() + firstObject->getWidth() / 2 > secondObject->getPositionX() - secondObject->getWidth() / 2
		&& firstObject->getPositionX() <= secondObject->getPositionX()) {
		return true;
	}
	else if (firstObject->getPositionX() - firstObject->getWidth() / 2 < secondObject->getPositionX() + secondObject->getWidth() / 2
		&& firstObject->getPositionX() >= secondObject->getPositionX()) {
		return true;
	}
	return false;
}

bool areAtTheSameHeight(WorldObject* firstObject, WorldObject* secondObject) {
	if (firstObject->getPositionY() >= secondObject->getPositionY()
		&& firstObject->getPositionY() - firstObject->getHeight() / 2 < secondObject->getPositionY() + secondObject->getHeight() / 2) {
		return true;
	}
	else if (firstObject->getPositionY() <= secondObject->getPositionY()
		&& firstObject->getPositionY() + firstObject->getHeight() / 2 > secondObject->getPositionY() - secondObject->getHeight() / 2) {
		return true;
	}
	return false;
}

bool isPlayerJumpingOnMonster(Player* player, NonControllableLivingObject* monster) {
	return (monster->getPositionY() - player->getPositionY() > 25);
}

void handleIfCollisionWithMonsterOccurs(Player* player, World& world) {
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
						world.changeShellMovementParameters(index, player->getPositionX()
							>= dynamic_cast<Shell*>(*it)->getPositionX() ? Left : Right);
					}
					break;
				}

				if (dynamic_cast<Turtle*>(*it)) {
					world.addShell((*it)->getPositionX(), (*it)->getPositionY() + 6);
				}
				else if (dynamic_cast<Creature*>(*it)) {
					world.addCrushedCreature(dynamic_cast<Creature*>(*it)->getPositionX(),
						dynamic_cast<Creature*>(*it)->getPositionY() + 8);
				}
				player->addPoints(100);
				world.addAnimatedText(ONE_HUNDRED, player->getPositionX() - 22, player->getPositionY() - 22);
				world.deleteMonster(index);
			}
			else {
				if (dynamic_cast<Shell*>(*it) && !(dynamic_cast<Shell*>(*it)->isActive())) {
					world.changeShellMovementParameters(index, player->getPositionX()
						>= dynamic_cast<Shell*>(*it)->getPositionX() ? Left : Right);

					break;
				}

				if (player->isImmortal()) {
					if (dynamic_cast<Turtle*>(*it) || (dynamic_cast<Shell*>(*it) && dynamic_cast<Shell*>(*it)->isActive())) {
						world.addDestroyedTurtle((*it)->getPositionX(), (*it)->getPositionY());
					}
					else if (dynamic_cast<Creature*>(*it)) {
						world.addDestroyedCreature((*it)->getPositionX(), (*it)->getPositionY());
					}
					player->addPoints(100);
					world.addAnimatedText(ONE_HUNDRED, player->getPositionX() - 22, player->getPositionY() - 22);
					world.deleteMonster(index);
				}
				else {
					player->loseBonusOrLife();
				}
			}
			break;
		}
	}
}

void handleIfShellCollideWithMonsters(World& world, Player* player) {
	std::vector<NonControllableLivingObject*> monsters = world.getMonsters();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (dynamic_cast<Shell*>(*it) && dynamic_cast<Shell*>(*it)->isActive()) {
			int index = 0;
			for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2, ++index) {
				if (!(dynamic_cast<Shell*>(*it2)) && (areAtTheSameWidth(*it, *it2) && areAtTheSameHeight(*it, *it2))) {
					if (dynamic_cast<Creature*>(*it2)) {
						world.addDestroyedCreature((*it2)->getPositionX(), (*it2)->getPositionY());
					}
					else if (dynamic_cast<Turtle*>(*it2) || dynamic_cast<Shell*>(*it2)) {
						world.addDestroyedTurtle((*it2)->getPositionX(), (*it2)->getPositionY());
					}
					world.deleteMonster(index);
					player->addPoints(200);
					world.addAnimatedText(TWO_HUNDRED, (*it)->getPositionX() - 20, (*it)->getPositionY() - 15);
				}
			}
		}
	}
}

void handleIfFireBallCollideWithMonsters(World& world, Player* player) {
	std::vector<FireBall> fireballs = world.getFireBalls();
	std::vector<NonControllableLivingObject*> monsters = world.getMonsters();
	int i = 0, j = 0;
	for (auto it = fireballs.begin(); it != fireballs.end(); ++it, ++i) {
		for (auto it2 = monsters.begin(); it2 != monsters.end(); ++it2, ++j) {
			if (areAtTheSameWidth(&*it, *it2) && areAtTheSameHeight(&*it, *it2)) {
				int alignment = (fireballs[i].getMoveDirection() == Left ? -5 : 5);
				if (dynamic_cast<Creature*>(*it2)) {
					world.addDestroyedCreature((*it2)->getPositionX() + alignment, (*it2)->getPositionY());
				}
				else if (dynamic_cast<Turtle*>(*it2) || dynamic_cast<Shell*>(*it2)) {
					world.addDestroyedTurtle((*it2)->getPositionX() + alignment, (*it2)->getPositionY());
				}

				world.deleteMonster(j);
				player->addPoints(100);
				world.addAnimatedText(ONE_HUNDRED, fireballs[i].getPositionX() - 22, fireballs[i].getPositionY() - 22);
				world.addExplosion(it->getPositionX(), it->getPositionY());
				world.deleteFireBall(i);
			}
		}
	}
}

void collectCoinIfPossible(Player* player, World& world) {
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

void collectBonusIfPossible(Player* player, World& world) {
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
					world.addAnimatedText(ONE_UP, player->getPositionX(), player->getPositionY() - 20);
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
			world.addAnimatedText(ONE_THOUSAND, player->getPositionX(), player->getPositionY() - 20);
		}
	}
}

int alignIfCollisionOccursDuringMovement(Direction direction, int distance, WorldObject* object, World& world) {
	std::vector<Block> blocks = world.getBlocks();
	int alignment = 0;
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (areAtTheSameHeight(object, *it) && isCharacterHittingBlock(object, *it, direction, distance)) {
			if ((object->getPositionX() + distance + object->getWidth() / 2) - (it->getPositionX() - it->getWidth() / 2) > alignment
				&& direction == Right) {
				alignment = (object->getPositionX() + distance + object->getWidth() / 2) - (it->getPositionX() - it->getWidth() / 2);
			}
			else if ((it->getPositionX() + it->getWidth() / 2) - (object->getPositionX() - distance - object->getWidth() / 2) > alignment
				&& direction == Left) {
				alignment = (it->getPositionX() + it->getWidth() / 2) - (object->getPositionX() - distance - object->getWidth() / 2);
			}
		}
	}
	return alignment;
}

int alignIfCollisionOccursDuringVerticalMovement(Direction direction, int distance, WorldObject* object, World& world) {
	std::vector<Block> blocks = world.getBlocks();
	int alignment = 0;
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (areAtTheSameWidth(object, *it) && isCharacterHittingBlock(object, *it, direction, distance)) {
			if ((it->getPositionY() + it->getHeight() / 2) - (object->getPositionY() - distance - object->getHeight() / 2) > alignment
				&& direction == Up) {
				world.setLastTouchedBlock(it - blocks.begin());
				alignment = (it->getPositionY() + it->getHeight() / 2) - (object->getPositionY() - distance - object->getHeight() / 2);
			}
			else if ((object->getPositionY() + distance + object->getHeight() / 2) - (it->getPositionY() - it->getHeight() / 2) > alignment
				&& direction == Down) {
				alignment = (object->getPositionY() + distance + object->getHeight() / 2) - (it->getPositionY() - it->getHeight() / 2);
			}
		}
	}
	return alignment;
}
