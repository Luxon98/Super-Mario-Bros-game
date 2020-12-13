#ifndef FireRocket_H
#define FireRocket_H

#include <array>
#include <chrono>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


class FireRocket : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 2> rocketImages;
	bool inactive;
	int model;
	std::chrono::steady_clock::time_point lastSoundTime;
	bool isRightTime();
	int computeImageIndex() const override;
	void changeModel();

public:
	FireRocket(Position position);
	static void loadFireRocketImages(SDL_Surface* display);
	bool isInactive() const;
	void setMoveDirection(Direction direction);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //FireRocket_H