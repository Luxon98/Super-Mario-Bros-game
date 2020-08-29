#ifndef _Flag_H
#define _Flag_H

#include "InanimateObject.h"

class Position;
struct SDL_Surface;


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
	void loadFlagImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void changePosition();
};

#endif //_Flag_H

