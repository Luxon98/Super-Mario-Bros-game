#ifndef AnimatedObject_H
#define AnimatedObject_H

#include <chrono>
#include "WorldObject.h"


class AnimatedObject : public WorldObject
{
protected:
	std::chrono::steady_clock::time_point creationTime;
	int auxiliaryCounter;
	virtual int computeImageIndex() const = 0;

public:
	virtual bool shouldBeRemoved() const = 0;
	virtual void slide() = 0;
};

#endif //AnimatedObject_H