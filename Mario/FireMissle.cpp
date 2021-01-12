#include "FireMissle.h"

#include "SoundController.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "World.h"
#include "CollisionHandling.h"


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

void FireMissle::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 7 == 0) {
		model = (model == 1 ? 2 : 1);
	}
}

void FireMissle::fallDown(World &world)
{
	int alignment = computeVerticalAlignment(Direction::Down, movement.getVerticalSpeed(), *this, world);
	int distance = movement.getVerticalSpeed() - alignment;

	if (distance != 0) {
		position.setY(position.getY() + distance);
	}
	else {
		inactive = true;
	}
}

void FireMissle::moveLeft(World &world)
{
	int alignment = computeHorizontalAlignment(Direction::Left, movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;

	if (distance != 0) {
		position.setX(position.getX() - distance);
		changeModel();

		if (isRightTime() && isPlayerCloseToFireRocket(*this, world)) {
			lastSoundTime = std::chrono::steady_clock::now();
			SoundController::playFireRocketEffect();
		}
	}
	else {
		inactive = true;
	}
}

int FireMissle::computeImageIndex() const
{
	return (missleType == MissleType::Bomb ? 2 : model - 1);
}

FireMissle::FireMissle(Position position, MissleType type)
{
	this->position = position;
	moveCounter = 0;
	changeModelCounter = 0;
	healthPoints = 2; // it is indestructible anyway
	inactive = false;
	model = 1;
	missleType = type;
	lastSoundTime = std::chrono::steady_clock::now();
	movement = Movement(1, 1, Direction::None, Direction::None);
	size = Size(50, 16);

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

bool FireMissle::shouldStartMoving(const Player &player) const
{
	if (movement.getDirection() == Direction::None && position.getX() < player.getX() + 480) {
		return true;
	}

	return false;
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

void FireMissle::startMoving()
{
	movement.setDirection(Direction::Left);
}

void FireMissle::performSpecificActions(World &world, int index)
{
	if (inactive) {
		Position explosionPosition = position;
		if (missleType == MissleType::Bomb) {
			explosionPosition.setY(position.getY() + 7);
		}

		world.deleteNpc(index);
		world.addExplosion(explosionPosition);
	}
}

void FireMissle::move(World &world)
{
	if (missleType == MissleType::Bomb) {
		fallDown(world);
	}
	else {
		if (movement.getDirection() == Direction::Left) {
			moveLeft(world);
		}
	}
}

void FireMissle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera) && !inactive) {
		drawSurface(display, missleImages[computeImageIndex()], position.getX() - beginningOfCamera, position.getY());
	}
}