#ifndef _Flag_H
#define _Flag_H

#include "SDL_Utility.h"
#include "InanimateObject.h"


class Flag : public InanimateObject
{
private:
	static SDL_Surface* flagImages[2];
	int stepsCounter;
	int stickPositionY;
	bool active;

public:
	Flag();
	Flag(Position* position);
	bool isActive() const;
	bool isDown() const;
	void setActiveState();
	void loadFlagImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	void changePosition();
};

#endif //_Flag_H

