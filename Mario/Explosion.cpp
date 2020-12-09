#include "Explosion.h"

#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 3> Explosion::explosionImages;

int Explosion::computeImageIndex() const
{
	auto timePoint = std::chrono::steady_clock::now();
	if (creationTime + std::chrono::milliseconds(55) >= timePoint) {
		return 0;
	}
	else if (creationTime + std::chrono::milliseconds(100) >= timePoint) {
		return 1;
	}
	else {
		return 2;
	}
}

Explosion::Explosion(Position position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
}

void Explosion::loadExplosionImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < explosionImages.size(); ++i) {
		std::string filename = "./img/te_imgs/explosion";
		filename += std::to_string(i + 1);
		filename += ".png";
		explosionImages[i] = loadPNG(filename, display);
	}
}

void Explosion::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 50 && position.getX() < endOfCamera + 50) {
		SDL_Surface* explosionImg = explosionImages[computeImageIndex()];
		drawSurface(display, explosionImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool Explosion::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(135) < timePoint);
}

void Explosion::slide() {}

