#ifndef Mushroom_H
#define Mushroom_H

#include <array>
#include "BonusObject.h"

class World;
class Player;
struct SDL_Surface;


// name in the original game: 'Super Mushroom'
class Mushroom : public BonusObject 
{
private:
	static std::array<SDL_Surface*, 3> mushroomImages;
	bool oneUp;
	int stepsUp;
	void moveUp(World &world);
	void moveHorizontally(World &world);
	void moveDiagonally(World &world);
	int computeImageIndex() const override;

public:
	Mushroom(Position position, bool oneUp);
	static void loadMushroomImages(SDL_Surface* display);
	int getPointsForCollecting() const override;
	void knockUp() override;
	void giveBonus(Player &player) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Mushroom_H