#ifndef BonusObject_H
#define BonusObject_H

#include "IndependentLivingObject.h"


class BonusObject : public IndependentLivingObject
{
protected:
	int growCounter;
	bool active;
	void grow();

public:
	bool isActive() const;
};

#endif //BonusObject_H

