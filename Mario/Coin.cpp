#include "Coin.h"

SDL_Surface* Coin::coinImages[2] = { nullptr };

int Coin::typeOfImage = 2;

Coin::Coin() {}

Coin::Coin(Position* position)
{
	this->position = position;
	size = new Size(11, 17);
}

void Coin::loadCoinImages(SDL_Surface* screen)
{
	coinImages[0] = loadPNG("./img/coin1.png", screen);
	coinImages[1] = loadPNG("./img/coin2.png", screen);
}

void Coin::changeCoinImage()
{
	Coin::typeOfImage = (Coin::typeOfImage == 1 ? 2 : 1);
}

void Coin::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* coinImg = nullptr;
	coinImg = coinImages[typeOfImage - 1];
	drawSurface(screen, coinImg, position->getX() - beginningOfCamera, position->getY());
}

