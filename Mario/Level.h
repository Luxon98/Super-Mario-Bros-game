#ifndef Level_H
#define Level_H

class World;


class Level 
{
public:
	static void setFirstLevel(World &world, bool bonusLifeBlockFlag = true);
	static void setSecondLevel(World &world);
};

#endif //Level_H