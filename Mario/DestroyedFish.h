#ifndef DestroyedFish_H
#define DestroyedFish_H

#include <array>
#include "AnimatedObject.h"

class Position;
struct SDL_Surface;


class DestroyedFish : public AnimatedObject
{
private:
	static std::array<SDL_Surface*, 2> destroyedFishImages;
	bool directionFlag;
	int computeImageIndex() const override;

public:
	DestroyedFish(Position position, bool directionFlag);
	static void loadDestroyedFishImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //DestroyedFish_H