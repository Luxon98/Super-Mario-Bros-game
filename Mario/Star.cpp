#include "Star.h"

SDL_Surface* Star::starImages[4] = { nullptr };

Star::Star() {}

Star::Star(Position* position)
{
	size = new Size(28, 32);
	this->position = position;
	moveDirection = Right;
	verticalDirection = Up;
	stepsCounter = 0;
	growCounter = 90;
}

void Star::loadStarImages(SDL_Surface* screen)
{
	for (int i = 0; i < 4; ++i) {
		std::string filename = "./img/star";
		filename += std::to_string(i + 1);
		filename += ".png";
		starImages[i] = loadPNG(filename, screen);
	}
}

void Star::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* starImg = nullptr;
	starImg = starImages[stepsCounter % 4];
	drawSurface(screen, starImg, position->getX() - beginningOfCamera, position->getY());
}

void Star::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (growCounter) {
		grow();
	}
	else {
		int alignment = getAlignmentIfCollisionOccursDuringMovement(moveDirection, 2 * distance, this, world);
		int realDistance = moveDirection == Right ? 1 : -1 * (2 * distance - alignment);
		position->setX(position->getX() + realDistance);

		if (alignment > 0) {
			moveDirection = (moveDirection == Right ? Left : Right);
		}

		alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(verticalDirection, distance, this, world);
		int realVerticalDistance = (verticalDirection == Down ? 1 : -1) * (distance - alignment);
		position->setY(position->getY() + realVerticalDistance);

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

