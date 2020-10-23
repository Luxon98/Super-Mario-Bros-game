#include "CheckPoint.h"

#include "Player.h"


CheckPoint::CheckPoint(Position position, bool automatic, int range, int mark)
	: position(position), automatic(automatic), range(range), mark(mark) {}

bool CheckPoint::isAutomatic() const
{
	return automatic;
}

int CheckPoint::getMark() const
{
	return mark;
}

bool CheckPoint::isPlayerInRangeOfCheckPoint(const Player &player)
{
	if ((player.getX() >= position.getX() - range && player.getX() <= position.getX() + range) 
		&& (player.getY() >= position.getY() - range && player.getY() <= position.getY() + range)) {

		return true;
	}

	return false;
}
