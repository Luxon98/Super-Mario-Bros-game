#ifndef Bush_H
#define Bush_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Bush : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 5> bushImages;

public:
	Bush() = default;
	Bush(int type, Position position);
	void loadBushImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //Bush_H

