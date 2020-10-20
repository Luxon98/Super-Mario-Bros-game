#ifndef Castle_H
#define Castle_H

#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Castle : public InanimateObject
{
private:
	static SDL_Surface* castleImage;

public:
	Castle() = default;
	Castle(Position position);
	static void loadCastleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Castle_H

