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
	Castle();
	Castle(Position position);
	void loadCastleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //Castle_H

