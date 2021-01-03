#include "FireMissle.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "CollisionHandling.h"
#include "SoundController.h"


std::array<SDL_Surface*, 3> FireMissle::missleImages;

bool FireMissle::isRightTime()
{
	auto timePoint = std::chrono::steady_clock::now();
	auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastSoundTime).count();
	if (difference > 4500) {
		return true;
	}

	return false;
}

int FireMissle::computeImageIndex() const
{
	return (missleType == MissleType::Bomb ? 2 : model - 1);
}

void FireMissle::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 7 == 0) {
		model = (model == 1 ? 2 : 1);
	}
}

FireMissle::FireMissle(Position position, MissleType type)
{
	size = Size(50, 16);
	movement = Movement(1, 1, Direction::None);
	this->position = position;
	healthPoints = 2;
	inactive = false;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;
	missleType = type;
	lastSoundTime = std::chrono::steady_clock::now();

	if (type == MissleType::Bomb) {
		movement.setVerticalDirection(Direction::Down);
		size.setSize(20, 22);
	}
}

void FireMissle::loadFireRocketImages(SDL_Surface* display)
{
	missleImages[0] = loadPNG("./img/npc_imgs/fire_rocket1.png", display);
	missleImages[1] = loadPNG("./img/npc_imgs/fire_rocket2.png", display);
	missleImages[2] = loadPNG("./img/npc_imgs/fire_bomb.png", display);
}

bool FireMissle::isCrushproof() const
{
	return true;
}

bool FireMissle::isResistantToImmortalPlayer() const
{
	return true;
}

bool FireMissle::isResistantToFireBalls() const
{
	return true;
}

bool FireMissle::isInactive() const
{
	return inactive;
}

void FireMissle::setMoveDirection(Direction direction)
{
	movement.setDirection(direction);
}

void FireMissle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera) && !inactive) {
		drawSurface(display, missleImages[computeImageIndex()], position.getX() - beginningOfCamera, position.getY());
	}
}

void FireMissle::move(World &world)
{
	if (missleType == MissleType::Bomb) {
		int alignment = computeVerticalAlignment(movement.getVerticalDirection(), movement.getVerticalSpeed(), *this, world);
		int distance = movement.getVerticalSpeed() - alignment;

		if (distance != 0) {
			position.setY(position.getY() + distance);
		}
		else {
			inactive = true;
		}
	}
	else {
		if (movement.getDirection() == Direction::Left) {
			int alignment = computeHorizontalAlignment(Direction::Left, movement.getSpeed(), *this, world);
			int distance = movement.getSpeed() - alignment;

			if (distance != 0) {
				position.setX(position.getX() - distance);
				changeModel();
			}
			else {
				inactive = true;
			}

			// to if
			if (isRightTime() && isPlayerCloseToFireRocket(*this, world)) {
				lastSoundTime = std::chrono::steady_clock::now();
				SoundController::playFireRocketEffect();
			}
		}
	}
}
