#include "Creature.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


// pictures with indexes 0-3 are pictures from the original Super Mario Bros
// the last two are custom graphics, created by me for the needs of the Winter World
std::array<SDL_Surface*, 8> Creature::creatureImages;

int Creature::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::Underground) {
		return 2;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::CustomWinter) {
		return 4;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::CustomSummer) {
		return 6;
	}
	else {
		return 0;
	}
}

int Creature::computeImageIndex() const
{
	int baseIndex = computeBaseIndex();
	return baseIndex + (model - 1);
}

void Creature::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 30 == 0) {
		model = (model == 1 ? 2 : 1);
	}
}

Creature::Creature(Position position)
{
	size = Size(32, 32);
	movement = Movement(1, 3, Direction::None);
	this->position = position;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;
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

void Creature::setMoveDirection(Direction direction)
{
	movement.setDirection(direction);
}

void Creature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 90 && position.getX() < endOfCamera + 90) {
		SDL_Surface* creatureImg = creatureImages[computeImageIndex()];
		drawSurface(display, creatureImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Creature::move(World &world)
{
	if (movement.getDirection() != Direction::None && stepsCounter % 3 == 0) {
		if (isCharacterStandingOnSomething(*this, world)) {
			moveHorizontally(world);
			changeModel();
		}
		else {
			moveDiagonally(world);
		}
	}
	++stepsCounter;
}