#include "GameFunctions.h"

#include <iostream>
#include <chrono>
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
#include "Rock.h"
#include "Castle.h"
#include "Level.h"
#include "World.h"
#include "Screen.h"
#include "Camera.h"
#include "Block.h"
#include "MovingPlatform.h"
#include "Position.h"
#include "FileNotLoadedException.h"


void loadBonusObjectsImages(SDL_Surface* display)
{
	Flower::loadFlowerImages(display);
	Mushroom::loadMushroomImages(display);
	Star::loadStarImages(display);
}

void loadInanimateObjectImages(SDL_Surface* display)
{
	Coin::loadCoinImages(display);
	Bush::loadBushImages(display);
	Cloud::loadCloudImages(display);
	Rock::loadRockImage(display);
	Flag::loadFlagImages(display);
	Castle::loadCastleImages(display);
}

void loadLivingObjectImages(SDL_Surface* display)
{
	Creature::loadCreatureImages(display);
	Turtle::loadTurtleImages(display);
	RedTurtle::loadTurtleImages(display);
	Plant::loadPlantImages(display);
	Shell::loadShellImage(display);
	FireBall::loadFireBallImages(display);
	Player::loadPlayerImages(display);
}

void loadTemporaryObjectImages(SDL_Surface* display)
{
	CrushedCreature::loadCrushedCreatureImage(display);
	DestroyedCreature::loadDestroyedCreatureImage(display);
	DestroyedTurtle::loadDestroyedTurtleImage(display);
	Explosion::loadExplosionImage(display);
	Shards::loadShardsImages(display);
	AnimatedCoin::loadAnimatedCoinImages(display);
	AnimatedText::loadAnimatedTextImages(display);
}

void loadBlockImages(SDL_Surface* display)
{
	Block::loadBlockImages(display);
	MovingPlatform::loadPlatformImage(display);
}

void loadImages(SDL_Surface* display)
{
	loadBonusObjectsImages(display);
	loadInanimateObjectImages(display);
	loadLivingObjectImages(display);
	loadTemporaryObjectImages(display);
	loadBlockImages(display);
}

void resetScreen(Screen &screen, int level, int checkPointMark)
{
	if (level == 1) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 1) {
			screen.resetScreen(0, 640, false);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(1600, 2240, false);
		}
	}
	else if (level == 2) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(0, 640, false);
		}
	}
	else if (level == 3) {
		screen.resetScreen(0, 640);
	}
}

void changeLevel(int level, World &world, bool playerState)
{
	if (level == 1) {
		Level::setFirstLevel(world, playerState);
	}
	else if (level == 2) {
		Level::setSecondLevel(world, playerState);
	}
	else if (level == 3) {
		Level::setThirdLevel(world);
	}
}

void setWorld(int level, Player &player, World &world, bool playerState)
{
	if (playerState) {
		player.setPositionXY(level);
	}
	else {
		player.reborn(level);
	}

	changeLevel(level, world, playerState);
}

void drawChangeStageScreen(Screen& screen)
{
	SoundController::playPipeTravelEffect();
	screen.drawChangeStageOfLevelScreen();
	SoundController::stopMusic();
}

void setSubWorld(int level, int checkPointMark, Player &player, World &world)
{
	player.resetSteps();
	player.setPositionXY(level, checkPointMark);

	if (level == 1) {
		if (checkPointMark == 1) {
			Level::setFirstBonusStage(world);
		}
		else {
			Level::setFirstLevel(world);
		}
	}
	else if (level == 2 && checkPointMark == 2) {
		Level::setSecondStageOnSecondLevel(world);
	}
}

void adjustCamera(int level, int checkPointMark)
{
	if ((level == 1 || level == 2) && checkPointMark == 1) {
		Camera::disableCameraMoving();
	}
	else {
		Camera::enableCameraMoving();
	}
}

void runGame()
{
	bool loadResourcesStatus = true;

	Screen screen = Screen();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(Camera(0, Screen::SCREEN_WIDTH));

	if (screen.getInitStatus()) {
		showScreenErrorWindow();
		return;
	}
	
	try {
		loadImages(screen.getDisplay());
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
	
		SoundController soundMixer = SoundController();

		std::shared_ptr<Player> player = std::make_shared<Player>(Player(Position(35, 400)));

		player->setCamera(camera);
		world.setCamera(camera);
		screen.setCamera(camera);

		world.setPlayer(player);
		screen.setPlayer(player);

		int level = 1, checkPointMark = -1;

		while (player->getLives() && !winStatus) {
			if (checkPointMark == -1) {
				setWorld(level, *player, world, playerState);
				playerState = true;
				screen.drawStartScreen();
			}
			else {
				drawChangeStageScreen(screen);
				setSubWorld(level, checkPointMark, *player, world);
			}
			adjustCamera(level, checkPointMark);
			resetScreen(screen, level, checkPointMark);

			soundMixer.playBackgroundMusic();

			while (playerState && timeState && !winStatus) {
				screen.updateScreen(world);

				while (SDL_PollEvent(&event) && playerState) {
					controller.handleKeysState(state);
					controller.forceActions(*player, world);

					if (player->isDead()) {
						playerState = false;
					}
					controller.clearKeysState();
				}

				if (playerState) {
					controller.forceActions(*player, world);
				}

				checkPointMark = world.getLastReachedCheckPointMark();
				if (checkPointMark != -1) {
					break;
				}

				if (world.isPlayerFinishingWorld() && !winStatus) {
					SoundController::playFlagDownEffect();
					world.switchOnFlag();
					player->setSlidingParameters();

					while (!world.isFlagDown()) {
						world.performActions();
						screen.updateScreen(world);
					}
					player->setFinishingRunParameters();

					screen.drawWorldFinishedScreen(world);
					
					++level;
					screen.setLevel(level);
					if (level == 4) {
						winStatus = true;
					}
					break;
				}

				if (player->isDead()) {
					playerState = false;
				}
				else if (screen.isTimePassed() && !winStatus) {
					timeState = false;
				}
			}

			if (!playerState) {
				screen.drawDeadMario(world);
			}
			else if (!timeState) {
				screen.drawTimeUpScreen();
				SoundController::playTimePassedMusic();
			}
		}

		SoundController::playGameOverMusic();
		screen.drawGameOverScreen();
	}
}