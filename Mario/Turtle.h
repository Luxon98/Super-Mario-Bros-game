#ifndef _Turtle_H
#define _Turtle_H

#include "IndependentLivingObject.h"

class World;
class Position;
enum Direction;
struct SDL_Surface;


class Turtle : public IndependentLivingObject
{
private:
	static SDL_Surface* turtleImages[4];
	int model;
	void chooseModel();

public:
	Turtle();
	Turtle(Position* position);
	void setMoveDirection(Direction direction);
	void loadTurtleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void move(World& world) override;
};

#endif //_Turtle_H
