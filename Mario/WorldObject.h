#ifndef _WorldObject_H
#define _WorldObject_H

#include "SDL_Utility.h"


class WorldObject {
protected:
	int positionX;
	int positionY;
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