#ifndef Explosion_H
#define Explosion_H

#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class Explosion : public TemporaryObject
{
private:
	static SDL_Surface* explosionImage;

public:
	Explosion();
	Explosion(Position position);
	void loadExplosionImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //Explosion_H

