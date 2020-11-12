#include "MovingPlatform.h"

#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "CollisionHandling.h"


std::array<SDL_Surface*, 2> MovingPlatform::platformImages;

bool MovingPlatform::shouldForcePlayerMovement() const
{
	if (playerForceMovementChecker && (platformType == PlatformType::MovingHorizontallyPlatform 
		|| platformType == PlatformType::MovingVerticallyPlatform || platformType == PlatformType::SmallPlatform)) {
		return true;
	}
	else if (platformType == PlatformType::MovingDownPlatform || platformType == PlatformType::MovingUpPlatform) {
		return true;
	}

	return false;
}

Direction MovingPlatform::getDirectionFromType() const
{
	if (platformType == PlatformType::MovingUpPlatform || platformType == PlatformType::MovingVerticallyPlatform) {
		return Direction::Up;
	}
	else if (platformType == PlatformType::MovingDownPlatform) {
		return Direction::Down;
	}
	else if (platformType == PlatformType::MovingHorizontallyPlatform || platformType == PlatformType::SmallPlatform) {
		return Direction::Left;
	}
	else {
		return Direction::None;
	}
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

MovingPlatform::MovingPlatform(Position position, PlatformType platformType)
{
	this->position = position;
	this->platformType = platformType;
	direction = getDirectionFromType();
	playerForceMovementChecker = false;
	slideCounter = 0;

	if (platformType != PlatformType::SmallPlatform) {
		size = Size(96, 16);
	}
	else {
		size = Size(48, 16);
	}
}

void MovingPlatform::loadPlatformImage(SDL_Surface* display)
{
	platformImages[0] = loadPNG("./img/platform.png", display);
	platformImages[1] = loadPNG("./img/small_platform.png", display);
}

Direction MovingPlatform::getDirection() const
{
	return direction;
}

void MovingPlatform::setDirection(Direction direction)
{
	this->direction = direction;
}

void MovingPlatform::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 120 && position.getX() < endOfCamera + 120) {
		int index = (platformType != PlatformType::SmallPlatform ? 0 : 1);
		drawSurface(display, platformImages[index], position.getX() - beginningOfCamera, position.getY());
	}
}

void MovingPlatform::slide(Player &player)
{
	if (isPlayerStandingOnThisPlatform(player, *this) && shouldForcePlayerMovement()) {
		player.forceMovement(direction);
	}

	if (platformType == PlatformType::MovingVerticallyPlatform) {
		slideUpDown();
	}
	else {
		if (platformType == PlatformType::MovingHorizontallyPlatform || platformType == PlatformType::SmallPlatform) {
			slideHorizontally();
		}
		else if (platformType == PlatformType::MovingUpPlatform) {
			slideUp();
		}
		else if (platformType == PlatformType::MovingDownPlatform) {
			slideDown();
		}
	}
}
