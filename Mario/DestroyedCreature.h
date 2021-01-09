#ifndef DestroyedCreature_H
#define DestroyedCreature_H

#include <array>
#include "TemporaryObject.h"
#include "Direction.h"

struct SDL_Surface;


class DestroyedCreature : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 8> destroyedCreatureImages;
	Direction direction;
	int computeBaseIndex() const;
	int computeImageIndex() const override;

public:
	DestroyedCreature(Position position, Direction direction);
	static void loadDestroyedCreatureImages(SDL_Surface* display);
	void slide() override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //DestroyedCreature_H