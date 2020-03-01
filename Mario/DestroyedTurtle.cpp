#include "DestroyedTurtle.h"

SDL_Surface* DestroyedTurtle::destroyedTurtleImage = nullptr;

DestroyedTurtle::DestroyedTurtle() {}

DestroyedTurtle::DestroyedTurtle(int x, int y) {
	this->positionX = x;
	this->positionY = y;
	this->creationTime = std::chrono::steady_clock::now();
	this->auxiliaryCounter = 0;
}

void DestroyedTurtle::loadDestroyedTurtleImage(SDL_Surface* screen) {
	this->destroyedTurtleImage = loadPNG("./img/destroyed_turtle.png", screen);
}

void DestroyedTurtle::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->destroyedTurtleImage, this->positionX - beginningOfCamera, this->positionY);
}

bool DestroyedTurtle::shouldBeRemoved() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (this->creationTime + std::chrono::milliseconds(2000) < timePoint);
}

void DestroyedTurtle::slide() {
	++this->auxiliaryCounter;

	if (this->auxiliaryCounter & 1) {
		if (this->auxiliaryCounter <= 12) {
			this->positionY -= 3;
		}
		else if (this->auxiliaryCounter >= 13 && this->auxiliaryCounter <= 24) {
			this->positionX += 3;
			this->positionY -= 2;
		}
		else if (this->auxiliaryCounter >= 25 && this->auxiliaryCounter <= 32) {
			this->positionX += 3;
		}
		else if (this->auxiliaryCounter >= 33 && this->auxiliaryCounter <= 44) {
			this->positionX += 3;
			this->positionY += 2;
		}
		else {
			this->positionY += 3;
			if (this->auxiliaryCounter % 3 == 0) {
				++this->positionX;
			}
		}
	}
}

