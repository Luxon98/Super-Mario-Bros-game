#include "DestroyedBoss.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 6> DestroyedBoss::destroyedBossImages;

int DestroyedBoss::computeImageIndex() const
{
	int baseIndex = (direction == Direction::Left ? 0 : 3);

	if (!normal) {
		if (auxiliaryCounter < 45 || (auxiliaryCounter >= 70 && auxiliaryCounter < 95)
			|| (auxiliaryCounter >= 120 && auxiliaryCounter < 145)) {

			return baseIndex + 0;
		}
		else {
			return baseIndex + 1;
		}
	}
	else {
		return baseIndex + 2;
	}
}

DestroyedBoss::DestroyedBoss(Position position, Direction direction, bool normal)
{
	this->position = position;
	this->direction = direction;
	this->normal = normal;
	auxiliaryCounter = 0;
	size = Size(64, 64);
}

void DestroyedBoss::loadDestroyedBossImages(SDL_Surface* display)
{
	destroyedBossImages[0] = loadPNG("./img/npc_imgs/boss1.png", display);
	destroyedBossImages[1] = loadPNG("./img/npc_imgs/boss2.png", display);
	destroyedBossImages[2] = loadPNG("./img/temp_imgs/destroyed_boss1.png", display);
	destroyedBossImages[3] = loadPNG("./img/npc_imgs/boss3.png", display);
	destroyedBossImages[4] = loadPNG("./img/npc_imgs/boss4.png", display);
	destroyedBossImages[5] = loadPNG("./img/temp_imgs/destroyed_boss2.png", display);
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

void DestroyedBoss::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* bossImg = destroyedBossImages[computeImageIndex()];
		drawSurface(display, bossImg, position.getX() - beginningOfCamera, position.getY());
	}
}