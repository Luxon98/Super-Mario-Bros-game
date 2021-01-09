#include "Platform.h"

#include "Player.h"
#include "CollisionHandling.h"
#include "World.h"
#include "LayoutStyle.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 6> Platform::platformImages;

bool Platform::shouldForcePlayerMovement() const
{
	if (playerForceMovementChecker && (platformType == PlatformType::MovingHorizontallyPlatform 
		|| platformType == PlatformType::MovingVerticallyPlatform || platformType == PlatformType::SmallPlatform)) {
		return true;
	}
	else if (platformType == PlatformType::MovingDownPlatform || platformType == PlatformType::MovingUpPlatform) {
		return true;
	}

	return false;
}

Direction Platform::getDirectionFromType() const
{
	if (platformType == PlatformType::MovingUpPlatform || platformType == PlatformType::MovingVerticallyPlatform) {
		return Direction::Up;
	}
	else if (platformType == PlatformType::MovingDownPlatform) {
		return Direction::Down;
	}
	else if (platformType == PlatformType::MovingHorizontallyPlatform || platformType == PlatformType::SmallPlatform) {
		return Direction::Left;
	}
	else {
		return Direction::None;
	}
}

Size Platform::getSizeFromPlatformType()
{
	switch (platformType) {
	case PlatformType::SmallPlatform:
		return Size(64, 16);
	case PlatformType::Bridge:
		return Size(352, 32);
	default:
		return Size(96, 16);
	}
}

void Platform::drawPlatform(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		int index = (World::LAYOUT_STYLE != LayoutStyle::CustomWinter ? 0 : 2);
		index += (platformType != PlatformType::SmallPlatform ? 0 : 1);
		drawSurface(display, platformImages[index], position.getX() - beginningOfCamera, position.getY());
	}
}

void Platform::drawBridge(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		for (int i = 0; i < bridgeLength; ++i) {
			int posX = (position.getX() - size.getWidth() / 2) - beginningOfCamera + (i * 8);
			drawSurface(display, platformImages[4], posX, position.getY());
		}

		if (bridgeLength == DEFAULT_BRIDGE_LENGTH) {
			int posX = position.getX() - beginningOfCamera + 156;
			drawSurface(display, platformImages[5], posX, position.getY() - 32);
		}
	}
}

void Platform::slideDown()
{
	position.setY(position.getY() + 1);
	if (position.getY() == 500) {
		position.setY(-20);
	}
}

void Platform::slideUp()
{
	position.setY(position.getY() - 1);
	if (position.getY() == -20) {
		position.setY(500);
	}
}

void Platform::slideUpDown()
{
	++slideCounter;
	if ((slideCounter > 20 && slideCounter <= 135) || slideCounter & 1) {
		int distance = (direction == Direction::Down ? 1 : -1);
		position.setY(position.getY() + distance);
		playerForceMovementChecker = true;
	}
	else {
		playerForceMovementChecker = false;
	}

	if (slideCounter == 155) {
		direction = (direction == Direction::Up ? Direction::Down : Direction::Up);
		slideCounter = 0;
	}
	
}

void Platform::slideHorizontally()
{
	++slideCounter;
	if ((slideCounter > 20 && slideCounter <= 125) || slideCounter & 1) {
		int distance = (direction == Direction::Left ? -1 : 1);
		position.setX(position.getX() + distance);
		playerForceMovementChecker = true;
	}
	else {
		playerForceMovementChecker = false;
	}

	if (slideCounter == 145) {
		direction = (direction == Direction::Left ? Direction::Right : Direction::Left);
		slideCounter = 0;
	}
}

Platform::Platform(Position position, PlatformType platformType)
{
	this->position = position;
	this->platformType = platformType;
	direction = getDirectionFromType();
	playerForceMovementChecker = false;
	slideCounter = 0;
	bridgeLength = (platformType == PlatformType::Bridge ? DEFAULT_BRIDGE_LENGTH : 0);
	size = getSizeFromPlatformType();
}

void Platform::loadPlatformImage(SDL_Surface* display)
{
	platformImages[0] = loadPNG("./img/other_imgs/platform.png", display);
	platformImages[1] = loadPNG("./img/other_imgs/small_platform.png", display);
	platformImages[2] = loadPNG("./img/other_imgs/platform2.png", display);
	platformImages[3] = loadPNG("./img/other_imgs/small_platform2.png", display);
	platformImages[4] = loadPNG("./img/other_imgs/bridge_element.png", display);
	platformImages[5] = loadPNG("./img/other_imgs/span.png", display);
}

int Platform::getBridgeLength() const
{
	return bridgeLength;
}

Direction Platform::getDirection() const
{
	return direction;
}

PlatformType Platform::getPlatformType() const
{
	return platformType;
}

void Platform::setDirection(Direction direction)
{
	this->direction = direction;
}

void Platform::slide(Player &player)
{
	if (isPlayerStandingOnThisPlatform(player, *this) && shouldForcePlayerMovement()) {
		player.forceMovement(direction);
	}

	if (platformType == PlatformType::MovingVerticallyPlatform) {
		slideUpDown();
	}
	else {
		if (platformType == PlatformType::MovingHorizontallyPlatform || platformType == PlatformType::SmallPlatform) {
			slideHorizontally();
		}
		else if (platformType == PlatformType::MovingUpPlatform) {
			slideUp();
		}
		else if (platformType == PlatformType::MovingDownPlatform) {
			slideDown();
		}
	}
}

void Platform::reduceBridge()
{
	if (platformType == PlatformType::Bridge) {
		--bridgeLength;
		size.setWidth(size.getWidth() - 8);
	}
}

void Platform::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (platformType != PlatformType::Bridge) {
		drawPlatform(display, beginningOfCamera, endOfCamera);
	}
	else {
		drawBridge(display, beginningOfCamera, endOfCamera);
	}
}