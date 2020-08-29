#include "BonusObject.h"

#include "Position.h"


void BonusObject::grow()
{
	this->growCounter--;
	if (this->growCounter % 3 == 0) {
		this->position->setY(this->position->getY() - 1);
	}
}
