#ifndef _DestroyedCreature_H
#define _DestroyedCreature_H

#include "SDL_Interface.h"
#include "TemporaryObject.h"


class DestroyedCreature : public TemporaryObject {
private:
	static SDL_Surface* destroyedCreatureImage;
	int auxiliaryCounter;

public:
	DestroyedCreature();
	DestroyedCreature(int x, int y);
	void loadDestroyedCreatureImage(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif