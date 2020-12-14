#include "CustomSummerDecoration.h"

#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> CustomSummerDecoration::decorationImages;

CustomSummerDecoration::CustomSummerDecoration(SummerDecorationType type, Position position)
{
	this->position = position;
	decorationType = type;

	size = Size(0, 0);
}

void CustomSummerDecoration::loadDecorationImages(SDL_Surface* display)
{
	decorationImages[0] = loadPNG("./img/ie_imgs/palm.png", display);
	decorationImages[1] = loadPNG("./img/ie_imgs/palm.png", display);
}

void CustomSummerDecoration::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		SDL_Surface* decorationImg = decorationImages[static_cast<int>(decorationType) - 1];
		drawSurface(display, decorationImg, position.getX() - beginningOfCamera, position.getY());
	}
}