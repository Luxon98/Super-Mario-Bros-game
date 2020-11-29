#ifndef Creature_H
#define Creature_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


class Creature : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 6> creatureImages; 
	int model;
	int computeBaseIndex() const;
	int computeImageIndex() const override;
	void changeModel();

public:
	Creature(Position position);
	static void loadCreatureImages(SDL_Surface* display);
	void setMoveDirection(Direction direction);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //Creature_H