#include "Shell.h"

SDL_Surface* Shell::shellImg = nullptr;

Shell::Shell() {}

Shell::Shell(int x, int y) {
	this->width = 32;
	this->height = 28;
	this->positionX = x;
	this->positionY = y;
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
	drawSurface(screen, this->shellImg, this->positionX - beginningOfCamera, this->positionY);
}

void Shell::move(Direction direction, int distance, World& world, Screen* mainScreen) {
	if (this->moveDirection != None && this->stepsCounter & 1) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			for (int i = 0; i < 3; ++i) {
				int alignment = alignIfCollisionOccursDuringMovement(direction, distance, this, world);
				this->positionX += (direction == Right ? (distance - alignment) : -1 * (distance - alignment));
				if (alignment > 0) {
					this->moveDirection = (this->moveDirection == Right ? Left : Right);
				}
			}
		}
		else {
			this->positionY += (2 * distance - alignIfCollisionOccursDuringVerticalMovement(Down, 2 * distance, this, world));
			this->positionX += (direction == Right ? 1 : -1) * (1 - alignIfCollisionOccursDuringMovement(direction, distance, this, world));
		}
	}
	++this->stepsCounter;
}

