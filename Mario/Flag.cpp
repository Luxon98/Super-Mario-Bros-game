#include "Flag.h"

#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> Flag::flagImages;

Flag::Flag(Position position)
{
	this->position = position;
	active = false;
	stickPositionY = position.getY() + 117;
	stepsCounter = 0;
}

bool Flag::isActive() const
{
	return active;
}

bool Flag::isDown() const
{
	return (stepsCounter >= 506);
}

void Flag::setActiveState()
{
	active = true;
}

void Flag::loadFlagImages(SDL_Surface* display)
{
	flagImages[0] = loadPNG("./img/flag.png", display);
	flagImages[1] = loadPNG("./img/stick.png", display);
}

void Flag::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		drawSurface(display, flagImages[1], position.getX() + 17 - beginningOfCamera, stickPositionY);
		drawSurface(display, flagImages[0], position.getX() - beginningOfCamera, position.getY());
	}
}

void Flag::changePosition()
{
	if (active && stepsCounter < 506) {
		++stepsCounter;
		if (stepsCounter & 1) {
			position.setY(position.getY() + 1);
		}
	}
	else if (stepsCounter >= 506) {
		active = false;
	}
}

