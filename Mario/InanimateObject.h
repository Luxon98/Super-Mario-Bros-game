#ifndef InanimateObject_H
#define InanimateObject_H

#include "WorldObject.h"


class InanimateObject : public WorldObject
{
protected:
	int model;
	
public:
	int getModel() const;
};

#endif //InanimateObject_H