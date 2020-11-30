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
	static void setFirstHiddenStage(World &world);
	static void setSecondHiddenStage(World &world);
	static void setSecondStageOnSecondLevel(World &world);
	static void setWinterWorld(World &world);
	static void setWinterHiddenStage(World &world);
};

#endif //Level_H