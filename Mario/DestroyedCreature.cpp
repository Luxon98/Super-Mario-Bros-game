#include "DestroyedCreature.h"

SDL_Surface* DestroyedCreature::destroyedCreatureImage = nullptr;

DestroyedCreature::DestroyedCreature() {}

DestroyedCreature::DestroyedCreature(Position* position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
}

void DestroyedCreature::loadDestroyedCreatureImage(SDL_Surface* display)
{
	destroyedCreatureImage = loadPNG("./img/destroyed_creature.png", display);
}

void DestroyedCreature::draw(SDL_Surface* display, int beginningOfCamera)
{
	drawSurface(display, destroyedCreatureImage, position->getX() - beginningOfCamera, position->getY());
}

bool DestroyedCreature::shouldBeRemoved()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(2000) < timePoint);
}

void DestroyedCreature::slide()
{
	auxiliaryCounter++;

	if (auxiliaryCounter & 1) {
		if (auxiliaryCounter <= 12) {
			position->setY(position->getY() - 2);
		}
		else if (auxiliaryCounter >= 13 && auxiliaryCounter <= 24) {
			position->setX(position->getX() + 2);
			position->setY(position->getY() - 3);
		}
		else if (auxiliaryCounter >= 25 && auxiliaryCounter <= 32) {
			position->setX(position->getX() + 2);
		}
		else if (auxiliaryCounter >= 33 && auxiliaryCounter <= 44) {
			position->setX(position->getX() + 2);
			position->setY(position->getY() + 2);
		}
		else {
			position->setY(position->getY() + 3);
			if (auxiliaryCounter % 3 == 0) {
				position->setX(position->getX() + 1);
			}
		}
	}
}

