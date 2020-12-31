#include "IndependentLivingObject.h"

#include "CollisionHandling.h"
#include "Movement.h"
#include "Position.h"


void IndependentLivingObject::moveHorizontally(World &world)
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

void IndependentLivingObject::moveDiagonally(World &world)
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

int IndependentLivingObject::getPointsForCrushing() const
{
	return 0;
}

bool IndependentLivingObject::isCrushproof() const
{
	return false;
}

void IndependentLivingObject::crush(World &world, int index) {}

void IndependentLivingObject::destroy(World &world) {}