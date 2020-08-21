#include "Bush.h"

SDL_Surface* Bush::bushImages[5] = { nullptr };

Bush::Bush() {}

Bush::Bush(int type, Position* position)
{
	model = type;
	this->position = position;

	size = new Size(0, 0);
}

void Bush::loadBushImages(SDL_Surface* display)
{
	for (int i = 0; i < 5; ++i) {
		std::string filename = "./img/bush";
		filename += std::to_string(i + 1);
		filename += ".png";
		bushImages[i] = loadPNG(filename, display);
	}
}

void Bush::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position->getX() > beginningOfCamera - 100 && position->getX() < endOfCamera + 100) {
		SDL_Surface* bushImg = nullptr;
		bushImg = bushImages[model - 1];
		drawSurface(display, bushImg, position->getX() - beginningOfCamera, position->getY());
	}
}

