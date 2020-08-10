#include "Mushroom.h"

SDL_Surface* Mushroom::mushroomImages[2] = { nullptr };

Mushroom::Mushroom() {}

Mushroom::Mushroom(Position* position, bool greenColor)
{
	size = new Size(32, 32);
	this->position = position;
	stepsCounter = 0;
	this->greenColor = greenColor;
	moveDirection = Right;
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

void Mushroom::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (growCounter) {
		grow();
	}
	else if (stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			int alignment = getAlignmentIfCollisionOccursDuringMovement(direction, distance, this, world);
			int realDistance = direction == Right ? (distance - alignment) : (-1) * (distance - alignment);
			position->setX(position->getX() + realDistance);

			if (alignment > 0) {
				moveDirection = (moveDirection == Right ? Left : Right);
			}
		}
		else {
			int realVerticalDistance = (2 * distance) - getAlignmentIfCollisionOccursDuringVerticalMovement(Down, 2 * distance, this, world);
			position->setY(position->getY() + realVerticalDistance);

			int realDistance = (direction == Right ? 1 : -1) * (1 - getAlignmentIfCollisionOccursDuringMovement(direction, distance, this, world));
			position->setX(position->getX() + realDistance);
		}
	}

	stepsCounter++;
}

