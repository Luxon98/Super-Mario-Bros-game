#ifndef AnimatedObject_H
#define AnimatedObject_H

#include "WorldObject.h"


class AnimatedObject : public WorldObject
{
public:
	virtual void move() = 0;
};

#endif //AnimatedObject_H