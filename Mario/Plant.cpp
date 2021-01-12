#include "Plant.h"

#include "World.h"
#include "LayoutStyle.h"
#include "SDL_Utility.h"
#include "CollisionHandling.h" 


std::array<SDL_Surface*, 4> Plant::plantImages;

bool Plant::isOutsidePipe() const
{
	if (moveCounter >= 42 && moveCounter <= 588) {
		return true;
	}

	return false;
}

void Plant::slide(World &world)
{
	if (moveCounter < 630) {
		if (!isPlayerCloseToPlant(*this, world) || isOutsidePipe()) {
			if (movement.getVerticalDirection() == Direction::Up) {
				position.setY(position.getY() - movement.getVerticalSpeed());
			}
			else {
				position.setY(position.getY() + movement.getVerticalSpeed());
			}
		}
		else {
			--moveCounter;
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

int Plant::computeImageIndex() const
{
	int baseIndex = (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 2);
	return baseIndex + (model - 1);
}

Plant::Plant(Position position, bool delay)
{
	this->position = position;
	moveCounter = (delay ? 629 : -1);
	changeModelCounter = 0;
	healthPoints = 1;
	auxiliaryCounter = 0;
	model = 1;
	movement = Movement(0, 1, Direction::None, Direction::Up);
	size = Size(24, 44);
}

void Plant::loadPlantImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < plantImages.size(); ++i) {
		std::string filename = "./img/npc_imgs/plant";
		filename += std::to_string(i + 1);
		filename += ".png";
		plantImages[i] = loadPNG(filename, display);
	}
}

bool Plant::isCrushproof() const
{
	return true;
}

bool Plant::isResistantToCollisionWithShell() const
{
	return false;
}

void Plant::move(World &world)
{
	++moveCounter;
	if (moveCounter < 90 || (moveCounter >= 540 && moveCounter < 820)) {
		slide(world);
	}
	else {
		changeModel();
	}

	if (moveCounter == 90) {
		movement.setVerticalDirection(Direction::Down);
	}
	else if (moveCounter == 820) {
		movement.setVerticalDirection(Direction::Up);
		moveCounter = -1;
	}
}

void Plant::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* plantImg = plantImages[computeImageIndex()];
		drawSurface(display, plantImg, position.getX() - beginningOfCamera, position.getY());
	}
}