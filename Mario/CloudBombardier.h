#ifndef CloudBombardier_H
#define CloudBombardier_H

#include <array>
#include "IndependentMovingObject.h"

struct SDL_Surface;


// name in the original game: 'Lakitu' ;; but is slightly reworked
class CloudBombardier : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 3> bombardierImages;
	bool active;
	bool isReadyToDropBomb() const;
	void flyVertically(World &world);
	void flyHorizontally(World &world);
	void changeParametersDuringFlight(World &world);
	int computeImageIndex() const override;

public:
	CloudBombardier(Position position);
	static void loadBombardierImages(SDL_Surface* display);
	bool shouldStartMoving(const Player &player) const override;
	bool isCrushproof() const override;
	void startMoving() override;
	void destroy(World &world, Direction direction) override;
	void performSpecificActions(World &world, int index) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //CloudBombardier_H