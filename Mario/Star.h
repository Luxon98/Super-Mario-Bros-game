#ifndef _Star_H
#define _Star_H

#include "SDL_Utility.h"
#include "BonusObject.h"
#include "World.h"


class Star : public BonusObject {
private:
	static SDL_Surface* starImages[4];
	int stepsCounter;
	int stepsUp;
	Direction verticalDirection;

public:
	Star();
	Star(int x, int y);
	void loadStarImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	void move(Direction direction, int distance, World& world, Screen* mainScreen) override;
};

#endif
