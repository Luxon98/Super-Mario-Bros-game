#ifndef Plant_H
#define Plant_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
struct SDL_Surface;


class Plant : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 4> plantImages;
	int model;
	int computeImageIndex() const override;
	void slide(World &world);
	void changeModel();

public:
	Plant() = default;
	Plant(Position position);
	static void loadPlantImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //Plant_H

