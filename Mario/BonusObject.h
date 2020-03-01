#ifndef _BonusObject_H
#define _BonusObject_H

#include "NonControllableLivingObject.h"


class BonusObject : public NonControllableLivingObject {
protected:
	int growCounter;
	void grow();
};

#endif

