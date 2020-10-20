#include "Shell.h"

#include "Size.h"
#include "Movement.h"
#include "Position.h"
#include "CollisionHandling.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 3> Shell::shellImages;

int Shell::computeIndex() const
{
	if (!red) {
		return (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 1);
	}
	else {
		return 2;
	}
}

Shell::Shell(Position position, bool red)
{
	size = Size(32, 28);
	movement = Movement(3, 2, Direction::None);
	this->position = position;
	this->red = red;
	stepsCounter = 0;
	creationTime = std::chrono::steady_clock::now();
	active = false;
}

void Shell::loadShellImage(SDL_Surface* display)
{
	for (std::size_t i = 0; i < shellImages.size(); ++i) {
		std::string filename = "./img/shell";
		filename += std::to_string(i + 1);
		filename += ".png";
		shellImages[i] = loadPNG(filename, display);
	}
}

bool Shell::isActive() const
{
	return active;
}

bool Shell::shouldTurnIntoTurtle() const
{
	if (red) {
		return false;
	}

	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(25000) < timePoint);
}

void Shell::setMovementDirectionAndActiveState(Direction direction)
{
	movement.setDirection(direction);
	active = (movement.getDirection() != Direction::None);
}

void Shell::resetCreationTime()
{
	creationTime = std::chrono::steady_clock::now();
}

void Shell::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 120 && position.getX() < endOfCamera + 120) {
		SDL_Surface* shellImg = shellImages[computeIndex()];
		drawSurface(display, shellImg, position.getX() - beginningOfCamera, position.getY());
	}
}

void Shell::move(World &world)
{
	if (movement.getDirection() != Direction::None && stepsCounter & 1) {
		if (isCharacterStandingOnSomething(*this, world)) {
			makeHorizontalMove(world);
		}
		else {
			makeDiagonalMove(world);
		}
	}
	++stepsCounter;
}

