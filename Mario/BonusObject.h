#ifndef _BonusObject_H
#define _BonusObject_H

#include "IndependentLivingObject.h"


class BonusObject : public IndependentLivingObject
{
protected:
	int growCounter;
	void grow();
};

#endif //_BonusObject_H

