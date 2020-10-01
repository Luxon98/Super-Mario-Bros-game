#include "Coin.h"

#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 4> Coin::coinImages;

int Coin::typeOfImage = 2;

int Coin::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld) {
		return 0;
	}
	else {
		return 2;
	}
}

Coin::Coin(Position position)
{
	this->position = position;

	size = Size(20, 28);
}

void Coin::loadCoinImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < coinImages.size(); ++i) {
		std::string filename = "./img/coin";
		filename += std::to_string(i + 1);
		filename += ".png";
		coinImages[i] = loadPNG(filename, display);
	}
}

void Coin::changeCoinImage()
{
	Coin::typeOfImage = (Coin::typeOfImage == 1 ? 2 : 1);
}

void Coin::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		SDL_Surface* coinImg = nullptr;
		int baseIndex = computeBaseIndex();
		coinImg = coinImages[baseIndex + (typeOfImage - 1)];
		drawSurface(display, coinImg, position.getX() - beginningOfCamera, position.getY());
	}
}

