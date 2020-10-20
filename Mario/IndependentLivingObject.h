#ifndef IndependentLivingObject_H
#define IndependentLivingObject_H

#include "LivingObject.h"

class World;


class IndependentLivingObject : public LivingObject
{
protected:
	void moveHorizontally(World &world);
	void moveDiagonally(World &world);
};

#endif //IndependentLivingObject_H

