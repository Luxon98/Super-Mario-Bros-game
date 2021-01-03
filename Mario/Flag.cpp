#include "Flag.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "LayoutStyle.h"
#include "World.h"


std::array<SDL_Surface*, 4> Flag::flagImages;

Flag::Flag(Position position)
{
	this->position = position;
	active = false;
	stickPositionY = position.getY() + 117;
	stepsCounter = 0;
	size = Size(48, 304);
}

void Flag::loadFlagImages(SDL_Surface* display)
{
	flagImages[0] = loadPNG("./img/other_imgs/flag.png", display);
	flagImages[1] = loadPNG("./img/other_imgs/stick.png", display);
	flagImages[2] = loadPNG("./img/other_imgs/winter_flag.png", display);
	flagImages[3] = loadPNG("./img/other_imgs/winter_stick.png", display);
}

bool Flag::isActive() const
{
	return active;
}

bool Flag::isDown() const
{
	return (stepsCounter >= 506);
}

bool Flag::isPlayerHittingThisFlag(const Player &player)
{
	if (player.getX() >= this->getX() + 15 && player.getX() <= this->getX() + 65) {
		return true;
	}

	return false;
}

void Flag::setActiveState()
{
	active = true;
}

void Flag::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		int baseIndex = (World::LAYOUT_STYLE == LayoutStyle::CustomWinter ? 2 : 0);
		drawSurface(display, flagImages[baseIndex + 1], position.getX() + 17 - beginningOfCamera, stickPositionY);
		drawSurface(display, flagImages[baseIndex + 0], position.getX() - beginningOfCamera, position.getY());
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

