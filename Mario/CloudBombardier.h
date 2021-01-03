#ifndef CloudBombardier_H
#define CloudBombardier_H

#include <array>
#include "IndependentMovingObject.h"

class World;
class Position;
struct SDL_Surface;


class CloudBombardier : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 3> bombardierImages;
	bool active;
	int computeImageIndex() const override;

public:
	CloudBombardier(Position position);
	static void loadBombardierImages(SDL_Surface* display);
	bool isCrushproof() const override;
	bool isGoingLeft() const;
	bool isReadyToDropBomb() const;
	void setActiveState();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void destroy(World &world, Direction direction) override;
};

#endif //CloudBombardier_H