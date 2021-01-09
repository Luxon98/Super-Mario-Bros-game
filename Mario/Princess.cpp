#include "Princess.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> Princess::princessImages;

Princess::Princess(Position position, bool fakePrincessFlag) : fakePrincessFlag(fakePrincessFlag)
{
	this->position = position;
	size = Size(32, 48);
}

void Princess::loadPrincessImages(SDL_Surface* display)
{
	princessImages[0] = loadPNG("./img/ie_imgs/princess.png", display);
	princessImages[1] = loadPNG("./img/ie_imgs/fake_princess.png", display);
}

void Princess::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* princessImg = princessImages[fakePrincessFlag];
		drawSurface(display, princessImg, position.getX() - beginningOfCamera, position.getY());
	}
}