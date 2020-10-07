#include "Turtle.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 8> Turtle::turtleImages;

int Turtle::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld) {
		return 0;
	}
	else {
		return 4;
	}
}

void Turtle::chooseModel()
{
	++changeModelCounter;
	if (changeModelCounter % 30 == 0) {
		model += (model & 1 ? 1 : -1);
	}
}

Turtle::Turtle(Position position)
{
	size = Size(26, 38);
	movement = Movement(1, 3, Direction::None);
	this->position = position;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;
}

void Turtle::setMoveDirection(Direction direction)
{
	movement.setDirection(direction);
}

void Turtle::loadTurtleImages(SDL_Surface* display)
{
	turtleImages[0] = loadPNG("./img/turtle_left1.png", display);
	turtleImages[1] = loadPNG("./img/turtle_left2.png", display);
	turtleImages[2] = loadPNG("./img/turtle_right1.png", display);
	turtleImages[3] = loadPNG("./img/turtle_right2.png", display);
	turtleImages[4] = loadPNG("./img/turtle_left3.png", display);
	turtleImages[5] = loadPNG("./img/turtle_left4.png", display);
	turtleImages[6] = loadPNG("./img/turtle_right3.png", display);
	turtleImages[7] = loadPNG("./img/turtle_right4.png", display);
}

void Turtle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		SDL_Surface* turtleImg = nullptr;
		int baseIndex = computeBaseIndex();
		turtleImg = turtleImages[baseIndex + (model - 1)];
		drawSurface(display, turtleImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Turtle::move(World &world)
{
	if (movement.getDirection() != Direction::None && stepsCounter % 3 == 0) {
		if (isCharacterStandingOnTheBlock(*this, world)) {
			makeHorizontalMove(world);
		}
		else {
			makeDiagonalMove(world);
		}
		chooseModel();
	}
	++stepsCounter;
}

