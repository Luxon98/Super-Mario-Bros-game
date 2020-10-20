#ifndef Flower_H
#define Flower_H

#include <array>
#include "BonusObject.h"

class World;
struct SDL_Surface;


class Flower : public BonusObject
{
private:
	static std::array<SDL_Surface*, 8> flowerImages;
	int imageIndex;
	int computeBaseIndex() const;
	void changeModel();

public:
	Flower() = default;
	Flower(Position position);
	static void loadFlowerImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //Flower_H

