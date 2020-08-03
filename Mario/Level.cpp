#include "Level.h"

void Level::setFirstLevel(World& world)
{
	world.blocks.clear();
	world.inanimateElements.clear();
	world.bonusElements.clear();
	world.monsters.clear();
	world.temporaryElements.clear();
	world.fireballs.clear();

	for (int i = 0; i < World::WORLD_WIDTH + CAMERA_REFERENCE_POINT; i += 32) {
		if (i != 2208 && i != 2240 && i != 4896 && i != 4928 && i != 2752 && i != 2784 && i != 2816) {
			world.blocks.push_back(Block(Ground, new Position(16 + i, Screen::SCREEN_HEIGHT - 16)));
			world.blocks.push_back(Block(Ground, new Position(16 + i, Screen::SCREEN_HEIGHT - 48)));
		}
	}
	world.blocks.push_back(Block(BonusWithCoin, new Position(528, 288)));
	world.blocks.push_back(Block(Destructible, new Position(656, 288)));
	world.blocks.push_back(Block(BonusWithRedMushroom, new Position(688, 288)));
	world.blocks.push_back(Block(Destructible, new Position(720, 288)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(720, 160)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(752, 288)));
	world.blocks.push_back(Block(Destructible, new Position(784, 288)));
	world.blocks.push_back(Block(Destructible, new Position(2478, 288)));
	world.blocks.push_back(Block(BonusWithFlower, new Position(2510, 288)));
	world.blocks.push_back(Block(Destructible, new Position(2542, 288)));
	for (int i = 0; i < 8; ++i) {
		world.blocks.push_back(Block(Destructible, new Position(2574 + i * 32, 160)));
	}
	world.blocks.push_back(Block(Destructible, new Position(2926, 160)));
	world.blocks.push_back(Block(Destructible, new Position(2958, 160)));
	world.blocks.push_back(Block(Destructible, new Position(2990, 160)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(3022, 160)));
	world.blocks.push_back(Block(Monetary, new Position(3022, 288)));
	world.blocks.push_back(Block(Destructible, new Position(3214, 288)));
	world.blocks.push_back(Block(BonusWithStar, new Position(3246, 288)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(3406, 288)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(3502, 288)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(3502, 160)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(3598, 288)));
	world.blocks.push_back(Block(Destructible, new Position(3790, 288)));
	world.blocks.push_back(Block(Destructible, new Position(3886, 160)));
	world.blocks.push_back(Block(Destructible, new Position(3918, 160)));
	world.blocks.push_back(Block(Destructible, new Position(3950, 160)));
	world.blocks.push_back(Block(Destructible, new Position(4146, 160)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(4178, 160)));
	world.blocks.push_back(Block(BonusWithCoin, new Position(4210, 160)));
	world.blocks.push_back(Block(Destructible, new Position(4242, 160)));
	world.blocks.push_back(Block(Destructible, new Position(4178, 288)));
	world.blocks.push_back(Block(Destructible, new Position(4210, 288)));
	world.blocks.push_back(Block(Indestructible, new Position(4302, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4334, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4366, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4398, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4334, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4366, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4398, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4366, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(4398, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(4398, 304)));
	world.blocks.push_back(Block(Indestructible, new Position(4494, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4526, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4558, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4590, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4494, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4526, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4558, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4494, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(4526, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(4494, 304)));
	world.blocks.push_back(Block(Indestructible, new Position(4752, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4784, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4816, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4848, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4880, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4784, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4816, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4848, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4880, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4816, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(4848, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(4880, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(4848, 304)));
	world.blocks.push_back(Block(Indestructible, new Position(4880, 304)));
	world.blocks.push_back(Block(Indestructible, new Position(4976, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(5008, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(5040, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(5072, 400)));
	world.blocks.push_back(Block(Indestructible, new Position(4976, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(5008, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(5040, 368)));
	world.blocks.push_back(Block(Indestructible, new Position(4976, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(5008, 336)));
	world.blocks.push_back(Block(Indestructible, new Position(4976, 304)));
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 9 - i; ++j) {
			world.blocks.push_back(Block(Indestructible, new Position(5806 + i * 32 + j * 32, 400 - i * 32)));
		}
	}
	world.blocks.push_back(Block(Indestructible, new Position(6350, 400)));
	world.blocks.push_back(Block(Tube, new Position(926, 399)));
	world.blocks.push_back(Block(TubeEntry, new Position(926, 368)));
	world.blocks.push_back(Block(Tube, new Position(1266, 399)));
	world.blocks.push_back(Block(Tube, new Position(1266, 367)));
	world.blocks.push_back(Block(TubeEntry, new Position(1266, 336)));
	world.blocks.push_back(Block(Tube, new Position(1502, 399)));
	world.blocks.push_back(Block(Tube, new Position(1502, 367)));
	world.blocks.push_back(Block(Tube, new Position(1502, 335)));
	world.blocks.push_back(Block(TubeEntry, new Position(1502, 304)));
	world.blocks.push_back(Block(Tube, new Position(1854, 399)));
	world.blocks.push_back(Block(Tube, new Position(1854, 367)));
	world.blocks.push_back(Block(Tube, new Position(1854, 335)));
	world.blocks.push_back(Block(TubeEntry, new Position(1854, 304)));
	world.blocks.push_back(Block(Tube, new Position(5246, 399)));
	world.blocks.push_back(Block(TubeEntry, new Position(5246, 368)));
	world.blocks.push_back(Block(Tube, new Position(5754, 399)));
	world.blocks.push_back(Block(TubeEntry, new Position(5754, 368)));
	world.blocks.push_back(Block(BonusWithGreenMushroom, new Position(2064, 288)));

	world.inanimateElements.push_back(new Bush(5, new Position(80, 381)));
	world.inanimateElements.push_back(new Bush(3, new Position(432, 400)));
	world.inanimateElements.push_back(new Bush(4, new Position(560, 397)));
	world.inanimateElements.push_back(new Cloud(1, new Position(656, 72)));
	world.inanimateElements.push_back(new Bush(1, new Position(782, 400)));
	world.inanimateElements.push_back(new Cloud(3, new Position(944, 104)));
	world.inanimateElements.push_back(new Cloud(2, new Position(1214, 72)));
	world.inanimateElements.push_back(new Bush(2, new Position(1374, 400)));
	world.inanimateElements.push_back(new Bush(5, new Position(1614, 381)));
	world.inanimateElements.push_back(new Cloud(1, new Position(1838, 104)));
	world.inanimateElements.push_back(new Bush(3, new Position(1966, 400)));
	world.inanimateElements.push_back(new Bush(4, new Position(2094, 397)));
	world.inanimateElements.push_back(new Cloud(1, new Position(2190, 72)));
	world.inanimateElements.push_back(new Bush(1, new Position(2318, 400)));
	world.inanimateElements.push_back(new Cloud(3, new Position(2478, 104)));
	world.inanimateElements.push_back(new Cloud(2, new Position(2750, 72)));
	world.inanimateElements.push_back(new Bush(2, new Position(2910, 400)));
	world.inanimateElements.push_back(new Bush(5, new Position(3150, 381)));
	world.inanimateElements.push_back(new Bush(3, new Position(3502, 400)));
	world.inanimateElements.push_back(new Bush(4, new Position(3628, 397)));
	world.inanimateElements.push_back(new Bush(1, new Position(3854, 400)));
	world.inanimateElements.push_back(new Cloud(1, new Position(3374, 104)));
	world.inanimateElements.push_back(new Cloud(1, new Position(3726, 72)));
	world.inanimateElements.push_back(new Cloud(3, new Position(4014, 104)));
	world.inanimateElements.push_back(new Cloud(2, new Position(4286, 72)));
	world.inanimateElements.push_back(new Bush(2, new Position(4448, 400)));
	world.inanimateElements.push_back(new Bush(5, new Position(4686, 381)));
	world.inanimateElements.push_back(new Cloud(1, new Position(4910, 104)));
	world.inanimateElements.push_back(new Bush(1, new Position(5050, 400)));
	world.inanimateElements.push_back(new Bush(4, new Position(5166, 397)));
	world.inanimateElements.push_back(new Bush(1, new Position(5390, 400)));
	world.inanimateElements.push_back(new Bush(5, new Position(6222, 381)));
	world.inanimateElements.push_back(new Bush(1, new Position(6608, 400)));
	world.inanimateElements.push_back(new Bush(4, new Position(6702, 397)));
	world.inanimateElements.push_back(new Cloud(1, new Position(5262, 72)));
	world.inanimateElements.push_back(new Cloud(3, new Position(5550, 104)));
	world.inanimateElements.push_back(new Cloud(2, new Position(5822, 72)));
	world.inanimateElements.push_back(new Cloud(1, new Position(6446, 104)));

	world.monsters.push_back(new Creature(new Position(730, 400)));
	world.monsters.push_back(new Creature(new Position(1650, 400)));
	world.monsters.push_back(new Creature(new Position(1710, 400)));
	world.monsters.push_back(new Creature(new Position(2650, 128)));
	world.monsters.push_back(new Creature(new Position(2700, 128)));
	world.monsters.push_back(new Creature(new Position(3180, 400)));
	world.monsters.push_back(new Creature(new Position(3220, 400)));
	world.monsters.push_back(new Turtle(new Position(3350, 400)));
	world.monsters.push_back(new Creature(new Position(3800, 400)));
	world.monsters.push_back(new Creature(new Position(3850, 400)));
	world.monsters.push_back(new Creature(new Position(4050, 400)));
	world.monsters.push_back(new Creature(new Position(4100, 400)));
	world.monsters.push_back(new Creature(new Position(4150, 400)));
	world.monsters.push_back(new Creature(new Position(4200, 400)));
	world.monsters.push_back(new Creature(new Position(5200, 400)));
	world.monsters.push_back(new Creature(new Position(5270, 400)));

	world.inanimateElements.push_back(new Castle(new Position(6542, 336)));
	world.flag = new Flag(new Position(6335, 116));
}

