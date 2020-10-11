#include "Plant.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "CollisionHandling.h" 
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 4> Plant::plantImages;

int Plant::computeBaseIndex() const
{
	return (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 2);
}

void Plant::slide(World &world)
{
	if (stepsCounter < 630) {
		if (!isPlayerCloseToPlant(*this, world)) {
			if (movement.getVerticalDirection() == Direction::Up) {
				position.setY(position.getY() - movement.getVerticalSpeed());
			}
			else {
				position.setY(position.getY() + movement.getVerticalSpeed());
			}
		}
		else {
			--stepsCounter;
		}
	}
}

void Plant::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 75 == 0) {
		model = (model == 1 ? 2 : 1);
		changeModelCounter = 0;
	}
}

Plant::Plant(Position position)
{
	size = Size(24, 44);
	movement = Movement(0, 1, Direction::None, Direction::Up);
	this->position = position;
	model = 1;
	stepsCounter = -1;
	changeModelCounter = 0;
}

void Plant::loadPlantImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < plantImages.size(); ++i) {
		std::string filename = "./img/plant";
		filename += std::to_string(i + 1);
		filename += ".png";
		plantImages[i] = loadPNG(filename, display);
	}
}

void Plant::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 75 && position.getX() < endOfCamera + 75) {
		SDL_Surface* plantImg = nullptr;
		int baseIndex = computeBaseIndex();
		plantImg = plantImages[baseIndex + (model - 1)];
		drawSurface(display, plantImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Plant::move(World& world)
{
	++stepsCounter;
	if (stepsCounter < 90 || (stepsCounter >= 540 && stepsCounter < 720)) {
		slide(world);
	}
	else {
		changeModel();
	}

	if (stepsCounter == 90) {
		movement.setVerticalDirection(Direction::Down);
	}
	else if (stepsCounter == 720) {
		movement.setVerticalDirection(Direction::Up);
		stepsCounter = -1;
	}
}
