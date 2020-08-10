#include "Flower.h"

SDL_Surface* Flower::flowerImages[2] = { nullptr };

int Flower::typeOfImage = 2;

Flower::Flower() {}

Flower::Flower(Position* position)
{
	size = new Size(32, 32);
	movement = new Movement(0, None);
	this->position = position;
	growCounter = 96;
}

void Flower::changeFlowerImage()
{
	Flower::typeOfImage = (Flower::typeOfImage == 1 ? 2 : 1);
}

void Flower::loadFlowerImages(SDL_Surface* display)
{
	flowerImages[0] = loadPNG("./img/flower1.png", display);
	flowerImages[1] = loadPNG("./img/flower2.png", display);
}

void Flower::draw(SDL_Surface* display, int beginningOfCamera)
{
	SDL_Surface* flowerImg = nullptr;
	flowerImg = flowerImages[typeOfImage - 1];
	drawSurface(display, flowerImg, position->getX() - beginningOfCamera, position->getY());
}

void Flower::move(World& world)
{
	if (growCounter) {
		grow();
	}
}
