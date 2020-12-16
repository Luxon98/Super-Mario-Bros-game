#include "Lava.h"

#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"
#include "LayoutStyle.h"
#include "World.h"


std::array<SDL_Surface*, 2> Lava::lavaImages;

Lava::Lava(Position position)
{
	this->position = position;

	size = Size(0, 0);
}

void Lava::loadLavaImage(SDL_Surface* display)
{
	lavaImages[0] = loadPNG("./img/ie_imgs/lava.png", display);
	lavaImages[1] = loadPNG("./img/ie_imgs/alt_lava.png", display);
}

void Lava::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		int index = (World::LAYOUT_STYLE == LayoutStyle::CustomSummer);
		drawSurface(display, lavaImages[index], position.getX() - beginningOfCamera, position.getY());
	}
}