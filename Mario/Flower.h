#ifndef _Flower_H
#define _Flower_H

#include "SDL_Utility.h"
#include "BonusObject.h"
#include "World.h"


class Flower : public BonusObject
{
private:
	static SDL_Surface* flowerImages[2];

public:
	static int typeOfImage;
	Flower();
	Flower(Position* position);
	static void changeFlowerImage();
	void loadFlowerImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	void move(World& world) override;
};

#endif //_Flower_H

