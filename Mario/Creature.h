#ifndef _Creature_H
#define _Creature_H

#include "IndependentLivingObject.h"

class World;
class Position;
enum Direction;
struct SDL_Surface;


class Creature : public IndependentLivingObject
{
private:
	static SDL_Surface* creatureImages[2];
	int model;
	void changeModel();

public:
	Creature();
	Creature(Position* position);
	void setMoveDirection(Direction direction);
	void loadCreatureImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void move(World& world) override;
};

#endif //_Creature_H