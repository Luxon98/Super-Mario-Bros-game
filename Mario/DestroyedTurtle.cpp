#include "DestroyedTurtle.h"

SDL_Surface* DestroyedTurtle::destroyedTurtleImage = nullptr;

DestroyedTurtle::DestroyedTurtle() {}

DestroyedTurtle::DestroyedTurtle(Position* position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
}

void DestroyedTurtle::loadDestroyedTurtleImage(SDL_Surface* screen)
{
	destroyedTurtleImage = loadPNG("./img/destroyed_turtle.png", screen);
}

void DestroyedTurtle::draw(SDL_Surface* screen, int beginningOfCamera)
{
	drawSurface(screen, destroyedTurtleImage, position->getX() - beginningOfCamera, position->getY());
}

bool DestroyedTurtle::shouldBeRemoved()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(2000) < timePoint);
}

void DestroyedTurtle::slide()
{
	++auxiliaryCounter;

	if (auxiliaryCounter & 1) {
		if (auxiliaryCounter <= 12) {
			position->setY(position->getY() - 3);
		}
		else if (auxiliaryCounter >= 13 && auxiliaryCounter <= 24) {
			position->setX(position->getX() + 3);
			position->setY(position->getY() - 2);
		}
		else if (auxiliaryCounter >= 25 && auxiliaryCounter <= 32) {
			position->setY(position->getY() + 3);
		}
		else if (auxiliaryCounter >= 33 && auxiliaryCounter <= 44) {
			position->setX(position->getX() + 3);
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

