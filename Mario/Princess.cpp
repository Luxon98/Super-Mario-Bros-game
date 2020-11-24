#include "Princess.h"

#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> Princess::princessImages;

Princess::Princess(Position position, bool fakePrincessFlag) : fakePrincessFlag(fakePrincessFlag)
{
	this->position = position;

	size = Size(0, 0);
}

void Princess::loadPrincessImages(SDL_Surface* display)
{
	princessImages[0] = loadPNG("./img/princess.png", display);
	princessImages[1] = loadPNG("./img/fake_princess.png", display);
}

void Princess::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 75 && position.getX() < endOfCamera + 75) {
		SDL_Surface* princessImg = princessImages[fakePrincessFlag];
		drawSurface(display, princessImg, position.getX() - beginningOfCamera, position.getY());
	}
}