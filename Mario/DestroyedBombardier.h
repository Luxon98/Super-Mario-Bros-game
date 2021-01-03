#ifndef DestroyedBombardier_H
#define DestroyedBombardier_H

#include <array>
#include "TemporaryObject.h"
#include "Direction.h"

class Position;
struct SDL_Surface;


class DestroyedBombardier :	public TemporaryObject 
{
private:
	static std::array<SDL_Surface*, 2> destroyedBombardierImages;
	bool leftSide;
	int computeImageIndex() const override;

public:
	DestroyedBombardier(Position position, bool leftSide);
	static void loadDestroyedBombardierImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //DestroyedBombardier_H