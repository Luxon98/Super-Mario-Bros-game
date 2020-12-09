#include "Castle.h"

#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> Castle::castleImages;

Castle::Castle(Position position, bool bigCastleFlag)
{
	this->position = position;
	this->bigCastleFlag = bigCastleFlag;

	size = Size(0, 0);
}

void Castle::loadCastleImages(SDL_Surface* display)
{
	castleImages[0] = loadPNG("./img/ie_imgs/castle.png", display);
	castleImages[1] = loadPNG("./img/ie_imgs/big_castle.png", display);
}

void Castle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 200 && position.getX() < endOfCamera + 200) {
		SDL_Surface* castleImg = castleImages[bigCastleFlag];
		drawSurface(display, castleImg, position.getX() - beginningOfCamera, position.getY());
	}
}

