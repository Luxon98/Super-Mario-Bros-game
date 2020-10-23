#include "Block.h"

#include <string>
#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 22> Block::blockImages;

bool Block::blockImage = true;

int Block::computeBaseIndex() const
{
	return (World::LAYOUT_STYLE == LayoutStyle::Underground ? 11 : 0);
}

int Block::computeImageIndex() const
{
	int baseIndex = computeBaseIndex();
	if (type <= BlockType::Destructible) {
		return (baseIndex + (static_cast<int>(type) - 1));
	}
	else if (type == BlockType::Monetary || type == BlockType::BonusWithStar) {
		return (baseIndex + 3);
	}
	else if (type == BlockType::Tube || type == BlockType::TubeTopEntry) {
		return (baseIndex + (static_cast<int>(type) - 4));
	}
	else if (type == BlockType::BonusWithOneUpMushroom) {
		return (baseIndex + (static_cast<int>(type) + 2));
	}
	else if (type == BlockType::TubeLeftEntry) {
		return (baseIndex + (static_cast<int>(type) - 3));
	}
	else {
		return (baseIndex + 4);
	}
}

Size Block::getSizeFromBlockType()
{
	switch (type) {
	case BlockType::Tube:
		return Size(56, 34);
	case BlockType::TubeTopEntry:
		return Size(64, 31);
	case BlockType::TubeLeftEntry:
		return Size(12, 64);
	default:
		return Size(32, 32);
	}
}

Block::Block(BlockType type, Position position)
{
	this->type = type;
	this->position = position;
	size = getSizeFromBlockType();
	availableCoins = (type == BlockType::Monetary ? 10 : 0);
	initialPositionY = position.getY();
	collisionsFlag = (type != BlockType::BonusWithOneUpMushroom);
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

	for (int j = 7; j < 16; ++j) {
		std::string filename = "./img/block";
		filename += std::to_string(j);
		filename += ".png";
		blockImages[j] = loadPNG(filename, display);
	}
	blockImages[16] = loadPNG("./img/block15.png", display);
	blockImages[17] = loadPNG("./img/block16.png", display);

	for (int j = 18; j < 22; ++j) {
		std::string filename = "./img/block";
		filename += std::to_string(j - 1);
		filename += ".png";
		blockImages[j] = loadPNG(filename, display);
	}
}

bool Block::hasCoins() const
{
	return (availableCoins > 0);
}

bool Block::canBeHitted() const
{
	return (position.getY() == initialPositionY);
}

bool Block::canCollideWithMushrooms() const
{
	return collisionsFlag;
}

bool Block::isInvisible() const
{
	if (type == BlockType::BonusWithOneUpMushroom && World::LAYOUT_STYLE == LayoutStyle::OpenWorld) {
		return true;
	}

	return false;
}

BlockType Block::getType() const
{
	return type;
}

void Block::resetBlockImage()
{
	Block::blockImage = true;
}

void Block::changeBlockImage()
{
	Block::blockImages[4] = Block::blockImages[5 + Block::blockImage];
	Block::blockImages[15] = Block::blockImages[16 + Block::blockImage];
	Block::blockImage = !Block::blockImage;
}

void Block::decrementCoins()
{
	if (availableCoins > 0) {
		--availableCoins;
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

void Block::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 120 && position.getX() < endOfCamera + 120) {
		SDL_Surface* blockImg = blockImages[computeImageIndex()];
		drawSurface(display, blockImg, position.getX() - beginningOfCamera, position.getY());
	}
}