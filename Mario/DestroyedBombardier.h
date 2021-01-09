#ifndef DestroyedBombardier_H
#define DestroyedBombardier_H

#include <array>
#include "TemporaryObject.h"
#include "Direction.h"

struct SDL_Surface;


class DestroyedBombardier :	public TemporaryObject 
{
private:
	static std::array<SDL_Surface*, 2> destroyedBombardierImages;
	Direction direction;
	int computeImageIndex() const override;

public:
	DestroyedBombardier(Position position, Direction direction);
	static void loadDestroyedBombardierImages(SDL_Surface* display);
	void slide() override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //DestroyedBombardier_H