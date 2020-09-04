#ifndef Flower_H
#define Flower_H

#include <array>
#include "BonusObject.h"

class World;
struct SDL_Surface;


class Flower : public BonusObject
{
private:
	static std::array<SDL_Surface*, 2> flowerImages;

public:
	static int typeOfImage;
	Flower() = default;
	Flower(Position position);
	static void changeFlowerImage();
	void loadFlowerImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //Flower_H

