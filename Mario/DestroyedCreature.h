#ifndef _DestroyedCreature_H
#define _DestroyedCreature_H

#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class DestroyedCreature : public TemporaryObject
{
private:
	static SDL_Surface* destroyedCreatureImage;
	int auxiliaryCounter;

public:
	DestroyedCreature();
	DestroyedCreature(Position* position);
	void loadDestroyedCreatureImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //_DestroyedCreature_H