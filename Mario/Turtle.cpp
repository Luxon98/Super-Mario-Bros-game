#include "Turtle.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 4> Turtle::turtleImages;

void Turtle::chooseModel()
{
	changeModelCounter++;
	if (changeModelCounter % 30 == 0) {
		model += (model & 1 ? 1 : -1);
	}
}

Turtle::Turtle() {}

Turtle::Turtle(Position position)
{
	size = Size(26, 38);
	movement = Movement(1, 2, None);
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
	turtleImages[2] = loadPNG("./img/turtle_rigth1.png", display);
	turtleImages[3] = loadPNG("./img/turtle_right2.png", display);
}

void Turtle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		SDL_Surface* turtleImg = nullptr;
		turtleImg = turtleImages[model - 1];
		drawSurface(display, turtleImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Turtle::move(World& world)
{
	if (movement.getDirection() != None && stepsCounter % 3 == 0) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			makeHorizontalMove(world);
		}
		else {
			makeDiagonalMove(world);
		}
		chooseModel();
	}
	stepsCounter++;
}

