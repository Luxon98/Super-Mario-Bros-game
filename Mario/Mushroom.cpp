#include "Mushroom.h"

SDL_Surface* Mushroom::mushroomImages[2] = { nullptr };

Mushroom::Mushroom() {}

Mushroom::Mushroom(int x, int y, bool colour) {
	this->width = 32;
	this->height = 32;
	this->positionX = x;
	this->positionY = y;
	this->stepsCounter = 0;
	this->green = colour;
	this->moveDirection = Right;
	this->growCounter = 96;
}

bool Mushroom::isGreen() {
	return this->green;
}

void Mushroom::loadMushroomImages(SDL_Surface* screen) {
	mushroomImages[0] = loadPNG("./img/mushroom_green.png", screen);
	mushroomImages[1] = loadPNG("./img/mushroom_red.png", screen);
}

void Mushroom::draw(SDL_Surface* screen, int beginningOfCamera) {
	SDL_Surface* mushroomImg = nullptr;
	mushroomImg = mushroomImages[!this->green];
	drawSurface(screen, mushroomImg, this->positionX - beginningOfCamera, this->positionY);
}

void Mushroom::move(Direction direction, int distance, World& world, Screen* mainScreen) {
	if (this->growCounter) {
		this->grow();
	}
	else if (this->stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			int alignment = alignIfCollisionOccursDuringMovement(direction, distance, this, world);
			this->positionX += (direction == Right ? (distance - alignment) : -1 * (distance - alignment));
			if (alignment > 0) {
				this->moveDirection = (this->moveDirection == Right ? Left : Right);
			}
		}
		else {
			this->positionY += (2 * distance - alignIfCollisionOccursDuringVerticalMovement(Down, 2 * distance, this, world));
			this->positionX += (direction == Right ? 1 : -1) * (1 - alignIfCollisionOccursDuringMovement(direction, distance, this, world));
		}
	}
	++this->stepsCounter;
}

