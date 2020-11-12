#ifndef MovingPlatform_H
#define MovingPlatform_H

#include <array>
#include "WorldObject.h"

class Position;
class Player;
enum class Direction;
struct SDL_Surface;


enum class PlatformType
{
	MovingHorizontallyPlatform,
	MovingVerticallyPlatform,
	MovingDownPlatform,
	MovingUpPlatform,
	SmallPlatform
};


class MovingPlatform : public WorldObject
{
private:
	static std::array<SDL_Surface*, 2> platformImages;
	PlatformType platformType;
	Direction direction;
	bool playerForceMovementChecker;
	int slideCounter;
	bool shouldForcePlayerMovement() const;
	Direction getDirectionFromType() const;
	void slideDown();
	void slideUp();
	void slideUpDown();
	void slideHorizontally();

public:
	MovingPlatform() = default;
	MovingPlatform(Position position, PlatformType platformType);
	static void loadPlatformImage(SDL_Surface* display);
	Direction getDirection() const;
	void setDirection(Direction direction);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void slide(Player &player);
};

#endif //MovingPlatform_H

