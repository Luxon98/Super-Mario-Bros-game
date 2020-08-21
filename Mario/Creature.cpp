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
	movement = new Movement(1, 2, None);
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

void Creature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position->getX() > beginningOfCamera - 90 && position->getX() < endOfCamera + 90) {
		SDL_Surface* creatureImg = nullptr;
		creatureImg = creatureImages[model - 1];
		drawSurface(display, creatureImg, position->getX() - beginningOfCamera, position->getY());
	}
}

void Creature::move(World& world)
{
	if (movement->getDirection() != None && stepsCounter % 3 == 0) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			makeHorizontalMove(world);
		}
		else {
			makeDiagonalMove(world);
		}
		changeModel();
	}
	stepsCounter++;
}

