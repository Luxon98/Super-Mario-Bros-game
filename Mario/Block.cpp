#include "Block.h"

#include <string>
#include "Position.h"
#include "Size.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


// pictures of blocks with indexes 0-35 are pictures from the original Super Mario Bros
// the last twelve are custom graphics, created by me for the needs of the Winter World
std::array<SDL_Surface*, 48> Block::blockImages;
std::array<SDL_Surface*, 12> Block::landImages;

bool Block::blockImage = true;

int Block::computeBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld || World::LAYOUT_STYLE == LayoutStyle::CustomSummer) {
		return 0;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::Underground) {
		return 12;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::Castle) {
		return 24;
	}
	else {
		return 36;
	}
}

int Block::computeLandImageIndex() const
{
	int baseIndex = (World::LAYOUT_STYLE == LayoutStyle::CustomSummer ? 6 : 0);
	for (int length = 5, index = 0; length <= 15; length += 2, ++index) {
		if (length == lengthOfLand) {
			return index + baseIndex;
		}
	}

	return 0;
}

int Block::computeBlockImageIndex() const
{
	int baseIndex = computeBaseIndex();

	if (type <= BlockType::BonusWithOneUpMushroom) {
		return (baseIndex + (static_cast<int>(type) - 1));
	}
	else if (type >= BlockType::BonusWithRedMushroom && type <= BlockType::BonusWithCoin) {
		return (baseIndex + 8 + blockImage);
	}
	else {
		return (baseIndex + 3);
	}
}

int Block::computeImageIndex() const
{
	int baseIndex = computeBaseIndex();
	if (type == BlockType::Monetary) {
		return (position.getY() == initialPositionY ? baseIndex + 3 : baseIndex + 10);
	}
	else if (type == BlockType::AlternativeEmpty) {
		return (position.getY() != initialPositionY ? baseIndex + 2 : baseIndex + 11);
	}
	else {
		return computeBlockImageIndex();
	}
}

SDL_Surface* Block::getImage() const
{
	return (type == BlockType::Land ? landImages[computeLandImageIndex()] : blockImages[computeImageIndex()]);
}

Size Block::getSizeFromBlockType()
{
	switch (type) {
	case BlockType::Tube:
		return Size(56, 34);
	case BlockType::TubeTopEntry:
		return Size(64, 31);
	case BlockType::TubeLeftEntry:
		return Size(78, 64);
	default:
		return Size(32, 32);
	}
}

Size Block::getSizeFromLength()
{
	switch (lengthOfLand) {
	case 5:
		return Size(96, 32);
	case 7:
		return Size(128, 32);
	case 9:
		return Size(160, 32);
	case 11:
		return Size(192, 32);
	case 13:
		return Size(224, 32);
	default:
		return Size(256, 32);
	}
}

void Block::loadPlainBlockImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < blockImages.size(); ++i) {
		std::string filename = "./img/block_imgs/block";
		filename += std::to_string(i + 1);
		filename += ".png";
		blockImages[i] = loadPNG(filename, display);
	}
}

void Block::loadLandImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < landImages.size(); ++i) {
		std::string filename = "./img/block_imgs/land";
		filename += std::to_string(i + 1);
		filename += ".png";
		landImages[i] = loadPNG(filename, display);
	}
}

Block::Block(BlockType type, Position position)
{
	this->position = position;
	this->type = type;
	availableCoins = (type == BlockType::Monetary ? 10 : 0);
	initialPositionY = position.getY();
	lengthOfLand = 0;
	collisionsFlag = (type != BlockType::BonusWithOneUpMushroom);
	size = getSizeFromBlockType();
}

Block::Block(Position position, int lengthOfLand)
{
	this->position = position;
	type = BlockType::Land;
	availableCoins = 0;
	initialPositionY = position.getY();
	this->lengthOfLand = lengthOfLand;
	collisionsFlag = true;
	size = getSizeFromLength();
}

void Block::loadBlockImages(SDL_Surface* display)
{
	loadPlainBlockImages(display);
	loadLandImages(display);
}

bool Block::hasCoins() const
{
	return (availableCoins > 0);
}

bool Block::canBeHitted() const
{
	return (position.getY() == initialPositionY);
}

bool Block::canCollideWithBonuses() const
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
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		drawSurface(display, getImage(), position.getX() - beginningOfCamera, position.getY());
	}
}