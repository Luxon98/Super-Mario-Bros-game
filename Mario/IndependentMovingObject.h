#ifndef IndependentMovingObject_H
#define IndependentMovingObject_H

#include "MovingObject.h"

class World;
class Player;


class IndependentMovingObject : public MovingObject
{
protected:
	int healthPoints;
	void moveHorizontally(World &world);
	void moveDiagonally(World &world);
	virtual int computeImageIndex() const = 0;

public:
	int getHealthPoints() const;
	virtual int getPointsForCrushing() const;
	virtual int getPointsForDestroying() const;
	virtual bool shouldStartMoving(const Player &player) const;
	virtual bool isCrushproof() const;
	virtual bool isResistantToImmortalPlayer() const;
	virtual bool isResistantToCollisionWithShell() const;
	virtual bool isResistantToCollisionWithBlock() const;
	virtual bool isResistantToFireBalls() const;
	virtual bool isActiveShell() const;
	virtual bool isBoss() const;
	void decrementHealthPoints();
	virtual void startMoving();
	virtual void crush(World &world, int index);
	virtual void destroy(World &world, Direction direction);
	virtual void performSpecificActions(World &world, int index);
};

#endif //IndependentMovingObject_H