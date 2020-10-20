#include "Mushroom.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 3> Mushroom::mushroomImages;

int Mushroom::computeImageIndex() const
{
	if (oneUp) {
		return (1 + (World::LAYOUT_STYLE == LayoutStyle::Underground));
	}
	
	return 0;
}

void Mushroom::makeMoveUp(World &world)
{
	int alignment = computeVerticalAlignment(Direction::Down, movement.getVerticalSpeed(), *this, world);
	int verticalDistance = movement.getVerticalSpeed() - alignment;
	position.setY(position.getY() - verticalDistance);
}

Mushroom::Mushroom(Position position, bool oneUp)
{
	size = Size(32, 32);
	movement = Movement(1, 2, Direction::Right);
	this->position = position;
	stepsCounter = 0;
	this->oneUp = oneUp;
	stepsUp = 0;
	growCounter = 96;
}

void Mushroom::loadMushroomImages(SDL_Surface* display)
{
	mushroomImages[0] = loadPNG("./img/mushroom_red.png", display);
	mushroomImages[1] = loadPNG("./img/mushroom_green.png", display);
	mushroomImages[2] = loadPNG("./img/mushroom_brown_blue.png", display);
}

bool Mushroom::isOneUp() const
{
	return oneUp;
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

void Mushroom::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 75 && position.getX() < endOfCamera + 75) {
		SDL_Surface* mushroomImg = nullptr;
		mushroomImg = mushroomImages[computeImageIndex()];
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
			--stepsUp;
			makeHorizontalMove(world);
		}
		else {
			if (isCharacterStandingOnSomething(*this, world)) {
				makeHorizontalMove(world);
			}
			else {
				makeDiagonalMove(world);
			}
		}
	}
	++stepsCounter;
}

