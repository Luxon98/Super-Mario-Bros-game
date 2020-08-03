#ifndef _Block_H
#define _Block_H

#include <string>
#include "SDL_Utility.h"
#include "InanimateObject.h"


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
	static SDL_Surface* blockImages[10];
	static bool changesChecker;
	int availableCoins;
	int computeImageIndex();
	Size* getSizeFromBlockType(BlockType type);

public:
	Block();
	Block(BlockType type, Position* position);
	int getAvailableCoins() const;
	void setModel(BlockType type);
	void addToPositionY(int y);
	void setAvailableCoins(int coins);
	static void changeBlockImage();
	void loadBlockImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
};

#endif //_Block_H

