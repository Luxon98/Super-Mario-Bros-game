#ifndef _DestroyedTurtle_H
#define _DestroyedTurtle_H

#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class DestroyedTurtle : public TemporaryObject
{
private:
	static SDL_Surface* destroyedTurtleImage;
	int auxiliaryCounter;

public:
	DestroyedTurtle();
	DestroyedTurtle(Position* position);
	void loadDestroyedTurtleImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //_DestroyedTurtle_H