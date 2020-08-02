#include "Star.h"

SDL_Surface* Star::starImages[4] = { nullptr };

Star::Star() {}

Star::Star(Position* position) {
	size = new Size(28, 32);
	this->position = position;
	this->moveDirection = Right;
	this->verticalDirection = Up;
	this->stepsCounter = 0;
	this->growCounter = 90;
}

void Star::loadStarImages(SDL_Surface* screen) {
	for (int i = 0; i < 4; ++i) {
		std::string filename = "./img/star";
		filename += std::to_string(i + 1);
		filename += ".png";
		this->starImages[i] = loadPNG(filename, screen);
	}
}

void Star::draw(SDL_Surface* screen, int beginningOfCamera) {
	SDL_Surface* starImg = nullptr;
	starImg = starImages[this->stepsCounter % 4];
	drawSurface(screen, starImg, this->position->getX() - beginningOfCamera, this->position->getY());
}

void Star::move(Direction direction, int distance, World& world, Screen* mainScreen) {
	if (this->growCounter) {
		this->grow();
	}
	else {
		int alignment = alignIfCollisionOccursDuringMovement(this->moveDirection, 2 * distance, this, world);
		int realDistance = this->moveDirection == Right ? 1 : -1 * (2 * distance - alignment);
		this->position->setX(this->position->getX() + realDistance);

		if (alignment > 0) {
			this->moveDirection = (this->moveDirection == Right ? Left : Right);
		}

		alignment = alignIfCollisionOccursDuringVerticalMovement(this->verticalDirection, distance, this, world);
		int realVerticalDistance = (this->verticalDirection == Down ? 1 : -1) * (distance - alignment);
		this->position->setY(this->position->getY() + realVerticalDistance);

		if (this->verticalDirection == Up) {
			++this->stepsUp;
		}

		if (alignment > 0) {
			this->verticalDirection = (this->verticalDirection == Down ? Up : Down);
			this->stepsUp = 0;
		}
		else if (this->stepsUp % 64 == 0 && this->verticalDirection == Up) {
			this->verticalDirection = Down;
			this->stepsUp = 0;
		}
	}
	++this->stepsCounter;
}

