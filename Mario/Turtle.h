#ifndef _Turtle_H
#define _Turtle_H

#include "SDL_Utility.h"
#include "World.h"
#include "IndependentLivingObject.h"


class Turtle : public IndependentLivingObject
{
private:
	static SDL_Surface* turtleImages[4];
	int model;
	void chooseModel();

public:
	Turtle();
	Turtle(Position* position);
	void setMoveDirection(Direction direction);
	void loadTurtleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	void move(World& world) override;
};

#endif //_Turtle_H
