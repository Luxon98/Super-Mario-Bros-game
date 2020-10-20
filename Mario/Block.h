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
	TubeEntry = 12
};


class Block : public WorldObject 
{
private:
	static std::array<SDL_Surface*, 20> blockImages;
	static bool blockImage;
	bool collisionsFlag;
	int availableCoins;
	int initialPositionY;
	BlockType type;
	int computeBaseIndex() const;
	int computeImageIndex() const;
	Size getSizeFromBlockType(BlockType type);

public:
	Block() = default;
	Block(BlockType type, Position position);
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

