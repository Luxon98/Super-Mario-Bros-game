#include "DestroyedCreature.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"
#include "UtilityFunctions.h"

// the first four pictures are from the original Mario
// the last two are custom pictures, created for the needs of the Winter world
std::array<SDL_Surface*, 6> DestroyedCreature::destroyedCreatureImages;

int DestroyedCreature::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::Underground) {
		return 2;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::CustomWinter) {
		return 4;
	}
	else {
		return 0;
	}
}

int DestroyedCreature::computeImageIndex() const
{
	int baseIndex = computeBaseIndex();
	return baseIndex + (slideDirection == Direction::Left);
}

DestroyedCreature::DestroyedCreature(Position position, Direction slideDirection)
{
	this->position = position;
	this->slideDirection = slideDirection;
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
}

void DestroyedCreature::loadDestroyedCreatureImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < destroyedCreatureImages.size(); ++i) {
		std::string filename = "./img/anm_imgs/destroyed_creature";
		filename += std::to_string(i + 1);
		filename += ".png";
		destroyedCreatureImages[i] = loadPNG(filename, display);
	}
}

void DestroyedCreature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 70 && position.getX() < endOfCamera + 70) {
		SDL_Surface* dcImg = destroyedCreatureImages[computeImageIndex()];
		drawSurface(display, dcImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool DestroyedCreature::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(2000) < timePoint);
}

void DestroyedCreature::slide()
{
	++auxiliaryCounter;
	int shift = determineShift(slideDirection, 2);

	if (auxiliaryCounter & 1) {
		if (auxiliaryCounter <= 12) {
			position.setY(position.getY() - 2);
		}
		else if (auxiliaryCounter >= 13 && auxiliaryCounter <= 24) {
			position.setX(position.getX() + shift);
			position.setY(position.getY() - 3);
		}
		else if (auxiliaryCounter >= 25 && auxiliaryCounter <= 32) {
			position.setX(position.getX() + shift);
		}
		else if (auxiliaryCounter >= 33 && auxiliaryCounter <= 44) {
			position.setX(position.getX() + shift);
			position.setY(position.getY() + 2);
		}
		else {
			position.setY(position.getY() + 3);
			if (auxiliaryCounter % 3 == 0) {
				position.setX(position.getX() + shift);
			}
		}
	}
}

