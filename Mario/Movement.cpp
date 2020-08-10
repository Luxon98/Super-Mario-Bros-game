#include "Movement.h"

Movement::Movement(int speed, Direction direction) : speed(speed), direction(direction) {}

int Movement::getSpeed() const
{
	return speed;
}

Direction Movement::getDirection() const
{
	return direction;
}

void Movement::setSpeed(int speed)
{
	if (speed > 0 && speed < 3) {
		this->speed = speed;
	}
}

void Movement::setDirection(Direction direction)
{
	if (direction == Left || direction == Right || direction == None) {
		this->direction = direction;
	}
}
