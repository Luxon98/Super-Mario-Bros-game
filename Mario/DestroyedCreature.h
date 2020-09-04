#ifndef DestroyedCreature_H
#define DestroyedCreature_H

#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class DestroyedCreature : public TemporaryObject
{
private:
	static SDL_Surface* destroyedCreatureImage;

public:
	DestroyedCreature() = default;
	DestroyedCreature(Position position);
	void loadDestroyedCreatureImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //DestroyedCreature_H