#include "DestroyedBombardier.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> DestroyedBombardier::destroyedBombardierImages;

int DestroyedBombardier::computeImageIndex() const
{
	return direction == (Direction::Left);
}

DestroyedBombardier::DestroyedBombardier(Position position, Direction direction)
{
	this->position = position;
	this->direction = direction;
	auxiliaryCounter = 0;
	size = Size(32, 48);
}

void DestroyedBombardier::loadDestroyedBombardierImages(SDL_Surface* display)
{
	destroyedBombardierImages[0] = loadPNG("./img/temp_imgs/destroyed_bombardier1.png", display);
	destroyedBombardierImages[1] = loadPNG("./img/temp_imgs/destroyed_bombardier2.png", display);
}

void DestroyedBombardier::slide()
{
	position.setY(position.getY() + 2);
}

void DestroyedBombardier::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* dbImg = destroyedBombardierImages[computeImageIndex()];
		drawSurface(display, dbImg, position.getX() - beginningOfCamera, position.getY());
	}
}