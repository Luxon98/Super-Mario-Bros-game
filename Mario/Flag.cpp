#include "Flag.h"

SDL_Surface* Flag::flagImages[2] = { nullptr };

Flag::Flag() {}

Flag::Flag(int x, int y) {
	this->positionX = x;
	this->positionY = y;
	this->active = false;
	this->stickPositionY = y + 117;
	this->stepsCounter = 0;
}

bool Flag::isActive() const {
	return this->active;
}

bool Flag::isDown() const {
	return (this->stepsCounter >= 506);
}

void Flag::setActiveState() {
	this->active = true;
}

void Flag::loadFlagImage(SDL_Surface* screen) {
	this->flagImages[0] = loadPNG("./img/flag.png", screen);
	this->flagImages[1] = loadPNG("./img/stick.png", screen);
}

void Flag::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->flagImages[1], this->positionX + 17 - beginningOfCamera, this->stickPositionY);
	drawSurface(screen, this->flagImages[0], this->positionX - beginningOfCamera, this->positionY);
}

void Flag::changePosition() {
	if (this->active && this->stepsCounter < 506) {
		++this->stepsCounter;
		if (this->stepsCounter & 1) {
			++this->positionY;
		}
	}
	else if (this->stepsCounter >= 506) {
		this->active = false;
	}
}

