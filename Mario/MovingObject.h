#ifndef MovingObject_H
#define MovingObject_H

#include "WorldObject.h"
#include "Movement.h"

class World;
enum class Direction;


class MovingObject : public WorldObject 
{
protected:
	int moveCounter;
	int changeModelCounter;
	Movement movement;

public:
	Direction getDirection() const;
	virtual void move(World &world) = 0;
};

#endif //MovingObject_H