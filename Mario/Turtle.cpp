#include "Turtle.h"

SDL_Surface* Turtle::turtleImages[4] = { nullptr };

void Turtle::chooseModel()
{
	changeModelCounter++;
	if (changeModelCounter % 30 == 0) {
		model += (model & 1 ? 1 : -1);
	}
}

Turtle::Turtle() {}

Turtle::Turtle(Position* position)
{
	size = new Size(26, 38);
	this->position = position;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;
	moveDirection = None;
}

void Turtle::setMoveDirection(Direction direction)
{
	moveDirection = direction;
}

void Turtle::loadTurtleImages(SDL_Surface* display)
{
	turtleImages[0] = loadPNG("./img/turtle_left1.png", display);
	turtleImages[1] = loadPNG("./img/turtle_left2.png", display);
	turtleImages[2] = loadPNG("./img/turtle_rigth1.png", display);
	turtleImages[3] = loadPNG("./img/turtle_right2.png", display);
}

void Turtle::draw(SDL_Surface* display, int beginningOfCamera)
{
	SDL_Surface* turtleImg = nullptr;
	turtleImg = turtleImages[model - 1];
	drawSurface(display, turtleImg, position->getX() - beginningOfCamera, position->getY());
}

void Turtle::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (moveDirection != None && stepsCounter % 3 == 0) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			int alignment = getAlignmentIfCollisionOccursDuringMovement(direction, distance, this, world);
			int realDistance = (direction == Right ? (distance - alignment) : -1 * (distance - alignment));
			position->setX(position->getX() + realDistance);

			if (alignment > 0) {
				moveDirection = (moveDirection == Right ? Left : Right);
				model = (moveDirection == Left ? 1 : 3);
			}
		}
		else {
			int realVerticalDistance = (2 * distance) - getAlignmentIfCollisionOccursDuringVerticalMovement(Down, 2 * distance, this, world);
			position->setY(position->getY() + realVerticalDistance);

			int realDistance = (direction == Right ? 1 : -1) * (1 - getAlignmentIfCollisionOccursDuringMovement(direction, distance, this, world));
			position->setX(position->getX() + realDistance);
		}

		chooseModel();
	}

	stepsCounter++;
}

