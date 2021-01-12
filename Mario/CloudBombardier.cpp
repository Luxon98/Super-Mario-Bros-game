#include "CloudBombardier.h"

#include "SoundController.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "World.h"
#include "CollisionHandling.h"


std::array<SDL_Surface*, 3> CloudBombardier::bombardierImages;

bool CloudBombardier::isReadyToDropBomb() const
{
	return (moveCounter % 175 == 0 && (moveCounter > 0 && moveCounter < 1300));
}

void CloudBombardier::flyVertically(World &world)
{
	if (moveCounter & 1) {
		int alignment = computeVerticalAlignment(movement.getVerticalDirection(), movement.getVerticalSpeed(), 
			*this, world);
		int verticalDistance = movement.getVerticalSpeed() - alignment;

		if (movement.getVerticalDirection() == Direction::Up) {
			verticalDistance *= -1;
		}

		position.setY(position.getY() + verticalDistance);
	}
}

void CloudBombardier::flyHorizontally(World &world)
{
	int alignment = computeHorizontalAlignment(movement.getDirection(), movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;

	if (movement.getDirection() == Direction::Left) {
		distance *= -1;
	}

	position.setX(position.getX() + distance);
}

void CloudBombardier::changeParametersDuringFlight(World &world)
{
	if (moveCounter % 75 == 0) {
		Direction direction = (isPlayerAheadOfNpc(*this, world) ? Direction::Right : Direction::Left);
		movement.setDirection(direction);
	}

	if (moveCounter == 1200) {
		movement.setVerticalDirection(Direction::Up);
	}
	if (moveCounter == 1600) {
		position.setY(600);
	}
}

int CloudBombardier::computeImageIndex() const
{
	return (!active ? 2 : (movement.getDirection() != Direction::Left));
}

CloudBombardier::CloudBombardier(Position position)
{
	this->position = position;
	moveCounter = 0;
	changeModelCounter = 0;
	healthPoints = 1;
	active = false;
	movement = Movement(1, 1, Direction::None, Direction::Down);
	size = Size(32, 32);
}

void CloudBombardier::loadBombardierImages(SDL_Surface* display)
{
	bombardierImages[0] = loadPNG("./img/npc_imgs/bombardier_left.png", display);
	bombardierImages[1] = loadPNG("./img/npc_imgs/bombardier_right.png", display);
	bombardierImages[2] = loadPNG("./img/npc_imgs/cloud.png", display);
}

bool CloudBombardier::shouldStartMoving(const Player &player) const
{
	if (movement.getDirection() == Direction::None && (player.getX() < position.getX()) 
		&& (position.getX() < player.getX() + 75)) {
		
		return true;
	}

	return false;
}

bool CloudBombardier::isCrushproof() const
{
	return true;
}

void CloudBombardier::startMoving()
{
	active = true;
	movement.setDirection(Direction::Right);
	size.setHeight(48);
}

void CloudBombardier::destroy(World &world, Direction direction)
{
	world.addDestroyedBombardier(position, direction);
}

void CloudBombardier::performSpecificActions(World &world, int index)
{
	if (isReadyToDropBomb()) {
		Position bombPosition = position;
		bombPosition.setY(bombPosition.getY() + 12);
		world.addFireBomb(bombPosition);
		SoundController::playBombDroppedEffect();
	}
}

void CloudBombardier::move(World &world)
{
	++moveCounter;
	if (!active) {
		--moveCounter;
	}
	else {
		if ((moveCounter >= 1 && moveCounter <= 100) || (moveCounter >= 1200 && moveCounter <= 1600)) {
			flyVertically(world);
		}
		else if (moveCounter > 100 && moveCounter < 1200) {
			flyHorizontally(world);
		}

		changeParametersDuringFlight(world);
	}
}

void CloudBombardier::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* bombardierImg = bombardierImages[computeImageIndex()];
		drawSurface(display, bombardierImg, position.getX() - beginningOfCamera, position.getY());
	}
}