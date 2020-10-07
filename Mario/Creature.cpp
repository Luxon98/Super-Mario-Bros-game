#include "Creature.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 4> Creature::creatureImages;

int Creature::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld) {
		return 0;
	}
	else {
		return 2;
	}
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

void Creature::setMoveDirection(Direction direction)
{
	movement.setDirection(direction);
}

void Creature::loadCreatureImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < creatureImages.size(); ++i) {
		std::string filename = "./img/creature";
		filename += std::to_string(i + 1);
		filename += ".png";
		creatureImages[i] = loadPNG(filename, display);
	}
}

void Creature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 90 && position.getX() < endOfCamera + 90) {
		SDL_Surface* creatureImg = nullptr;
		int baseIndex = computeBaseIndex();
		creatureImg = creatureImages[baseIndex + (model - 1)];
		drawSurface(display, creatureImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Creature::move(World &world)
{
	if (movement.getDirection() != Direction::None && stepsCounter % 3 == 0) {
		if (isCharacterStandingOnTheBlock(*this, world)) {
			makeHorizontalMove(world);
		}
		else {
			makeDiagonalMove(world);
		}
		changeModel();
	}
	++stepsCounter;
}

