#include "Creature.h"

#include "SoundController.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "World.h"
#include "LayoutStyle.h"
#include "CollisionHandling.h"


std::array<SDL_Surface*, 8> Creature::creatureImages;

void Creature::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 30 == 0) {
		model = (model == 1 ? 2 : 1);
	}
}

int Creature::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld || World::LAYOUT_STYLE == LayoutStyle::Castle) {
		return 0;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::Underground) {
		return 2;
	} 
	else {
		return 2 * (static_cast<int>(World::LAYOUT_STYLE) - 1);
	}
}

int Creature::computeImageIndex() const
{
	int baseIndex = computeBaseIndex();
	return baseIndex + (model - 1);
}

Creature::Creature(Position position)
{
	this->position = position;
	moveCounter = 0;
	changeModelCounter = 0;
	healthPoints = 1;
	model = 1;
	movement = Movement(1, 3, Direction::None, Direction::None);
	size = Size(32, 32);
}

void Creature::loadCreatureImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < creatureImages.size(); ++i) {
		std::string filename = "./img/npc_imgs/creature";
		filename += std::to_string(i + 1);
		filename += ".png";
		creatureImages[i] = loadPNG(filename, display);
	}
}

int Creature::getPointsForCrushing() const
{
	return 100;
}

int Creature::getPointsForDestroying() const
{
	return 100;
}

bool Creature::shouldStartMoving(const Player &player) const
{
	if (movement.getDirection() == Direction::None && position.getX() < player.getX() + 480) {
		return true;
	}

	return false;
}

bool Creature::isResistantToCollisionWithShell() const
{
	return false;
}

bool Creature::isResistantToCollisionWithBlock() const
{
	return false;
}

void Creature::startMoving()
{
	movement.setDirection(Direction::Left);
}

void Creature::crush(World &world, int index)
{
	world.addCrushedCreature(Position(position.getX(), position.getY() + 8));
	world.deleteNpc(index);

	SoundController::playEnemyDestroyedEffect();
}

void Creature::destroy(World &world, Direction direction)
{
	world.addDestroyedCreature(position, direction);
}

void Creature::move(World &world)
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

void Creature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* creatureImg = creatureImages[computeImageIndex()];
		drawSurface(display, creatureImg, position.getX() - beginningOfCamera, position.getY());
	}
}