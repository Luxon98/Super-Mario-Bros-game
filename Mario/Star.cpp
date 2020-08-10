#include "Star.h"

SDL_Surface* Star::starImages[4] = { nullptr };

Star::Star() {}

Star::Star(Position* position)
{
	size = new Size(28, 32);
	this->position = position;
	movement = new Movement(1, Right);
	verticalDirection = Up;
	stepsCounter = 0;
	growCounter = 90;
}

void Star::loadStarImages(SDL_Surface* display)
{
	for (int i = 0; i < 4; ++i) {
		std::string filename = "./img/star";
		filename += std::to_string(i + 1);
		filename += ".png";
		starImages[i] = loadPNG(filename, display);
	}
}

void Star::draw(SDL_Surface* display, int beginningOfCamera)
{
	SDL_Surface* starImg = nullptr;
	starImg = starImages[stepsCounter % 4];
	drawSurface(display, starImg, position->getX() - beginningOfCamera, position->getY());
}

void Star::move(World& world)
{
	if (growCounter) {
		grow();
	}
	else {
		int alignment = getAlignmentIfCollisionOccursDuringMovement(movement->getDirection(), 2 * movement->getSpeed(), this, world);
		int distance = movement->getDirection() == Right ? 1 : -1 * (2 * movement->getSpeed() - alignment);
		position->setX(position->getX() + distance);

		if (alignment > 0) {
			movement->setDirection(movement->getDirection() == Right ? Left : Right);
		}

		alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(verticalDirection, movement->getSpeed(), this, world);
		int verticalDistance = (verticalDirection == Down ? 1 : -1) * (movement->getSpeed() - alignment);

		position->setY(position->getY() + verticalDistance);

		if (verticalDirection == Up) {
			stepsUp++;
		}

		if (alignment > 0) {
			verticalDirection = (verticalDirection == Down ? Up : Down);
			stepsUp = 0;
		}
		else if (stepsUp % 64 == 0 && verticalDirection == Up) {
			verticalDirection = Down;
			stepsUp = 0;
		}
	}

	stepsCounter++;
}

