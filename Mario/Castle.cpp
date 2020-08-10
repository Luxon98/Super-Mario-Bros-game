#include "Castle.h"

SDL_Surface* Castle::castleImage = nullptr;

Castle::Castle() {}

Castle::Castle(Position* position)
{
	this->position = position;

	size = new Size(0, 0);
}

void Castle::loadCastleImages(SDL_Surface* display)
{
	castleImage = loadPNG("./img/castle.png", display);
}

void Castle::draw(SDL_Surface* display, int beginningOfCamera)
{
	drawSurface(display, castleImage, position->getX() - beginningOfCamera, position->getY());
}

