#include "Castle.h"

SDL_Surface* Castle::castleImage = nullptr;

Castle::Castle() {}

Castle::Castle(Position* position) {
	this->position = position;

	size = new Size(0, 0);
}

void Castle::loadCastleImages(SDL_Surface* screen) {
	this->castleImage = loadPNG("./img/castle.png", screen);
}

void Castle::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->castleImage, this->position->getX() - beginningOfCamera, this->position->getY());
}

