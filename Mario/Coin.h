#ifndef Coin_H
#define Coin_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Coin : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 4> coinImages; 
	int computeBaseIndex() const;

public:
	static int typeOfImage;
	Coin() = default;
	Coin(Position position);
	void loadCoinImages(SDL_Surface* display);
	static void changeCoinImage();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Coin_H

