#ifndef TemporaryObject_H
#define TemporaryObject_H

#include "WorldObject.h"


class TemporaryObject : public WorldObject
{
protected:
	int auxiliaryCounter;
	virtual int computeImageIndex() const = 0;

public:
	virtual bool shouldBeRemoved() const;
	virtual bool isAnimatedCoin() const;
	virtual void slide();
};

#endif //TemporaryObject_H