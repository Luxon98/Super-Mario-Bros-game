#include "Turtle.h"

#include "SoundController.h"
#include "Player.h"
#include "World.h"
#include "LayoutStyle.h"
#include "SDL_Utility.h"
#include "CollisionHandling.h"


std::array<SDL_Surface*, 8> Turtle::turtleImages;

void Turtle::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 30 == 0) {
		model += (model & 1 ? 1 : -1);
	}
}

int Turtle::computeImageIndex() const
{
	int baseIndex = (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 4);
	if (movement.getDirection() == Direction::Right) {
		baseIndex += 2;
	}

	return baseIndex + (model - 1);
}

Turtle::Turtle(Position position)
{
	this->position = position;
	moveCounter = 0;
	changeModelCounter = 0;
	healthPoints = 1;
	model = 1;
	movement = Movement(1, 3, Direction::None, Direction::None);
	size = Size(26, 44);
}

void Turtle::loadTurtleImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < turtleImages.size(); ++i) {
		std::string filename = "./img/npc_imgs/turtle";
		filename += std::to_string(i + 1);
		filename += ".png";
		turtleImages[i] = loadPNG(filename, display);
	}
}

bool Turtle::shouldStartMoving(const Player &player) const
{
	if (movement.getDirection() == Direction::None && position.getX() < player.getX() + 480) {
		return true;
	}

	return false;
}

bool Turtle::isResistantToCollisionWithShell() const
{
	return false;
}

bool Turtle::isResistantToCollisionWithBlock() const
{
	return false;
}

void Turtle::startMoving()
{
	movement.setDirection(Direction::Left);
}

void Turtle::crush(World &world, int index)
{
	world.addShell(Position(position.getX(), position.getY() + 6));
	world.deleteNpc(index);

	SoundController::playEnemyDestroyedEffect();
}

void Turtle::destroy(World &world, Direction direction)
{
	world.addDestroyedTurtle(position, direction);
}

void Turtle::move(World &world)
{
	if (movement.getDirection() != Direction::None && moveCounter % 3 == 0) {
		if (isCharacterStandingOnSomething(*this, world)) {
			moveHorizontally(world);
			changeModel();
		}
		else {
			moveDiagonally(world);
		}
	}
	++moveCounter;
}

void Turtle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* turtleImg = turtleImages[computeImageIndex()];
		drawSurface(display, turtleImg, position.getX() - beginningOfCamera, position.getY());
	}
}