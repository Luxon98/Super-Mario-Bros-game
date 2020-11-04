#include "MovingPlatform.h"

#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "CollisionHandling.h"


SDL_Surface* MovingPlatform::platformImage = nullptr;

bool MovingPlatform::shouldForcePlayerMovement() const
{
	if (playerForceMovementChecker && (upDownFlag || direction == Direction::Left || direction == Direction::Right)) {
		return true;
	}
	else if (!upDownFlag && (direction == Direction::Up || direction == Direction::Down)) {
		return true;
	}

	return false;
}

void MovingPlatform::slideDown()
{
	position.setY(position.getY() + 1);
	if (position.getY() == 500) {
		position.setY(-20);
	}
}

void MovingPlatform::slideUp()
{
	position.setY(position.getY() - 1);
	if (position.getY() == -20) {
		position.setY(500);
	}
}

void MovingPlatform::slideUpDown()
{
	++slideCounter;
	if ((slideCounter > 20 && slideCounter <= 135) || slideCounter & 1) {
		int distance = (direction == Direction::Down ? 1 : -1);
		position.setY(position.getY() + distance);
		playerForceMovementChecker = true;
	}
	else {
		playerForceMovementChecker = false;
	}

	if (slideCounter == 155) {
		direction = (direction == Direction::Up ? Direction::Down : Direction::Up);
		slideCounter = 0;
	}
	
}

void MovingPlatform::slideHorizontally()
{
	++slideCounter;
	if ((slideCounter > 20 && slideCounter <= 125) || slideCounter & 1) {
		int distance = (direction == Direction::Left ? -1 : 1);
		position.setX(position.getX() + distance);
		playerForceMovementChecker = true;
	}
	else {
		playerForceMovementChecker = false;
	}

	if (slideCounter == 145) {
		direction = (direction == Direction::Left ? Direction::Right : Direction::Left);
		slideCounter = 0;
	}
}

MovingPlatform::MovingPlatform(Position position, Direction direction, bool upDownFlag)
{
	this->position = position;
	this->direction = direction;
	this->upDownFlag = upDownFlag;
	playerForceMovementChecker = false;
	size = Size(96, 16);
	slideCounter = 0;
}

void MovingPlatform::loadPlatformImage(SDL_Surface* display)
{
	platformImage = loadPNG("./img/platform.png", display);
}

Direction MovingPlatform::getDirection() const
{
	return direction;
}

void MovingPlatform::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 120 && position.getX() < endOfCamera + 120) {
		drawSurface(display, platformImage, position.getX() - beginningOfCamera, position.getY());
	}
}

void MovingPlatform::slide(Player &player)
{
	if (isPlayerStandingOnThisPlatform(player, *this) && shouldForcePlayerMovement()) {
		player.forceMovement(direction);
	}

	if (upDownFlag) {
		slideUpDown();
	}
	else {
		if (direction == Direction::Right || direction == Direction::Left) {
			slideHorizontally();
		}
		else if (direction == Direction::Up) {
			slideUp();
		}
		else if (direction == Direction::Down) {
			slideDown();
		}
	}
}
