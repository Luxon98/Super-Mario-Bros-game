#include "DestroyedCreature.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 2> DestroyedCreature::destroyedCreatureImages;

int DestroyedCreature::computeIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld) {
		return 0;
	}
	else {
		return 1;
	}
}

DestroyedCreature::DestroyedCreature(Position position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
}

void DestroyedCreature::loadDestroyedCreatureImage(SDL_Surface* display)
{
	destroyedCreatureImages[0] = loadPNG("./img/destroyed_creature1.png", display);
	destroyedCreatureImages[1] = loadPNG("./img/destroyed_creature2.png", display);
}

void DestroyedCreature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 70 && position.getX() < endOfCamera + 70) {
		SDL_Surface* dcImg = nullptr;
		dcImg = destroyedCreatureImages[computeIndex()];
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

	if (auxiliaryCounter & 1) {
		if (auxiliaryCounter <= 12) {
			position.setY(position.getY() - 2);
		}
		else if (auxiliaryCounter >= 13 && auxiliaryCounter <= 24) {
			position.setX(position.getX() + 2);
			position.setY(position.getY() - 3);
		}
		else if (auxiliaryCounter >= 25 && auxiliaryCounter <= 32) {
			position.setX(position.getX() + 2);
		}
		else if (auxiliaryCounter >= 33 && auxiliaryCounter <= 44) {
			position.setX(position.getX() + 2);
			position.setY(position.getY() + 2);
		}
		else {
			position.setY(position.getY() + 3);
			if (auxiliaryCounter % 3 == 0) {
				position.setX(position.getX() + 1);
			}
		}
	}
}

