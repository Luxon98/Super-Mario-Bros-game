#include "BonusObject.h"

void BonusObject::grow() {
	--this->growCounter;
	if (this->growCounter % 3 == 0) {
		--this->positionY;
	}
}
