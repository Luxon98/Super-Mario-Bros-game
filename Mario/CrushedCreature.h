#ifndef CrushedCreature_H
#define CrushedCreature_H

#include <array>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class CrushedCreature : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 2> crushedCreatureImages;
	int computeImageIndex() const override;

public:
	CrushedCreature() = default;
	CrushedCreature(Position position);
	static void loadCrushedCreatureImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //CrushedCreature_H