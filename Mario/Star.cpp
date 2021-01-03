#include "Star.h"

#include <string>
#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "SoundController.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 8> Star::starImages;

int Star::computeImageIndex() const
{
	int baseIndex = (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 4);
	return baseIndex + (stepsCounter % 4);
}

void Star::makeVerticalMove(World &world)
{
	int alignment = computeHorizontalAlignment(movement.getDirection(), movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;
	if (movement.getDirection() == Direction::Left) {
		distance *= -1;
	}
	position.setX(position.getX() + distance);

	if (alignment > 0) {
		movement.setDirection(movement.getDirection() == Direction::Right ? Direction::Left : Direction::Right);
	}
}

void Star::makeHorizontalMove(World &world)
{
	int alignment = computeVerticalAlignment(movement.getVerticalDirection(), movement.getVerticalSpeed(), 
		*this, world);
	int verticalDistance = movement.getVerticalSpeed() - alignment;
	if (movement.getVerticalDirection() == Direction::Up) {
		verticalDistance *= -1;
		++stepsUp;
	}
	position.setY(position.getY() + verticalDistance);

	if (alignment > 0) {
		movement.setVerticalDirection(
			movement.getVerticalDirection() == Direction::Down ? Direction::Up : Direction::Down);

		stepsUp = 0;
	}
	else if (stepsUp % 64 == 0 && movement.getVerticalDirection() == Direction::Up) {
		movement.setVerticalDirection(Direction::Down);
		stepsUp = 0;
	}
}

Star::Star(Position position)
{
	size = Size(28, 32);
	movement = Movement(1, 1, Direction::Right, Direction::Up);
	this->position = position;
	stepsUp = 0;
	stepsCounter = 0;
	growCounter = 90;
}

void Star::loadStarImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < starImages.size(); ++i) {
		std::string filename = "./img/bonus_imgs/star";
		filename += std::to_string(i + 1);
		filename += ".png";
		starImages[i] = loadPNG(filename, display);
	}
}

void Star::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* starImg = starImages[computeImageIndex()];
		drawSurface(display, starImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Star::move(World &world)
{
	if (growCounter) {
		grow();
	}
	else {
		makeVerticalMove(world);
		makeHorizontalMove(world);
	}
	++stepsCounter;
}

void Star::giveBonus(Player &player)
{
	if (player.isSmall()) {
		player.setCurrentAnimation(PlayerAnimation::ImmortalSmall);
	}
	else {
		player.setCurrentAnimation(PlayerAnimation::Immortal);
	}

	SoundController::playStarMusic();
}