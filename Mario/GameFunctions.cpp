#include "GameFunctions.h"

#include <iostream>
#include <chrono>
#include <memory>
#include "KeyboardController.h"
#include "SoundController.h"
#include "Player.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Star.h"
#include "FireBall.h"
#include "Turtle.h"
#include "RedTurtle.h"
#include "Creature.h"
#include "Plant.h"
#include "Shell.h"
#include "Flag.h"
#include "AnimatedText.h"
#include "AnimatedCoin.h"
#include "Shards.h"
#include "Explosion.h"
#include "CrushedCreature.h"
#include "DestroyedCreature.h"
#include "DestroyedTurtle.h"
#include "Bush.h"
#include "Cloud.h"
#include "Castle.h"
#include "Level.h"
#include "World.h"
#include "Screen.h"
#include "Block.h"
#include "Position.h"
#include "FileNotLoadedException.h"


bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions)
{
	for (int i = begin, j = 0; j < repetitions; i += shift, j++) {
		if (difference >= i && difference <= i + 150) {
			return true;
		}
	}

	return false;
}

void loadBonusObjectsImages(SDL_Surface* display)
{
	Flower tempFlower = Flower();
	tempFlower.loadFlowerImages(display);

	Mushroom tempMushroom = Mushroom();
	tempMushroom.loadMushroomImages(display);

	Star tempStar = Star();
	tempStar.loadStarImages(display);

	Coin tempCoin = Coin();
	tempCoin.loadCoinImages(display);
}

void loadInanimateObjectImages(SDL_Surface* display)
{
	Bush tempBush = Bush();
	tempBush.loadBushImages(display);

	Cloud tempCloud = Cloud();
	tempCloud.loadCloudImages(display);

	Castle tempCastle = Castle();
	tempCastle.loadCastleImages(display);

	Flag tempFlag = Flag();
	tempFlag.loadFlagImages(display);
}

void loadLivingObjectImages(SDL_Surface* display)
{
	Creature tempCreature = Creature();
	tempCreature.loadCreatureImages(display);

	Turtle tempTurtle = Turtle();
	tempTurtle.loadTurtleImages(display);

	RedTurtle tempRedTurtle = RedTurtle();
	tempRedTurtle.loadTurtleImages(display);

	Plant tempPlant = Plant();
	tempPlant.loadPlantImages(display);

	Shell tempShell = Shell();
	tempShell.loadShellImage(display);

	FireBall tempFireBall = FireBall();
	tempFireBall.loadFireBallImages(display);

	Player tempPlayer = Player();
	tempPlayer.loadPlayerImages(display);
}

void loadTemporaryObjectImages(SDL_Surface* display)
{
	CrushedCreature tempCrushedCreature = CrushedCreature();
	tempCrushedCreature.loadCrushedCreatureImage(display);

	DestroyedCreature tempDestroyedCreature = DestroyedCreature();
	tempDestroyedCreature.loadDestroyedCreatureImage(display);

	DestroyedTurtle tempDestroyedTurtle = DestroyedTurtle();
	tempDestroyedTurtle.loadDestroyedTurtleImage(display);

	Explosion tempExplosion = Explosion();
	tempExplosion.loadExplosionImage(display);

	Shards tempShards = Shards();
	tempShards.loadShardsImages(display);

	AnimatedCoin tempAnimatedCoin = AnimatedCoin();
	tempAnimatedCoin.loadAnimatedCoinImages(display);

	AnimatedText tempAnimatedText = AnimatedText();
	tempAnimatedText.loadAnimatedTextImages(display);
}

void loadBlockImages(SDL_Surface* display)
{
	Block tempBlock = Block();
	tempBlock.loadBlockImages(display);
}

void loadImages(SDL_Surface* display)
{
	loadBonusObjectsImages(display);
	loadInanimateObjectImages(display);
	loadLivingObjectImages(display);
	loadTemporaryObjectImages(display);
	loadBlockImages(display);
}

void playBackgroundMusic(int level)
{
	if (level == 1 || level == 3) {
		SoundController::playOpenWorldMusic();
	}
	else if (level == 2) {
		SoundController::playUndergroundMusic();
	}
	else {
		SoundController::playCastleMusic();
	}
}

void reset(KeyboardController &controller, Screen* screen, bool * playerState)
{
	controller.clearKeysState();
	screen->resetScreen();
	*playerState = true;
}

void setWorld(int level, Player &player, World &world, bool playerState)
{
	if (playerState) {
		player.setStartingXY(level);
	}
	else {
		player.reborn(level);
	}

	if (level == 1) {
		Level::setFirstLevel(world, playerState);
	}
	else if (level == 2) {
		Level::setSecondLevel(world);
	}
}

void runGame()
{
	bool loadResourcesStatus = true;

	// screen cannot be a smart shared_ptr, because this class contains pointers to types from SDL library
	// which cause problems (when automatically deleted) due to lack of proper deconstructors
	Screen* screen = new Screen();

	if (screen->getInitStatus()) {
		showScreenErrorWindow();
		return;
	}
	
	try {
		loadImages(screen->getDisplay());
	}
	catch (const FileNotLoadedException & e) {
		loadResourcesStatus = false;
		showFileErrorWindow(e.what());
	}

	KeyboardController controller = KeyboardController();
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	if (loadResourcesStatus) {
		bool playerState = true, winStatus = false, timeState = true;
		SDL_Event event;

		World world = World();
		world.setScreen(screen);

		SoundController soundMixer = SoundController();

		std::shared_ptr<Player> player = std::make_shared<Player>(Player(Position(35, 400)));

		world.setPlayer(player);
		screen->setPlayer(player);

		int level = 2;

		while (player->getLives() && !winStatus) {
			setWorld(level, *player, world, playerState);
			reset(controller, screen, &playerState);

			screen->drawStartScreen();
			playBackgroundMusic(level);

			while (playerState && timeState && !winStatus) {
				screen->updateScreen(world);

				while (SDL_PollEvent(&event) && playerState) {
					controller.handleKeysState(state);
					controller.handleKeys(*player, world);

					if (player->isDead()) {
						playerState = false;
					}
					controller.clearKeysState();
				}

				if (playerState) {
					controller.handleKeys(*player, world);
				}

				if (world.isPlayerFinishingWorld() && !winStatus) {
					SoundController::playFlagDownEffect();
					world.switchOnFlag();
					player->setSlidingParameters();

					while (!world.isFlagDown()) {
						world.performActions();
						screen->updateScreen(world);
					}
					player->setFinishingRunParameters();

					screen->drawWorldFinishedScreen(world);
					
					++level;
					screen->setLevel(level);
					if (level == 3) {
						winStatus = true;
					}
					break;
				}

				if (player->isDead()) {
					playerState = false;
				}
				else if (screen->isTimePassed() && !winStatus) {
					timeState = false;
				}
			}

			if (!playerState) {
				screen->drawDeadMario(world);
			}
			else if (!timeState) {
				screen->drawTimeUpScreen();
				SoundController::playTimePassedMusic();
			}
		}

		SoundController::playGameoverMusic();
		screen->drawGameOverScreen();
	}

	delete screen;
}