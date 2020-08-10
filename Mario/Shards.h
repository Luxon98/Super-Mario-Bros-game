#ifndef _Shards_H
#define _Shards_H

#include <vector>
#include "SDL_Utility.h"
#include "TemporaryObject.h"


class Shards : public TemporaryObject
{
private:
	static SDL_Surface* shardsImages[2];
	std::vector<Position*> shardsPositions;
	int auxiliaryCounter;
	int imageIndex;
	void initPositionsVector(Position* position);

public:
	Shards();
	Shards(Position* position);
	void loadShardsImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //_Shards_H
