#include "DestroyedBoss.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"


std::array<SDL_Surface*, 3> DestroyedBoss::destroyedBossImages;

int DestroyedBoss::computeImageIndex() const
{
	if (!normal) {
		if (auxiliaryCounter < 45 || (auxiliaryCounter >= 70 && auxiliaryCounter < 95)
			|| (auxiliaryCounter >= 120 && auxiliaryCounter < 145)) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 2;
	}
}

DestroyedBoss::DestroyedBoss(Position position, bool normal) : normal(normal)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
}

void DestroyedBoss::loadDestroyedBossImages(SDL_Surface* display)
{
	destroyedBossImages[0] = loadPNG("./img/npc_imgs/boss1.png", display);
	destroyedBossImages[1] = loadPNG("./img/npc_imgs/boss2.png", display);
	destroyedBossImages[2] = loadPNG("./img/anm_imgs/destroyed_boss.png", display);
}

void DestroyedBoss::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 90 && position.getX() < endOfCamera + 90) {
		SDL_Surface* bossImg = destroyedBossImages[computeImageIndex()];
		drawSurface(display, bossImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool DestroyedBoss::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(2750) < timePoint);
}

void DestroyedBoss::slide()
{
	if (!normal) {
		++auxiliaryCounter;
		if (auxiliaryCounter < 20 && auxiliaryCounter) {
			position.setY(position.getY() - 1);
		}
		else if (auxiliaryCounter >= 145) {
			position.setY(position.getY() + 1);
		}
	}
	else {
		position.setY(position.getY() + 1);
	}
}