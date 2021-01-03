#ifndef BonusObject_H
#define BonusObject_H

#include "MovingObject.h"

class Player;


class BonusObject : public MovingObject
{
protected:
	int growCounter;
	bool active;
	void grow();

public:
	bool isActive() const;
	virtual bool isCoin() const;
	virtual int getPointsForCollecting() const;
	virtual void knockUp();
	virtual void giveBonus(Player &player) = 0;
};

#endif //BonusObject_H

