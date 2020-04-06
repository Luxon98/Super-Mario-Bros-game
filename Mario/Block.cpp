#include "Block.h"

SDL_Surface* Block::blockImages[10] = { nullptr };

bool Block::changesChecker = true;

int Block::computeImageIndex() {
	if (this->model <= Destructible) {
		return this->model - 1;
	}
	else if (this->model == Monetary || this->model == BonusWithStar) {
		return 3;
	}
	else if (this->model == Tube || this->model == TubeEntry) {
		return this->model - 4;
	}
	else if (this->model == BonusWithGreenMushroom) {
		return 9;
	}
	else {
		return 4;
	}
}

Block::Block() {}

Block::Block(BlockType type, int x, int y) {
	this->model = type;
	this->positionX = x;
	this->positionY = y;
	if (type == Tube) {
		this->width = 56;
		this->height = 34;
	}
	else if (type == TubeEntry) {
		this->width = 64;
		this->height = 31;
	}
	else {
		this->width = 32;
		this->height = 32;
	}
	this->availableCoins = (type == Monetary ? 5 : 0);
}

int Block::getAvailableCoins() const {
	return this->availableCoins;
}

void Block::setModel(BlockType type) {
	this->model = type;
}

void Block::setAvailableCoins(int coins) {
	if (coins >= 0) {
		this->availableCoins = coins;
	}
}

void Block::changePositionY(int y) {
	this->positionY += y;
}

void Block::changeBlockImage() {
	Block::blockImages[4] = Block::blockImages[5 + Block::changesChecker];
	Block::changesChecker = !Block::changesChecker;
}

void Block::loadBlockImages(SDL_Surface* screen) {
	for (int i = 0; i < 5; ++i) {
		std::string filename = "./img/block";
		filename += std::to_string(i + 1);
		filename += ".png";
		blockImages[i] = loadPNG(filename, screen);
	}
	blockImages[5] = loadPNG("./img/block5.png", screen);
	blockImages[6] = loadPNG("./img/block6.png", screen);
	blockImages[7] = loadPNG("./img/tube.png", screen);
	blockImages[8] = loadPNG("./img/entry.png", screen);
	blockImages[9] = loadPNG("./img/block_empty.png", screen);
}

void Block::draw(SDL_Surface* screen, int beginningOfCamera) {
	SDL_Surface * blockImg = nullptr;
	blockImg = blockImages[this->computeImageIndex()];
	drawSurface(screen, blockImg, this->positionX - beginningOfCamera, this->positionY);
}

