#include "Mushroom.h"

SDL_Surface* Mushroom::mushroomImages[2] = { nullptr };

Mushroom::Mushroom() {}

Mushroom::Mushroom(Position* position, bool colour)
{
	this->size = new Size(32, 32);
	this->position = position;
	this->stepsCounter = 0;
	this->green = colour;
	this->moveDirection = Right;
	this->growCounter = 96;
}

bool Mushroom::isGreen()
{
	return this->green;
}

void Mushroom::loadMushroomImages(SDL_Surface* screen)
{
	mushroomImages[0] = loadPNG("./img/mushroom_green.png", screen);
	mushroomImages[1] = loadPNG("./img/mushroom_red.png", screen);
}

void Mushroom::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* mushroomImg = nullptr;
	mushroomImg = mushroomImages[!this->green];
	drawSurface(screen, mushroomImg, this->position->getX() - beginningOfCamera, this->position->getY());
}

void Mushroom::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (this->growCounter) {
		this->grow();
	}
	else if (this->stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			int alignment = getAlignmentIfCollisionOccursDuringMovement(direction, distance, this, world);
			int realDistance = direction == Right ? (distance - alignment) : (-1) * (distance - alignment);
			this->position->setX(this->position->getX() + realDistance);

			if (alignment > 0) {
				this->moveDirection = (this->moveDirection == Right ? Left : Right);
			}
		}
		else {
			int realVerticalDistance = (2 * distance) - getAlignmentIfCollisionOccursDuringVerticalMovement(Down, 2 * distance, this, world);
			this->position->setY(this->position->getY() + realVerticalDistance);

			int realDistance = (direction == Right ? 1 : -1) * (1 - getAlignmentIfCollisionOccursDuringMovement(direction, distance, this, world));
			this->position->setX(this->position->getX() + realDistance);
		}
	}

	this->stepsCounter++;
}

