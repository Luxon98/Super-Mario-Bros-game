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
	DestroyedCreature();
	DestroyedCreature(Position position);
	void loadDestroyedCreatureImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //DestroyedCreature_H