#include "CustomWinterDecoration.h"

#include <string>
#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 6> CustomWinterDecoration::decorationImages;

CustomWinterDecoration::CustomWinterDecoration(DecorationType type, Position position)
{
	this->position = position;
	decorationType = type;

	size = Size(0, 0);
}

void CustomWinterDecoration::loadDecorationImages(SDL_Surface* display)
{
	decorationImages[0] = loadPNG("./img/sky_star1.png", display);
	decorationImages[1] = loadPNG("./img/sky_star2.png", display);
	decorationImages[2] = loadPNG("./img/christmas_tree.png", display);
	decorationImages[3] = loadPNG("./img/winter_cloud.png", display);
	decorationImages[4] = loadPNG("./img/moon.png", display);
	decorationImages[5] = loadPNG("./img/signpost.png", display);
}

void CustomWinterDecoration::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		SDL_Surface* decorationImg = decorationImages[static_cast<int>(decorationType) - 1];
		drawSurface(display, decorationImg, position.getX() - beginningOfCamera, position.getY());
	}
}