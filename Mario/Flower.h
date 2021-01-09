#ifndef Flower_H
#define Flower_H

#include <array>
#include "BonusObject.h"

class World;
class Player;
struct SDL_Surface;


// name in the original game: 'Fire Flower'
class Flower : public BonusObject
{
private:
	static std::array<SDL_Surface*, 8> flowerImages;
	int imageIndex;
	void changeModel();
	int computeImageIndex() const override;

public:
	Flower(Position position);
	static void loadFlowerImages(SDL_Surface* display);
	void giveBonus(Player &player) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Flower_H