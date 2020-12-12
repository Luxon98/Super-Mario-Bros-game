#include "Shards.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"

// the first four pictures are from the original Mario
// the last two are custom pictures, created for the needs of the Winter world
std::array<SDL_Surface*, 6> Shards::shardsImages;

int Shards::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::Underground) {
		return 2;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::CustomWinter) {
		return 4;
	}
	else {
		return 0;
	}
}

int Shards::computeImageIndex() const {
	int baseIndex = computeBaseIndex();
	return baseIndex + imageIndex;
}

void Shards::initPositionsVector(Position position)
{
	shardsPositions.push_back(Position(position.getX() - 15, position.getY() - 15));
	shardsPositions.push_back(Position(position.getX() + 15, position.getY() - 15));
	shardsPositions.push_back(Position(position.getX() + 15, position.getY() + 15));
	shardsPositions.push_back(Position(position.getX() - 15, position.getY() + 15));
}

Shards::Shards(Position position)
{
	initPositionsVector(position);
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
	imageIndex = 0;
}

void Shards::loadShardsImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < shardsImages.size(); ++i) {
		std::string filename = "./img/anm_imgs/shard";
		filename += std::to_string(i + 1);
		filename += ".png";
		shardsImages[i] = loadPNG(filename, display);
	}
}

void Shards::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	SDL_Surface* shardImg = shardsImages[computeImageIndex()];
	for (int i = 0; i < 4; ++i) {
		drawSurface(display, shardImg, shardsPositions[i].getX() - beginningOfCamera, shardsPositions[i].getY());
	}
}

bool Shards::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(3000) < timePoint);
}

void Shards::slide()
{
	++auxiliaryCounter;
	if (auxiliaryCounter & 1) {
		if (auxiliaryCounter < 30) {
			shardsPositions[0].setY(shardsPositions[0].getY() - 5);
			shardsPositions[0].setX(shardsPositions[0].getX() - 5);
			shardsPositions[1].setY(shardsPositions[1].getY() - 5);
			shardsPositions[1].setX(shardsPositions[1].getX() + 5);
			shardsPositions[2].setY(shardsPositions[2].getY() - 3);
			shardsPositions[2].setX(shardsPositions[2].getX() + 3);
			shardsPositions[3].setY(shardsPositions[3].getY() - 3);
			shardsPositions[3].setX(shardsPositions[3].getX() - 3);
		}
		else if (auxiliaryCounter >= 30 && auxiliaryCounter < 36) {
			shardsPositions[0].setY(shardsPositions[0].getY() - 2);
			shardsPositions[0].setX(shardsPositions[0].getX() - 2);
			shardsPositions[1].setY(shardsPositions[1].getY() - 2);
			shardsPositions[1].setX(shardsPositions[1].getX() + 2);
			shardsPositions[2].setY(shardsPositions[2].getY() - 2);
			shardsPositions[2].setX(shardsPositions[2].getX() + 2);
			shardsPositions[3].setY(shardsPositions[3].getY() - 2);
			shardsPositions[3].setX(shardsPositions[3].getX() - 2);
		}
		else if (auxiliaryCounter >= 36 && auxiliaryCounter < 48) {
			shardsPositions[0].setY(shardsPositions[0].getY() + 5);
			shardsPositions[0].setX(shardsPositions[0].getX() - 2);
			shardsPositions[1].setY(shardsPositions[1].getY() + 5);
			shardsPositions[1].setX(shardsPositions[1].getX() + 2);
			shardsPositions[2].setY(shardsPositions[2].getY() + 4);
			shardsPositions[2].setX(shardsPositions[2].getX() - 2);
			shardsPositions[3].setY(shardsPositions[3].getY() + 4);
			shardsPositions[3].setX(shardsPositions[3].getX() + 2);
		}
		else if (auxiliaryCounter >= 48 && auxiliaryCounter < 98) {
			shardsPositions[0].setY(shardsPositions[0].getY() + 5);
			shardsPositions[1].setY(shardsPositions[1].getY() + 5);
			shardsPositions[2].setY(shardsPositions[2].getY() + 3);
			shardsPositions[3].setY(shardsPositions[3].getY() + 3);
		}
		else {
			for (int i = 0; i < 4; ++i) {
				shardsPositions[i].setY(shardsPositions[i].getY() + 6);
			}
		}
	}

	if (auxiliaryCounter % 30 == 0) {
		imageIndex = (imageIndex == 0 ? 1 : 0);
	}
}

