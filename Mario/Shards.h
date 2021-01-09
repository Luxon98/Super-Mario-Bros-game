#ifndef Shards_H
#define Shards_H

#include <array>
#include <vector>
#include "TemporaryObject.h"

struct SDL_Surface;


class Shards : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 6> shardsImages;
	std::vector<Position> shardsPositions;
	int imageIndex;
	void initPositionsVector(Position position);
	int computeBaseIndex() const;
	int computeImageIndex() const override;

public:
	Shards(Position position);
	static void loadShardsImages(SDL_Surface* display);
	bool shouldBeRemoved() const override;
	void slide() override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Shards_H
