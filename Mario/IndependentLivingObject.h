#ifndef IndependentLivingObject_H
#define IndependentLivingObject_H

#include "LivingObject.h"

class World;


class IndependentLivingObject : public LivingObject
{
protected:
	void makeHorizontalMove(World &world);
	void makeDiagonalMove(World &world);
};

#endif //IndependentLivingObject_H

