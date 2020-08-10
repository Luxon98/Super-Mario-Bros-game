#ifndef _Star_H
#define _Star_H

#include "SDL_Utility.h"
#include "BonusObject.h"
#include "World.h"
#include "Direction.h"


class Star : public BonusObject 
{
private:
	static SDL_Surface* starImages[4];
	int stepsCounter;
	int stepsUp;
	Direction verticalDirection;

public:
	Star();
	Star(Position* position);
	void loadStarImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	void move(World& world) override;
};

#endif //_Star_H
