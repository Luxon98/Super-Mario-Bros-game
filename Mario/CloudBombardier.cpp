#include "CloudBombardier.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"
#include "CollisionHandling.h"


std::array<SDL_Surface*, 3> CloudBombardier::bombardierImages;

int CloudBombardier::computeImageIndex() const
{
	return (!active ? 2 : (movement.getDirection() != Direction::Left));
}

CloudBombardier::CloudBombardier(Position position)
{
	size = Size(32, 32);
	movement = Movement(1, 1, Direction::None, Direction::Down);
	this->position = position;
	active = false;
	stepsCounter = 0;
	changeModelCounter = 0;
}

void CloudBombardier::loadBombardierImages(SDL_Surface* display)
{
	bombardierImages[0] = loadPNG("./img/npc_imgs/bombardier_left.png", display);
	bombardierImages[1] = loadPNG("./img/npc_imgs/bombardier_right.png", display);
	bombardierImages[2] = loadPNG("./img/npc_imgs/cloud.png", display);
}

void CloudBombardier::setActiveState()
{
	active = true;
	movement.setDirection(Direction::Right);
	size.setHeight(48);
}

void CloudBombardier::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 90 && position.getX() < endOfCamera + 90) {
		SDL_Surface* bombardierImg = bombardierImages[computeImageIndex()];
		drawSurface(display, bombardierImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void CloudBombardier::move(World &world)
{
	++stepsCounter;
	if (!active) {
		--stepsCounter;
	}
	else {
		if ((stepsCounter >= 1 && stepsCounter <= 100) || (stepsCounter >= 1200 && stepsCounter <= 1600)) {
			if (stepsCounter & 1) {
				int alignment = computeVerticalAlignment(movement.getVerticalDirection(), movement.getVerticalSpeed(), *this, world);
				int verticalDistance = movement.getVerticalSpeed() - alignment;
				if (movement.getVerticalDirection() == Direction::Up) {
					verticalDistance *= -1;
				}
				position.setY(position.getY() + verticalDistance);
			}
		}
		else if (stepsCounter > 100 && stepsCounter < 1200) {
			int alignment = computeHorizontalAlignment(movement.getDirection(), movement.getSpeed(), *this, world);
			int distance = movement.getSpeed() - alignment;
			if (movement.getDirection() == Direction::Left) {
				distance *= -1;
			}
			position.setX(position.getX() + distance);
		}

		if (stepsCounter % 150 == 0) {
			Direction direction = (isPlayerAheadOfBombardier(*this, world) ? Direction::Right : Direction::Left);
			movement.setDirection(direction);
		}

		if (stepsCounter == 1200) {
			movement.setVerticalDirection(Direction::Up);
		}
		if (stepsCounter == 1600) {
			position.setY(600);
		}
	}
}