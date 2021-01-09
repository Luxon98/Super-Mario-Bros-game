#include "FireSerpent.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 24> FireSerpent::fireSerpentImages;
std::array<int, 24> FireSerpent::xDifferences = { 0, -17, -34, -48, -58, -64, -66, -64, -58, -48, -34, -17, 0, 17, 34,
													48, 58, 64, 66, 64, 58, 48, 34, 17};
std::array<int, 24> FireSerpent::yDifferences = { 66, 62, 55, 46, 29, 14, 0, -20, -37, -51, -63, -68, -71, -68, -63, 
													-51, -37, -20, 0, 16, 33, 46, 57, 63 };

void FireSerpent::changePosition()
{
	position.setX(initialPosition.getX() + xDifferences[positionCounter - 1]);
	position.setY(initialPosition.getY() + yDifferences[positionCounter - 1]);
}

FireSerpent::FireSerpent(int counter, Position position)
{
	this->position = position;
	auxiliaryCounter = 0;
	positionCounter = counter;
	initialPosition = position;
	size = Size(20, 20);
}

void FireSerpent::loadFireSerpentImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < fireSerpentImages.size(); ++i) {
		std::string filename = "./img/other_imgs/fire_serpent";
		filename += std::to_string(i + 1);
		filename += ".png";
		fireSerpentImages[i] = loadPNG(filename, display);
	}
}

void FireSerpent::move()
{
	++auxiliaryCounter;
	if (auxiliaryCounter % 16 == 0) {
		++positionCounter;

		if (positionCounter == 25) {
			positionCounter = 1;
		}

		auxiliaryCounter = 0;
		changePosition();
	}
}

void FireSerpent::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	drawSurface(display, fireSerpentImages[positionCounter - 1], initialPosition.getX() - beginningOfCamera, 
		initialPosition.getY());
}