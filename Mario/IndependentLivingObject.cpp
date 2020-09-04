#include "IndependentLivingObject.h"

#include "CollisionHandling.h"
#include "Movement.h"
#include "Position.h"


void IndependentLivingObject::makeHorizontalMove(World &world)
{
	int alignment = getAlignmentForHorizontalMove(movement.getDirection(), movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;
	if (movement.getDirection() == Direction::Left) {
		distance *= -1;
	}
	position.setX(position.getX() + distance);

	if (alignment > 0) {
		movement.setDirection(movement.getDirection() == Direction::Right ? Direction::Left : Direction::Right);
	}
}

void IndependentLivingObject::makeDiagonalMove(World &world)
{
	int alignment = getAlignmentForVerticalMove(Direction::Down, movement.getVerticalSpeed(), *this, world);
	int verticalDistance = movement.getVerticalSpeed() - alignment;
	position.setY(position.getY() + verticalDistance);

	alignment = getAlignmentForHorizontalMove(movement.getDirection(), movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;
	if (movement.getDirection() == Direction::Left) {
		distance *= -1;
	}
	position.setX(position.getX() + distance);
}
