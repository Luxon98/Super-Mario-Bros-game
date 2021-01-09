#include "TemporaryObject.h"


bool TemporaryObject::shouldBeRemoved() const
{
	return (position.getY() > 530);
}

bool TemporaryObject::isAnimatedCoin() const
{
	return false;
}

void TemporaryObject::slide() {}