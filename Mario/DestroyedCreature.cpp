#include "DestroyedCreature.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 4> DestroyedCreature::destroyedCreatureImages;

int DestroyedCreature::computeImageIndex() const
{
	int baseIndex = (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 2);
	return baseIndex + (slideDirection == Direction::Left);
}

DestroyedCreature::DestroyedCreature(Position position, Direction slideDirection)
{
	this->position = position;
	this->slideDirection = slideDirection;
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
}

void DestroyedCreature::loadDestroyedCreatureImage(SDL_Surface* display)
{
	for (std::size_t i = 0; i < destroyedCreatureImages.size(); ++i) {
		std::string filename = "./img/destroyed_creature";
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

	int shift = (slideDirection == Direction::Left ? -2 : 2);

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

