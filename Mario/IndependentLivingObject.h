#ifndef IndependentLivingObject_H
#define IndependentLivingObject_H

#include "LivingObject.h"

class World;


class IndependentLivingObject : public LivingObject
{
protected:
	void moveHorizontally(World &world);
	void moveDiagonally(World &world);

public:
	virtual int getPointsForCrushing() const;
	virtual int getPointsForDestroying() const;
	virtual bool isCrushproof() const;
	virtual bool isResistantToImmortalPlayer() const;
	virtual void crush(World &world, int index);
	virtual void destroy(World &world, Direction direction);
};

#endif //IndependentLivingObject_H