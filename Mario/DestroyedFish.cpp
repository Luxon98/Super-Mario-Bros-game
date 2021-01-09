#include "DestroyedFish.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> DestroyedFish::destroyedFishImages;

int DestroyedFish::computeImageIndex() const
{
	return (direction == Direction::Left);
}

DestroyedFish::DestroyedFish(Position position, Direction direction)
{
	this->position = position;
	this->direction = direction;
	auxiliaryCounter = 0;
	size = Size(30, 32);
}

void DestroyedFish::loadDestroyedFishImages(SDL_Surface* display)
{
	destroyedFishImages[0] = loadPNG("./img/temp_imgs/destroyed_fish1.png", display);
	destroyedFishImages[1] = loadPNG("./img/temp_imgs/destroyed_fish2.png", display);
}

void DestroyedFish::slide()
{
	++auxiliaryCounter;
	position.setY(position.getY() + 2);
}

void DestroyedFish::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* destroyedFishImg = destroyedFishImages[computeImageIndex()];
		drawSurface(display, destroyedFishImg, position.getX() - beginningOfCamera, position.getY());
	}
}