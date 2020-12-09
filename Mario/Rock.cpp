#include "Rock.h"

#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"


SDL_Surface* Rock::rockImage = nullptr;

Rock::Rock(Position position)
{
	this->position = position;

	size = Size(0, 0);
}

void Rock::loadRockImage(SDL_Surface* display)
{
	rockImage = loadPNG("./img/ie_imgs/rock.png", display);
}

void Rock::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		drawSurface(display, rockImage, position.getX() - beginningOfCamera, position.getY());
	}
}
