#include "Shell.h"

SDL_Surface* Shell::shellImage = nullptr;

Shell::Shell() {}

Shell::Shell(Position* position)
{
	size = new Size(32, 28);
	this->position = position;
	stepsCounter = 0;
	moveDirection = None;
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
	moveDirection = direction;
	active = (moveDirection != None);
}

void Shell::resetCreationTime()
{
	creationTime = std::chrono::steady_clock::now();
}


void Shell::loadShellImage(SDL_Surface* screen)
{
	shellImage = loadPNG("./img/shell.png", screen);
}

void Shell::draw(SDL_Surface* screen, int beginningOfCamera)
{
	drawSurface(screen, shellImage, position->getX() - beginningOfCamera, position->getY());
}

void Shell::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (moveDirection != None && stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			for (int i = 0; i < 3; ++i) {
				int alignment = getAlignmentIfCollisionOccursDuringMovement(direction, distance, this, world);
				int realDistance = direction == Right ? (distance - alignment) : (-1) * (distance - alignment);
				position->setX(position->getX() + realDistance);

				if (alignment > 0) {
					moveDirection = (moveDirection == Right ? Left : Right);
				}
			}
		}
		else {
			int realVerticalDistance = (2 * distance - getAlignmentIfCollisionOccursDuringVerticalMovement(Down, 2 * distance, this, world));
			position->setY(position->getY() + realVerticalDistance);

			int realDistance = (direction == Right ? 1 : -1) * (1 - getAlignmentIfCollisionOccursDuringMovement(direction, distance, this, world));
			position->setX(position->getX() + realDistance);
		}
	}

	stepsCounter++;
}

