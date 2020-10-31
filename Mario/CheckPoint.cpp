#include "CheckPoint.h"

#include "Player.h"


CheckPoint::CheckPoint(Position position, bool automatic, int mark) 
	: position(position), automatic(automatic), mark(mark) 
{
	horizontalRange = (automatic ? 15 : 5);
	verticalRange = 40;
}

bool CheckPoint::isAutomatic() const
{
	return automatic;
}

unsigned int CheckPoint::getMark() const
{
	return mark;
}

bool CheckPoint::isPlayerInRangeOfCheckPoint(const Player &player) const
{
	if ((player.getX() >= position.getX() - horizontalRange && player.getX() <= position.getX() + horizontalRange)
		&& (player.getY() >= position.getY() - verticalRange && player.getY() <= position.getY() + verticalRange)) {

		return true;
	}

	return false;
}
