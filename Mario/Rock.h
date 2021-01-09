#ifndef Rock_H
#define Rock_H

#include "InanimateObject.h"

struct SDL_Surface;


class Rock : public InanimateObject
{
private:
	static SDL_Surface* rockImage;

public:
	Rock(Position position);
	static void loadRockImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Rock_H