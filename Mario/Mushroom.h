#ifndef _Mushroom_H
#define _Mushroom_H

#include "SDL_Utility.h"
#include "BonusObject.h"
#include "World.h"


class Mushroom : public BonusObject 
{
private:
	static SDL_Surface* mushroomImages[2];
	bool greenColor;

public:
	Mushroom();
	Mushroom(Position* position, bool greenColor);
	bool isGreen();
	void loadMushroomImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	void move(Direction direction, int distance, World& world, Screen* mainScreen) override;
};

#endif //_Mushroom_H
