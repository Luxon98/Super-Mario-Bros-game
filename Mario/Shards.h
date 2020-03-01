#ifndef _Shards_H
#define _Shards_H

#include "SDL_Interface.h"
#include "TemporaryObject.h"


class Shards : public TemporaryObject {
private:
	static SDL_Surface* shardsImages[2];
	int positionsX[4];
	int positionsY[4];
	int auxiliaryCounter;
	int imageIndex;

public:
	Shards();
	Shards(int x, int y);
	void loadShardsImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif
