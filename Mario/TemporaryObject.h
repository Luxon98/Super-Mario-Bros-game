#ifndef _TemporaryObject_H
#define _TemporaryObject_H

#include <chrono>
#include "WorldObject.h"


class TemporaryObject : public WorldObject
{
protected:
	std::chrono::steady_clock::time_point creationTime;

public:
	virtual bool shouldBeRemoved() = 0;
	virtual void slide() = 0;
};

#endif //_TemporaryObject_H
