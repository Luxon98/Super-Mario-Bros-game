#include "Level.h"

#include "World.h"
#include "Screen.h"
#include "Block.h"
#include "Position.h"
#include "Creature.h"
#include "Turtle.h"
#include "RedTurtle.h"
#include "Plant.h"
#include "Bush.h"
#include "Cloud.h"
#include "Coin.h"
#include "Flag.h"
#include "Castle.h"
#include "LayoutStyle.h"
#include "Flower.h"


void Level::setFirstLevel(World &world, bool bonusLifeBlockFlag)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.fireballs.clear();

	world.slidingCounter = 0;
	world.resetImages();

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
			world.blocks.push_back(Block(BlockType::Indestructible, 
				Position(5806 + i * 32 + j * 32, 400 - i * 32)));
		}
	}

	world.blocks.push_back(Block(BlockType::Destructible, Position(5390, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(5422, 288)));
	world.blocks.push_back(Block(BlockType::BonusWithCoin, Position(5454, 288)));
	world.blocks.push_back(Block(BlockType::Destructible, Position(5486, 288)));
	world.blocks.push_back(Block(BlockType::Indestructible, Position(6350, 400)));
	world.blocks.push_back(Block(BlockType::Tube, Position(926, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(926, 368)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1266, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1266, 367)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1266, 336)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1502, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1502, 367)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1502, 335)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1502, 304)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1854, 399)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1854, 367)));
	world.blocks.push_back(Block(BlockType::Tube, Position(1854, 335)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(1854, 304)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5246, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(5246, 368)));
	world.blocks.push_back(Block(BlockType::Tube, Position(5754, 399)));
	world.blocks.push_back(Block(BlockType::TubeTopEntry, Position(5754, 368)));

	if (bonusLifeBlockFlag) {
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

	world.inanimateElements.push_back(std::make_shared<Castle>(Castle(Position(6542, 336))));
	world.flag = Flag(Position(6335, 116));
}

void Level::setSecondLevel(World &world, bool bonusLifeBlockFlag)
{
	world.blocks.clear();
	world.platforms.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.fireballs.clear();
	
	world.slidingCounter = 0;
	world.resetImages();

	world.LAYOUT_STYLE = LayoutStyle::Underground;

	if (bonusLifeBlockFlag) {
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

		if (i < 4800) {
			world.blocks.push_back(Block(BlockType::Destructible, Position(16 + i, 272)));
		}
	}

	world.blocks.push_back(Block(BlockType::Monetary, Position(4816, 272)));

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

	world.platforms.push_back(MovingPlatform(Position(4526, 120), Direction::Down));
	world.platforms.push_back(MovingPlatform(Position(4526, 380), Direction::Down));
	world.platforms.push_back(MovingPlatform(Position(5010, 120), Direction::Up));
	world.platforms.push_back(MovingPlatform(Position(5010, 380), Direction::Up));

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
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(3520, 356))));
	world.monsters.push_back(std::make_shared<Plant>(Plant(Position(3712, 420))));

	world.monsters.push_back(std::make_shared<RedTurtle>(RedTurtle(Position(4850, 397), false)));

	for (int i = 1326; i < 1454; i += 32) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 176))));
	}

	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1294, 272))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(1454, 272))));
	world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(2190, 272))));

	for (int i = 1870; i < 1998; i += 32) {
		world.inanimateElements.push_back(std::make_shared<Coin>(Coin(Position(i, 272))));
	}


	world.inanimateElements.push_back(std::make_shared<Castle>(Castle(Position(6684, 336))));
	world.flag = Flag(Position(6635, 116));
}

