#ifndef _Movement_H
#define _Movement_H

#include "Direction.h"


class Movement
{
protected:
	int speed;
	int verticalSpeed;
	Direction direction;
	Direction verticalDirection;

public:
	Movement();
	Movement(int speed, int verticalSpeed, Direction direction, Direction verticalDirection = None);
	int getSpeed() const;
	int getVerticalSpeed() const;
	Direction getDirection() const;
	Direction getVerticalDirection() const;
	void setSpeed(int speed);
	void setVerticalSpeed(int verticalSpeed);
	void setDirection(Direction direction);
	void setVerticalDirection(Direction verticalDirection);
};

#endif //_Movement_H
