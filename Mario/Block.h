#ifndef Block_H
#define Block_H

#include <array>
#include "InanimateObject.h"

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
	BonusWithGreenMushroom = 7,
	BonusWithRedMushroom = 8,
	BonusWithFlower = 9,
	BonusWithStar = 10,
	Tube = 11,
	TubeEntry = 12
};


class Block : public InanimateObject 
{
private:
	static std::array<SDL_Surface*, 17> blockImages;
	static bool changesChecker;
	int availableCoins;
	int initialPositionY;
	BlockType type;
	int computeBaseIndex() const;
	int computeImageIndex() const;
	Size getSizeFromBlockType(BlockType type);

public:
	Block() = default;
	Block(BlockType type, Position position);
	int getAvailableCoins() const;
	bool canBeHitted() const;
	bool isInvisible() const;
	BlockType getType() const;
	static void changeBlockImage();
	void addToPositionY(int y);
	void setAvailableCoins(int coins);
	void setType(BlockType type);
	void loadBlockImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Block_H

