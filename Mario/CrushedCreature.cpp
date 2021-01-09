#include "CrushedCreature.h"

#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 4> CrushedCreature::crushedCreatureImages;

int CrushedCreature::computeImageIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld || World::LAYOUT_STYLE == LayoutStyle::Castle) {
		return 0;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::Underground) {
		return 1;
	}
	else {
		return static_cast<int>(World::LAYOUT_STYLE) - 1;
	}
}

CrushedCreature::CrushedCreature(Position position)
{
	this->position = position;
	creationTime = std::chrono::steady_clock::now();
	size = Size(32, 16);
}

void CrushedCreature::loadCrushedCreatureImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < crushedCreatureImages.size(); ++i) {
		std::string filename = "./img/temp_imgs/crushed_creature";
		filename += std::to_string(i + 1);
		filename += ".png";
		crushedCreatureImages[i] = loadPNG(filename, display);
	}
}

bool CrushedCreature::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(1200) < timePoint);
}

void CrushedCreature::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* ccImg = crushedCreatureImages[computeImageIndex()];
		drawSurface(display, ccImg, position.getX() - beginningOfCamera, position.getY());
	}
}