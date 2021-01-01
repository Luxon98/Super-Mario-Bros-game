#include "IndependentLivingObject.h"

#include "CollisionHandling.h"
#include "Movement.h"
#include "Position.h"
#include "World.h"


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

int IndependentLivingObject::getPointsForDestroying() const
{
	return 200;
}

bool IndependentLivingObject::isCrushproof() const
{
	return false;
}

bool IndependentLivingObject::isResistantToImmortalPlayer() const
{
	return false;
}

bool IndependentLivingObject::isMonsterResistantToCollisionWithShell() const
{
	return true;
}

bool IndependentLivingObject::isActiveShell() const
{
	return false;
}

void IndependentLivingObject::crush(World &world, int index) {}

void IndependentLivingObject::destroy(World &world, Direction direction) {}