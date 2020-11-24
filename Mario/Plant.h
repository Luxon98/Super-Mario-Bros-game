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
	bool isOutsidePipe() const;
	void slide(World &world);
	void changeModel();

public:
	Plant(Position position, bool delay = false);
	static void loadPlantImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //Plant_H

