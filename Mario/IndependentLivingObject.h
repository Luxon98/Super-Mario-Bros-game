#ifndef _IndependentLivingObject_H
#define _IndependentLivingObject_H

#include "LivingObject.h"


int getAlignmentIfCollisionOccursDuringMovement(Direction direction, int distance, WorldObject* object, World& world);

int getAlignmentIfCollisionOccursDuringVerticalMovement(Direction direction, int distance, WorldObject* object, World& world);


class IndependentLivingObject : public LivingObject
{
protected:
	void makeHorizontalMove(World& world);
	void makeDiagonalMove(World& world);
};

#endif //_IndependentLivingObject_H

