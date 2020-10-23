#ifndef CheckPoint_H
#define CheckPoint_H

#include "Position.h"

class Player;


class CheckPoint
{
private:
	Position position;
	bool automatic;
	int range;
	int mark;

public:
	CheckPoint(Position position, bool automatic, int range, int mark);
	bool isAutomatic() const;
	int getMark() const;
	bool isPlayerInRangeOfCheckPoint(const Player &player);
};

#endif //CheckPoint_H