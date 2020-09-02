#ifndef Block_H
#define Block_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;

enum BlockType
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
	static std::array<SDL_Surface*, 10> blockImages;
	static bool changesChecker;
	int availableCoins;
	int initialPositionY;
	int computeImageIndex();
	Size getSizeFromBlockType(BlockType type);

public:
	Block() = default;
	Block(BlockType type, Position position);
	int getAvailableCoins() const;
	bool canBeHitted();
	bool isInvisible();
	void setModel(BlockType type);
	void addToPositionY(int y);
	void setAvailableCoins(int coins);
	static void changeBlockImage();
	void loadBlockImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //Block_H

