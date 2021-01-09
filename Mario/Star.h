#ifndef Star_H
#define Star_H

#include <array>
#include "BonusObject.h"

class World;
class Player;
struct SDL_Surface;


// name in the original game: 'Super Star'
class Star : public BonusObject 
{
private:
	static std::array<SDL_Surface*, 12> starImages;
	int stepsCounter;
	int stepsUp;
	void makeVerticalMove(World &world);
	void makeHorizontalMove(World &world);
	int computeImageIndex() const override;

public:
	Star(Position position);
	static void loadStarImages(SDL_Surface* display);
	void giveBonus(Player &player) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Star_H