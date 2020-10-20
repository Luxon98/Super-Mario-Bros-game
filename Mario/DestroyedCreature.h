#ifndef DestroyedCreature_H
#define DestroyedCreature_H

#include <array>
#include "TemporaryObject.h"
#include "Direction.h"

class Position;
struct SDL_Surface;


class DestroyedCreature : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 4> destroyedCreatureImages;
	Direction slideDirection;
	int computeImageIndex() const override;

public:
	DestroyedCreature() = default;
	DestroyedCreature(Position position, Direction slideDirection);
	static void loadDestroyedCreatureImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //DestroyedCreature_H