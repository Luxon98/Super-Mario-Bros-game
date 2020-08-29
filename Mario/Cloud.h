#ifndef _Cloud_H
#define _Cloud_H

#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Cloud : public InanimateObject
{
private:
	static SDL_Surface* cloudImages[3];

public:
	Cloud();
	Cloud(int type, Position* position);
	void loadCloudImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //_Cloud_H