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
	Tube = 5,
	TubeTopEntry = 6,
	TubeLeftEntry = 7,
	BonusWithOneUpMushroom = 8,
	BonusWithRedMushroom = 9,
	BonusWithFlower = 10,
	BonusWithCoin = 11,
	BonusWithStar = 12,
	Monetary = 13,
	AlternativeEmpty = 14,
	Land = 15
};


class Block : public WorldObject 
{
private:
	static std::array<SDL_Surface*, 48> blockImages;
	static std::array<SDL_Surface*, 12> landImages;
	static bool blockImage;
	bool collisionsFlag;
	int availableCoins;
	int initialPositionY;
	int lengthOfLand;
	BlockType type;
	int computeBaseIndex() const;
	int computeLandImageIndex() const;
	int computeBlockImageIndex() const;
	int computeImageIndex() const;
	SDL_Surface* getImage() const;
	Size getSizeFromBlockType();
	Size getSizeFromLength();
	static void loadPlainBlockImages(SDL_Surface* display);
	static void loadLandImages(SDL_Surface* display);

public:
	Block(BlockType type, Position position);
	Block(Position position, int lengthOfLand);
	static void loadBlockImages(SDL_Surface* display);
	bool hasCoins() const;
	bool canBeHitted() const;
	bool canCollideWithBonuses() const;
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