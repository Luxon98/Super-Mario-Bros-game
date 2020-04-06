#include "Castle.h"

SDL_Surface* Castle::castleImage = nullptr;

Castle::Castle() {}

Castle::Castle(int x, int y) {
	this->positionX = x;
	this->positionY = y;
}

void Castle::loadCastleImages(SDL_Surface* screen) {
	this->castleImage = loadPNG("./img/castle.png", screen);
}

void Castle::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->castleImage, this->positionX - beginningOfCamera, this->positionY);
}

