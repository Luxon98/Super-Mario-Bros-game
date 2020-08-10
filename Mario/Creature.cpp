#include "Creature.h"

SDL_Surface* Creature::creatureImages[2] = { nullptr };

void Creature::changeModel()
{
	changeModelCounter++;
	if (changeModelCounter % 30 == 0) {
		model = (model == 1 ? 2 : 1);
	}
}

Creature::Creature() {}

Creature::Creature(Position* position)
{
	size = new Size(32, 32);
	this->position = position;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;
	moveDirection = None;
}

void Creature::setMoveDirection(Direction direction)
{
	moveDirection = direction;
}

void Creature::loadCreatureImages(SDL_Surface* display)
{
	creatureImages[0] = loadPNG("./img/creature1.png", display);
	creatureImages[1] = loadPNG("./img/creature2.png", display);
}

void Creature::draw(SDL_Surface* display, int beginningOfCamera)
{
	SDL_Surface* creatureImg = nullptr;
	creatureImg = creatureImages[model - 1];
	drawSurface(display, creatureImg, position->getX() - beginningOfCamera, position->getY());
}

void Creature::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (moveDirection != None && stepsCounter % 3 == 0) {
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

		changeModel();
	}

	stepsCounter++;
}

