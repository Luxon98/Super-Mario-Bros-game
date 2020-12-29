#ifndef Mushroom_H
#define Mushroom_H

#include <array>
#include "BonusObject.h"

class World;
class Player;
struct SDL_Surface;


// this class is equivalent to a collectible bonus, which was called 'Super Mushroom' in the original Mario series
class Mushroom : public BonusObject 
{
private:
	static std::array<SDL_Surface*, 3> mushroomImages;
	bool oneUp;
	int stepsUp;
	int computeImageIndex() const override;
	void moveUp(World &world);
	void moveHorizontally(World &world);
	void moveDiagonally(World &world);

public:
	Mushroom(Position position, bool oneUp);
	static void loadMushroomImages(SDL_Surface* display);
	int getPointsForCollecting() const override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void knockUp() override;
	void giveBonus(Player &player) override;
};

#endif //Mushroom_H