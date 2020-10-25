#ifndef Block_H
#define Block_H

#include <array>
#include "WorldObject.h"

class Position;
struct SDL_Surface;


enum class BlockType
{
	Ground = 1,
	Indestructible = 2,
	Empty = 3,
	Destructible = 4,
	Monetary = 5,
	BonusWithCoin = 6,
	BonusWithOneUpMushroom = 7,
	BonusWithRedMushroom = 8,
	BonusWithFlower = 9,
	BonusWithStar = 10,
	Tube = 11,
	TubeTopEntry = 12,
	TubeLeftEntry = 13,
	Land = 14
};


class Block : public WorldObject 
{
private:
	static std::array<SDL_Surface*, 22> blockImages;
	static std::array<SDL_Surface*, 6> landImages;
	static bool blockImage;
	bool collisionsFlag;
	int availableCoins;
	int initialPositionY;
	int lengthOfLand;
	BlockType type;
	int computeBaseIndex() const;
	int computeImageIndex() const;
	int computeLandImageIndex() const;
	Size getSizeFromBlockType();
	Size getSizeFromLength();
	static void loadPlainBlockImages(SDL_Surface* display);
	static void loadLandImages(SDL_Surface* display);

public:
	Block() = default;
	Block(BlockType type, Position position);
	Block(Position position, int lengthOfLand);
	static void loadBlockImages(SDL_Surface* display);
	bool hasCoins() const;
	bool canBeHitted() const;
	bool canCollideWithMushrooms() const;
	bool isInvisible() const;
	BlockType getType() const;
	static void resetBlockImage();
	static void changeBlockImage();
	void addToPositionY(int y);
	void decrementCoins();
	void setType(BlockType type);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Block_H

