#include "Shell.h"

SDL_Surface* Shell::shellImg = nullptr;

Shell::Shell() {}

Shell::Shell(Position* position) {
	size = new Size(32, 28);
	this->position = position;
	this->stepsCounter = 0;
	this->moveDirection = None;
	this->creationTime = std::chrono::steady_clock::now();
	this->active = false;
}

bool Shell::isActive() {
	return this->active;
}

bool Shell::shouldTurnIntoTurtle() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (this->creationTime + std::chrono::milliseconds(25000) < timePoint);
}

void Shell::setMovementDirectionAndActiveState(Direction direction) {
	this->moveDirection = direction;
	this->active = (this->moveDirection != None);
}

void Shell::resetCreationTime() {
	this->creationTime = std::chrono::steady_clock::now();
}


void Shell::loadShellImage(SDL_Surface* screen) {
	shellImg = loadPNG("./img/shell.png", screen);
}

void Shell::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->shellImg, this->position->getX() - beginningOfCamera, this->position->getY());
}

void Shell::move(Direction direction, int distance, World& world, Screen* mainScreen) {
	if (this->moveDirection != None && this->stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			for (int i = 0; i < 3; ++i) {
				int alignment = alignIfCollisionOccursDuringMovement(direction, distance, this, world);
				int realDistance = direction == Right ? (distance - alignment) : (-1) * (distance - alignment);
				this->position->setX(this->position->getX() + realDistance);
				
				if (alignment > 0) {
					this->moveDirection = (this->moveDirection == Right ? Left : Right);
				}
			}
		}
		else {
			int realVerticalDistance = (2 * distance - alignIfCollisionOccursDuringVerticalMovement(Down, 2 * distance, this, world));
			this->position->setY(this->position->getY() + realVerticalDistance);
			
			int realDistance = (direction == Right ? 1 : -1) * (1 - alignIfCollisionOccursDuringMovement(direction, distance, this, world));
			this->position->setX(this->position->getX() + realDistance);
		}
	}
	++this->stepsCounter;
}

