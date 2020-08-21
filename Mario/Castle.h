#ifndef _Castle_H
#define _Castle_H

#include "SDL_Utility.h"
#include "InanimateObject.h"


class Castle : public InanimateObject
{
private:
	static SDL_Surface* castleImage;

public:
	Castle();
	Castle(Position* position);
	void loadCastleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //_Castle_H

