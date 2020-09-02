#ifndef Creature_H
#define Creature_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum Direction;
struct SDL_Surface;


class Creature : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 2> creatureImages;
	int model;
	void changeModel();

public:
	Creature() = default;
	Creature(Position position);
	void setMoveDirection(Direction direction);
	void loadCreatureImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void move(World &world) override;
};

#endif //Creature_H