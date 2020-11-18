#include "FireSerpent.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 24> FireSerpent::serpentImages;

FireSerpent::FireSerpent(bool down, Position position) : down(down)
{
	this->position = position;
	positionCounter = 1;
	auxiliaryCounter = 0;
	size = Size(5, 5);
}

void FireSerpent::loadFireSerpentImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < serpentImages.size(); ++i) {
		std::string filename = "./img/fire_serpent";
		filename += std::to_string(i + 1);
		filename += ".png";
		serpentImages[i] = loadPNG(filename, display);
	}
}

void FireSerpent::move()
{
	++auxiliaryCounter;
	if (auxiliaryCounter % 15 == 0) {
		++positionCounter;

		if (positionCounter == 25) {
			positionCounter = 1;
		}

		auxiliaryCounter = 0;
	}
}

void FireSerpent::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 100 && position.getX() < endOfCamera + 100) {
		drawSurface(display, serpentImages[positionCounter - 1], position.getX() - beginningOfCamera, position.getY());
	}
}
