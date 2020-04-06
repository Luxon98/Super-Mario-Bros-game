#ifndef _Castle_H
#define _Castle_H

#include "SDL_Utility.h"
#include "InanimateObject.h"


class Castle : public InanimateObject {
private:
	static SDL_Surface* castleImage;

public:
	Castle();
	Castle(int x, int y);
	void loadCastleImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
};

#endif

