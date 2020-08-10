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
	movement = new Movement(1, None);
	this->position = position;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;
}

void Creature::setMoveDirection(Direction direction)
{
	movement->setDirection(direction);
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

void Creature::move(World& world)
{
	if (movement->getDirection() != None && stepsCounter % 3 == 0) {
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

		changeModel();
	}

	stepsCounter++;
}

