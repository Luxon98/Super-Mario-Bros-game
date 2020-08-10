#ifndef _Cloud_H
#define _Cloud_H

#include "SDL_Utility.h"
#include "InanimateObject.h"


class Cloud : public InanimateObject
{
private:
	static SDL_Surface* cloudImages[3];

public:
	Cloud();
	Cloud(int type, Position* position);
	void loadCloudImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
};

#endif //_Cloud_H