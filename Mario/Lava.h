#ifndef Lava_H
#define Lava_H

#include <array>
#include "InanimateObject.h"

struct SDL_Surface;


class Lava : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 2> lavaImages;

public:
	Lava(Position position);
	static void loadLavaImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Lava_H