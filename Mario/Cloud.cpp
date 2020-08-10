#include "Cloud.h"

SDL_Surface* Cloud::cloudImages[3] = { nullptr };

Cloud::Cloud() {}

Cloud::Cloud(int type, Position* position)
{
	model = type;
	this->position = position;

	size = new Size(0, 0);
}

void Cloud::loadCloudImages(SDL_Surface* display)
{
	cloudImages[0] = loadPNG("./img/cloud1.png", display);
	cloudImages[1] = loadPNG("./img/cloud2.png", display);
	cloudImages[2] = loadPNG("./img/cloud3.png", display);
}

void Cloud::draw(SDL_Surface* display, int beginningOfCamera)
{
	SDL_Surface* cloudImg = nullptr;
	cloudImg = cloudImages[model - 1];
	drawSurface(display, cloudImg, position->getX() - beginningOfCamera, position->getY());
}

