#include "FireBall.h"

SDL_Surface* FireBall::fireBallImages[4] = { nullptr };

void FireBall::computeModelIndex() {
	++this->counter;
	if (this->counter % 8 == 0) {
		++this->modelIndex;

		if (this->modelIndex == 4) {
			this->modelIndex = 0;
		}
	}
}

FireBall::FireBall() {}

FireBall::FireBall(int x, int y, Direction direction) {
	this->width = 16;
	this->height = 16;
	this->positionX = x;
	this->positionY = y;
	this->moveDirection = direction;
	this->verticalDirection = Down;
	this->counter = 0;
	this->stepsUp = 0;
	this->modelIndex = 0;
	this->stop = false;
}

bool FireBall::shouldBeRemoved() {
	return this->stop;
}

void FireBall::loadFireBallImages(SDL_Surface* screen) {
	for (int i = 0; i < 4; ++i) {
		std::string filename = "./img/fireball";
		filename += std::to_string(i + 1);
		filename += ".png";
		fireBallImages[i] = loadPNG(filename, screen);
	}
}

void FireBall::draw(SDL_Surface* screen, int beginningOfCamera) {
	SDL_Surface* fireballImg = nullptr;
	fireballImg = fireBallImages[this->modelIndex];
	drawSurface(screen, fireballImg, this->positionX - beginningOfCamera, this->positionY);
}

void FireBall::move(Direction direction, int distance, World& world, Screen* mainScreen) {
	if (!this->stop) {
		int alignment = alignIfCollisionOccursDuringMovement(this->moveDirection, 2 * distance, this, world);
		this->positionX += (this->moveDirection == Right ? 1 : -1) * (2 * distance - alignment);

		if (alignment > 0) {
			this->stop = true;
			SoundController::playBlockHittedEffect();
		}

		alignment = alignIfCollisionOccursDuringVerticalMovement(this->verticalDirection, distance, this, world);
		this->positionY += (this->verticalDirection == Down ? 1 : -1) * (distance - alignment);

		this->computeModelIndex();

		if (this->verticalDirection == Up) {
			++this->stepsUp;
		}

		if (alignment > 0) {
			this->verticalDirection = (this->verticalDirection == Down ? Up : Down);
			this->stepsUp = 0;
		}
		else if (this->stepsUp % 48 == 0 && this->verticalDirection == Up) {
			this->verticalDirection = Down;
			this->stepsUp = 0;
		}
	}
}

