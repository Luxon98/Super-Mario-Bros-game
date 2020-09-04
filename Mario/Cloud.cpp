#include "Cloud.h"

#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 3> Cloud::cloudImages;

Cloud::Cloud(int type, Position position)
{
	model = type;
	this->position = position;

	size = Size(0, 0);
}

void Cloud::loadCloudImages(SDL_Surface* display)
{
	cloudImages[0] = loadPNG("./img/cloud1.png", display);
	cloudImages[1] = loadPNG("./img/cloud2.png", display);
	cloudImages[2] = loadPNG("./img/cloud3.png", display);
}

void Cloud::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		SDL_Surface* cloudImg = nullptr;
		cloudImg = cloudImages[model - 1];
		drawSurface(display, cloudImg, position.getX() - beginningOfCamera, position.getY());
	}
}

