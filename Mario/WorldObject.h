#ifndef WorldObject_H
#define WorldObject_H

#include "Size.h"
#include "Position.h"

struct SDL_Surface;


class WorldObject 
{
protected:
	Position position;
	Size size;

public:
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	virtual void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) = 0;
};

#endif //WorldObject_H