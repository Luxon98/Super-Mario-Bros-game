#ifndef Shell_H
#define Shell_H

#include <array>
#include <chrono>
#include "IndependentMovingObject.h"

enum class Direction;
struct SDL_Surface;


class Shell : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 3> shellImages;
	std::chrono::steady_clock::time_point stateTime;
	bool active;
	bool red;
	bool shouldTurnIntoTurtle() const;
	int computeImageIndex() const override;
	
public:
	Shell(Position position, bool red = false);
	static void loadShellImage(SDL_Surface* display);
	void changeActiveState(Direction direction);
	bool isResistantToImmortalPlayer() const override;
	bool isActiveShell() const override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
	void performSpecificActions(World &world, int index) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Shell_H