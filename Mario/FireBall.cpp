#include "FireBall.h"

SDL_Surface* FireBall::fireBallImages[4] = { nullptr };

void FireBall::computeModelIndex()
{
	this->changeModelCounter++;
	if (this->changeModelCounter % 8 == 0) {
		this->modelIndex++;
		if (this->modelIndex == 4) {
			this->modelIndex = 0;
		}
	}
}

FireBall::FireBall() {}

FireBall::FireBall(Position* position, Direction direction)
{
	this->size = new Size(16, 16);
	this->position = position;
	this->moveDirection = direction;
	this->verticalDirection = Down;
	this->changeModelCounter = 0;
	this->stepsUp = 0;
	this->modelIndex = 0;
	this->stop = false;
}

bool FireBall::shouldBeRemoved()
{
	return this->stop;
}

void FireBall::loadFireBallImages(SDL_Surface* screen)
{
	for (int i = 0; i < 4; ++i) {
		std::string filename = "./img/fireball";
		filename += std::to_string(i + 1);
		filename += ".png";
		fireBallImages[i] = loadPNG(filename, screen);
	}
}

void FireBall::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* fireballImg = nullptr;
	fireballImg = fireBallImages[this->modelIndex];
	drawSurface(screen, fireballImg, this->position->getX() - beginningOfCamera, this->position->getY());
}

void FireBall::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (!this->stop) {
		int alignment = getAlignmentIfCollisionOccursDuringMovement(this->moveDirection, 2 * distance, this, world);
		int realDistance = (this->moveDirection == Right ? 1 : -1) * (2 * distance - alignment);
		this->position->setX(this->position->getX() + realDistance);

		if (alignment > 0) {
			this->stop = true;
			SoundController::playBlockHittedEffect();
		}

		alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(this->verticalDirection, distance, this, world);
		int realVerticalDistance = (this->verticalDirection == Down ? 1 : -1) * (distance - alignment);
		this->position->setY(this->position->getY() + realVerticalDistance);

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

