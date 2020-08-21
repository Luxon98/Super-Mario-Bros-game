#include "Shards.h"

SDL_Surface* Shards::shardsImages[2] = { nullptr };

void Shards::initPositionsVector(Position* position)
{
	shardsPositions.push_back(new Position(position->getX() - 15, position->getY() - 15));
	shardsPositions.push_back(new Position(position->getX() + 15, position->getY() - 15));
	shardsPositions.push_back(new Position(position->getX() + 15, position->getY() + 15));
	shardsPositions.push_back(new Position(position->getX() - 15, position->getY() + 15));
}

Shards::Shards() {}

Shards::Shards(Position* position)
{
	initPositionsVector(position);
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
	imageIndex = 0;
}

void Shards::loadShardsImages(SDL_Surface* display)
{
	shardsImages[0] = loadPNG("./img/shard1.png", display);
	shardsImages[1] = loadPNG("./img/shard2.png", display);
}

void Shards::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (auxiliaryCounter % 30 == 0) {
		imageIndex = (imageIndex == 0 ? 1 : 0);
	}

	SDL_Surface* shardImg = shardsImages[imageIndex];
	for (int i = 0; i < 4; i++) {
		drawSurface(display, shardImg, shardsPositions[i]->getX() - beginningOfCamera, shardsPositions[i]->getY());
	}
}

bool Shards::shouldBeRemoved()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(3000) < timePoint);
}

void Shards::slide()
{
	auxiliaryCounter++;
	if (auxiliaryCounter % 3 == 0) {
		if (auxiliaryCounter < 46) {
			shardsPositions[0]->setY(shardsPositions[0]->getY() - 5);
			shardsPositions[0]->setX(shardsPositions[0]->getX() - 5);
			shardsPositions[1]->setY(shardsPositions[1]->getY() - 5);
			shardsPositions[1]->setX(shardsPositions[1]->getX() + 5);
			shardsPositions[2]->setY(shardsPositions[2]->getY() - 3);
			shardsPositions[2]->setX(shardsPositions[2]->getX() + 3);
			shardsPositions[3]->setY(shardsPositions[3]->getY() - 3);
			shardsPositions[3]->setX(shardsPositions[3]->getX() - 3);
		}
		else if (auxiliaryCounter >= 46 && auxiliaryCounter < 55) {
			shardsPositions[0]->setY(shardsPositions[0]->getY() - 2);
			shardsPositions[0]->setX(shardsPositions[0]->getX() - 2);
			shardsPositions[1]->setY(shardsPositions[1]->getY() - 2);
			shardsPositions[1]->setX(shardsPositions[1]->getX() + 2);
			shardsPositions[2]->setY(shardsPositions[2]->getY() - 2);
			shardsPositions[2]->setX(shardsPositions[2]->getX() + 2);
			shardsPositions[3]->setY(shardsPositions[3]->getY() - 2);
			shardsPositions[3]->setX(shardsPositions[3]->getX() - 2);
		}
		else if (auxiliaryCounter >= 55 && auxiliaryCounter < 72) {
			shardsPositions[0]->setY(shardsPositions[0]->getY() + 5);
			shardsPositions[0]->setX(shardsPositions[0]->getX() - 2);
			shardsPositions[1]->setY(shardsPositions[1]->getY() + 5);
			shardsPositions[1]->setX(shardsPositions[1]->getX() + 2);
			shardsPositions[2]->setY(shardsPositions[2]->getY() + 4);
			shardsPositions[2]->setX(shardsPositions[2]->getX() - 2);
			shardsPositions[3]->setY(shardsPositions[3]->getY() + 4);
			shardsPositions[3]->setX(shardsPositions[3]->getX() + 2);
		}
		else if (auxiliaryCounter >= 72 && auxiliaryCounter < 146) {
			shardsPositions[0]->setY(shardsPositions[0]->getY() + 5);
			shardsPositions[1]->setY(shardsPositions[1]->getY() + 5);
			shardsPositions[2]->setY(shardsPositions[2]->getY() + 3);
			shardsPositions[3]->setY(shardsPositions[3]->getY() + 3);
		}
		else {
			for (int i = 0; i < 4; ++i) {
				shardsPositions[i]->setY(shardsPositions[i]->getY() + 6);
			}
		}
	}
}

