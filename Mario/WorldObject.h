#ifndef _WorldObject_H
#define _WorldObject_H

#include "SDL_Utility.h"
#include "Position.h"


class WorldObject {
protected:
	Position* position;
	int width;
	int height;

public:
	int getPositionX() const;
	int getPositionY() const;
	int getWidth() const;
	int getHeight() const;
	virtual void draw(SDL_Surface* screen, int beginningOfCamera) = 0;
};

#endif