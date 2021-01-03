#ifndef DestroyedFish_H
#define DestroyedFish_H

#include <array>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class DestroyedFish : public TemporaryObject
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