#ifndef _FireBall_H
#define _FireBall_H


#include "SDL_Utility.h"
#include "NonControllableLivingObject.h"
#include "World.h"


class FireBall : public NonControllableLivingObject
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
	void loadFireBallImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	void move(Direction direction, int distance, World& world, Screen* mainScreen) override;
};

#endif //_FireBall_H
