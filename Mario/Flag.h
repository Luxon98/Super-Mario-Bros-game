#ifndef _Flag_H
#define _Flag_H

#include "SDL_Interface.h"
#include "InanimateObject.h"


class Flag : public InanimateObject {
private:
	static SDL_Surface* flagImages[2];
	int stepsCounter;
	int stickPositionY;
	bool active;

public:
	Flag();
	Flag(int x, int y);
	bool isActive() const;
	bool isDown() const;
	void setActiveState();
	void loadFlagImage(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	void changePosition();
};

#endif

