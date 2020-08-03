#ifndef _DestroyedTurtle_H
#define _DestroyedTurtle_H

#include "SDL_Utility.h"
#include "TemporaryObject.h"


class DestroyedTurtle : public TemporaryObject
{
private:
	static SDL_Surface* destroyedTurtleImage;
	int auxiliaryCounter;

public:
	DestroyedTurtle();
	DestroyedTurtle(Position* position);
	void loadDestroyedTurtleImage(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //_DestroyedTurtle_H