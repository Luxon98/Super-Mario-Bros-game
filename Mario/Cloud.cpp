#include "Cloud.h"

#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 3> Cloud::cloudImages;

Cloud::Cloud(int type, Position position)
{
	model = type;
	this->position = position;

	size = Size(0, 0);
}

void Cloud::loadCloudImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < cloudImages.size(); ++i) {
		std::string filename = "./img/cloud";
		filename += std::to_string(i + 1);
		filename += ".png";
		cloudImages[i] = loadPNG(filename, display);
	}
}

void Cloud::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		SDL_Surface* cloudImg = cloudImages[model - 1];
		drawSurface(display, cloudImg, position.getX() - beginningOfCamera, position.getY());
	}
}

