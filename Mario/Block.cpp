#include "Block.h"

#include <string>
#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"


SDL_Surface* Block::blockImages[10] = { nullptr };

bool Block::changesChecker = true;

int Block::computeImageIndex()
{
	if (model <= Destructible) {
		return model - 1;
	}
	else if (model == Monetary || model == BonusWithStar) {
		return 3;
	}
	else if (model == Tube || model == TubeEntry) {
		return model - 4;
	}
	else if (model == BonusWithGreenMushroom) {
		return 9;
	}
	else {
		return 4;
	}
}

Size* Block::getSizeFromBlockType(BlockType type)
{
	if (type == Tube) {
		return new Size(56, 34);
	}
	else if (type == TubeEntry) {
		return new Size(64, 31);
	}
	else {
		return new Size(32, 32);
	}
}

Block::Block() {}

Block::Block(BlockType type, Position* position)
{
	model = type;
	this->position = position;
	size = getSizeFromBlockType(type);
	availableCoins = (type == Monetary ? 10 : 0);
	initialPositionY = position->getY();
}

int Block::getAvailableCoins() const
{
	return availableCoins;
}

bool Block::canBeHitted()
{
	return (position->getY() == initialPositionY);
}

bool Block::isInvisible()
{
	if (model == BonusWithGreenMushroom) {
		return true;
	}

	return false;
}

void Block::setModel(BlockType type)
{
	model = type;
}

void Block::setAvailableCoins(int coins)
{
	if (coins >= 0) {
		availableCoins = coins;
	}
}

void Block::addToPositionY(int y)
{
	position->setY(position->getY() + y);
}

void Block::changeBlockImage()
{
	Block::blockImages[4] = Block::blockImages[5 + Block::changesChecker];
	Block::changesChecker = !Block::changesChecker;
}

void Block::loadBlockImages(SDL_Surface* display)
{
	for (int i = 0; i < 5; ++i) {
		std::string filename = "./img/block";
		filename += std::to_string(i + 1);
		filename += ".png";
		blockImages[i] = loadPNG(filename, display);
	}
	blockImages[5] = loadPNG("./img/block5.png", display);
	blockImages[6] = loadPNG("./img/block6.png", display);
	blockImages[7] = loadPNG("./img/tube.png", display);
	blockImages[8] = loadPNG("./img/entry.png", display);
	blockImages[9] = loadPNG("./img/block_empty.png", display);
}

void Block::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera)
{
	if (position->getX() > beginningOfCamera - 120 && position->getX() < endOfCamera + 120) {
		SDL_Surface* blockImg = nullptr;
		blockImg = blockImages[computeImageIndex()];
		drawSurface(display, blockImg, position->getX() - beginningOfCamera, position->getY());
	}
}

