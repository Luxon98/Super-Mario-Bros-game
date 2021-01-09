#include "IndependentMovingObject.h"

#include "CollisionHandling.h"


void IndependentMovingObject::moveHorizontally(World &world)
{
	int alignment = computeHorizontalAlignment(movement.getDirection(), movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;
	if (movement.getDirection() == Direction::Left) {
		distance *= -1;
	}
	position.setX(position.getX() + distance);

	if (alignment > 0) {
		movement.setDirection(movement.getDirection() == Direction::Right ? Direction::Left : Direction::Right);
	}
}

void IndependentMovingObject::moveDiagonally(World &world)
{
	int alignment = computeVerticalAlignment(Direction::Down, movement.getVerticalSpeed(), *this, world);
	int verticalDistance = movement.getVerticalSpeed() - alignment;
	position.setY(position.getY() + verticalDistance);

	alignment = computeHorizontalAlignment(movement.getDirection(), movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;
	if (movement.getDirection() == Direction::Left) {
		distance *= -1;
	}
	position.setX(position.getX() + distance);
}

int IndependentMovingObject::getHealthPoints() const
{
	return healthPoints;
}

int IndependentMovingObject::getPointsForCrushing() const
{
	return 0;
}

int IndependentMovingObject::getPointsForDestroying() const
{
	return 200;
}

bool IndependentMovingObject::shouldStartMoving(const Player &player) const
{
	return false;
}

bool IndependentMovingObject::isCrushproof() const
{
	return false;
}

bool IndependentMovingObject::isResistantToImmortalPlayer() const
{
	return false;
}

bool IndependentMovingObject::isResistantToCollisionWithShell() const
{
	return true;
}

bool IndependentMovingObject::isResistantToCollisionWithBlock() const
{
	return true;
}

bool IndependentMovingObject::isResistantToFireBalls() const
{
	return false;
}

bool IndependentMovingObject::isActiveShell() const
{
	return false;
}

bool IndependentMovingObject::isBoss() const
{
	return false;
}

void IndependentMovingObject::decrementHealthPoints()
{
	--healthPoints;
}

void IndependentMovingObject::startMoving() {}

void IndependentMovingObject::crush(World &world, int index) {}

void IndependentMovingObject::destroy(World &world, Direction direction) {}

void IndependentMovingObject::performSpecificActions(World &world, int index) {}