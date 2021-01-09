#ifndef Platform_H
#define Platform_H

#include <array>
#include "WorldObject.h"

class Player;
enum class Direction;
struct SDL_Surface;


enum class PlatformType
{
	MovingHorizontallyPlatform,
	MovingVerticallyPlatform,
	MovingDownPlatform,
	MovingUpPlatform,
	SmallPlatform,
	Bridge
};


class Platform : public WorldObject
{
private:
	static std::array<SDL_Surface*, 6> platformImages;
	static constexpr int DEFAULT_BRIDGE_LENGTH = 44;
	PlatformType platformType;
	Direction direction;
	bool playerForceMovementChecker;
	int slideCounter;
	int bridgeLength;
	bool shouldForcePlayerMovement() const;
	Direction getDirectionFromType() const;
	Size getSizeFromPlatformType();
	void drawPlatform(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const;
	void drawBridge(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const;
	void slideDown();
	void slideUp();
	void slideUpDown();
	void slideHorizontally();

public:
	Platform(Position position, PlatformType platformType);
	static void loadPlatformImage(SDL_Surface* display);
	int getBridgeLength() const;
	Direction getDirection() const;
	PlatformType getPlatformType() const;
	void setDirection(Direction direction);
	void slide(Player &player);
	void reduceBridge();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Platform_H

