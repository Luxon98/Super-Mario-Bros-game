#ifndef Coin_H
#define Coin_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Coin : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 2> coinImages; 

public:
	static int typeOfImage;
	Coin();
	Coin(Position position);
	void loadCoinImages(SDL_Surface* display);
	static void changeCoinImage();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //Coin_H

