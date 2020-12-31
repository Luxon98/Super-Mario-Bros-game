#include "BonusObject.h"

#include "Position.h"


void BonusObject::grow()
{
	--growCounter;
	if (growCounter % 3 == 0) {
		position.setY(position.getY() - 1);
	}

	if (growCounter < 50 && !active) {
		active = true;
	}
}

bool BonusObject::isActive() const
{
	if (isCoin()) {
		return true;
	}

	return active;
}

bool BonusObject::isCoin() const
{
	return false;
}

int BonusObject::getPointsForCollecting() const
{
	return 1000;
}

void BonusObject::knockUp() {}