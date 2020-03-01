#ifndef _Turtle_H
#define _Turtle_H

#include "SDL_Interface.h"
#include "NonControllableLivingObject.h"
#include "World.h"


class Turtle : public NonControllableLivingObject {
private:
	static SDL_Surface* turtleImages[4];
	int model;
	void chooseModel();

public:
	Turtle();
	Turtle(int x, int y);
	void setMoveDirection(Direction direction);
	void loadTurtleImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	void move(Direction direction, int distance, World& world, Screen* mainScreen) override;
};

#endif
