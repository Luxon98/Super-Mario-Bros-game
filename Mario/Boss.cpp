#include "Boss.h"

#include "SDL_Utility.h"
#include "Player.h"
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
		movement.setDirection(isPlayerAheadOfNpc(*this, world) ? Direction::Right : Direction::Left);
 	}
}

Boss::Boss(Position position)
{
	this->position = position;
	moveCounter = 0;
	changeModelCounter = 0;
	healthPoints = 5;
	model = 1;
	auxiliaryCounter = 0;
	movement = Movement(1, 1, Direction::None, Direction::None);
	size = Size(58, 64);
}

void Boss::loadBossImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < bossImages.size(); ++i) {
		std::string filename = "./img/npc_imgs/boss";
		filename += std::to_string(i + 1);
		filename += ".png";
		bossImages[i] = loadPNG(filename, display);
	}
}

bool Boss::shouldStartMoving(const Player &player) const
{
	if (movement.getDirection() == Direction::None && position.getX() < player.getX() + 480) {
		return true;
	}

	return false;
}

bool Boss::isCrushproof() const
{
	return true;
}

bool Boss::isResistantToImmortalPlayer() const
{
	return true;
}

bool Boss::isBoss() const
{
	return true;
}

int Boss::getPointsForDestroying() const
{
	return 5000;
}

void Boss::startMoving()
{
	movement.setDirection(Direction::Left);
}

void Boss::destroy(World &world, Direction direction)
{
	world.addDestroyedBoss(position, direction);
}

void Boss::move(World &world)
{
	++moveCounter;
	if (movement.getDirection() != Direction::None && moveCounter & 1) {
		moveAndJump(world);
		changeModel();
	}
}

void Boss::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* bossImg = bossImages[computeImageIndex()];
		drawSurface(display, bossImg, position.getX() - beginningOfCamera, position.getY());
	}
}