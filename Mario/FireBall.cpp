#include "FireBall.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SoundController.h"
#include "SDL_Utility.h"


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

void FireBall::makeVerticalMove(World& world)
{
	int alignment = getAlignmentForHorizontalMove(movement->getDirection(), movement->getSpeed(), this, world);
	int distance = movement->getSpeed() - alignment;
	if (movement->getDirection() == Left) {
		distance *= -1;
	}
	position->setX(position->getX() + distance);

	if (alignment > 0) {
		stop = true;
		SoundController::playBlockHittedEffect();
	}
}

void FireBall::makeHorizontalMove(World& world)
{
	int alignment = getAlignmentForVerticalMove(movement->getVerticalDirection(), movement->getVerticalSpeed(), this, world);
	int verticalDistance = movement->getVerticalSpeed() - alignment;
	if (movement->getVerticalDirection() == Up) {
		verticalDistance *= -1;
	}
	position->setY(position->getY() + verticalDistance);

	computeModelIndex();

	if (movement->getVerticalDirection() == Up) {
		stepsUp++;
	}

	if (alignment > 0) {
		movement->setVerticalDirection(movement->getVerticalDirection() == Down ? Up : Down);
		stepsUp = 0;
	}
	else if (stepsUp % 20 == 0 && movement->getVerticalDirection() == Up) {
		movement->setVerticalDirection(Down);
		stepsUp = 0;
	}
}

FireBall::FireBall() {}

FireBall::FireBall(Position* position, Direction direction)
{
	size = new Size(16, 16);
	movement = new Movement(3, 2, direction, Down);
	this->position = position;
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

void FireBall::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position->getX() > beginningOfCamera - 120 && position->getX() < endOfCamera + 120) {
		SDL_Surface* fireballImg = nullptr;
		fireballImg = fireBallImages[modelIndex];
		drawSurface(display, fireballImg, position->getX() - beginningOfCamera, position->getY());
	}
}

void FireBall::move(World& world)
{
	if (!stop) {
		makeVerticalMove(world);
		makeHorizontalMove(world);
	}
}

