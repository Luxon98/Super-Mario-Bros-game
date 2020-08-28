#ifndef _IndependentLivingObject_H
#define _IndependentLivingObject_H

#include "LivingObject.h"


int getAlignmentForHorizontalMove(Direction direction, int distance, WorldObject* object, World& world);

int getAlignmentForVerticalMove(Direction direction, int distance, WorldObject* object, World& world);


class IndependentLivingObject : public LivingObject
{
protected:
	void makeHorizontalMove(World& world);
	void makeDiagonalMove(World& world);
};

#endif //_IndependentLivingObject_H

