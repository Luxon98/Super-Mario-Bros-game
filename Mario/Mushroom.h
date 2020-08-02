#ifndef _Mushroom_H
#define _Mushroom_H

#include "SDL_Utility.h"
#include "BonusObject.h"
#include "World.h"


class Mushroom : public BonusObject {
private:
	static SDL_Surface* mushroomImages[2];
	bool green;

public:
	Mushroom();
	Mushroom(Position* position, bool colour);
	bool isGreen();
	void loadMushroomImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	void move(Direction direction, int distance, World& world, Screen* mainScreen) override;
};

#endif
