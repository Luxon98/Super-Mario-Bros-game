#ifndef Castle_H
#define Castle_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Castle : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 2> castleImages;
	bool bigCastleFlag;

public:
	Castle(Position position, bool bigCastleFlag);
	static void loadCastleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Castle_H

