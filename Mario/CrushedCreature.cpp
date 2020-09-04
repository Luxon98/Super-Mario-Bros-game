#include "CrushedCreature.h"

#include "Position.h"
#include "SDL_Utility.h"


SDL_Surface* CrushedCreature::crushedCreatureImage = nullptr;

CrushedCreature::CrushedCreature(Position position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
}

void CrushedCreature::loadCrushedCreatureImage(SDL_Surface* display)
{
	crushedCreatureImage = loadPNG("./img/crushed_creature.png", display);
}

void CrushedCreature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		drawSurface(display, crushedCreatureImage, position.getX() - beginningOfCamera, position.getY());
	}
}

bool CrushedCreature::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(1200) < timePoint);
}

void CrushedCreature::slide() {}

