#ifndef _LivingObject_H
#define _LivingObject_H

#include "WorldObject.h"


enum Direction;
class World;
class Screen;


class LivingObject : public WorldObject 
{
protected:
	int stepsCounter;
	int changeModelCounter;

public:
	virtual void move(Direction direction, int distance, World& world, Screen* mainScreen = nullptr) = 0;
};

#endif //_LivingObject_H