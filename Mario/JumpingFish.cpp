#include "JumpingFish.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"
#include "World.h"
#include "SoundController.h"


std::array<SDL_Surface*, 4> JumpingFish::fishImages;

int JumpingFish::computeImageIndex() const
{
	int baseIndex = 2 * directionFlag;
	return baseIndex + (model - 1);
}

void JumpingFish::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 20 == 0) {
		model = (model == 1 ? 2 : 1);
		changeModelCounter = 0;
	}
}

JumpingFish::JumpingFish(Position position, bool directionFlag)
{
	size = Size(32, 32);
	movement = Movement(1, 3, Direction::None, Direction::Up);
	this->position = position;
	this->directionFlag = directionFlag;
	movingFlag = false;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;
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

bool JumpingFish::isGoingLeft() const
{
	return directionFlag;
}

void JumpingFish::setMoveDirection()
{
	movement.setDirection(directionFlag ? Direction::Right : Direction::Left);
}

void JumpingFish::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 90 && position.getX() < endOfCamera + 90) {
		SDL_Surface* fishImg = fishImages[computeImageIndex()];
		drawSurface(display, fishImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void JumpingFish::move(World &world)
{
	// bad-written code
	// it will be refactored
	++stepsCounter;
	if (movement.getDirection() == Direction::None && !movingFlag) {
		stepsCounter = 0;
	}
	else {
		movingFlag = true;
		if (stepsCounter % 2 == 0) {
			int distance = movement.getSpeed() * (directionFlag ? -1 : 1);
			position.setX(position.getX() + distance);

			int verticalDistance = movement.getVerticalSpeed() * (movement.getVerticalDirection() == Direction::Up ? -1 : 1);
			position.setY(position.getY() + verticalDistance);

			if (stepsCounter == 200) {
				movement.setVerticalSpeed(2);
			}
			else if (stepsCounter == 240) {
				movement.setVerticalSpeed(1);
			}
			else if (stepsCounter == 260) {
				movement.setVerticalSpeed(0);
				movement.setVerticalDirection(Direction::Down);
			}
			else if (stepsCounter == 280) {
				movement.setVerticalSpeed(1);
			}
			else if (stepsCounter == 300) {
				movement.setVerticalSpeed(2);
			}
			else if (stepsCounter == 340) {
				movement.setVerticalSpeed(3);
			}

			changeModel();
		}
	}
}

void JumpingFish::crush(World &world, int index)
{
	world.addDestroyedFish(position, directionFlag);
	world.deleteMonster(index);

	SoundController::playEnemyDestroyedEffect();
}