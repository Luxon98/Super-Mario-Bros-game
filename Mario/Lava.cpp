#include "Lava.h"

#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 2> Lava::lavaImages;

Lava::Lava(Position position)
{
	this->position = position;
	size = Size(16, 48);
}

void Lava::loadLavaImage(SDL_Surface* display)
{
	lavaImages[0] = loadPNG("./img/ie_imgs/lava.png", display);
	lavaImages[1] = loadPNG("./img/ie_imgs/alt_lava.png", display);
}

void Lava::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		int index = (World::LAYOUT_STYLE == LayoutStyle::CustomSummer);
		drawSurface(display, lavaImages[index], position.getX() - beginningOfCamera, position.getY());
	}
}