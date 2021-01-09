#ifndef Plant_H
#define Plant_H

#include <array>
#include "IndependentMovingObject.h"

struct SDL_Surface;


// name in the original game: 'Piranha Plant'
class Plant : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 4> plantImages;
	int model;
	int auxiliaryCounter;
	bool isOutsidePipe() const;
	void slide(World &world);
	void changeModel();
	int computeImageIndex() const override;

public:
	Plant(Position position, bool delay = false);
	static void loadPlantImages(SDL_Surface* display);
	bool isCrushproof() const override;
	bool isResistantToCollisionWithShell() const override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Plant_H