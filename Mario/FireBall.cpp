#include "FireBall.h"

SDL_Surface* FireBall::fireBallImages[4] = { nullptr };

void FireBall::computeModelIndex()
{
	changeModelCounter++;
	if (changeModelCounter % 8 == 0) {
		modelIndex++;
		if (modelIndex == 4) {
			modelIndex = 0;
		}
	}
}

FireBall::FireBall() {}

FireBall::FireBall(Position* position, Direction direction)
{
	size = new Size(16, 16);
	this->position = position;
	moveDirection = direction;
	verticalDirection = Down;
	changeModelCounter = 0;
	stepsUp = 0;
	modelIndex = 0;
	stop = false;
}

bool FireBall::shouldBeRemoved()
{
	return stop;
}

void FireBall::loadFireBallImages(SDL_Surface* display)
{
	for (int i = 0; i < 4; ++i) {
		std::string filename = "./img/fireball";
		filename += std::to_string(i + 1);
		filename += ".png";
		fireBallImages[i] = loadPNG(filename, display);
	}
}

void FireBall::draw(SDL_Surface* display, int beginningOfCamera)
{
	SDL_Surface* fireballImg = nullptr;
	fireballImg = fireBallImages[modelIndex];
	drawSurface(display, fireballImg, position->getX() - beginningOfCamera, position->getY());
}

void FireBall::move(Direction direction, int distance, World& world, Screen* mainScreen)
{
	if (!stop) {
		int alignment = getAlignmentIfCollisionOccursDuringMovement(moveDirection, 2 * distance, this, world);
		int realDistance = (moveDirection == Right ? 1 : -1) * (2 * distance - alignment);
		position->setX(position->getX() + realDistance);

		if (alignment > 0) {
			stop = true;
			SoundController::playBlockHittedEffect();
		}

		alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(verticalDirection, distance, this, world);
		int realVerticalDistance = (verticalDirection == Down ? 1 : -1) * (distance - alignment);
		position->setY(position->getY() + realVerticalDistance);

		computeModelIndex();

		if (verticalDirection == Up) {
			++stepsUp;
		}

		if (alignment > 0) {
			verticalDirection = (verticalDirection == Down ? Up : Down);
			stepsUp = 0;
		}
		else if (stepsUp % 48 == 0 && verticalDirection == Up) {
			verticalDirection = Down;
			stepsUp = 0;
		}
	}
}

