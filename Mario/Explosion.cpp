#include "Explosion.h"

SDL_Surface* Explosion::explosionImage = nullptr;

Explosion::Explosion() {}

Explosion::Explosion(int x, int y) {
	this->positionX = x;
	this->positionY = y;
	this->creationTime = std::chrono::steady_clock::now();
}

void Explosion::loadExplosionImage(SDL_Surface* screen) {
	this->explosionImage = loadPNG("./img/explosion.png", screen);
}

void Explosion::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->explosionImage, this->positionX - beginningOfCamera, this->positionY);
}

bool Explosion::shouldBeRemoved() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (this->creationTime + std::chrono::milliseconds(75) < timePoint);
}

void Explosion::slide() {}

