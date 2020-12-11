#include "GameFunctions.h"

#include <iostream>
#include <chrono>
#include "KeyboardController.h"
#include "SoundController.h"
#include "PreloadingImages.h"
#include "Level.h"
#include "World.h"
#include "Screen.h"
#include "Camera.h"
#include "Position.h"
#include "Player.h"
#include "WorldInteractionFunctions.h"
#include "MenuManager.h"
#include "FileNotLoadedException.h"


void setCameraPointer(Player& player, World& world, Screen& screen, std::shared_ptr<Camera> camera)
{
	player.setCamera(camera);
	world.setCamera(camera);
	screen.setCamera(camera);
}

void setPlayerPointer(World& world, Screen& screen, std::shared_ptr<Player> player)
{
	world.setPlayer(player);
	screen.setPlayer(player);
}

bool isLevelClassic(int level)
{
	return (level > 0 && level < 5);
}

bool isLevelTheLast(int level)
{
	return (level == 4);
}

bool isLevelCustom(int level)
{
	return (level == 77 || level == 88);
}

bool isCheckPointLeadingToHiddenStage(int level, int checkPointMark)
{
	if ((level == 1 || level == 2 || level == 77) && checkPointMark == 1) {
		return true;
	}

	return false;
}

bool isPlayerEnteringPipe(int level, int checkPointMark)
{
	if ((level == 1 || level == 2) && checkPointMark == 1) {
		return true;
	}
	else if (level == 77 && (checkPointMark == 1 || checkPointMark == 3)) {
		return true;
	}

	return false;
}

bool isPlayerExitingPipe(int level, int checkPointMark)
{
	if ((level == 1 && checkPointMark == 2) || (level == 2 && (checkPointMark == 2 || checkPointMark == 3))) {
		return true;
	}
	else if (level == 77 && (checkPointMark == 2 || checkPointMark == 3)) {
		return true;
	}

	return false;
}

void resetScreenForClassicLevels(Screen &screen, int level, int checkPointMark)
{
	if (level == 1) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 1) {
			screen.resetScreen(0, 640, false);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(5060, 5700, false);
		}
	}
	else if (level == 2) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 1 || checkPointMark == 3) {
			screen.resetScreen(0, 640, false);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(3560, 4200, false);
		}
	}
	else if (level == 3 || level == 4) {
		screen.resetScreen(0, 640);
	}
}

void resetScreenForCustomLevels(Screen &screen, int level, int checkPointMark)
{
	if (level == 77) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 1 || checkPointMark == 3) {
			screen.resetScreen(0, 640, false);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(6860, 7500, false);
		}
	}
	else if (level == 88) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
	}
}

void resetScreen(Screen &screen, int level, int checkPointMark)
{
	if (isLevelClassic(level)) {
		resetScreenForClassicLevels(screen, level, checkPointMark);
	}
	else if (isLevelCustom(level)) {
		resetScreenForCustomLevels(screen, level, checkPointMark);
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
	else if (level == 4) {
		Level::setFourthLevel(world);
	}
	else if (level == 77) {
		Level::setWinterWorld(world);
	}
	else if (level == 88) {
		Level::setSummerWorld(world);
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

void setSubWorldForClassicLevels(int level, int checkPointMark, World &world)
{
	if (level == 1) {
		if (checkPointMark == 1) {
			Level::setFirstHiddenStage(world);
		}
		else {
			Level::setFirstLevel(world, false);
		}
	}
	else if (level == 2) {
		if (checkPointMark == 1) {
			Level::setSecondHiddenStage(world);
		}
		else if (checkPointMark == 2) {
			Level::setSecondLevel(world, false);
		}
		else if (checkPointMark == 3) {
			Level::setSecondStageOnSecondLevel(world);
		}
	}
}

void setSubWorldForCustomLevels(int level, int checkPointMark, World &world)
{
	if (level == 77) {
		if (checkPointMark == 1) {
			Level::setWinterHiddenStage(world);
		}
		else if (checkPointMark == 2) {
			Level::setWinterWorld(world);
		}
		else if (checkPointMark == 3) {
			Level::setSecondStageOnWinterWorld(world);
		}
	}
}

void setSubWorld(int level, int checkPointMark, Player &player, World &world)
{
	player.resetSteps();
	player.setPositionXY(level, checkPointMark);

	if (isLevelClassic(level)) {
		setSubWorldForClassicLevels(level, checkPointMark, world);
	}
	else if (isLevelCustom(level)) {
		setSubWorldForCustomLevels(level, checkPointMark, world);
	}
}

void adjustCamera(int level, int checkPointMark)
{
	if (isCheckPointLeadingToHiddenStage(level, checkPointMark)) {
		Camera::disableCameraMoving();
	}
	else {
		Camera::enableCameraMoving();
	}
}

void initSound()
{
	bool soundInitStatus = SoundController::initSoundMixer();
	if (soundInitStatus) {
		SoundController::loadSounds();
	}
	else {
		showSoundErrorWindow();
	}
}

void handleMenu(bool * exitStatus, int * gameSpeed, int * level, Screen &screen)
{
	MenuManager menu = MenuManager();

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	SDL_Event menuEvent;

	while (menu.isStillOpen()) {
		menu.drawMenu(screen);

		if (SDL_PollEvent(&menuEvent)) {
			menu.handleKeys(state);
		}
	}

	*gameSpeed = menu.getGameSpeed();
	*level = menu.getLevel();

	if (menu.getExitStatus()) {
		*exitStatus = true;
	}
}

void showLevelFinishingAnimation(Player &player, World &world, Screen &screen, int level)
{
	SoundController::playFlagDownEffect();
	world.switchOnFlag();
	player.setSlidingParameters();
	getPointsFromFlag(player, world);

	while (!world.isFlagDown()) {
		world.performActions();
		screen.updateScreen(world);
	}
	player.setFinishingRunParameters(level);

	screen.drawLevelFinishedScreen(world);
}

void showWorldFinishingAnimation(Player &player, World &world, Screen &screen)
{
	screen.drawBridgeSpolilingScreen(world);
	player.setFinishingRunParameters(4);
	screen.drawWorldFinishedScreen(world);
}

void showCustomWorldFinishingAnimation(Player &player, World &world, Screen &screen)
{
	SoundController::playFlagDownEffect();
	world.switchOnFlag();
	player.setSlidingParameters();
	getPointsFromFlag(player, world);

	while (!world.isFlagDown()) {
		world.performActions();
		screen.updateScreen(world);
	}
	player.setFinishingRunParameters(0);

	screen.drawCustomWorldFinishedScreen(world);
}

void runGame()
{
	bool loadResourcesStatus = true;

	Screen screen = Screen();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(Camera(0, Screen::SCREEN_WIDTH));

	int initStatus = screen.getInitStatus();
	if (initStatus) {
		if (initStatus != 2) {
			showScreenErrorWindow();
		}
		return;
	}

	initSound();

	try {
		preloadImages(screen.getDisplay());
	}
	catch (const FileNotLoadedException & e) {
		loadResourcesStatus = false;
		showFileErrorWindow(e.what());
	}

	bool exitStatus = false;
	int gameSpeed = 7;

	while (true) {
		SoundController::stopMusic();
		int level = 1, checkPointMark = -1;

		if (loadResourcesStatus) {
			handleMenu(&exitStatus, &gameSpeed, &level, screen);
		}

		if (!loadResourcesStatus || exitStatus) {
			break;
		}

		const Uint8* state = SDL_GetKeyboardState(nullptr);

		bool playerState = true, winStatus = false, timeState = true;
		SDL_Event event;

		World world = World();
		world.setGameSpeed(gameSpeed);

		KeyboardController controller = KeyboardController();

		std::shared_ptr<Player> player = std::make_shared<Player>(Player(Position(35, 400)));

		setCameraPointer(*player, world, screen, camera);
		setPlayerPointer(world, screen, player);

		screen.setLevel(level);

		while (player->getLives() && !winStatus) {
			if (checkPointMark == -1) {
				setWorld(level, *player, world, playerState);
				playerState = true;
				screen.drawStartScreen();
			}
			else {
				screen.drawChangeStageOfLevelScreen();
				setSubWorld(level, checkPointMark, *player, world);
			}
			adjustCamera(level, checkPointMark);
			resetScreen(screen, level, checkPointMark);

			if (isPlayerExitingPipe(level, checkPointMark)) {
				screen.drawMarioPipeTravellingScreen(world, Direction::Up);
			}

			SoundController::playBackgroundMusic();

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
					player->resetModel();

					SoundController::playPipeTravelEffect();

					if (isPlayerEnteringPipe(level, checkPointMark)) {
						screen.drawMarioPipeTravellingScreen(world, Direction::Down);
					}
					break;
				}

				if (world.isPlayerFinishingWorld() && !winStatus) {
					if (isLevelClassic(level)) {
						if (isLevelTheLast(level)) {
							showWorldFinishingAnimation(*player, world, screen);
							winStatus = true;
						}
						else {
							showLevelFinishingAnimation(*player, world, screen, level);
							++level;
							screen.setLevel(level);
						}
						break;
					}
					else if (isLevelCustom(level)) {
						showCustomWorldFinishingAnimation(*player, world, screen);
						winStatus = true;
						break;
					}
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

		if (!winStatus) {
			SoundController::playGameOverMusic();
			screen.drawGameOverScreen();
		}
	}

	SoundController::closeSoundController();
}