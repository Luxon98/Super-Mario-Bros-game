#ifndef _FireBall_H
#define _FireBall_H

#include "IndependentLivingObject.h"

class World;
class Position;
enum Direction;
struct SDL_Surface;


class FireBall : public IndependentLivingObject
{
private:
	static SDL_Surface* fireBallImages[4];
	int stepsUp;
	int modelIndex;
	bool stop;
	void computeModelIndex();
	void makeVerticalMove(World& world);
	void makeHorizontalMove(World& world);

public:
	FireBall();
	FireBall(Position* position, Direction direction);
	bool shouldBeRemoved();
	void loadFireBallImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void move(World& world) override;
};

#endif //_FireBall_H
