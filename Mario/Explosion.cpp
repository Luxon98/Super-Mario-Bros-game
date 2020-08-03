#include "Explosion.h"

SDL_Surface* Explosion::explosionImage = nullptr;

Explosion::Explosion() {}

Explosion::Explosion(Position* position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
}

void Explosion::loadExplosionImage(SDL_Surface* screen)
{
	explosionImage = loadPNG("./img/explosion.png", screen);
}

void Explosion::draw(SDL_Surface* screen, int beginningOfCamera)
{
	drawSurface(screen, explosionImage, position->getX() - beginningOfCamera, position->getY());
}

bool Explosion::shouldBeRemoved()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(75) < timePoint);
}

void Explosion::slide() {}

