#include "Bush.h"

SDL_Surface* Bush::bushImages[5] = { nullptr };

Bush::Bush() {}

Bush::Bush(int type, Position* position) {
	this->model = type;
	this->position = position;

	size = new Size(0, 0);
}

void Bush::loadBushImages(SDL_Surface* screen) {
	for (int i = 0; i < 5; ++i) {
		std::string filename = "./img/bush";
		filename += std::to_string(i + 1);
		filename += ".png";
		this->bushImages[i] = loadPNG(filename, screen);
	}
}

void Bush::draw(SDL_Surface* screen, int beginningOfCamera) {
	SDL_Surface* bushImg = nullptr;
	bushImg = bushImages[model - 1];
	drawSurface(screen, bushImg, this->position->getX() - beginningOfCamera, this->position->getY());
}

