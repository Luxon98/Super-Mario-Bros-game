#ifndef Lava_H
#define Lava_H

#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Lava : public InanimateObject
{
private:
	static SDL_Surface* lavaImage;

public:
	Lava() = default;
	Lava(Position position);
	static void loadLavaImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Lava_H