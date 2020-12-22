#include "CrushedCreature.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


// the first two pictures are from the original Mario
// the last one is a picture created for the needs of the Winter world
std::array<SDL_Surface*, 4> CrushedCreature::crushedCreatureImages;

int CrushedCreature::computeImageIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::Underground) {
		return 1;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::CustomWinter) {
		return 2;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::CustomSummer) {
		return 3;
	}
	else {
		return 0;
	}
}

CrushedCreature::CrushedCreature(Position position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
}

void CrushedCreature::loadCrushedCreatureImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < crushedCreatureImages.size(); ++i) {
		std::string filename = "./img/anm_imgs/crushed_creature";
		filename += std::to_string(i + 1);
		filename += ".png";
		crushedCreatureImages[i] = loadPNG(filename, display);
	}
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