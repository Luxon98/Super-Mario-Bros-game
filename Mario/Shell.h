#ifndef _Shell_H
#define _Shell_H

#include <chrono>
#include "SDL_Utility.h"
#include "World.h"
#include "IndependentLivingObject.h"


class Shell : public IndependentLivingObject
{
private:
	static SDL_Surface* shellImage;
	std::chrono::steady_clock::time_point creationTime;
	bool active;
	
public:
	Shell();
	Shell(Position* position);
	bool isActive();
	bool shouldTurnIntoTurtle();
	void setMovementDirectionAndActiveState(Direction direction);
	void resetCreationTime();
	void loadShellImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	void move(World& world) override;
};

#endif //_Shell_H

