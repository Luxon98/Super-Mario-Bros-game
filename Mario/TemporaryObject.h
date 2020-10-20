#ifndef TemporaryObject_H
#define TemporaryObject_H

#include <chrono>
#include "WorldObject.h"


class TemporaryObject : public WorldObject
{
protected:
	std::chrono::steady_clock::time_point creationTime;
	int auxiliaryCounter;
	virtual int computeImageIndex() const = 0;

public:
	virtual bool shouldBeRemoved() const = 0;
	virtual void slide() = 0;
};

#endif //TemporaryObject_H
