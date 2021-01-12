#include "JumpingFish.h"

#include "SoundController.h"
#include "Player.h"
#include "World.h"
#include "SDL_Utility.h"
#include "CollisionHandling.h"


std::array<SDL_Surface*, 4> JumpingFish::fishImages;

void JumpingFish::changeParametersDuringJump()
{
	if (moveCounter == 200 || moveCounter == 300) {
		movement.setVerticalSpeed(2);
	}
	else if (moveCounter == 240 || moveCounter == 280) {
		movement.setVerticalSpeed(1);
	}
	else if (moveCounter == 260) {
		movement.setVerticalSpeed(0);
		movement.setVerticalDirection(Direction::Down);
	}
	else if (moveCounter == 340) {
		movement.setVerticalSpeed(3);
	}
}

void JumpingFish::jump()
{
	movingFlag = true;
	if (moveCounter % 2 == 0) {
		int distance = movement.getSpeed() * (direction == Direction::Left ? -1 : 1);
		position.setX(position.getX() + distance);

		int verticalDistance = movement.getVerticalSpeed() * (movement.getVerticalDirection() == Direction::Up ? -1 : 1);
		position.setY(position.getY() + verticalDistance);

		changeParametersDuringJump();

		changeModel();
	}
}

void JumpingFish::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 20 == 0) {
		model = (model == 1 ? 2 : 1);
		changeModelCounter = 0;
	}
}

int JumpingFish::computeImageIndex() const
{
	int baseIndex = 2 * (direction == Direction::Left);
	return baseIndex + (model - 1);
}

JumpingFish::JumpingFish(Position position, Direction direction)
{
	this->position = position;
	this->direction = direction;
	moveCounter = 0;
	changeModelCounter = 0;
	healthPoints = 1;
	movingFlag = false;
	model = 1;
	movement = Movement(1, 3, Direction::None, Direction::Up);
	size = Size(32, 32);
}

void JumpingFish::loadFishImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < fishImages.size(); ++i) {
		std::string filename = "./img/npc_imgs/fish";
		filename += std::to_string(i + 1);
		filename += ".png";
		fishImages[i] = loadPNG(filename, display);
	}
}

int JumpingFish::getPointsForCrushing() const
{
	return 200;
}

bool JumpingFish::shouldStartMoving(const Player &player) const
{
	if (movement.getDirection() == Direction::None) {
		if (direction == Direction::Right) {
			return (player.getX() > position.getX() && (position.getX() > player.getX() - 40));
		}
		else {
			return (player.getX() < position.getX() && (position.getX() < player.getX() + 120));
		}
	}

	return false;
}

void JumpingFish::startMoving()
{
	movement.setDirection(direction);
}

void JumpingFish::crush(World &world, int index)
{
	world.addDestroyedFish(position, direction);
	world.deleteNpc(index);

	SoundController::playEnemyDestroyedEffect();
}

void JumpingFish::destroy(World &world, Direction direction)
{
	world.addDestroyedFish(position, direction);
}

void JumpingFish::move(World &world)
{
	++moveCounter;
	if (movement.getDirection() == Direction::None && !movingFlag) {
		moveCounter = 0;
	}
	else {
		jump();
	}
}

void JumpingFish::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* fishImg = fishImages[computeImageIndex()];
		drawSurface(display, fishImg, position.getX() - beginningOfCamera, position.getY());
	}
}