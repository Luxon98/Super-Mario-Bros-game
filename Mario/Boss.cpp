#include "Boss.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "CollisionHandling.h"


std::array<SDL_Surface*, 4> Boss::bossImages;

int Boss::computeImageIndex() const
{
	int baseIndex = (movement.getDirection() == Direction::Left ? 0 : 2);
	return baseIndex + (model - 1);
}

void Boss::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 45 == 0) {
		model = (model == 1 ? 2 : 1);

		changeModelCounter = 0;
	}
}

void Boss::moveAndJump(World &world)
{
	++auxiliaryCounter;

	int multiplier = (movement.getDirection() == Direction::Left ? 1 : -1);
	if (auxiliaryCounter < 11) {
		position.setX(position.getX() - (1 * multiplier));
		position.setY(position.getY() - 2);
	}
	else if (auxiliaryCounter >= 11 && auxiliaryCounter < 18) {
		position.setX(position.getX() - (1 * multiplier));
		position.setY(position.getY() - 1);
	}
	else if (auxiliaryCounter >= 18 && auxiliaryCounter < 22) {
		position.setX(position.getX() - (1 * multiplier));
	}
	else if (auxiliaryCounter >= 22 && auxiliaryCounter < 28) {
		position.setX(position.getX() - (1 * multiplier));
		position.setY(position.getY() + 2);
	}
	else if (auxiliaryCounter >= 28 && auxiliaryCounter < 37) {
		position.setY(position.getY() + 1);
	}
	else if (auxiliaryCounter >= 37 && auxiliaryCounter < 40) {
		position.setX(position.getX() + (1 * multiplier));
	}
	else if (auxiliaryCounter >= 40 && auxiliaryCounter < 45) {
		position.setX(position.getX() - (1 * multiplier));
		position.setY(position.getY() + 2);
	}
	else if (auxiliaryCounter == 120) {
		position.setY(position.getY() - 4);
		auxiliaryCounter = 0;
		movement.setDirection(isPlayerAheadOfMonster(*this, world) ? Direction::Right : Direction::Left);
 	}
}

Boss::Boss(Position position)
{
	size = Size(58, 64);
	movement = Movement(1, 1, Direction::None);
	this->position = position;
	healthPoints = 5;
	model = 1;
	auxiliaryCounter = 0;
	stepsCounter = 0;
	changeModelCounter = 0;
}

void Boss::loadBossImages(SDL_Surface* display)
{
	bossImages[0] = loadPNG("./img/npc_imgs/boss1.png", display);
	bossImages[1] = loadPNG("./img/npc_imgs/boss2.png", display);
	bossImages[2] = loadPNG("./img/npc_imgs/boss3.png", display);
	bossImages[3] = loadPNG("./img/npc_imgs/boss4.png", display);
}

bool Boss::isCrushproof() const
{
	return true;
}

bool Boss::isResistantToImmortalPlayer() const
{
	return true;
}

int Boss::getPointsForDestroying() const
{
	return 5000;
}

void Boss::setMoveDirection(Direction direction)
{
	movement.setDirection(direction);
}

void Boss::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 90 && position.getX() < endOfCamera + 90) {
		SDL_Surface* bossImg = bossImages[computeImageIndex()];
		drawSurface(display, bossImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Boss::move(World &world)
{
	++stepsCounter;
	if (movement.getDirection() != Direction::None && stepsCounter & 1) {
		moveAndJump(world);
		changeModel();
	}
}