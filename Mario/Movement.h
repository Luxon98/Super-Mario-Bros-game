#ifndef Movement_H
#define Movement_H

#include "Direction.h"


class Movement
{
protected:
	int speed;
	int verticalSpeed;
	Direction direction;
	Direction verticalDirection;

public:
	Movement() = default;
	Movement(int speed, int verticalSpeed, Direction direction, Direction verticalDirection);
	int getSpeed() const;
	int getVerticalSpeed() const;
	Direction getDirection() const;
	Direction getVerticalDirection() const;
	void setSpeed(int speed);
	void setVerticalSpeed(int verticalSpeed);
	void setDirection(Direction direction);
	void setVerticalDirection(Direction verticalDirection);
};

#endif //Movement_H
