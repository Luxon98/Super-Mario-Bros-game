#ifndef Shell_H
#define Shell_H

#include <chrono>
#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


class Shell : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 3> shellImages;
	std::chrono::steady_clock::time_point creationTime;
	bool active;
	bool red;
	int computeImageIndex() const override;
	
public:
	Shell(Position position, bool red = false);
	static void loadShellImage(SDL_Surface* display);
	bool isResistantToImmortalPlayer() const override;
	bool isActiveShell() const override;
	bool isActive() const;
	bool isRed() const;
	bool shouldTurnIntoTurtle() const;
	void setActiveStateParameters(Direction direction);
	void resetCreationTime();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
};

#endif //Shell_H