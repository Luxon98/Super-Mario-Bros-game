#include "Explosion.h"

#include "Position.h"
#include "SDL_Utility.h"


SDL_Surface* Explosion::explosionImage = nullptr;

Explosion::Explosion(Position position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
}

void Explosion::loadExplosionImage(SDL_Surface* display)
{
	explosionImage = loadPNG("./img/explosion.png", display);
}

void Explosion::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position.getX() > beginningOfCamera - 50 && position.getX() < endOfCamera + 50) {
		drawSurface(display, explosionImage, position.getX() - beginningOfCamera, position.getY());
	}
}

bool Explosion::shouldBeRemoved()
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(75) < timePoint);
}

void Explosion::slide() {}

