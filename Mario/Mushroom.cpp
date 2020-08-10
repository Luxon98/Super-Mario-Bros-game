#include "Mushroom.h"

SDL_Surface* Mushroom::mushroomImages[2] = { nullptr };

Mushroom::Mushroom() {}

Mushroom::Mushroom(Position* position, bool greenColor)
{
	size = new Size(32, 32);
	movement = new Movement(1, Right);
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
			int alignment = getAlignmentIfCollisionOccursDuringMovement(movement->getDirection(), movement->getSpeed(), this, world);
			int distance = movement->getDirection() == Right ? (movement->getSpeed() - alignment) : (-1) * (movement->getSpeed() - alignment);
			position->setX(position->getX() + distance);

			if (alignment > 0) {
				movement->setDirection(movement->getDirection() == Right ? Left : Right);
			}
		}
		else {
			int verticalDistance = (2 * movement->getSpeed()) - getAlignmentIfCollisionOccursDuringVerticalMovement(Down, 2 * movement->getSpeed(), this, world);
			position->setY(position->getY() + verticalDistance);

			int distance = (movement->getDirection() == Right ? 1 : -1) * (1 - getAlignmentIfCollisionOccursDuringMovement(movement->getDirection(), movement->getSpeed(), this, world));
			position->setX(position->getX() + distance);
		}
	}

	stepsCounter++;
}

