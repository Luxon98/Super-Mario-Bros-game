#ifndef _CrushedCreature_H
#define _CrushedCreature_H

#include "SDL_Utility.h"
#include "TemporaryObject.h"


class CrushedCreature : public TemporaryObject {
private:
	static SDL_Surface* crushedCreatureImage;

public:
	CrushedCreature(); 
	CrushedCreature(Position* position);
	void loadCrushedCreatureImage(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif