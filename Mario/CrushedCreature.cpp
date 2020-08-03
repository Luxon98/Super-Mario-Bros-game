#include "CrushedCreature.h"

SDL_Surface* CrushedCreature::crushedCreatureImage = nullptr;

CrushedCreature::CrushedCreature() {}

CrushedCreature::CrushedCreature(Position* position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
}

void CrushedCreature::loadCrushedCreatureImage(SDL_Surface* screen)
{
	crushedCreatureImage = loadPNG("./img/crushed_creature.png", screen);
}

void CrushedCreature::draw(SDL_Surface* screen, int beginningOfCamera)
{
	drawSurface(screen, crushedCreatureImage, position->getX() - beginningOfCamera, position->getY());
}

bool CrushedCreature::shouldBeRemoved()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(1200) < timePoint);
}

void CrushedCreature::slide() {}

