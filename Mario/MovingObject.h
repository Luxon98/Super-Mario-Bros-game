#ifndef MovingObject_H
#define MovingObject_H

#include "WorldObject.h"
#include "Movement.h"
#include "Size.h"

class World;


class MovingObject : public WorldObject 
{
protected:
	int stepsCounter;
	int changeModelCounter;
	Movement movement;
	virtual int computeImageIndex() const = 0;

public:
	Movement getMovement() const;
	virtual void move(World &world) = 0;
};

#endif //MovingObject_H