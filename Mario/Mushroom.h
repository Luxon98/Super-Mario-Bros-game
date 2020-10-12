#ifndef Mushroom_H
#define Mushroom_H

#include <array>
#include "BonusObject.h"

class World;
struct SDL_Surface;


class Mushroom : public BonusObject 
{
private:
	static std::array<SDL_Surface*, 3> mushroomImages;
	bool oneUp;
	int stepsUp;
	int computeImageIndex() const;
	void makeMoveUp(World &world);

public:
	Mushroom() = default;
	Mushroom(Position position, bool oneUp);
	bool isOneUp() const;
	void decreasePositionY();
	void setStepsUp(int stepsUp);
	void loadMushroomImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //Mushroom_H