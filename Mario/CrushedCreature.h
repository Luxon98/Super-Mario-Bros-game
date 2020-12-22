#ifndef CrushedCreature_H
#define CrushedCreature_H

#include <array>
#include "AnimatedObject.h"

class Position;
struct SDL_Surface;


class CrushedCreature : public AnimatedObject
{
private:
	static std::array<SDL_Surface*, 4> crushedCreatureImages;
	int computeImageIndex() const override;

public:
	CrushedCreature(Position position);
	static void loadCrushedCreatureImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //CrushedCreature_H