#include "Star.h"

#include <string>
#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 4> Star::starImages;

void Star::makeVerticalMove(World &world)
{
	int alignment = getAlignmentForHorizontalMove(movement.getDirection(), movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;
	if (movement.getDirection() == Left) {
		distance *= -1;
	}
	position.setX(position.getX() + distance);

	if (alignment > 0) {
		movement.setDirection(movement.getDirection() == Right ? Left : Right);
	}
}

void Star::makeHorizontalMove(World &world)
{
	int alignment = getAlignmentForVerticalMove(movement.getVerticalDirection(), movement.getVerticalSpeed(), 
		*this, world);
	int verticalDistance = movement.getVerticalSpeed() - alignment;
	if (movement.getVerticalDirection() == Up) {
		verticalDistance *= -1;
	}
	position.setY(position.getY() + verticalDistance);

	if (movement.getVerticalDirection() == Up) {
		stepsUp++;
	}

	if (alignment > 0) {
		movement.setVerticalDirection(movement.getVerticalDirection() == Down ? Up : Down);
		stepsUp = 0;
	}
	else if (stepsUp % 64 == 0 && movement.getVerticalDirection() == Up) {
		movement.setVerticalDirection(Down);
		stepsUp = 0;
	}
}

Star::Star(Position position)
{
	size = Size(28, 32);
	this->position = position;
	movement = Movement(2, 1, Right, Up);
	stepsCounter = 0;
	growCounter = 90;
}

void Star::loadStarImages(SDL_Surface* display)
{
	for (unsigned int i = 0; i < starImages.size(); ++i) {
		std::string filename = "./img/star";
		filename += std::to_string(i + 1);
		filename += ".png";
		starImages[i] = loadPNG(filename, display);
	}
}

void Star::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position.getX() > beginningOfCamera - 90 && position.getX() < endOfCamera + 90) {
		SDL_Surface* starImg = nullptr;
		starImg = starImages[stepsCounter % 4];
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
	stepsCounter++;
}

