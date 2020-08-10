#ifndef _Movement_H
#define _Movement_H

#include "Direction.h"


class Movement
{
private:
	int speed;
	Direction direction;

public:
	Movement(int speed, Direction direction);
	int getSpeed() const;
	Direction getDirection() const;
	void setSpeed(int speed);
	void setDirection(Direction direction);
};

#endif //_Movement_H
