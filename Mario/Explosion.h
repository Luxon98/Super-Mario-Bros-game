#ifndef _Explosion_H
#define _Explosion_H

#include "SDL_Utility.h"
#include "TemporaryObject.h"


class Explosion : public TemporaryObject {
private:
	static SDL_Surface* explosionImage;

public:
	Explosion();
	Explosion(int x, int y);
	void loadExplosionImage(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif

