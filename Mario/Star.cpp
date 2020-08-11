#include "Star.h"

SDL_Surface* Star::starImages[4] = { nullptr };

void Star::makeVerticalMove(World& world)
{
	int alignment = getAlignmentIfCollisionOccursDuringMovement(movement->getDirection(), movement->getSpeed(), this, world);
	int distance = movement->getSpeed() - alignment;
	if (movement->getDirection() == Left) {
		distance *= -1;
	}
	position->setX(position->getX() + distance);

	if (alignment > 0) {
		movement->setDirection(movement->getDirection() == Right ? Left : Right);
	}
}

void Star::makeHorizontalMove(World& world)
{
	int alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(movement->getVerticalDirection(), movement->getVerticalSpeed(), this, world);
	int verticalDistance = movement->getVerticalSpeed() - alignment;
	if (movement->getVerticalDirection() == Up) {
		verticalDistance *= -1;
	}
	position->setY(position->getY() + verticalDistance);

	if (movement->getVerticalDirection() == Up) {
		stepsUp++;
	}

	if (alignment > 0) {
		movement->setVerticalDirection(movement->getVerticalDirection() == Down ? Up : Down);
		stepsUp = 0;
	}
	else if (stepsUp % 64 == 0 && movement->getVerticalDirection() == Up) {
		movement->setVerticalDirection(Down);
		stepsUp = 0;
	}
}

Star::Star() {}

Star::Star(Position* position)
{
	size = new Size(28, 32);
	this->position = position;
	movement = new Movement(2, 1, Right, Up);
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
		makeVerticalMove(world);
		makeHorizontalMove(world);
	}
	stepsCounter++;
}

