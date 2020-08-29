#ifndef _WorldObject_H
#define _WorldObject_H

class Position;
class Size;
struct SDL_Surface;


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
	virtual void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) = 0;
};

#endif //_WorldObject_H