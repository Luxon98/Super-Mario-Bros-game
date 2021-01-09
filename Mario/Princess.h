#ifndef Princess_H
#define Princess_H

#include <array>
#include "InanimateObject.h"

struct SDL_Surface;


class Princess : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 2> princessImages;
	bool fakePrincessFlag;

public:
	Princess(Position position, bool fakePrincessFlag);
	static void loadPrincessImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Princess_H