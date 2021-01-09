#include "Shards.h"

#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 6> Shards::shardsImages;

void Shards::initPositionsVector(Position position)
{
	shardsPositions.push_back(Position(position.getX() - 15, position.getY() - 15));
	shardsPositions.push_back(Position(position.getX() + 15, position.getY() - 15));
	shardsPositions.push_back(Position(position.getX() + 15, position.getY() + 15));
	shardsPositions.push_back(Position(position.getX() - 15, position.getY() + 15));
}

int Shards::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::Underground || World::LAYOUT_STYLE == LayoutStyle::CustomWinter) {
		return static_cast<int>(World::LAYOUT_STYLE) + 1;
	}
	else {
		return 0;
	}
}

int Shards::computeImageIndex() const {
	int baseIndex = computeBaseIndex();
	return baseIndex + imageIndex;
}

Shards::Shards(Position position)
{
	initPositionsVector(position);
	auxiliaryCounter = 0;
	imageIndex = 0;
	// it is an object containing few shars and its size cannot be determined correctly
	// additionaly, its size is not needed for anything
	size = Size(0, 0);
}

void Shards::loadShardsImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < shardsImages.size(); ++i) {
		std::string filename = "./img/temp_imgs/shard";
		filename += std::to_string(i + 1);
		filename += ".png";
		shardsImages[i] = loadPNG(filename, display);
	}
}

bool Shards::shouldBeRemoved() const
{
	return (shardsPositions[0].getY() > 530);
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

void Shards::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	SDL_Surface* shardImg = shardsImages[computeImageIndex()];
	for (int i = 0; i < 4; ++i) {
		drawSurface(display, shardImg, shardsPositions[i].getX() - beginningOfCamera, shardsPositions[i].getY());
	}
}