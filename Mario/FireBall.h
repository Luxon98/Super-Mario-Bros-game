#ifndef _FireBall_H
#define _FireBall_H


#include "SDL_Utility.h"
#include "World.h"
#include "Direction.h"


class FireBall : public LivingObject
{
private:
	static SDL_Surface* fireBallImages[4];
	Direction verticalDirection;
	int stepsUp;
	int modelIndex;
	bool stop;
	void computeModelIndex();

public:
	FireBall();
	FireBall(Position* position, Direction direction);
	bool shouldBeRemoved();
	void loadFireBallImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	void move(World& world) override;
};

#endif //_FireBall_H
