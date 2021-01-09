#include "Bush.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 5> Bush::bushImages;

Size Bush::getSizeFromModel() const
{
	if (model == 1) {
		return Size(64, 32);
	}
	else if (model == 2) {
		return Size(96, 32);
	}
	else if (model == 3) {
		return Size(128, 32);
	}
	else if (model == 4) {
		return Size(96, 38);
	}
	else {
		return Size(160, 70);
	}
}

Bush::Bush(int type, Position position)
{
	this->position = position;
	model = type;
	size = getSizeFromModel();
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
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* bushImg = bushImages[model - 1];
		drawSurface(display, bushImg, position.getX() - beginningOfCamera, position.getY());
	}
}