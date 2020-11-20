#include "CrushedCreature.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 2> CrushedCreature::crushedCreatureImages;

int CrushedCreature::computeImageIndex() const
{
	return (World::LAYOUT_STYLE != LayoutStyle::OpenWorld);
}

CrushedCreature::CrushedCreature(Position position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
}

void CrushedCreature::loadCrushedCreatureImages(SDL_Surface* display)
{
	crushedCreatureImages[0] = loadPNG("./img/crushed_creature1.png", display);
	crushedCreatureImages[1] = loadPNG("./img/crushed_creature2.png", display);
}

void CrushedCreature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		SDL_Surface* ccImg = crushedCreatureImages[computeImageIndex()];
		drawSurface(display, ccImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool CrushedCreature::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(1200) < timePoint);
}

void CrushedCreature::slide() {}

