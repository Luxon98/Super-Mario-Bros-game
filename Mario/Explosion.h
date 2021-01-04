#ifndef Explosion_H
#define Explosion_H

#include <array>
#include <chrono>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class Explosion : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 3> explosionImages;
	std::chrono::steady_clock::time_point creationTime;
	int computeImageIndex() const override;

public:
	Explosion(Position position);
	static void loadExplosionImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
};

#endif //Explosion_H

