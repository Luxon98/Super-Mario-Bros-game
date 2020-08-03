#include "Cloud.h"

SDL_Surface* Cloud::cloudImages[3] = { nullptr };

Cloud::Cloud() {}

Cloud::Cloud(int type, Position* position)
{
	model = type;
	this->position = position;

	size = new Size(0, 0);
}

void Cloud::loadCloudImages(SDL_Surface* screen)
{
	cloudImages[0] = loadPNG("./img/cloud1.png", screen);
	cloudImages[1] = loadPNG("./img/cloud2.png", screen);
	cloudImages[2] = loadPNG("./img/cloud3.png", screen);
}

void Cloud::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* cloudImg = nullptr;
	cloudImg = cloudImages[model - 1];
	drawSurface(screen, cloudImg, position->getX() - beginningOfCamera, position->getY());
}

