#ifndef _Coin_H
#define _Coin_H

#include "SDL_Utility.h"
#include "InanimateObject.h"


class Coin : public InanimateObject {
private:
	static SDL_Surface* coinImages[2]; 

public:
	static int typeOfImage;
	Coin();
	Coin(Position* position);
	void loadCoinImages(SDL_Surface* screen);
	static void changeCoinImage();
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
};

#endif

