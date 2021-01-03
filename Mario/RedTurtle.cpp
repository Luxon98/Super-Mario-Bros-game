#include "RedTurtle.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"
#include "SoundController.h"


std::array<SDL_Surface*, 6> RedTurtle::redTurtleImages;

int RedTurtle::computeImageIndex() const
{
	int baseIndex;
	if (flying) {
		baseIndex = 4;
	}
	else {
		baseIndex = (movement.getDirection() == Direction::Left ? 0 : 2);
	}

	return baseIndex + (model - 1);
}

void RedTurtle::fly(World &world)
{
	++stepsCounter;
	if (stepsCounter % 3 == 0) {
		int alignment = computeVerticalAlignment(movement.getVerticalDirection(), 
			movement.getVerticalSpeed(), *this, world);

		int verticalDistance = movement.getVerticalSpeed() - alignment;
		
		if (movement.getVerticalDirection() == Direction::Up) {
			verticalDistance *= -1;
		}
		position.setY(position.getY() + verticalDistance);
	}

	if (stepsCounter == 180) {
		movement.setVerticalDirection(
			movement.getVerticalDirection() == Direction::Down ? Direction::Up : Direction::Down);

		stepsCounter = 0;
	}
	changeModel();
}

void RedTurtle::patrol(World &world)
{
	++stepsCounter;
	if (stepsCounter % 3 == 0) {
		if (!isCharacterStandingOnSomething(*this, world)) {
			moveDiagonally(world);
		}
		else {
			moveHorizontally(world);
			changeModel();
		}
	}

	if (stepsCounter == 480) {
		if (isCharacterStandingOnSomething(*this, world)) {
			movement.setDirection(movement.getDirection() == Direction::Right ? Direction::Left : Direction::Right);
		}
		stepsCounter = 0;
	}
}

void RedTurtle::changeModel()
{
	++changeModelCounter;
	if (flying && changeModelCounter % 90 == 0) {
		model += (model & 1 ? 1 : -1);
	}
	else if (!flying && changeModelCounter % 30 == 0) {
		model += (model & 1 ? 1 : -1);
	}
}

RedTurtle::RedTurtle(Position position, bool flying)
{
	size = Size(26, 44);
	movement = Movement(1, 3, Direction::Left);
	this->position = position;
	this->flying = flying;
	healthPoints = 1;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;

	if (flying) {
		movement.setVerticalDirection(Direction::Up);
		movement.setVerticalSpeed(2);
	}
}

void RedTurtle::loadTurtleImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < redTurtleImages.size(); ++i) {
		std::string filename = "./img/npc_imgs/red_turtle";
		filename += std::to_string(i + 1);
		filename += ".png";
		redTurtleImages[i] = loadPNG(filename, display);
	}
}

bool RedTurtle::isResistantToCollisionWithShell() const
{
	return false;
}

bool RedTurtle::isResistantToCollisionWithBlock() const
{
	return false;
}

bool RedTurtle::isFlying() const
{
	return flying;
}

void RedTurtle::loseFlyingAbility()
{
	flying = false;
	stepsCounter = 0;
	movement.setVerticalDirection(Direction::None);
	movement.setDirection(Direction::Left);
	movement.setVerticalSpeed(3);
	position.setY(position.getY() + 10);
}

void RedTurtle::setMoveDirection(Direction direction)
{
	movement.setDirection(direction);
}

void RedTurtle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* redTurtleImg = redTurtleImages[computeImageIndex()];
		drawSurface(display, redTurtleImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void RedTurtle::move(World &world)
{
	if (flying) {
		fly(world);
	}
	else {
		if (movement.getDirection() != Direction::None) {
			patrol(world);
		}
	}
}

void RedTurtle::crush(World &world, int index)
{
	if (flying) {
		loseFlyingAbility();
	}
	else {
		world.addShell(Position(position.getX(), position.getY() + 6), true);
		world.deleteNpc(index);
	}

	SoundController::playEnemyDestroyedEffect();
}

void RedTurtle::destroy(World &world, Direction direction)
{
	world.addDestroyedTurtle(position, direction, true);
}