#ifndef Mushroom_H
#define Mushroom_H

#include <array>
#include "BonusObject.h"

class World;
struct SDL_Surface;


class Mushroom : public BonusObject 
{
private:
	static std::array<SDL_Surface*, 2> mushroomImages;
	bool greenColor;
	int stepsUp;
	void makeMoveUp(World &world);

public:
	Mushroom() = default;
	Mushroom(Position position, bool greenColor);
	bool isGreen();
	void decreasePositionY();
	void setStepsUp(int stepsUp);
	void loadMushroomImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void move(World &world) override;
};

#endif //Mushroom_H