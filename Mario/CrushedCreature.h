#ifndef CrushedCreature_H
#define CrushedCreature_H

#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class CrushedCreature : public TemporaryObject
{
private:
	static SDL_Surface* crushedCreatureImage;

public:
	CrushedCreature() = default;
	CrushedCreature(Position position);
	void loadCrushedCreatureImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //CrushedCreature_H