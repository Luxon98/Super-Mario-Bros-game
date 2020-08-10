#include "Shell.h"

SDL_Surface* Shell::shellImage = nullptr;

Shell::Shell() {}

Shell::Shell(Position* position)
{
	size = new Size(32, 28);
	movement = new Movement(1, None);
	this->position = position;
	stepsCounter = 0;
	creationTime = std::chrono::steady_clock::now();
	active = false;
}

bool Shell::isActive()
{
	return active;
}

bool Shell::shouldTurnIntoTurtle()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(25000) < timePoint);
}

void Shell::setMovementDirectionAndActiveState(Direction direction)
{
	movement->setDirection(direction);
	active = (movement->getDirection() != None);
}

void Shell::resetCreationTime()
{
	creationTime = std::chrono::steady_clock::now();
}


void Shell::loadShellImage(SDL_Surface* display)
{
	shellImage = loadPNG("./img/shell.png", display);
}

void Shell::draw(SDL_Surface* display, int beginningOfCamera)
{
	drawSurface(display, shellImage, position->getX() - beginningOfCamera, position->getY());
}

void Shell::move(World& world)
{
	if (movement->getDirection() != None && stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			for (int i = 0; i < 3; ++i) {
				int alignment = getAlignmentIfCollisionOccursDuringMovement(movement->getDirection(), movement->getSpeed(), this, world);
				int distance = movement->getDirection() == Right ? (movement->getSpeed() - alignment) : (-1) * (movement->getSpeed() - alignment);
				position->setX(position->getX() + distance);

				if (alignment > 0) {
					movement->setDirection(movement->getDirection() == Right ? Left : Right);
				}
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

