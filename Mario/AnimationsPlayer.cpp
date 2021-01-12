#include "AnimationsPlayer.h"

#include <thread>
#include "SoundController.h"
#include "Screen.h"
#include "Player.h"
#include "World.h"
#include "Camera.h"


std::array<SDL_Surface*, 5> AnimationsPlayer::deadMarioImages;
std::array<int, 10> AnimationsPlayer::xPositions = { 290, 390, 275, 350, 290, 350, 250, 365, 320, 320 };
std::array<int, 10> AnimationsPlayer::yPositions = { 270, 230, 190, 270, 215, 215, 230, 190, 200, 170 };

void AnimationsPlayer::addExplosions(World &world, int i, Screen &screen)
{
	if (i % 50 == 0) {
		int index = i / 50;
		index %= 10;

		if (index >= 1 && index <= 10) {
			int beg = screen.camera->getBeginningOfCamera();
			world.addExplosion(Position(beg + xPositions[index - 1], yPositions[index - 1]));
		}
	}
}

void AnimationsPlayer::drawBasicScreenElements(Screen &screen)
{
	screen.drawScreenElements();
	screen.drawTime(screen.time);
	screen.drawPoints(screen.player->getPoints());
	screen.drawCoins(screen.player->getCoins());
}

void AnimationsPlayer::drawFireworks(World &world, Screen &screen)
{
	screen.time = 0;

	for (int i = 0; i < FIREWORKS_FRAMES_NUMBER; ++i) {
		screen.fillBackground();

		world.performActions();
		world.draw(screen.display);
		drawBasicScreenElements(screen);
		screen.updateView();

		if (i <= FIREWORKS_FRAMES_NUMBER - 500) {
			if (i % (FIREWORKS_FRAMES_NUMBER / 10) == 0) {
				SoundController::playFireworksEffect();
			}

			addExplosions(world, i, screen);
		}
	}
}

void AnimationsPlayer::playAddingPointsAnimation(World &world, bool checker, Screen &screen)
{
	for (int i = screen.time; i >= 0; --i) {
		screen.fillBackground();
		world.draw(screen.display, !checker);
		screen.player->addPoints(checker ? 100 : 50);
		drawBasicScreenElements(screen);
		--screen.time;
		screen.updateView();

		if (checker && (i % 6 == 0)) {
			SoundController::playGettingPointsEffect();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void AnimationsPlayer::loadAnimationsPlayerImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < deadMarioImages.size(); ++i) {
		std::string filename = "./img/mario_imgs/mario_dead";
		filename += std::to_string(i + 1);
		filename += ".png";
		deadMarioImages[i] = loadPNG(filename, display);
	}
}

void AnimationsPlayer::playMarioDyingAnimation(World &world, Screen &screen)
{
	SoundController::stopMusic();
	SoundController::playMarioDeadEffect();

	SDL_Surface* img = deadMarioImages[screen.player->getDeadMarioImageIndex()];

	int shift = 0;
	for (int i = 0; i < MARIO_DYING_ANIMATION_FRAMES_NUMBER; ++i) {
		if (i % 3 == 0) {
			screen.fillBackground();
			world.draw(screen.display, false);
			drawBasicScreenElements(screen);
			drawSurface(screen.display, img, screen.player->getX() - screen.camera->getBeginningOfCamera(), 
				screen.player->getY() + shift);
			screen.updateView();

			shift += (i <= 450 ? -1 : 1);
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1250));
}

void AnimationsPlayer::playMarioPipeTravellingAnimation(World &world, Direction direction, Screen &screen)
{
	screen.player->resetModel();
	SDL_Surface* img = screen.player->getImage();
	int x = screen.player->getX() - screen.camera->getBeginningOfCamera();
	int y = screen.player->getY() + (direction == Direction::Down ? 0 : 70);

	for (int i = 0; i < MARIO_PIPE_TRAVELLING_ANIMATION_FRAMES_NUMBER; ++i) {
		screen.fillBackground();
		drawSurface(screen.display, img, x, y);
		world.performActions();
		world.draw(screen.display, false);
		screen.time = screen.computeTime();
		drawBasicScreenElements(screen);
		screen.updateView();

		if (i % 5 == 0) {
			y += (direction == Direction::Down ? 1 : -1);
		}
	}
}

void AnimationsPlayer::playBridgeSpolilingAnimation(World &world, Screen &screen)
{
	do {
		screen.fillBackground();
		world.spoilBridgeAndBoss();
		world.performActions(false);
		world.draw(screen.display);
		screen.time = screen.computeTime();
		drawBasicScreenElements(screen);
		screen.updateView();
	} while (!world.areAnimatedElementsEmpty() || !world.isBridgeDestroyedAlready());
}

void AnimationsPlayer::playLevelFinishedAnimation(World &world, Screen &screen)
{
	SoundController::playLevelFinishedEffect();

	while (screen.player->isStillRunning()) {
		screen.updateScreen(world);
	}

	playAddingPointsAnimation(world, true, screen);
}

void AnimationsPlayer::playWorldFinishedAnimation(World &world, Screen &screen)
{
	SoundController::playWorldFinishedEffect();

	while (screen.player->isStillRunning()) {
		screen.updateScreen(world);
	}

	screen.drawThankYouScreen(world);
	screen.drawPressEnterScreen();
}

void AnimationsPlayer::playCustomWorldFinishedAnimation(World &world, int level, Screen &screen)
{
	SoundController::playWorldFinishedEffect();

	while (screen.player->isStillRunning()) {
		screen.updateScreen(world);
	}

	playAddingPointsAnimation(world, false, screen);

	SoundController::stopMusic();
	drawFireworks(world, screen);

	screen.drawCustomWorldThankYouScreen(world, level);
	screen.drawPressEnterScreen();
}