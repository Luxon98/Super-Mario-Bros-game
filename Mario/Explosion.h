#ifndef Explosion_H
#define Explosion_H

#include <array>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class Explosion : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 3> explosionImages;
	int computeIndex() const;

public:
	Explosion() = default;
	Explosion(Position position);
	static void loadExplosionImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //Explosion_H

