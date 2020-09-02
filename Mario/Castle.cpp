#include "Castle.h"

#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"


SDL_Surface* Castle::castleImage = nullptr;

Castle::Castle(Position position)
{
	this->position = position;

	size = Size(0, 0);
}

void Castle::loadCastleImages(SDL_Surface* display)
{
	castleImage = loadPNG("./img/castle.png", display);
}

void Castle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position.getX() > beginningOfCamera - 200 && position.getX() < endOfCamera + 200) {
		drawSurface(display, castleImage, position.getX() - beginningOfCamera, position.getY());
	}
}

