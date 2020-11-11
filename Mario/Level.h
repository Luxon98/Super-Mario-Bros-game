#ifndef Level_H
#define Level_H

class World;


class Level 
{
public:
	static void setFirstLevel(World &world, bool checker = true);
	static void setSecondLevel(World &world, bool checker = true);
	static void setThirdLevel(World &world);
	static void setFourthLevel(World &world);
	static void setFirstBonusStage(World &world);
	static void setSecondBonusStage(World &world);
	static void setSecondStageOnSecondLevel(World &world);
};

#endif //Level_H