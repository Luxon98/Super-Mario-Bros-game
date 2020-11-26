#include "Flower.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 8> Flower::flowerImages;

int Flower::computeImageIndex() const
{
	int baseIndex = (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 4);
	return baseIndex + imageIndex;
}

void Flower::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 10 == 0) {
		++imageIndex;
		if (imageIndex > 3) {
			imageIndex = 0;
		}
	}
}

Flower::Flower(Position position)
{
	size = Size(32, 32);
	movement = Movement();
	this->position = position;
	growCounter = 96;
	changeModelCounter = 0;
	imageIndex = 0;
}

void Flower::loadFlowerImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < flowerImages.size(); ++i) {
		std::string filename = "./img/flower";
		filename += std::to_string(i + 1);
		filename += ".png";
		flowerImages[i] = loadPNG(filename, display);
	}
}

void Flower::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		SDL_Surface* flowerImg = flowerImages[computeImageIndex()];
		drawSurface(display, flowerImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Flower::move(World &world)
{
	if (growCounter) {
		grow();
	}

	changeModel();
}