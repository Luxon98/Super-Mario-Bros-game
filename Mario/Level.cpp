#include "Level.h"

#include "World.h"
#include "Screen.h"
#include "Block.h"
#include "Position.h"
#include "Creature.h"
#include "Turtle.h"
#include "RedTurtle.h"
#include "Plant.h"
#include "FireRocket.h"
#include "Boss.h"
#include "Bush.h"
#include "Cloud.h"
#include "Coin.h"
#include "Flag.h"
#include "Button.h"
#include "Castle.h"
#include "LayoutStyle.h"
#include "Flower.h"
#include "CheckPoint.h"
#include "Rock.h"
#include "Lava.h"
#include "Princess.h"
#include "CustomWinterDecoration.h"
#include "FireSerpent.h"
#include "Player.h"


void Level::setFirstLevel(World &world, bool checker)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::OpenWorld;

	for (int i = 0; i < 7120; i += 32) {
		if (i != 2208 && i != 2240 && i != 4896 && i != 4928 && i != 2752 && i != 2784 && i != 2816) {
			world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 464)));
			world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 432)));
		}
	}

	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(528, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(656, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithRedMushroom, Position(688, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(720, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(720, 160)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(752, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(784, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(2478, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithFlower, Position(2510, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(2542, 288)));

	for (int i = 0; i < 8; ++i) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(2574 + i * 32, 160)));
	}

	world.blocks.push_back(Block(BlockType::Destructible, Position(2926, 160)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(2958, 160)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(2990, 160)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(3022, 160)));
	world.blocks.push_back(Block(BlockType::Monetary, Position(3022, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(3214, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithStar, Position(3246, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(3406, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(3502, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(3502, 160)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(3598, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(3790, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(3886, 160)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(3918, 160)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(3950, 160)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(4146, 160)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(4178, 160)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(4210, 160)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(4242, 160)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(4178, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(4210, 288)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4302, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4334, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4366, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4398, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4334, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4366, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4398, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4366, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4398, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4398, 304)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4494, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4526, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4558, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4590, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4494, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4526, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4558, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4494, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4526, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4494, 304)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4752, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4784, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4816, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4848, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4880, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4784, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4816, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4848, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4880, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4816, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4848, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4880, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4848, 304)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4880, 304)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4976, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5008, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5040, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5072, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4976, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5008, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5040, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4976, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5008, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4976, 304)));

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 9 - i; ++j) {
			world.blocks.push_back(Block(BlockType::Indestructible, Position(5808 + i * 32 + j * 32, 400 - i * 32)));
		}
	}

	world.blocks.push_back(Block(BlockType::Destructible, Position(5390, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(5422, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(5454, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(5486, 288)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(6350, 400)));
	world.blocks.push_back(Block(BlockType::Tube, Position(928, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(928, 368)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1248, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1248, 367)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1248, 336)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1504, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1504, 367)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1504, 335)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1504, 304)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1856, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1856, 367)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1856, 335)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1856, 304)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5248, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(5248, 368)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5760, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(5760, 368)));

	if (checker) {
		world.blocks.push_back(Block(BlockType::BonusWithOneUpMushroom, Position(2064, 288)));
	}

	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(5, Position(80, 381))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(3, Position(432, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(4, Position(560, 397))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(656, 72))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(1, Position(782, 400))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(3, Position(944, 104))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(1214, 72))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(2, Position(1374, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(5, Position(1614, 381))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(1838, 104))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(3, Position(1966, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(4, Position(2094, 397))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(2190, 72))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(1, Position(2318, 400))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(3, Position(2478, 104))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(2750, 72))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(2, Position(2910, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(5, Position(3150, 381))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(3, Position(3502, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(4, Position(3628, 397))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(1, Position(3854, 400))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(3374, 104))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(3726, 72))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(3, Position(4014, 104))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(4286, 72))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(2, Position(4448, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(5, Position(4686, 381))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(4910, 104))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(1, Position(5050, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(4, Position(5166, 397))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(1, Position(5390, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(5, Position(6222, 381))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(1, Position(6608, 400))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(4, Position(6702, 397))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(5262, 72))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(3, Position(5550, 104))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(5822, 72))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(6446, 104))));

	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(730, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1650, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1710, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2650, 128))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2730, 128))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3180, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3220, 400))));
	world.monsters.push_back(std::make_shared<Turtle>(Turtle(Position(3350, 397))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3800, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3850, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4050, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4100, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4150, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4200, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(5200, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(5270, 400))));

	world.checkPoints.push_back(CheckPoint(Position(1856, 265), false, 1));

	world.inanimateElements.push_back(std::make_shared<Castle>(Castle(Position(6542, 336), false)));
	world.flag = std::make_unique<Flag>(Flag(Position(6335, 116)));
	world.button = nullptr;
}

void Level::setSecondLevel(World &world, bool checker)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();
	
	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::Underground;

	if (checker) {
		world.blocks.push_back(Block(BlockType::BonusWithOneUpMushroom, Position(2864, 80)));

	}
	else {
		world.blocks.push_back(Block(BlockType::Destructible, Position(2864, 80)));
	}

	for (int i = 0; i < 2560; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 432)));
	}

	for (int i = 2656; i < 3840; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 432)));
	}

	world.blocks.push_back(Block(BlockType::Ground, Position(3920, 464)));
	world.blocks.push_back(Block(BlockType::Ground, Position(3920, 432)));
	world.blocks.push_back(Block(BlockType::Ground, Position(3952, 464)));
	world.blocks.push_back(Block(BlockType::Ground, Position(3952, 432)));

	for (int i = 0; i < 3; ++i) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(3920, 400 - (i * 32))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(3952, 400 - (i * 32))));
	}


	for (int i = 4032; i < 4416; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 432)));
	}

	for (int i = 4640; i < 4896; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + i, 432)));

		if (i < 4832) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(16 + i, 272)));
		}
	}

	for (int i = 5136; i < 5712; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 400)));
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 368)));
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 336)));
	}

	world.blocks.push_back(Block(BlockType::BonusWithFlower, Position(336, 288))); 
	for (int i = 352; i < 480; i += 32) {
		world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(16 + i, 288))); 
	}

	for (int i = 416; i > 64; i -= 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(16, i - 16))); 
	}

	world.blocks.push_back(Block(BlockType::Indestructible, Position(560, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(624, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(624, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(686, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(686, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(686, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(750, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(750, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(750, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(750, 304)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(814, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(814, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(814, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(814, 304)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(878, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(878, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(878, 336)));
	world.blocks.push_back(Block(BlockType::Monetary, Position(942, 272)));        
	world.blocks.push_back(Block(BlockType::Indestructible, Position(1006, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(1006, 368)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(1006, 336)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(1070, 400)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(1070, 368)));

	for (int i = 192; i < 4416; i += 32) {
		if (i != 2848) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(i + 16, 80)));
		}
	}

	for (int i = 0; i < 3; ++i) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(1262, 304 - (32 * i))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(1326, 304 - (32 * i))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(1422, 304 - (32 * i))));
	}

	world.blocks.push_back(Block(BlockType::BonusWithStar, Position(1486, 240)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1486, 272)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1486, 304)));

	world.blocks.push_back(Block(BlockType::Destructible, Position(1294, 304)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1454, 304)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1358, 240)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1390, 240)));

	for (int i = 4272; i < 4432; i += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 400)));
	}

	for (int i = 4304; i < 4432; i += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 368)));
	}

	for (int i = 4336; i < 4432; i += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 336)));
	}

	world.blocks.push_back(Block(BlockType::Indestructible, Position(4368, 304)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4400, 304)));
	world.blocks.push_back(Block(BlockType::Tube, Position(3328, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(3328, 367)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(3328, 336)));
	world.blocks.push_back(Block(BlockType::Tube, Position(3520, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(3520, 367)));
	world.blocks.push_back(Block(BlockType::Tube, Position(3520, 335)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(3520, 304)));
	world.blocks.push_back(Block(BlockType::Tube, Position(3712, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(3712, 368)));

	
	for (int i = 2448; i < 2576; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 112))); 
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 144))); 
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 304))); 
	}

	
	for (int i = 2704; i < 2896; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 240))); 
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 272)));

		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 176))));
	}
	
	for (int i = 0; i < 5; ++i) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(1680, 176 + (i * 32))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(1712, 176 + (i * 32))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(2000, 176 + (i * 32))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(2032, 176 + (i * 32))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(2160, 176 + (i * 32))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(2320, 176 + (i * 32))));
		world.blocks.push_back(Block(BlockType::Destructible, Position(2352, 176 + (i * 32)))); 
	}

	for (int i = 1744; i < 2256; i += 32) {
		if (i != 1808 && i != 1840 && i != 2064 && i != 2096) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(i, 112))); 
			world.blocks.push_back(Block(BlockType::Destructible, Position(i, 144))); 
		}
	}

	for (int i = 1744; i < 2000; i += 32) {
		if (i != 1808 && i != 1840) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(i, 304)));
		}
	}

	world.blocks.push_back(Block(BlockType::Destructible, Position(2192, 304)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(2224, 304)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(2224, 272)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1744, 336)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1776, 336)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1744, 368)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1776, 368)));

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(5456 + (j * 32), 48 + (i * 32))));
		}
	}

	world.blocks.push_back(Block(BlockType::Destructible, Position(5712, 16)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(5712, -16)));

	world.blocks.push_back(Block(BlockType::TubeLeftEntry, Position(5347, 288)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 303)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 271)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 239)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 207)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 175)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 143)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 111)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 79)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5410, 49)));

	for (int i = 0; i < 7; ++i) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(5168 + (i * 32), 48)));
	}

	world.platforms.push_back(Platform(Position(4526, 120), PlatformType::MovingDownPlatform));
	world.platforms.push_back(Platform(Position(4526, 380), PlatformType::MovingDownPlatform));
	world.platforms.push_back(Platform(Position(5010, 120), PlatformType::MovingUpPlatform));
	world.platforms.push_back(Platform(Position(5010, 380), PlatformType::MovingUpPlatform));

	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(518, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(558, 368))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(942, 400))));
	world.monsters.push_back(std::make_shared<Turtle>(Turtle(Position(1525, 397))));
	world.monsters.push_back(std::make_shared<Turtle>(Turtle(Position(1575, 397))));
	world.monsters.push_back(std::make_shared<Turtle>(Turtle(Position(1925, 397))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2070, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2125, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2380, 112))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2490, 208))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2535, 208))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3200, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3238, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3276, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3635, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4235, 240))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4385, 272))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(3328, 388))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(3520, 356), true)));
	if (checker) {
		world.monsters.push_back(std::make_shared<Plant>(Plant(Position(3712, 420))));
	}

	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(4847, 397), false)));

	for (int i = 1326; i < 1454; i += 32) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 176))));
	}

	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1294, 274))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1454, 274))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(2190, 274))));

	for (int i = 1870; i < 1998; i += 32) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 274))));
	}

	world.checkPoints.push_back(CheckPoint(Position(3328, 297), false, 1));
	world.checkPoints.push_back(CheckPoint(Position(5354, 294), true, 3));

	world.inanimateElements.push_back(std::make_shared<Castle>(Castle(Position(6684, 336), false)));
	world.flag = nullptr;
	world.button = nullptr;
}

void Level::setThirdLevel(World &world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::OpenWorld;

	world.inanimateElements.push_back(std::make_shared<Castle>(Castle(Position(80, 336), false)));

	for (int i = 16; i < 528; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	world.blocks.push_back(Block(Position(640, 400), 7));
	world.blocks.push_back(Block(Position(896, 304), 15));
	world.blocks.push_back(Block(Position(912, 176), 9));
	world.blocks.push_back(Block(Position(1072, 400), 5));
	world.blocks.push_back(Block(Position(1200, 272), 9));
	world.blocks.push_back(Block(Position(1392, 144), 13));
	world.blocks.push_back(Block(Position(1664, 432), 7));
	world.blocks.push_back(Block(Position(1968, 432), 9));
	world.blocks.push_back(Block(Position(2160, 432), 9));
	world.blocks.push_back(Block(Position(2288, 304), 5));
	world.blocks.push_back(Block(Position(1982, 176), 7));
	world.blocks.push_back(Block(Position(2526, 208), 11));
	world.blocks.push_back(Block(Position(3198, 368), 7));
	world.blocks.push_back(Block(Position(3456, 240), 15));
	world.blocks.push_back(Block(Position(3662, 432), 5));
	world.blocks.push_back(Block(Position(3774, 304), 7));
	world.blocks.push_back(Block(Position(3966, 304), 7));

	world.blocks.push_back(Block(BlockType::BonusWithFlower, Position(1906, 320)));

	for (int i = 4144; i < 5584; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	world.platforms.push_back(Platform(Position(1810, 390), PlatformType::MovingVerticallyPlatform));
	world.platforms.push_back(Platform(Position(2822, 265), PlatformType::MovingHorizontallyPlatform));
	world.platforms.push_back(Platform(Position(2922, 294), PlatformType::MovingHorizontallyPlatform));
	world.platforms[world.platforms.size() - 1].setDirection(Direction::Right);
	world.platforms.push_back(Platform(Position(4260, 196), PlatformType::MovingHorizontallyPlatform));

	for (int i = 4432; i < 4624; i += 32) {
		for (int j = 400; j > 272; j -= 32) {
			world.blocks.push_back(Block(BlockType::Indestructible, Position(i, j)));
		}
	}

	for (int i = 4496; i < 4624; i += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 272)));
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 240)));
	}

	world.blocks.push_back(Block(BlockType::Indestructible, Position(4592, 208)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4560, 208)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4592, 176)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4560, 176)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(4880, 400)));

	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(158, 122))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(336, 248))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(640, 88))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(1169, 248))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(1264, 215))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(1520, 376))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(1696, 120))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(1872, 252))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(2176, 88))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(2496, 380))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(2688, 250))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(2800, 218))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(3056, 378))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(3232, 122))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(3712, 88))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(4014, 380))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(4240, 250))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(4336, 218))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(4590, 374))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(4768, 122))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(4942, 248))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(5267, 88))));

	for (int i = 624; i < 688; i += 32) {
		for (int j = 464; j > 400; j -= 32) {
			world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(i, j))));
		}
	}

	for (int i = 816; i < 1008; i += 32) {
		for (int j = 464; j > 304; j -= 32) {
			world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(i, j))));
		}
	}

	for (int i = 880; i < 976; i += 32) {
		for (int j = 272; j > 176; j -= 32) {
			world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(i, j))));
		}
	}

	world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(1072, 432))));
	world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(1072, 464))));

	for (int i = 1168; i < 1264; i += 32) {
		for (int j = 464; j > 272; j -= 32) {
			world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(i, j))));
		}
	}

	for (int i = 1328; i < 1488; i += 32) {
		for (int j = 464; j > 144; j -= 32) {
			world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(i, j))));
		}
	}

	world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(1648, 464))));
	world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(1680, 464))));

	for (int i = 1936; i < 2224; i += 32) {
		if (i != 2032 && i != 2064 && i != 2096) {
			world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(i, 464))));
		}
	}

	for (int i = 464; i > 304; i -= 32) {
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(2288, i))));
	}

	for (int i = 400; i > 176; i -= 32) {
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(1966, i))));
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(1998, i))));
	}

	for (int i = 2478; i < 2606; i += 32) {
		for (int j = 464; j > 208; j -= 32) {
			world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(i, j))));
		}
	}

	for (int i = 464; i > 304; i -= 32) {
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(3758, i))));
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(3790, i))));
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(3950, i))));
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(3982, i))));
	}

	for (int i = 464; i > 368; i -= 32) {
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(3182, i))));
		world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(3214, i))));
	}

	for (int i = 3376; i < 3568; i += 32) {
		for (int j = 464; j > 240; j -= 32) {
			world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(i, j))));
		}
	}

	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(878, 146))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(910, 146))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(942, 146))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1072, 370))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1198, 82))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1230, 82))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1614, 208))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1646, 208))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1934, 146))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1966, 146))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1998, 146))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(2030, 146))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(2988, 148))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(3020, 148))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(3118, 148))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(3150, 148))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(2734, 174))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(2766, 174))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(3854, 174))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(3886, 174))));

	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1423, 112))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1488, 112))));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(989, 141), false)));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(2384, 148), true)));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2575, 176))));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(3538, 205), false)));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(3665, 182), true)));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(4348, 397), false)));

	world.inanimateElements.push_back(std::make_shared<Rock>(Rock(Position(3662, 464))));

	world.inanimateElements.push_back(std::make_shared<Castle>(Castle(Position(5135, 240), true)));
	world.flag = std::make_unique<Flag>(Flag(Position(4863, 116))); 
	world.button = nullptr;
}

void Level::setFourthLevel(World &world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 450;
	world.LAYOUT_STYLE = LayoutStyle::Castle;

	for (int i = 16; i < 432; i += 32) {
		for (int j = 464; j > 304; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	for (int i = 480; i < 832; i += 32) {
		for (int j = 464; j > 304; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	for (int i = 928; i < 1024; i += 32) {
		for (int j = 464; j > 304; j -= 32) {
			if (i == 960 && j == 336) {
				world.blocks.push_back(Block(BlockType::Empty, Position(960, 336)));
			}
			else {
				world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
			}
		}
	}

	for (int i = 1120; i < 2304; i += 32) {
		for (int j = 464; j > 272; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	for (int i = 16; i < 176; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 304)));
	}

	for (int i = 16; i < 144; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 272)));
	}

	for (int i = 16; i < 112; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 240)));
	}

	for (int i = 16; i < 6096; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 80)));
	}

	for (int i = 2304; i < 3424; i += 32) {
		for (int j = 464; j > 304; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	for (int i = 3136; i < 4288; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
	}

	for (int i = 16; i < 752; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 112)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 144)));
	}

	world.blocks.push_back(Block(BlockType::Ground, Position(720, 176)));
	world.blocks.push_back(Block(BlockType::Empty, Position(720, 207)));
	world.blocks.push_back(Block(BlockType::BonusWithFlower, Position(960, 207)));

	for (int i = 1200; i < 2312; i += 32) {
		for (int j = 176; j > 80; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	world.blocks.push_back(Block(BlockType::Empty, Position(1200, 207)));
	world.blocks.push_back(Block(BlockType::Empty, Position(1584, 207)));
	world.blocks.push_back(Block(BlockType::Empty, Position(1936, 207)));
	world.blocks.push_back(Block(BlockType::Empty, Position(2160, 207)));

	for (int i = 3200; i < 3424; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 112)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 144)));
	}

	world.blocks.push_back(Block(BlockType::Ground, Position(2592, 112)));
	world.blocks.push_back(Block(BlockType::Ground, Position(2880, 112)));
	world.blocks.push_back(Block(BlockType::Empty, Position(2592, 143)));
	world.blocks.push_back(Block(BlockType::Empty, Position(2880, 143)));
	world.blocks.push_back(Block(BlockType::Empty, Position(2448, 304)));
	world.blocks.push_back(Block(BlockType::Empty, Position(2736, 304)));
	world.blocks.push_back(Block(BlockType::Empty, Position(3024, 304)));

	for (int i = 3904; i < 4032; i += 32) {
		for (int j = 400; j > 304; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	for (int i = 4128; i < 4288; i += 32) {
		for (int j = 400; j > 304; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}

		world.blocks.push_back(Block(BlockType::Ground, Position(i, 112)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 144)));
	}

	for (int i = 4640; i < 5600; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
	}

	for (int i = 4640; i < 4736; i += 32) {
		for (int j = 400; j > 272; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	for (int i = 4672; i < 4736; i += 32) {
		for (int j = 176; j > 80; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	for (int i = 424; i < 472; i += 16) {
		world.inanimateElements.push_back(std::make_shared<Lava>(Lava(Position(i, 454))));
	}

	for (int i = 824; i < 920; i += 16) {
		world.inanimateElements.push_back(std::make_shared<Lava>(Lava(Position(i, 454))));
	}

	for (int i = 1016; i < 1112; i += 16) {
		world.inanimateElements.push_back(std::make_shared<Lava>(Lava(Position(i, 454))));
	}

	for (int i = 4272; i < 4704; i += 16) {
		world.inanimateElements.push_back(std::make_shared<Lava>(Lava(Position(i, 454))));
	}

	world.platforms.push_back(Platform(Position(4576, 210), PlatformType::SmallPlatform));

	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(3200, 235))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(4000, 280))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(4450, 200))));

	world.fireSerpents.push_back(FireSerpent(1, Position(960, 336)));
	world.fireSerpents.push_back(FireSerpent(8, Position(1584, 207)));
	world.fireSerpents.push_back(FireSerpent(13, Position(1936, 207)));
	world.fireSerpents.push_back(FireSerpent(21, Position(2160, 207)));
	world.fireSerpents.push_back(FireSerpent(1, Position(2880, 143)));
	world.fireSerpents.push_back(FireSerpent(10, Position(2448, 304)));
	world.fireSerpents.push_back(FireSerpent(18, Position(2736, 304)));

	// bridge and boss should always be added last
	world.platforms.push_back(Platform(Position(4452, 336), PlatformType::Bridge));
	world.monsters.push_back(std::make_shared<Boss>(Boss(Position(4575, 285))));

	world.inanimateElements.push_back(std::make_shared<Princess>(Princess(Position(5000, 392), true)));

	world.flag = nullptr;
	world.button = std::make_unique<Button>(Button(Position(4640, 272)));
}

void Level::setFirstHiddenStage(World &world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::Underground;

	for (int i = 16; i < 688; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	for (int i = 172; i < 428; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 80)));
		for (int j = 400; j > 304; j -= 32) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(i, j)));
		}
	}

	for (int i = 80; i < 432; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(16, i)));
	}

	for (int i = 172; i < 428; i += 32) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 306))));
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 242))));
		if (i != 172 && i != 396) {
			world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 178))));
		}
	}

	world.blocks.push_back(Block(BlockType::TubeLeftEntry, Position(583, 384)));
	for (int i = 399; i > 47; i -= 32) {
		world.blocks.push_back(Block(BlockType::Tube, Position(645, i)));
	}

	world.checkPoints.push_back(CheckPoint(Position(590, 390), true, 2));

	world.flag = nullptr;
	world.button = nullptr;
}

void Level::setSecondHiddenStage(World &world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::Underground;

	for (int i = 16; i < 688; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	world.blocks.push_back(Block(BlockType::Monetary, Position(528, 304)));

	for (int i = 80; i < 432; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(16, i)));
	}

	world.blocks.push_back(Block(BlockType::TubeLeftEntry, Position(583, 384)));

	for (int i = 399; i > 47; i -= 32) {
		world.blocks.push_back(Block(BlockType::Tube, Position(645, i)));
	}

	for (int i = 144; i < 624; i += 32) {
		if (i != 528) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(i, 304)));
		}
		
		for (int j = 80; j < 208; j += 32) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(i, j)));
		}
	}

	for (int i = 208; i < 304; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(560, i)));
		world.blocks.push_back(Block(BlockType::Destructible, Position(592, i)));
	}

	world.blocks.push_back(Block(BlockType::Indestructible, Position(560, 336)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(560, 336)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(592, 336)));

	for (int i = 172; i < 496; i += 32) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 274))));
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 402))));
	}

	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(140, 402))));

	world.checkPoints.push_back(CheckPoint(Position(590, 390), true, 2));

	world.flag = nullptr;
	world.button = nullptr;
}

void Level::setSecondStageOnSecondLevel(World &world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::OpenWorld;

	for (int i = 0; i < 50; ++i) {
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + (32 * i), 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(16 + (32 * i), 432)));
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 9 - i; ++j) {
			world.blocks.push_back(Block(BlockType::Indestructible, Position(176 + i * 32 + j * 32, 400 - i * 32)));
		}
	}

	world.blocks.push_back(Block(BlockType::Tube, Position(128, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(128, 368)));

	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(2, Position(192, 72))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(816, 104))));
	world.inanimateElements.push_back(std::make_shared<Cloud>(Cloud(1, Position(1168, 72))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(5, Position(592, 381))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(4, Position(1072, 397))));
	world.inanimateElements.push_back(std::make_shared<Bush>(Bush(1, Position(972, 400))));

	world.blocks.push_back(Block(BlockType::Indestructible, Position(720, 400)));

	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(128, 420))));

	world.inanimateElements.push_back(std::make_shared<Castle>(Castle(Position(915, 336), false)));
	world.flag = std::make_unique<Flag>(Flag(Position(703, 116)));
	world.button = nullptr;
}

void Level::setWinterWorld(World &world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::CustomWinter;

	for (int i = 16; i < 1168; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	for (int i = 176; i < 304; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 280)));
	}
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(224, 165)));

	world.blocks.push_back(Block(BlockType::Destructible, Position(464, 280)));

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5 - i; ++j) {
			world.blocks.push_back(Block(BlockType::Ground, Position(1008 + i * 32 + j * 32, 400 - i * 32)));
		}
	}

	for (int i = 463; i >= 367; i -= 32) {
		world.blocks.push_back(Block(BlockType::Tube, Position(1265, i)));
	}
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1265, 336)));

	world.blocks.push_back(Block(BlockType::AlternativeEmpty, Position(1440, 288)));
	world.blocks.push_back(Block(BlockType::AlternativeEmpty, Position(1616, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(1528, 144)));
	
	for (int i = 1776; i < 2416; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	world.blocks.push_back(Block(BlockType::Tube, Position(2080, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(2080, 368)));

	world.blocks.push_back(Block(BlockType::BonusWithRedMushroom, Position(2224, 256)));

	for (int i = 2528; i < 3112; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	for (int i = 400; i > 304; i -= 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(2624, i)));
	}

	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(2816, 272)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(2848, 160)));
	world.blocks.push_back(Block(BlockType::Monetary, Position(2880, 160)));

	for (int i = 2784; i < 2944; i += 32) {
		if (i != 2816) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(i, 272)));
		}
	}

	for (int i = 3456; i < 3680; i += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 464)));
		if (i != 3456 && i != 3648) {
			world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 432)));
		}
	}

	world.blocks.push_back(Block(BlockType::Empty, Position(3552, 208)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(3840, 208)));

	for (int i = 4032; i < 4960; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	world.blocks.push_back(Block(BlockType::Tube, Position(4143, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(4143, 368)));
	world.blocks.push_back(Block(BlockType::Tube, Position(4912, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(4912, 367)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(4912, 336)));

	world.blocks.push_back(Block(BlockType::Indestructible, Position(5120, 464)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5120, 432)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5260, 464)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5260, 432)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5400, 464)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(5400, 432)));

	for (int i = 5760; i < 6336; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	for (int i = 5776; i < 6320; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 400)));
	}

	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(5856, 256)));

	world.blocks.push_back(Block(BlockType::Tube, Position(5997, 367)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(5997, 336)));

	for (int i = 368; i > 128; i -= 30) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(6048, i)));
		world.blocks.push_back(Block(BlockType::Destructible, Position(6080, i)));
	}
	
	for (int i = 5952; i < 6048; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 158)));
	}

	for (int i = 6128, j = 158; i < 6296 && j < 398; i += 24, j += 40) {
		world.blocks.push_back(Block(BlockType::Empty, Position(i, j)));
	}

	world.blocks.push_back(Block(BlockType::BonusWithFlower, Position(6460, 144)));

	for (int i = 463; i >= 399; i -= 32) {
		world.blocks.push_back(Block(BlockType::Tube, Position(6700, i)));
	}
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(6700, 368)));

	for (int i = 6944; i < 8324; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	world.blocks.push_back(Block(BlockType::Tube, Position(6960, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(6960, 368)));

	world.blocks.push_back(Block(BlockType::Destructible, Position(7120, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(7152, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(7248, 288)));

	world.blocks.push_back(Block(BlockType::Tube, Position(7408, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(7408, 367)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(7408, 336)));

	for (int i = 7600; i < 7728; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 288)));
	}

	world.blocks.push_back(Block(BlockType::Destructible, Position(7632, 160)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(7664, 160)));

	for (int i = 8164; i < 8260; i += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 288)));
	}
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(8196, 160)));

	world.blocks.push_back(Block(BlockType::Tube, Position(8660, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(8660, 368)));

	for (int i = 8452; i < 10340; i += 32) {
		if (i != 10148 && i != 10180) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
			world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));

			if (i > 8932) {
				world.blocks.push_back(Block(BlockType::Ground, Position(i, 400)));
			}
			if (i > 9412) {
				world.blocks.push_back(Block(BlockType::Ground, Position(i, 368)));
			}
		}
	}

	world.blocks.push_back(Block(BlockType::Destructible, Position(8772, 240)));
	world.blocks.push_back(Block(BlockType::BonusWithFlower, Position(8996, 256)));
	world.blocks.push_back(Block(BlockType::Ground, Position(9732, 336)));

	for (int i = 9764; i < 10340; i += 32) {
		if (i != 10148 && i != 10180) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, 336)));
			world.blocks.push_back(Block(BlockType::Ground, Position(i, 304)));
		}
	}
	
	world.blocks.push_back(Block(BlockType::Tube, Position(9908, 271)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(9908, 240)));

	for (int i = 272; i > 0; i -= 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(9970, i)));
		world.blocks.push_back(Block(BlockType::Indestructible, Position(10002, i)));
	}

	for (int i = 463; i >= 271; i -= 32) {
		world.blocks.push_back(Block(BlockType::Tube, Position(10164, i)));
	}
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(10164, 240)));

	world.platforms.push_back(Platform(Position(3352, 385), PlatformType::MovingHorizontallyPlatform));
	world.platforms.push_back(Platform(Position(3892, 385), PlatformType::MovingHorizontallyPlatform));
	world.platforms.push_back(Platform(Position(5640, 375), PlatformType::SmallPlatform));
	world.platforms.push_back(Platform(Position(6460, 385), PlatformType::MovingVerticallyPlatform));

	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1040, 336))));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(2619, 225), true)));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2920, 400))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(2080, 420))));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(2325, 397), false)));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(3640, 300))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(4143, 420), true)));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(4912, 388))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4320, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4420, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4520, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4620, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4720, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(6208, 368))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(6700, 420))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(7408, 388))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(7800, 224))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(8160, 400))));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(8376, 245), true)));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(8660, 420), true)));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(9088, 368))));

	world.fireSerpents.push_back(FireSerpent(1, Position(3552, 208)));

	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(464, 250))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(2992, 272))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(6064, 90))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(8772, 210))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SIGNPOST, Position(49, 389))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::CHRISTMAS_TREE, Position(715, 377))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WINTER_CLOUD, Position(185, 75))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(572, 160))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(805, 76))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WINTER_CLOUD, Position(1081, 94))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(1305, 73))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(1627, 88))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::MOON, Position(1884, 126))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::CHRISTMAS_TREE, Position(2576, 377))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::CHRISTMAS_TREE, Position(6120, 345))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::CHRISTMAS_TREE, Position(10060, 249))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WINTER_CLOUD, Position(10235, 80))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SECOND_SIGNPOST, Position(9924, 100))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(2013, 111))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(1998, 65))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(2104, 75))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(2147, 68))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(2179, 87))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(2257, 102))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(2300, 64))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(2321, 105))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(2402, 67))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(2489, 131))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(2575, 84))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(2670, 121))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(2801, 79))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(2889, 91))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(2950, 103))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(3012, 97))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(3087, 69))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(3112, 113))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(3358, 95))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(3417, 80))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(3499, 112))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(3580, 91))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(3661, 120))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(3801, 142))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(3794, 71))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(3885, 110))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(3935, 93))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(3998, 81))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(4102, 99))));

	for (int i = 0; i < 5; ++i) {
		world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
			CustomWinterDecoration(DecorationType::WHITE_STAR, Position(4187 + i * 135, 104))));

		world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
			CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(4251 + i * 135, 88))));

		world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
			CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(4301 + i * 135, 123))));
	}

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(4560, 69))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(4712, 145))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(4475, 78))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(4800, 135))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(5000, 127))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(5073, 100))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(5163, 126))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(5225, 84))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(5371, 138))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(5450, 103))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(5526, 79))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::MOON, Position(5612, 99))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WINTER_CLOUD, Position(6385, 75))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(6805, 84))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WINTER_CLOUD, Position(7081, 101))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(7327, 73))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WINTER_CLOUD, Position(7895, 112))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(8140, 160))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::CHRISTMAS_TREE, Position(7876, 377))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(8760, 69))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(9012, 145))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(9275, 78))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(9633, 125))));

	world.checkPoints.push_back(CheckPoint(Position(5997, 297), false, 1));
	world.checkPoints.push_back(CheckPoint(Position(9908, 201), false, 3));

	world.flag = nullptr;
	world.button = nullptr;
}

void Level::setSecondStageOnWinterWorld(World &world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::CustomWinter;

	for (int i = 463; i >= 367; i -= 32) {
		world.blocks.push_back(Block(BlockType::Tube, Position(77, i)));
	}
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(77, 336)));

	for (int i = 128; i < 1056; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	world.blocks.push_back(Block(BlockType::Destructible, Position(368, 304)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(400, 304)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(432, 304)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(464, 304)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(496, 304)));

	world.blocks.push_back(Block(BlockType::Destructible, Position(800, 176)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(832, 176)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(768, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(800, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(832, 288)));
	world.blocks.push_back(Block(BlockType::Monetary, Position(864, 288)));

	for (int i = 1024; i < 1632; i += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 400)));
	}

	world.blocks.push_back(Block(BlockType::Empty, Position(1536, 288)));

	for (int i = 1600; i < 1980; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));

		world.blocks.push_back(Block(BlockType::Ground, Position(i, 208)));
	}

	world.blocks.push_back(Block(BlockType::Ground, Position(1728, 176)));
	world.blocks.push_back(Block(BlockType::Ground, Position(1760, 176)));
	world.blocks.push_back(Block(BlockType::Ground, Position(1888, 176)));
	world.blocks.push_back(Block(BlockType::Ground, Position(1920, 176)));
	world.blocks.push_back(Block(BlockType::Ground, Position(1888, 144)));
	world.blocks.push_back(Block(BlockType::Ground, Position(1920, 144)));

	world.blocks.push_back(Block(BlockType::Tube, Position(1744, 143)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1744, 111)));

	world.blocks.push_back(Block(BlockType::Tube, Position(1904, 111)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1904, 79)));

	for (int i = 2028; i < 2636; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));

		if (i != 2028) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, 208)));
		}
	}

	world.blocks.push_back(Block(BlockType::Ground, Position(2508, 176)));
	world.blocks.push_back(Block(BlockType::Ground, Position(2540, 176)));

	world.blocks.push_back(Block(BlockType::Tube, Position(2524, 143)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(2524, 111)));

	world.blocks.push_back(Block(BlockType::Destructible, Position(1232, 256)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(1264, 256)));
	world.blocks.push_back(Block(BlockType::BonusWithStar, Position(1296, 256)));

	world.blocks.push_back(Block(BlockType::Empty, Position(2246, 320)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(2374, 112)));
	world.blocks.push_back(Block(BlockType::BonusWithRedMushroom, Position(2406, 112)));

	for (int i = 463; i >= 399; i -= 32) {
		world.blocks.push_back(Block(BlockType::Tube, Position(2652, i)));
	}
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(2652, 368)));

	for (int i = 2700; i < 3212; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}
	world.blocks.push_back(Block(BlockType::Ground, Position(3180, 400)));

	for (int i = 2812; i < 3068; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 208)));
	}

	for (int i = 3840; i < 5440; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 9 - i; ++j) {
			world.blocks.push_back(Block(BlockType::Indestructible, Position(4160 + i * 32 + j * 32, 400 - i * 32)));
		}
	}

	world.blocks.push_back(Block(BlockType::Tube, Position(4112, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(4112, 368)));

	world.blocks.push_back(Block(BlockType::Indestructible, Position(4704, 400)));
	
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(4040, 400))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(4112, 420))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(910, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1285, 368))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(1450, 315))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1536, 256))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1830, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2295, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2460, 400))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(2050, 250))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(2050, 365))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(2800, 240))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(3110, 283))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(2400, 75))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2800, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3100, 400))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3400, 400))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(3330, 252))));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(2700, 255), true)));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2850, 176))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(3020, 176))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1950, 176))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2300, 176))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2685, 176))));
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(1720, 176))));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(1755, 132))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(1744, 163))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(1904, 131), true)));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(2524, 163))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(2652, 420), true)));
	
	world.monsters.push_back(std::make_shared<Creature>(Creature(Position(2920, 400))));
	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(2325, 397), false)));
	world.monsters.push_back(std::make_shared<FireRocket>(FireRocket(Position(3640, 300))));

	world.fireSerpents.push_back(FireSerpent(1, Position(2246, 320)));

	world.platforms.push_back(Platform(Position(3325, 120), PlatformType::MovingDownPlatform));
	world.platforms.push_back(Platform(Position(3325, 380), PlatformType::MovingDownPlatform));
	world.platforms.push_back(Platform(Position(3599, 120), PlatformType::MovingUpPlatform));
	world.platforms.push_back(Platform(Position(3599, 380), PlatformType::MovingUpPlatform));

	for (int i = 1048; i < 1612; i += 16) {
		world.inanimateElements.push_back(std::make_shared<Lava>(Lava(Position(i, 456))));
	}

	for (int i = 2812; i < 3068; i += 32) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 120))));
	}

	for (int i = 1792; i < 1888; i += 32) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 178))));
	}

	for (int i = 124; i < 324; i += 40) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(3462, i))));
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(3762, i))));
	}

	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(3180, 300))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SIGNPOST, Position(226, 389))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::MOON, Position(225, 111))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(45, 88))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(125, 104))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(77, 167))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::CHRISTMAS_TREE, Position(702, 377))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::CHRISTMAS_TREE, Position(2600, 153))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(525, 67))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(601, 74))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(439, 82))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(751, 107))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(825, 93))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(889, 111))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(1001, 75))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(1325, 73))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(1089, 85))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(1200, 107))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(1134, 134))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WHITE_STAR, Position(1540, 81))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::YELLOW_STAR, Position(1600, 105))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::GOLDEN_STAR, Position(1630, 120))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(3212, 99))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WINTER_CLOUD, Position(3875, 123))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(4124, 87))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::WINTER_CLOUD, Position(5012, 115))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::SMALL_WINTER_CLOUD, Position(5225, 89))));

	world.inanimateElements.push_back(std::make_shared<CustomWinterDecoration>(
		CustomWinterDecoration(DecorationType::CHRISTMAS_TREE, Position(5167, 377))));

	world.flag = std::make_unique<Flag>(Flag(Position(4689, 116)));
	world.button = nullptr;
}

void Level::setWinterHiddenStage(World &world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 450;
	world.LAYOUT_STYLE = LayoutStyle::Underground;

	for (int i = 40; i <= 544; i += 72) {
		world.blocks.push_back(Block(BlockType::AlternativeEmpty, Position(i, 408)));
	}

	for (int i = 528; i < 688; i += 32) {
		for (int j = 464; j > 368; j -= 32) {
			world.blocks.push_back(Block(BlockType::Ground, Position(i, j)));
		}
	}

	for (int i = 140; i < 524; i += 32) {
		world.blocks.push_back(Block(BlockType::Destructible, Position(i, 80)));
	}

	world.blocks.push_back(Block(BlockType::AlternativeEmpty, Position(592, 295)));
	
	int coins = world.getPlayer().getCoins();
	if (coins < 25) {
		world.blocks.push_back(Block(BlockType::BonusWithOneUpMushroom, Position(592, 170)));
	}
	else {
		world.blocks.push_back(Block(BlockType::Destructible, Position(592, 170)));
	}

	world.blocks.push_back(Block(BlockType::TubeLeftEntry, Position(583, 352)));
	for (int i = 367; i > 15; i -= 32) {
		world.blocks.push_back(Block(BlockType::Tube, Position(645, i)));
	}

	world.blocks.push_back(Block(BlockType::Tube, Position(85, -5)));

	world.blocks.push_back(Block(BlockType::Ground, Position(633, 15)));
	world.blocks.push_back(Block(BlockType::Ground, Position(665, 15)));

	world.blocks.push_back(Block(BlockType::Ground, Position(16, 304)));
	world.blocks.push_back(Block(BlockType::Ground, Position(16, 272)));
	world.blocks.push_back(Block(BlockType::Ground, Position(48, 272)));
	world.blocks.push_back(Block(BlockType::Monetary, Position(32, 144)));

	world.blocks.push_back(Block(BlockType::AlternativeEmpty, Position(304, 208)));

	world.fireSerpents.push_back(FireSerpent(13, Position(304, 208)));

	for (int i = 8; i < 512; i += 16) {
		world.inanimateElements.push_back(std::make_shared<Lava>(Lava(Position(i, 456))));
	}

	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(32, 242))));

	for (int i = 76; i <= 440; i += 72) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 360))));
	}

	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(520, 169))));

	world.checkPoints.push_back(CheckPoint(Position(590, 358), true, 2));

	world.flag = nullptr;
	world.button = nullptr;
}

void Level::setSummerWorld(World& world)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.destroyedElements.clear();
	world.fireballs.clear();
	world.checkPoints.clear();
	world.fireSerpents.clear();

	world.slidingCounter = 0;
	world.resetImages();

	world.WORLD_HEIGHT = 480;
	world.LAYOUT_STYLE = LayoutStyle::CustomSummer;


	for (int i = 16; i < 656; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 464)));
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 432)));
	}
	world.blocks.push_back(Block(BlockType::Ground, Position(16, 400)));
	world.blocks.push_back(Block(BlockType::Ground, Position(48, 400)));

	world.blocks.push_back(Block(BlockType::Tube, Position(32, 367)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(32, 336)));

	world.blocks.push_back(Block(BlockType::Tube, Position(576, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(576, 368)));

	for (int i = 144; i < 304; i += 32) {
		world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(i, 304)));
		world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(i, 192)));
	}
	world.blocks.push_back(Block(BlockType::BonusWithRedMushroom, Position(304, 304)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(304, 192)));

	for (int i = 656, j = 400; i < 912; i += 32, j -= 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, j)));
	}

	for (int i = 1040, j = 176; i < 1296; i += 32, j += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, j)));
	}

	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(880, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithFlower, Position(1040, 288)));

	world.blocks.push_back(Block(Position(1405, 435), 7));
	world.blocks.push_back(Block(Position(1652, 397), 15));
	world.blocks.push_back(Block(Position(1974, 442), 11));
	world.blocks.push_back(Block(Position(1740, 200), 7));
	world.blocks.push_back(Block(Position(2310, 291), 9));
	world.blocks.push_back(Block(Position(2447, 416), 5));
	world.blocks.push_back(Block(Position(2628, 370), 5));

	world.blocks.push_back(Block(BlockType::Ground, Position(2132, 464)));
	world.blocks.push_back(Block(BlockType::Ground, Position(2132, 432)));
	world.blocks.push_back(Block(BlockType::Ground, Position(2164, 464)));
	world.blocks.push_back(Block(BlockType::Ground, Position(2164, 432)));

	world.blocks.push_back(Block(BlockType::Tube, Position(2148, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(2148, 368)));

	world.blocks.push_back(Block(BlockType::BonusWithFlower, Position(1970, 104)));

	for (int i = 2752; i < 3360; i += 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(i, 464)));
	}

	for (int i = 2784; i < 3104; i += 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(i, 304)));
	}

	for (int i = 304; i > -32; i -= 32) {
		world.blocks.push_back(Block(BlockType::Ground, Position(3104, i)));
	}

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 7 - i; ++j) {
			world.blocks.push_back(Block(BlockType::Indestructible, Position(3360 + i * 32 + j * 32, 464 - i * 32)));
		}
	}

	for (int i = 464; i > 304; i -= 32) {
		world.blocks.push_back(Block(BlockType::Indestructible, Position(3744, i)));
		world.blocks.push_back(Block(BlockType::Indestructible, Position(3904, i)));
		world.blocks.push_back(Block(BlockType::Indestructible, Position(4064, i)));
	}

	world.blocks.push_back(Block(BlockType::Tube, Position(4250, 463)));
	world.blocks.push_back(Block(BlockType::Tube, Position(4250, 431)));
	world.blocks.push_back(Block(BlockType::Tube, Position(4250, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(4250, 367)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(4250, 336)));

	world.platforms.push_back(Platform(Position(960, 460), PlatformType::MovingVerticallyPlatform));
	world.platforms.push_back(Platform(Position(1970, 335), PlatformType::MovingVerticallyPlatform));


	world.flag = nullptr;
	world.button = nullptr;
}