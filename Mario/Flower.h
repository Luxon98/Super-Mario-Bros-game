#ifndef Flower_H
#define Flower_H

#include <array>
#include "BonusObject.h"

class World;
class Player;
struct SDL_Surface;


// this class is equivalent to a collectible bonus, which was called 'Fire Flower' in the original Mario series
class Flower : public BonusObject
{
private:
	static std::array<SDL_Surface*, 8> flowerImages;
	int imageIndex;
	int computeImageIndex() const override;
	void changeModel();

public:
	Flower(Position position);
	static void loadFlowerImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void giveBonus(Player &player) override;
};

#endif //Flower_H