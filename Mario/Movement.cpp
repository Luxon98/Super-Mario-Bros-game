#include "Movement.h"


Movement::Movement()
{
	speed = 0;
	verticalSpeed = 0;
	direction = None;
	verticalDirection = None;
}

Movement::Movement(int speed, int verticalSpeed, Direction direction, Direction verticalDirection) : speed(speed), verticalSpeed(verticalSpeed), direction(direction), verticalDirection(verticalDirection) {}

int Movement::getSpeed() const
{
	return speed;
}

int Movement::getVerticalSpeed() const
{
	return verticalSpeed;
}

Direction Movement::getDirection() const
{
	return direction;
}

Direction Movement::getVerticalDirection() const
{
	return verticalDirection;
}

void Movement::setSpeed(int speed)
{
	if (speed > 0 && speed < 3) {
		this->speed = speed;
	}
}

void Movement::setVerticalSpeed(int verticalSpeed)
{
	if (speed > 0 && speed < 5) {
		this->verticalSpeed = verticalSpeed;
	}
}

void Movement::setDirection(Direction direction)
{
	if (direction == Left || direction == Right || direction == None) {
		this->direction = direction;
	}
}

void Movement::setVerticalDirection(Direction verticalDirection)
{
	if (verticalDirection == Up || verticalDirection == Down || verticalDirection == None) {
		this->verticalDirection = verticalDirection;
	}
}
