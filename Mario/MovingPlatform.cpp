#include "MovingPlatform.h"

#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "CollisionHandling.h"


SDL_Surface* MovingPlatform::platformImage = nullptr;

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
	if (slideCounter < 125) {
		int distance = (direction == Direction::Down ? 1 : -1);
		position.setY(position.getY() + distance);
	}
	else if (slideCounter == 125) {
		direction = (direction == Direction::Up ? Direction::Down : Direction::Up);
		slideCounter = 0;
	}
}

void MovingPlatform::slideHorizontally()
{
	++slideCounter;
	int distance = (direction == Direction::Left ? -1 : 1);
	position.setX(position.getX() + distance);

	if (slideCounter == 125) {
		direction = (direction == Direction::Left ? Direction::Right : Direction::Left);
		slideCounter = 0;
	}
}

MovingPlatform::MovingPlatform(Position position, Direction direction, bool upDownChanger)
{
	this->position = position;
	this->direction = direction;
	this->upDownChanger = upDownChanger;
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
	if (isPlayerStandingOnThisPlatform(player, *this)) {
		player.forceMovement(direction);
	}

	if (upDownChanger) {
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
