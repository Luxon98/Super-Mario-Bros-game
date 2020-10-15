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

void MovingPlatform::slideHorizontally()
{
	++slideCounter;
	int distance = (direction == Direction::Left ? -1 : 1);
	position.setX(position.getX() + distance);

	if (slideCounter == 500) {
		direction = (direction == Direction::Left ? Direction::Right : Direction::Left);
		slideCounter = 0;
	}
}

MovingPlatform::MovingPlatform(Position position, Direction direction)
{
	this->position = position;
	this->direction = direction;
	size = Size(96, 16);
	slideCounter = 0;
}

Direction MovingPlatform::getDirection()
{
	return direction;
}

void MovingPlatform::loadPlatformImage(SDL_Surface* display)
{
	platformImage = loadPNG("./img/platform.png", display);
}

void MovingPlatform::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 120 && position.getX() < endOfCamera + 120) {
		drawSurface(display, platformImage, position.getX() - beginningOfCamera, position.getY());
	}
}

void MovingPlatform::slide(Player &player)
{
	if (direction == Direction::Right || direction == Direction::Left) {
		slideHorizontally();
	}	
	else if (direction == Direction::Up) {
		slideUp();
	}
	else if (direction == Direction::Down) {
		slideDown();
	}

	if (isPlayerStandingOnThisPlatform(player, *this)) {
		player.forceMovement(direction);
	}
}
