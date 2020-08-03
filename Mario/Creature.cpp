#include "Creature.h"

SDL_Surface* Creature::creatureImages[2] = { nullptr };

void Creature::chooseModel()
{
	this->changeModelCounter++;
	if (this->changeModelCounter % 30 == 0) {
		this->model = (this->model == 1 ? 2 : 1);
	}
}

Creature::Creature() {}

Creature::Creature(Position* position)
{
	this->size = new Size(32, 32);
	this->position = position;
	this->model = 1;
	this->stepsCounter = 0;
	this->changeModelCounter = 0;
	this->moveDirection = None;
}

void Creature::setMoveDirection(Direction direction)
{
	this->moveDirection = direction;
}

void Creature::loadCreatureImages(SDL_Surface* screen)
{
	creatureImages[0] = loadPNG("./img/creature1.png", screen);
	creatureImages[1] = loadPNG("./img/creature2.png", screen);
}

void Creature::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* creatureImg = nullptr;
	creatureImg = creatureImages[this->model - 1];
	drawSurface(screen, creatureImg, this->position->getX() - beginningOfCamera, this->position->getY());
}

void Creature::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (this->moveDirection != None && this->stepsCounter % 3 == 0) {
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

		this->chooseModel();
	}

	this->stepsCounter++;
}

