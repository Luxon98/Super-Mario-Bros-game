#include "Flower.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> Flower::flowerImages;

int Flower::typeOfImage = 2;

Flower::Flower(Position position)
{
	size = Size(32, 32);
	movement = Movement();
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

void Flower::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		SDL_Surface* flowerImg = nullptr;
		flowerImg = flowerImages[typeOfImage - 1];
		drawSurface(display, flowerImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Flower::move(World &world)
{
	if (growCounter) {
		grow();
	}
}
