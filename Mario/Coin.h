#ifndef _Coin_H
#define _Coin_H

#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Coin : public InanimateObject
{
private:
	static SDL_Surface* coinImages[2]; 

public:
	static int typeOfImage;
	Coin();
	Coin(Position* position);
	void loadCoinImages(SDL_Surface* display);
	static void changeCoinImage();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //_Coin_H

