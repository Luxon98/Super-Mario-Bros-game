#ifndef _LivingObject_H
#define _LivingObject_H

#include "WorldObject.h"

class World;
class Movement;


class LivingObject : public WorldObject 
{
protected:
	int stepsCounter;
	int changeModelCounter;
	Movement* movement;

public:
	Movement* getMovement() const;
	virtual void move(World& world) = 0;
};

#endif //_LivingObject_H