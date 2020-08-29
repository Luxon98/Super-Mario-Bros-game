#include "Shell.h"

#include "Size.h"
#include "Movement.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"


SDL_Surface* Shell::shellImage = nullptr;

Shell::Shell() {}

Shell::Shell(Position* position)
{
	size = new Size(32, 28);
	movement = new Movement(3, 2, None);
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

void Shell::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position->getX() > beginningOfCamera - 120 && position->getX() < endOfCamera + 120) {
		drawSurface(display, shellImage, position->getX() - beginningOfCamera, position->getY());
	}
}

void Shell::move(World& world)
{
	if (movement->getDirection() != None && stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			makeHorizontalMove(world);
		}
		else {
			makeDiagonalMove(world);
		}
	}
	stepsCounter++;
}

