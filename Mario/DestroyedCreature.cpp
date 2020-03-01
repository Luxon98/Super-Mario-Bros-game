#include "DestroyedCreature.h"

SDL_Surface* DestroyedCreature::destroyedCreatureImage = nullptr;

DestroyedCreature::DestroyedCreature() {}

DestroyedCreature::DestroyedCreature(int x, int y) {
	this->positionX = x;
	this->positionY = y;
	this->creationTime = std::chrono::steady_clock::now();
	this->auxiliaryCounter = 0;
}

void DestroyedCreature::loadDestroyedCreatureImage(SDL_Surface* screen) {
	this->destroyedCreatureImage = loadPNG("./img/destroyed_creature.png", screen);
}

void DestroyedCreature::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->destroyedCreatureImage, this->positionX - beginningOfCamera, this->positionY);
}

bool DestroyedCreature::shouldBeRemoved() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (this->creationTime + std::chrono::milliseconds(2000) < timePoint);
}

void DestroyedCreature::slide() {
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

