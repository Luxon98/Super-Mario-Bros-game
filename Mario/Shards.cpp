#include "Shards.h"

SDL_Surface* Shards::shardsImages[2] = { nullptr };

Shards::Shards() {}

Shards::Shards(int x, int y) {
	this->creationTime = std::chrono::steady_clock::now();
	this->positionsX[0] = x - 15;
	this->positionsY[0] = y - 15;
	this->positionsX[1] = x + 15;
	this->positionsY[1] = y - 15;
	this->positionsX[2] = x + 15;
	this->positionsY[2] = y + 15;
	this->positionsX[3] = x - 15;
	this->positionsY[3] = y + 15;
	this->auxiliaryCounter = 0;
	this->imageIndex = 0;
}

void Shards::loadShardsImages(SDL_Surface* screen) {
	this->shardsImages[0] = loadPNG("./img/shard1.png", screen);
	this->shardsImages[1] = loadPNG("./img/shard2.png", screen);
}

void Shards::draw(SDL_Surface* screen, int beginningOfCamera) {
	if (this->auxiliaryCounter % 30 == 0) {
		this->imageIndex = (this->imageIndex == 0 ? 1 : 0);
	}

	SDL_Surface* shardImg = this->shardsImages[this->imageIndex];
	for (int i = 0; i < 4; ++i) {
		drawSurface(screen, shardImg, this->positionsX[i] - beginningOfCamera, this->positionsY[i]);
	}
}

bool Shards::shouldBeRemoved() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (this->creationTime + std::chrono::milliseconds(3000) < timePoint);
}

void Shards::slide() {
	++this->auxiliaryCounter;
	if (this->auxiliaryCounter % 3 == 0) {
		if (this->auxiliaryCounter < 46) {
			this->positionsY[0] -= 5;
			this->positionsX[0] -= 5;
			this->positionsY[1] -= 5;
			this->positionsX[1] += 5;
			this->positionsY[2] -= 3;
			this->positionsX[2] += 3;
			this->positionsY[3] -= 3;
			this->positionsX[3] -= 3;
		}
		else if (this->auxiliaryCounter >= 46 && this->auxiliaryCounter < 55) {
			this->positionsY[0] -= 2;
			this->positionsX[0] -= 2;
			this->positionsY[1] -= 2;
			this->positionsX[1] += 2;
			this->positionsY[2] -= 2;
			this->positionsX[2] += 2;
			this->positionsY[3] -= 2;
			this->positionsX[3] -= 2;
		}
		else if (this->auxiliaryCounter >= 55 && this->auxiliaryCounter < 72) {
			this->positionsY[0] += 5;
			this->positionsX[0] -= 2;
			this->positionsY[1] += 5;
			this->positionsX[1] += 2;
			this->positionsY[2] += 4;
			this->positionsX[2] += 2;
			this->positionsY[3] += 4;
			this->positionsX[3] -= 2;
		}
		else if (this->auxiliaryCounter >= 72 && this->auxiliaryCounter < 146) {
			this->positionsY[0] += 5;
			this->positionsY[1] += 5;
			this->positionsY[2] += 3;
			this->positionsY[3] += 3;
		}
		else {
			for (int i = 0; i < 4; ++i) {
				this->positionsY[i] += 6;
			}
		}
	}
}

