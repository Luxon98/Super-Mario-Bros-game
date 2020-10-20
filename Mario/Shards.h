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
	static std::array<SDL_Surface*, 4> shardsImages;
	std::vector<Position> shardsPositions;
	int imageIndex;
	int computeImageIndex() const;
	void initPositionsVector(Position position);

public:
	Shards() = default;
	Shards(Position position);
	static void loadShardsImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //Shards_H
