#ifndef _Creature_H
#define _Creature_H

#include "SDL_Utility.h"
#include "NonControllableLivingObject.h"
#include "World.h"


class Creature : public NonControllableLivingObject 
{
private:
	static SDL_Surface* creatureImages[2];
	int model;
	void changeModel();

public:
	Creature();
	Creature(Position* position);
	void setMoveDirection(Direction direction);
	void loadCreatureImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	void move(Direction direction, int distance, World& world, Screen* mainScreen) override;
};

#endif //_Creature_H