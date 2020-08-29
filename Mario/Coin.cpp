#include "Coin.h"

#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"


SDL_Surface* Coin::coinImages[2] = { nullptr };

int Coin::typeOfImage = 2;

Coin::Coin() {}

Coin::Coin(Position* position)
{
	this->position = position;
	size = new Size(11, 17);
}

void Coin::loadCoinImages(SDL_Surface* display)
{
	coinImages[0] = loadPNG("./img/coin1.png", display);
	coinImages[1] = loadPNG("./img/coin2.png", display);
}

void Coin::changeCoinImage()
{
	Coin::typeOfImage = (Coin::typeOfImage == 1 ? 2 : 1);
}

void Coin::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position->getX() > beginningOfCamera - 60 && position->getX() < endOfCamera + 60) {
		SDL_Surface* coinImg = nullptr;
		coinImg = coinImages[typeOfImage - 1];
		drawSurface(display, coinImg, position->getX() - beginningOfCamera, position->getY());
	}
}

