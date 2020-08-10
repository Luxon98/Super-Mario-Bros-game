#ifndef _BonusObject_H
#define _BonusObject_H

#include "LivingObject.h"


class BonusObject : public LivingObject
{
protected:
	int growCounter;
	void grow();
};

#endif //_BonusObject_H

