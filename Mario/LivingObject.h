#ifndef LivingObject_H
#define LivingObject_H

#include "WorldObject.h"
#include "Movement.h"
#include "Size.h"

class World;


class LivingObject : public WorldObject 
{
protected:
	int stepsCounter;
	int changeModelCounter;
	Movement movement;

public:
	Movement getMovement() const;
	virtual void move(World& world) = 0;
};

#endif //LivingObject_H