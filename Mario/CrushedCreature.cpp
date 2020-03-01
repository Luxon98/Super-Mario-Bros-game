#include "CrushedCreature.h"

SDL_Surface* CrushedCreature::crushedCreatureImage = nullptr;

CrushedCreature::CrushedCreature() {}

CrushedCreature::CrushedCreature(int x, int y) {
	this->positionX = x;
	this->positionY = y;
	this->creationTime = std::chrono::steady_clock::now();
}

void CrushedCreature::loadCrushedCreatureImage(SDL_Surface* screen) {
	this->crushedCreatureImage = loadPNG("./img/crushed_creature.png", screen);
}

void CrushedCreature::draw(SDL_Surface* screen, int beginningOfCamera) {
	drawSurface(screen, this->crushedCreatureImage, this->positionX - beginningOfCamera, this->positionY);
}

bool CrushedCreature::shouldBeRemoved() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (this->creationTime + std::chrono::milliseconds(1200) < timePoint);
}

void CrushedCreature::slide() {}

