#ifndef _InanimateObject_H
#define _InanimateObject_H

#include "SDL_Utility.h"
#include "WorldObject.h"


class InanimateObject : public WorldObject
{
protected:
	int model;
	
public:
	int getModel() const;
};

#endif //_InanimateObject_H