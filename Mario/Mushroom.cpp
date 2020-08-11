#include "Mushroom.h"

SDL_Surface* Mushroom::mushroomImages[2] = { nullptr };

void Mushroom::makeHorizontalMovea(World& world)
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

void Mushroom::makeDiagonalMovea(World& world)
{
	int alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(Down, movement->getVerticalSpeed(), this, world);
	int verticalDistance = movement->getVerticalSpeed() - alignment;
	position->setY(position->getY() + verticalDistance);

	alignment = getAlignmentIfCollisionOccursDuringMovement(movement->getDirection(), movement->getSpeed(), this, world);
	int distance = movement->getSpeed() - alignment;
	if (movement->getDirection() == Left) {
		distance *= -1;
	}
	position->setX(position->getX() + distance);
}

Mushroom::Mushroom() {}

Mushroom::Mushroom(Position* position, bool greenColor)
{
	size = new Size(32, 32);
	movement = new Movement(1, 2, Right);
	this->position = position;
	stepsCounter = 0;
	this->greenColor = greenColor;
	growCounter = 96;
}

bool Mushroom::isGreen()
{
	return greenColor;
}

void Mushroom::loadMushroomImages(SDL_Surface* display)
{
	mushroomImages[0] = loadPNG("./img/mushroom_green.png", display);
	mushroomImages[1] = loadPNG("./img/mushroom_red.png", display);
}

void Mushroom::draw(SDL_Surface* display, int beginningOfCamera)
{
	SDL_Surface* mushroomImg = nullptr;
	mushroomImg = mushroomImages[!greenColor];
	drawSurface(display, mushroomImg, position->getX() - beginningOfCamera, position->getY());
}

void Mushroom::move(World& world)
{
	if (growCounter) {
		grow();
	}
	else if (stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			makeHorizontalMove(world);
		}
		else {
			makeDiagonalMove(world);
		}
	}
	stepsCounter++;
}

