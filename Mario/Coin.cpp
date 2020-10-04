#include "Coin.h"

#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 4> Coin::coinImages;

bool Coin::coinImage = true;

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

void Coin::resetCoinImage()
{
	Coin::coinImage = true;
}

void Coin::changeCoinImage()
{
	Coin::coinImage = !Coin::coinImage;
}

void Coin::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		SDL_Surface* coinImg = nullptr;
		int baseIndex = computeBaseIndex();
		coinImg = coinImages[baseIndex + coinImage];
		drawSurface(display, coinImg, position.getX() - beginningOfCamera, position.getY());
	}
}

