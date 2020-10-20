#ifndef Star_H
#define Star_H

#include <array>
#include "BonusObject.h"

class World;
struct SDL_Surface;


class Star : public BonusObject 
{
private:
	static std::array<SDL_Surface*, 8> starImages;
	int stepsCounter;
	int stepsUp;
	int computeBaseIndex() const;
	void makeVerticalMove(World &world);
	void makeHorizontalMove(World &world);

public:
	Star() = default;
	Star(Position position);
	static void loadStarImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //Star_H
