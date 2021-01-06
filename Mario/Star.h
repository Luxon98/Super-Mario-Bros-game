#ifndef Star_H
#define Star_H

#include <array>
#include "BonusObject.h"

class World;
class Player;
struct SDL_Surface;


// this class is equivalent to a collectible bonus, which was called 'Super Star' in the original Mario series
class Star : public BonusObject 
{
private:
	static std::array<SDL_Surface*, 12> starImages;
	int stepsCounter;
	int stepsUp;
	int computeImageIndex() const override;
	void makeVerticalMove(World &world);
	void makeHorizontalMove(World &world);

public:
	Star(Position position);
	static void loadStarImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void giveBonus(Player &player) override;
};

#endif //Star_H