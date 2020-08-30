#ifndef BonusObject_H
#define BonusObject_H

#include "IndependentLivingObject.h"


class BonusObject : public IndependentLivingObject
{
protected:
	int growCounter;
	void grow();
};

#endif //BonusObject_H

