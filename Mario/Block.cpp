#include "Block.h"

#include <string>
#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 10> Block::blockImages;

bool Block::changesChecker = true;

int Block::computeImageIndex() const
{
	if (type <= BlockType::Destructible) {
		return (static_cast<int>(type) - 1);
	}
	else if (type == BlockType::Monetary || type == BlockType::BonusWithStar) {
		return 3;
	}
	else if (type == BlockType::Tube || type == BlockType::TubeEntry) {
		return (static_cast<int>(type) - 4);
	}
	else if (type == BlockType::BonusWithGreenMushroom) {
		return 9;
	}
	else {
		return 4;
	}
}

Size Block::getSizeFromBlockType(BlockType type)
{
	if (type == BlockType::Tube) {
		return Size(56, 34);
	}
	else if (type == BlockType::TubeEntry) {
		return Size(64, 31);
	}
	else {
		return Size(32, 32);
	}
}

Block::Block(BlockType type, Position position)
{
	this->type = type;
	this->position = position;
	size = getSizeFromBlockType(type);
	availableCoins = (type == BlockType::Monetary ? 10 : 0);
	initialPositionY = position.getY();
}

int Block::getAvailableCoins() const
{
	return availableCoins;
}

bool Block::canBeHitted() const
{
	return (position.getY() == initialPositionY);
}

bool Block::isInvisible() const
{
	if (type == BlockType::BonusWithGreenMushroom) {
		return true;
	}

	return false;
}

BlockType Block::getType() const
{
	return type;
}

void Block::setAvailableCoins(int coins)
{
	if (coins >= 0) {
		availableCoins = coins;
	}
}

void Block::setType(BlockType type)
{
	this->type = type;
}

void Block::addToPositionY(int y)
{
	position.setY(position.getY() + y);
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

void Block::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 120 && position.getX() < endOfCamera + 120) {
		SDL_Surface* blockImg = nullptr;
		blockImg = blockImages[computeImageIndex()];
		drawSurface(display, blockImg, position.getX() - beginningOfCamera, position.getY());
	}
}

