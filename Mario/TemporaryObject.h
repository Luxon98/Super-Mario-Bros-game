#ifndef TemporaryObject_H
#define TemporaryObject_H

#include <chrono>
#include "WorldObject.h"


class TemporaryObject : public WorldObject
{
protected:
	std::chrono::steady_clock::time_point creationTime;
	int auxiliaryCounter;

public:
	virtual bool shouldBeRemoved() = 0;
	virtual void slide() = 0;
};

#endif //TemporaryObject_H
