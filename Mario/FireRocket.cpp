#include "FireRocket.h"

#include "Movement.h"
#include "Size.h"
#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "CollisionHandling.h"
#include "SoundController.h"


std::array<SDL_Surface*, 2> FireRocket::rocketImages;

bool FireRocket::isRightTime()
{
	auto timePoint = std::chrono::steady_clock::now();
	auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastSoundTime).count();
	if (difference > 4500) {
		return true;
	}

	return false;
}

int FireRocket::computeImageIndex() const
{
	return model - 1;
}

void FireRocket::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 7 == 0) {
		model = (model == 1 ? 2 : 1);
	}
}

FireRocket::FireRocket(Position position)
{
	size = Size(50, 16);
	movement = Movement(1, 0, Direction::None);
	this->position = position;
	model = 1;
	stepsCounter = 0;
	changeModelCounter = 0;
	lastSoundTime = std::chrono::steady_clock::now();
}

void FireRocket::loadFireRocketImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < rocketImages.size(); ++i) {
		std::string filename = "./img/fire_rocket";
		filename += std::to_string(i + 1);
		filename += ".png";
		rocketImages[i] = loadPNG(filename, display);
	}
}

void FireRocket::setMoveDirection(Direction direction)
{
	movement.setDirection(direction);
}

void FireRocket::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 90 && position.getX() < endOfCamera + 90) {
		drawSurface(display, rocketImages[computeImageIndex()], position.getX() - beginningOfCamera, position.getY());
	}
}

void FireRocket::move(World &world)
{
	if (movement.getDirection() == Direction::Left) {
		position.setX(position.getX() - 1);
		changeModel();

		if (isRightTime() && isPlayerCloseToFireRocket(*this, world)) {
			lastSoundTime = std::chrono::steady_clock::now();
			SoundController::playFireRocketEffect();
		}
	}
}
