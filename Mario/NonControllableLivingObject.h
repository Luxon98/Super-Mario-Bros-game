#ifndef _NonControllableLivingObject_H
#define _NonControllableLivingObject_H

#include "LivingObject.h"


class NonControllableLivingObject : public LivingObject 
{
protected:
	Direction moveDirection;

public:
	Direction getMoveDirection() const;
};

#endif //_NonControllableLivingObject_H

