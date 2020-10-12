#include "Block.h"

#include <string>
#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 20> Block::blockImages;

bool Block::blockImage = true;

int Block::computeBaseIndex() const
{
	return (World::LAYOUT_STYLE == LayoutStyle::Underground ? 10 : 0);
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
	else if (type == BlockType::Tube || type == BlockType::TubeEntry) {
		return (baseIndex + (static_cast<int>(type) - 4));
	}
	else if (type == BlockType::BonusWithOneUpMushroom) {
		return (baseIndex + (static_cast<int>(type) + 2));
	}
	else {
		return (baseIndex + 4);
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

bool Block::hasCoins() const
{
	return (availableCoins > 0);
}

bool Block::canBeHitted() const
{
	return (position.getY() == initialPositionY);
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
	Block::blockImages[14] = Block::blockImages[15 + Block::blockImage];
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

	for (int j = 7; j < 15; ++j) {
		std::string filename = "./img/block";
		filename += std::to_string(j);
		filename += ".png";
		blockImages[j] = loadPNG(filename, display);
	}
	blockImages[15] = loadPNG("./img/block14.png", display);
	blockImages[16] = loadPNG("./img/block15.png", display);

	for (int j = 17; j < 20; ++j) {
		std::string filename = "./img/block";
		filename += std::to_string(j - 1);
		filename += ".png";
		blockImages[j] = loadPNG(filename, display);
	}
}

void Block::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 120 && position.getX() < endOfCamera + 120) {
		SDL_Surface* blockImg = nullptr;
		blockImg = blockImages[computeImageIndex()];
		drawSurface(display, blockImg, position.getX() - beginningOfCamera, position.getY());
	}
}

