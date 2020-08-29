#ifndef _IndependentLivingObject_H
#define _IndependentLivingObject_H

#include "LivingObject.h"

class World;


class IndependentLivingObject : public LivingObject
{
protected:
	void makeHorizontalMove(World& world);
	void makeDiagonalMove(World& world);
};

#endif //_IndependentLivingObject_H

