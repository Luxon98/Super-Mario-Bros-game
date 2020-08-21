#ifndef _Bush_H
#define _Bush_H

#include <string>
#include "SDL_Utility.h"
#include "InanimateObject.h"


class Bush : public InanimateObject
{
private:
	static SDL_Surface* bushImages[5];

public:
	Bush();
	Bush(int type, Position* position);
	void loadBushImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //_Bush_H

