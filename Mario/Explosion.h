#ifndef Explosion_H
#define Explosion_H

#include <array>
#include "AnimatedObject.h"

class Position;
struct SDL_Surface;


class Explosion : public AnimatedObject
{
private:
	static std::array<SDL_Surface*, 3> explosionImages;
	int computeImageIndex() const override;

public:
	Explosion(Position position);
	static void loadExplosionImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //Explosion_H

