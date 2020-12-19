#include "DestroyedFish.h"

#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> DestroyedFish::destroyedFishImages;

int DestroyedFish::computeImageIndex() const
{
	return directionFlag;
}

DestroyedFish::DestroyedFish(Position position, bool directionFlag)
{
	this->position = position;
	this->directionFlag = directionFlag;
	auxiliaryCounter = 0;
}

void DestroyedFish::loadDestroyedFishImages(SDL_Surface* display)
{
	destroyedFishImages[0] = loadPNG("./img/anm_imgs/destroyed_fish1.png", display);
	destroyedFishImages[1] = loadPNG("./img/anm_imgs/destroyed_fish2.png", display);
}

void DestroyedFish::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		SDL_Surface* destroyedFishImg = destroyedFishImages[computeImageIndex()];
		drawSurface(display, destroyedFishImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool DestroyedFish::shouldBeRemoved() const
{
	return (auxiliaryCounter > 350);
}

void DestroyedFish::slide()
{
	++auxiliaryCounter;
	position.setY(position.getY() + 2);
}