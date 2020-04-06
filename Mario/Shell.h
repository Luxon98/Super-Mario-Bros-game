#ifndef _Shell_H
#define _Shell_H

#include <chrono>
#include "SDL_Utility.h"
#include "NonControllableLivingObject.h"
#include "World.h"


class Shell : public NonControllableLivingObject {
private:
	static SDL_Surface* shellImg;
	std::chrono::steady_clock::time_point creationTime;
	bool active;
	
public:
	Shell();
	Shell(int x, int y);
	bool isActive();
	bool shouldTurnIntoTurtle();
	void setMovementDirectionAndActiveState(Direction direction);
	void resetCreationTime();
	void loadShellImage(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	void move(Direction direction, int distance, World& world, Screen* mainScreen) override;
};

#endif

