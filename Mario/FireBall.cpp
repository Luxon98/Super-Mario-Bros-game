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
	movement = new Movement(1, direction);
	this->position = position;
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

void FireBall::move(World& world)
{
	if (!stop) {
		int alignment = getAlignmentIfCollisionOccursDuringMovement(movement->getDirection(), 2 * movement->getSpeed(), this, world);
		int distance = (movement->getDirection() == Right ? 1 : -1) * (2 * movement->getSpeed() - alignment);
		position->setX(position->getX() + distance);

		if (alignment > 0) {
			stop = true;
			SoundController::playBlockHittedEffect();
		}

		alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(verticalDirection, movement->getSpeed(), this, world);
		int verticalDistance = (verticalDirection == Down ? 1 : -1) * (movement->getSpeed() - alignment);
		position->setY(position->getY() + verticalDistance);

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

