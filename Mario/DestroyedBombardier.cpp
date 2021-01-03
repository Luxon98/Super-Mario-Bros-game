#include "DestroyedBombardier.h"

#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> DestroyedBombardier::destroyedBombardierImages;

int DestroyedBombardier::computeImageIndex() const
{
	return leftSide;
}

DestroyedBombardier::DestroyedBombardier(Position position, bool leftSide)
{
	this->position = position;
	this->leftSide = leftSide;
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
	size = Size(32, 48);
}

void DestroyedBombardier::loadDestroyedBombardierImages(SDL_Surface* display)
{
	destroyedBombardierImages[0] = loadPNG("./img/anm_imgs/destroyed_bombardier1.png", display);
	destroyedBombardierImages[1] = loadPNG("./img/anm_imgs/destroyed_bombardier2.png", display);
}

void DestroyedBombardier::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* dbImg = destroyedBombardierImages[computeImageIndex()];
		drawSurface(display, dbImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool DestroyedBombardier::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(2000) < timePoint);
}

void DestroyedBombardier::slide()
{
	position.setY(position.getY() + 2);
}