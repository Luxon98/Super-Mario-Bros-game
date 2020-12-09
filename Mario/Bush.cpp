#include "Bush.h"

#include <string>
#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 5> Bush::bushImages;

Bush::Bush(int type, Position position)
{
	this->position = position;
	model = type;

	size = Size(0, 0);
}

void Bush::loadBushImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < bushImages.size(); ++i) {
		std::string filename = "./img/ie_imgs/bush";
		filename += std::to_string(i + 1);
		filename += ".png";
		bushImages[i] = loadPNG(filename, display);
	}
}

void Bush::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		SDL_Surface* bushImg = bushImages[model - 1];
		drawSurface(display, bushImg, position.getX() - beginningOfCamera, position.getY());
	}
}

