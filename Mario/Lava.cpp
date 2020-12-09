#include "Lava.h"

#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"


SDL_Surface* Lava::lavaImage;

Lava::Lava(Position position)
{
	this->position = position;

	size = Size(0, 0);
}

void Lava::loadLavaImage(SDL_Surface* display)
{
	lavaImage = loadPNG("./img/ie_imgs/lava.png", display);
}

void Lava::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		drawSurface(display, lavaImage, position.getX() - beginningOfCamera, position.getY());
	}
}