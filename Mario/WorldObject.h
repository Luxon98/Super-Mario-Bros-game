#ifndef _WorldObject_H
#define _WorldObject_H

#include "SDL_Utility.h"
#include "Position.h"
#include "Size.h"


class WorldObject 
{
protected:
	Position* position;
	Size* size;

public:
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	virtual void draw(SDL_Surface* display, int beginningOfCamera) = 0;
};

#endif //_WorldObject_H