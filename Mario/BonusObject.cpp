#include "BonusObject.h"

#include "Position.h"


void BonusObject::grow()
{
	growCounter--;
	if (growCounter % 3 == 0) {
		position.setY(position.getY() - 1);
	}
}
