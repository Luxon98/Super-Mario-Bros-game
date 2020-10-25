#ifndef MovingPlatform_H
#define MovingPlatform_H

#include "WorldObject.h"

class Position;
class Player;
enum class Direction;
struct SDL_Surface;


class MovingPlatform : public WorldObject
{
private:
	static SDL_Surface* platformImage;
	Direction direction;
	bool upDownChanger;
	int slideCounter;
	void slideDown();
	void slideUp();
	void slideUpDown();
	void slideHorizontally();

public:
	MovingPlatform() = default;
	MovingPlatform(Position position, Direction direction, bool upDownChanger = false);
	static void loadPlatformImage(SDL_Surface* display);
	Direction getDirection() const;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void slide(Player &player);
};

#endif //MovingPlatform_H

