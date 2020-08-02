#include "DestroyedTurtle.h"

SDL_Surface* DestroyedTurtle::destroyedTurtleImage = nullptr;

DestroyedTurtle::DestroyedTurtle() {}

DestroyedTurtle::DestroyedTurtle(Position* position) {
	this->position = position;
	this->creationTime = std::chrono::steady_clock::now();
	this->auxiliaryCounter = 0;
}

void DestroyedTurtle::loadDestroyedTurtleImage(SDL_Surface* screen) {
	this->destroyedTurtleImage = loadPNG("./img/destroyed_turtle.png", screen);
}

void DestroyedTurtle::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->destroyedTurtleImage, this->position->getX() - beginningOfCamera, this->position->getY());
}

bool DestroyedTurtle::shouldBeRemoved() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (this->creationTime + std::chrono::milliseconds(2000) < timePoint);
}

void DestroyedTurtle::slide() {
	++this->auxiliaryCounter;

	if (this->auxiliaryCounter & 1) {
		if (this->auxiliaryCounter <= 12) {
			this->position->setY(this->position->getY() - 3);
		}
		else if (this->auxiliaryCounter >= 13 && this->auxiliaryCounter <= 24) {
			this->position->setX(this->position->getX() + 3);
			this->position->setY(this->position->getY() - 2);
		}
		else if (this->auxiliaryCounter >= 25 && this->auxiliaryCounter <= 32) {
			this->position->setY(this->position->getY() + 3);
		}
		else if (this->auxiliaryCounter >= 33 && this->auxiliaryCounter <= 44) {
			this->position->setX(this->position->getX() + 3);
			this->position->setY(this->position->getY() + 2);
		}
		else {
			this->position->setY(this->position->getY() + 3);
			if (this->auxiliaryCounter % 3 == 0) {
				this->position->setX(this->position->getX() + 1);
			}
		}
	}
}

