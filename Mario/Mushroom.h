#ifndef _Mushroom_H
#define _Mushroom_H

#include "BonusObject.h"

class World;
struct SDL_Surface;


class Mushroom : public BonusObject 
{
private:
	static SDL_Surface* mushroomImages[2];
	bool greenColor;
	int stepsUp;
	void makeMoveUp(World& world);

public:
	Mushroom();
	Mushroom(Position* position, bool greenColor);
	bool isGreen();
	void decreasePositionY();
	void setStepsUp(int stepsUp);
	void loadMushroomImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void move(World& world) override;
};

#endif //_Mushroom_H