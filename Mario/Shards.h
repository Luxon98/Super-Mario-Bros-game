#ifndef Shards_H
#define Shards_H

#include <array>
#include <vector>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class Shards : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 2> shardsImages;
	std::vector<Position> shardsPositions;
	int imageIndex;
	void initPositionsVector(Position position);

public:
	Shards() = default;
	Shards(Position position);
	void loadShardsImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //Shards_H
