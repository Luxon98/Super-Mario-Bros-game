#ifndef Bush_H
#define Bush_H

#include <array>
#include "InanimateObject.h"

class Position;
class Size;
struct SDL_Surface;


class Bush : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 5> bushImages;
	Size getSizeFromModel() const;

public:
	Bush(int type, Position position);
	static void loadBushImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Bush_H