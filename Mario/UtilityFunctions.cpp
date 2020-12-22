#include "UtilityFunctions.h"

#include "WorldObject.h"
#include "LivingObject.h"
#include "Block.h"
#include "Plant.h"
#include "FireMissle.h"
#include "Shell.h"
#include "Boss.h"
#include "JumpingFish.h"
#include "CloudBombardier.h"
#include "Player.h"


bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions)
{
	for (int i = begin, j = 0; j < repetitions; i += shift, j++) {
		if (difference >= i && difference <= i + 150) {
			return true;
		}
	}

	return false;
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

bool isElementDirectlyAboveObject(const WorldObject &element, const WorldObject &object)
{
	if (element.getY() + element.getHeight() / 2 == object.getY() - object.getHeight() / 2) {
		return true;
	}

	return false;
}

bool isMonsterCloseAboveBlock(const LivingObject &monster, const Block &block)
{
	if (abs((monster.getY() + monster.getHeight() / 2) - (block.getY() - block.getHeight() / 2)) < 2) {
		return true;
	}

	return false;
}

bool isMonsterCrushproof(std::shared_ptr<LivingObject> monster)
{
	if (std::dynamic_pointer_cast<Plant>(monster) || std::dynamic_pointer_cast<FireMissle>(monster)
		|| std::dynamic_pointer_cast<Boss>(monster) || std::dynamic_pointer_cast<CloudBombardier>(monster)) {

		return true;
	}

	return false;
}

bool isMonsterResistantToKnocks(std::shared_ptr<LivingObject> monster)
{
	if (std::dynamic_pointer_cast<FireMissle>(monster) || std::dynamic_pointer_cast<Boss>(monster)) {
		return true;
	}

	return false;
}

bool isMonsterResistantToFireBalls(std::shared_ptr<LivingObject> monster)
{
	if (std::dynamic_pointer_cast<FireMissle>(monster)) {
		return true;
	}

	return false;
}

bool isMonsterResistantToCollisionWithShell(std::shared_ptr<LivingObject> monster)
{
	if (std::dynamic_pointer_cast<Shell>(monster) || std::dynamic_pointer_cast<FireMissle>(monster) 
		|| std::dynamic_pointer_cast<Boss>(monster) || std::dynamic_pointer_cast<JumpingFish>(monster)
		|| std::dynamic_pointer_cast<CloudBombardier>(monster)) {

		return true;
	}

	return false;
}

int determineShift(const LivingObject &object, int base)
{
	return (object.getMovement().getDirection() == Direction::Left ? base * (-1) : base);
}

int determineShift(Direction direction, int base)
{
	return (direction == Direction::Left ? base * (-1) : base);
}

Direction determineDirection(const WorldObject &firstObject, const WorldObject &secondObject)
{
	return (firstObject.getX() <= secondObject.getX() ? Direction::Right : Direction::Left);
}

Direction determineDirection(const Player &player)
{
	return (player.isTurnedRight() ? Direction::Right : Direction::Left);
}
