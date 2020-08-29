#ifndef _Shards_H
#define _Shards_H

#include <vector>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


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
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //_Shards_H
