#include "Mushroom.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> Mushroom::mushroomImages;

void Mushroom::makeMoveUp(World &world)
{
	int alignment = getAlignmentForVerticalMove(Down, movement.getVerticalSpeed(), *this, world);
	int verticalDistance = movement.getVerticalSpeed() - alignment;
	position.setY(position.getY() - verticalDistance);
}

Mushroom::Mushroom(Position position, bool greenColor)
{
	size = Size(32, 32);
	movement = Movement(1, 2, Right);
	this->position = position;
	stepsCounter = 0;
	this->greenColor = greenColor;
	stepsUp = 0;
	growCounter = 96;
}

bool Mushroom::isGreen()
{
	return greenColor;
}

void Mushroom::decreasePositionY()
{
	position.setY(position.getY() - 3);
}

void Mushroom::setStepsUp(int stepsUp)
{
	if (this->stepsUp == 0) {
		this->stepsUp = stepsUp;
	}
}

void Mushroom::loadMushroomImages(SDL_Surface* display)
{
	mushroomImages[0] = loadPNG("./img/mushroom_green.png", display);
	mushroomImages[1] = loadPNG("./img/mushroom_red.png", display);
}

void Mushroom::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position.getX() > beginningOfCamera - 75 && position.getX() < endOfCamera + 75) {
		SDL_Surface* mushroomImg = nullptr;
		mushroomImg = mushroomImages[!greenColor];
		drawSurface(display, mushroomImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Mushroom::move(World &world)
{
	if (growCounter) {
		grow();
	}
	else if (stepsCounter & 1) {
		if (stepsUp > 0) {
			makeMoveUp(world);
			stepsUp--;
			makeHorizontalMove(world);
		}
		else {
			if (isCharacterStandingOnTheBlock(*this, world)) {
				makeHorizontalMove(world);
			}
			else {
				makeDiagonalMove(world);
			}
		}
	}
	stepsCounter++;
}

