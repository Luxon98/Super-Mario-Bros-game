#ifndef _Explosion_H
#define _Explosion_H

#include "SDL_Utility.h"
#include "TemporaryObject.h"


class Explosion : public TemporaryObject
{
private:
	static SDL_Surface* explosionImage;

public:
	Explosion();
	Explosion(Position* position);
	void loadExplosionImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //_Explosion_H

