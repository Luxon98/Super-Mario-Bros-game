#include "UtilityFunctions.h"

#include "WorldObject.h"
#include "LivingObject.h"
#include "Block.h"


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

bool isMonsterCloseAboveBlock(const LivingObject& monster, const Block& block)
{
	if (abs((monster.getY() + monster.getHeight() / 2) - (block.getY() - block.getHeight() / 2)) < 2) {
		return true;
	}

	return false;
}

Direction determineDirection(const WorldObject &firstObject, const WorldObject &secondObject)
{
	return (firstObject.getX() <= secondObject.getX() ? Direction::Right : Direction::Left);
}
