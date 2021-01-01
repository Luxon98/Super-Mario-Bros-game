#ifndef IndependentLivingObject_H
#define IndependentLivingObject_H

#include "LivingObject.h"

class World;


class IndependentLivingObject : public LivingObject
{
protected:
	int healthPoints;
	void moveHorizontally(World &world);
	void moveDiagonally(World &world);

public:
	int getHealthPoints() const;
	virtual int getPointsForCrushing() const;
	virtual int getPointsForDestroying() const;
	virtual bool isCrushproof() const;
	virtual bool isResistantToImmortalPlayer() const;
	virtual bool isResistantToCollisionWithShell() const;
	virtual bool isResistantToFireBalls() const;
	virtual bool isActiveShell() const;
	void decrementHealthPoints();
	virtual void crush(World &world, int index);
	virtual void destroy(World &world, Direction direction);
};

#endif //IndependentLivingObject_H