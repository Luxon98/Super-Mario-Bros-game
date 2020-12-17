#include "Screen.h"

#include <string>
#include <thread>
#include "Player.h"
#include "World.h"
#include "SoundController.h"
#include "LayoutStyle.h"
#include "Camera.h"
#include "FileNotLoadedException.h"


bool Screen::coinImage = true;

bool Screen::isPlayerExceedingCameraReferencePoint() const
{
	if (player->getX() - camera->getBeginningOfCamera() > Screen::SCREEN_WIDTH - camera->getReferencePoint()) {
		return true;
	}

	return false;
}

int Screen::computeCoinBaseIndex() const
{
	if (World::LAYOUT_STYLE == LayoutStyle::Underground) {
		return 2;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::Castle) {
		return 4;
	}
	else if (World::LAYOUT_STYLE == LayoutStyle::CustomWinter) {
		return 6;
	}
	else {
		return 0;
	}
}

int Screen::computeDifference() const
{
	return (player->getX() - camera->getBeginningOfCamera() - (SCREEN_WIDTH - camera->getReferencePoint()));
}

int Screen::getInitialTime() const
{
	if (level == 3 || level == 4) {
		return 300;
	}
	else if (level == 77 || level == 88) {
		return 600;
	}
	else {
		return 400;
	}
}

int Screen::computeTime() const
{
	auto timePoint = std::chrono::steady_clock::now();

	int initialTime = getInitialTime();
	int time = static_cast<int>(initialTime - 
		std::chrono::duration_cast<std::chrono::seconds>(timePoint - timeBegin).count());

	return time;
}

void Screen::setPositionOfTheScreen(int begX, int endX)
{
	camera->setBeginningOfCamera(begX);
	camera->setEndOfCamera(endX);
}

void Screen::loadDigitImages()
{
	for (std::size_t i = 0; i < digitImages.size(); ++i) {
		std::string filename = "./img/digit_imgs/";
		filename += std::to_string(i);
		filename += ".png";
		digitImages[i] = loadPNG(filename, display);
	}
}

void Screen::loadOtherImages()
{
	screenImages[0] = loadPNG("./img/scr_imgs/mario.png", display);
	screenImages[1] = loadPNG("./img/scr_imgs/time.png", display);
	screenImages[2] = loadPNG("./img/scr_imgs/x.png", display);

	screenImages[11] = loadPNG("./img/mario_imgs/mario_right1.png", display);
	screenImages[12] = loadPNG("./img/scr_imgs/timeup.png", display);
	screenImages[13] = loadPNG("./img/scr_imgs/gameover.png", display);
	screenImages[14] = loadPNG("./img/scr_imgs/thanks.png", display);
	screenImages[15] = loadPNG("./img/scr_imgs/info_castle.png", display);
	screenImages[16] = loadPNG("./img/scr_imgs/info_custom_worlds.png", display);
	screenImages[17] = loadPNG("./img/scr_imgs/info_winter.png", display);
}

void Screen::loadWorldImages()
{
	for (std::size_t i = 0; i < 4; ++i) {
		std::string filename = "./img/scr_imgs/world1";
		filename += std::to_string(i + 1);
		filename += ".png";
		worldImages[i] = loadPNG(filename, display);
	}
	worldImages[4] = loadPNG("./img/scr_imgs/world_custom.png", display);

	for (std::size_t j = 5; j < 9; ++j) {
		std::string filename = "./img/scr_imgs/world_start1";
		filename += std::to_string(j - 4);
		filename += ".png";
		worldImages[j] = loadPNG(filename, display);
	}
	worldImages[9] = loadPNG("./img/scr_imgs/world_start_custom.png", display);
}

void Screen::loadCoinImages()
{
	for (int j = 3; j < 11; ++j) {
		std::string filename = "./img/scr_imgs/s_coin";
		filename += std::to_string(j - 2);
		filename += ".png";
		screenImages[j] = loadPNG(filename, display);
	}
}

void Screen::loadDeadMarioImages()
{
	for (std::size_t k = 18; k < screenImages.size(); ++k) {
		std::string filename = "./img/mario_imgs/mario_dead";
		filename += std::to_string(k - 17);
		filename += ".png";
		screenImages[k] = loadPNG(filename, display);
	}
}

void Screen::loadScreenImages()
{
	try {
		loadDigitImages();
		loadOtherImages();
		loadCoinImages();
		loadDeadMarioImages();
		loadWorldImages();
	}
	catch (const FileNotLoadedException & e) {
		initStatus = 2;
		showFileErrorWindow(e.what());
	}
}

void Screen::setBlueBackground()
{
	// color: 90 149 252 (BLUE)
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0x5A, 0x95, 0xFC));
}

void Screen::setBlackBackground()
{
	// color: 0 0 0 (BLACK)
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0x00, 0x00, 0x00));
}

void Screen::fillBackground()
{
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld || World::LAYOUT_STYLE == LayoutStyle::CustomSummer) {
		setBlueBackground();
	}
	else {
		setBlackBackground();
	}
}

void Screen::drawScreenElements()
{
	SDL_Surface* marioImg = screenImages[0];
	drawSurface(display, marioImg, 114, 30);

	SDL_Surface* worldImg = (level == 77 || level == 88 ? worldImages[4] : worldImages[level - 1]);
	drawSurface(display, worldImg, SCREEN_WIDTH - 227, 30);

	SDL_Surface* timeImg = screenImages[1];
	drawSurface(display, timeImg, SCREEN_WIDTH - 100, 19);
}

void Screen::drawStartScreenElements(int lives)
{
	SDL_Surface* worldImg = (level == 77 || level == 88 ? worldImages[9] : worldImages[4 + level]);
	drawSurface(display, worldImg, 303, 162);

	SDL_Surface* marioImg = screenImages[11];
	drawSurface(display, marioImg, 261, 215);

	SDL_Surface* xImg = screenImages[2];
	drawSurface(display, xImg, 310, 217);

	SDL_Surface* livesImg = digitImages[lives];
	drawSurface(display, livesImg, 360, 215);
}

void Screen::drawGameOver()
{
	SDL_Surface* img = screenImages[13];
	drawSurface(display, img, 310, 200);
}

void Screen::drawTimeUp()
{
	SDL_Surface* img = screenImages[12];
	drawSurface(display, img, 310, 200);
}

void Screen::drawTime(long long int time)
{
	std::string timeStr = std::to_string(time);
	for (int i = timeStr.length() - 1, j = 1; i >= 0; --i, ++j) {
		SDL_Surface* img = digitImages[timeStr[i] - '0'];
		drawSurface(display, img, SCREEN_WIDTH - (61 + j * 16), 40);
	}
}

void Screen::drawPoints(int points)
{
	std::string pointsStr = std::to_string(points);
	for (int i = pointsStr.length() - 1, j = 1; i >= 0; --i, ++j) {
		SDL_Surface* img = digitImages[pointsStr[i] - '0'];
		drawSurface(display, img, 168 - j * 16, 40);
	}

	if (pointsStr.length() < 6) {
		SDL_Surface* img = digitImages[0];
		for (int m = 6 - pointsStr.length() - 1, n = 1; m >= 0; --m, ++n) {
			drawSurface(display, img, 56 + n * 16, 40);
		}
	}
}

void Screen::drawCoins(int coins)
{
	SDL_Surface* img1, * img2;
	int coinBaseIndex = computeCoinBaseIndex();
	img1 = screenImages[3 + coinImage + coinBaseIndex];
	drawSurface(display, img1, 230, 41);

	img1 = screenImages[2];
	drawSurface(display, img1, 250, 42);

	std::string coinsStr = std::to_string(coins);
	if (coinsStr.length() == 2) {
		img1 = digitImages[coinsStr[0] - '0'];
		img2 = digitImages[coinsStr[1] - '0'];
	}
	else {
		img1 = digitImages[0];
		img2 = digitImages[coinsStr[0] - '0'];
	}
	drawSurface(display, img1, 270, 40);
	drawSurface(display, img2, 286, 40);
}

void Screen::drawAddingPointsAnimation(World &world, bool checker)
{
	for (int i = time; i >= 0; --i) {
		fillBackground();
		world.draw(display, !checker);
		player->addPoints(checker ? 100 : 50);
		drawScreenElements();
		drawTime(time);
		drawPoints(player->getPoints());
		drawCoins(player->getCoins());
		--time;
		updateView();

		if (checker && (i % 6 == 0)) {
			SoundController::playGettingPointsEffect();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void Screen::addExplosions(World &world, int i)
{
	std::array<int, 10> xPositions = { 290, 390, 275, 350, 290, 350, 250, 365, 320, 320 };
	std::array<int, 10> yPositions = { 270, 230, 190, 270, 215, 215, 230, 190, 200, 170 };

	if (i % 50 == 0) {
		int index = i / 50;
		index %= 10;
		world.addExplosion(Position(camera->getBeginningOfCamera() + xPositions[index - 1], yPositions[index - 1]));
	}
}

void Screen::drawFireworks(World &world)
{
	for (int i = 0; i < 2500; ++i) {
		fillBackground();

		world.performActions();
		world.draw(display);

		drawScreenElements();
		drawTime(0);
		drawPoints(player->getPoints());
		drawCoins(player->getCoins());
		updateView();

		if (i <= 2000) {
			if (i % 250 == 0) {
				SoundController::playFireworksEffect();
			}

			addExplosions(world, i);
		}
	}
}

void Screen::drawWinterWorldThankYouScreen(World& world)
{
	for (int i = 0; i < 2000; ++i) {
		fillBackground();
		world.draw(display);
		drawScreenElements();
		drawTime(0);
		drawPoints(player->getPoints());
		drawCoins(player->getCoins());

		if (i > 300) {
			drawSurface(display, screenImages[14], 330, 160);
		}
		if (i > 600) {
			drawSurface(display, screenImages[17], 330, 275);
		}

		updateView();
	}
}

void Screen::drawThankYouInscriptions(int i)
{
	if (i > 200 && i <= 1300) {
		drawSurface(display, screenImages[14], 330, 160);
	}
	if (i > 500 && i <= 1300) {
		drawSurface(display, screenImages[15], 330, 250);
	}

	if (i > 1300) {
		drawSurface(display, screenImages[16], 320, 225);
	}
}

void Screen::drawThankYouScreen(World &world)
{
	for (int i = 0; i < 1600; ++i) {
		fillBackground();
		world.draw(display);
		drawScreenElements();
		drawTime(time);
		drawPoints(player->getPoints());
		drawCoins(player->getCoins());
		drawThankYouInscriptions(i);
		updateView();
	}
}

int Screen::initGUI()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return 1;
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	int status = SDL_CreateWindowAndRenderer(Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, 0, &window, &renderer);

	display = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Super Mario Bros");

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);
	return status;
}

void Screen::closeGUI()
{
	SDL_FreeSurface(charset);
	SDL_FreeSurface(display);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

Screen::Screen()
{
	display = nullptr;
	charset = nullptr;
	scrtex = nullptr;
	window = nullptr;
	renderer = nullptr;
	initStatus = initGUI();
	time = 400;
	level = 1;

	loadScreenImages();

	timeBegin = std::chrono::steady_clock::now();
}

int Screen::getInitStatus() const
{
	return initStatus;
}

int Screen::getTime() const
{
	return time;
}

bool Screen::isTimePassed() const
{
	return (time <= 0);
}

SDL_Surface* Screen::getDisplay() const
{
	return display;
}

void Screen::updateView()
{
	SDL_UpdateTexture(scrtex, nullptr, display->pixels, display->pitch);
	SDL_RenderCopy(renderer, scrtex, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void Screen::setPlayer(std::shared_ptr<Player> player)
{
	this->player = std::move(player);
}

void Screen::setCamera(std::shared_ptr<Camera> camera)
{
	this->camera = std::move(camera);
}

void Screen::setLevel(int level)
{
	this->level = level;
}

void Screen::resetCoinImage()
{
	Screen::coinImage = true;
}

void Screen::changeCoinImage()
{
	Screen::coinImage = !Screen::coinImage;
}

void Screen::resetScreen(int begX, int endX, bool resetTimeFlag)
{
	if (resetTimeFlag) {
		timeBegin = std::chrono::steady_clock::now();
	}

	camera->setBeginningOfCamera(begX);
	camera->setEndOfCamera(endX);
}

void Screen::drawStartScreen()
{
	SoundController::stopMusic();

	setBlackBackground();
	drawScreenElements();
	drawStartScreenElements(player->getLives());
	drawPoints(player->getPoints());
	drawCoins(player->getCoins());
	updateView();

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

void Screen::drawChangeStageOfLevelScreen()
{
	SoundController::stopMusic();

	setBlackBackground();
	updateView();

	std::this_thread::sleep_for(std::chrono::milliseconds(725));
}

void Screen::drawGameOverScreen()
{
	setBlackBackground();
	drawScreenElements();
	drawGameOver();
	drawPoints(player->getPoints());
	drawCoins(player->getCoins());
	updateView();

	std::this_thread::sleep_for(std::chrono::milliseconds(6600));
}

void Screen::drawTimeUpScreen()
{
	SoundController::stopMusic();

	setBlackBackground();
	drawScreenElements();
	drawTimeUp();
	drawPoints(player->getPoints());
	drawCoins(player->getCoins());
	updateView();
}

void Screen::drawDeadMario(World &world)
{
	SoundController::stopMusic();
	SoundController::playMarioDeadEffect();

	int index = player->getDeadMarioImageIndex() + 18;
	SDL_Surface* img = screenImages[index];
	int shift = 0;
	for (int i = 0; i < 2400; ++i) {
		if (i % 3 == 0) {
			time = computeTime();
			fillBackground();
			world.draw(display, false);

			drawScreenElements();
			drawTime(time);
			drawPoints(player->getPoints());
			drawCoins(player->getCoins());

			drawSurface(display, img, player->getX() - camera->getBeginningOfCamera(), player->getY() + shift);
			updateView();

			shift += (i <= 450 ? -1 : 1);
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1250));
}

void Screen::drawMarioPipeTravellingScreen(World &world, Direction direction)
{
	player->resetModel();
	SDL_Surface* img = player->getImage();
	int x = player->getX() - camera->getBeginningOfCamera();
	int y = player->getY() + (direction == Direction::Down ? 0 : 70);

	for (int i = 0; i < 70; ++i) {
		fillBackground();

		drawSurface(display, img, x, y);
		world.performActions();
		world.draw(display, false);

		drawScreenElements();
		time = computeTime();
		drawTime(time);
		drawPoints(player->getPoints());
		drawCoins(player->getCoins());
		updateView();

		y += (direction == Direction::Down ? 1 : -1);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Screen::drawBridgeSpolilingScreen(World &world)
{
	do {
		fillBackground();

		world.spoilBridgeAndBoss();
		world.performActions(false);
		world.draw(display);

		drawScreenElements();
		time = computeTime();
		drawTime(time);
		drawPoints(player->getPoints());
		drawCoins(player->getCoins());
		updateView();
	} 
	while (!world.areAnimatedElementsEmpty() || !world.isBridgeDestroyedAlready());
}

void Screen::drawLevelFinishedScreen(World &world)
{
	SoundController::playLevelFinishedEffect();

	while (player->isStillRunning()) {
		updateScreen(world);
	}

	drawAddingPointsAnimation(world, true);
}

void Screen::drawWorldFinishedScreen(World &world)
{
	SoundController::playWorldFinishedEffect();

	while (player->isStillRunning()) {
		updateScreen(world);
	}

	drawThankYouScreen(world);
}

void Screen::drawCustomWorldFinishedScreen(World &world)
{
	SoundController::playWorldFinishedEffect();

	while (player->isStillRunning()) {
		updateScreen(world);
	}

	drawAddingPointsAnimation(world, false);

	SoundController::stopMusic();
	drawFireworks(world);

	drawWinterWorldThankYouScreen(world);
}

void Screen::updateScreen(World &world)
{
	if (isPlayerExceedingCameraReferencePoint()) {
		int difference = computeDifference();

		setPositionOfTheScreen(camera->getBeginningOfCamera() + difference, camera->getEndOfCamera() + difference);
	}
	time = computeTime();
	fillBackground();

	world.performActions();
	world.draw(display);

	drawScreenElements();
	drawTime(time);
	drawPoints(player->getPoints());
	drawCoins(player->getCoins());
	updateView();
}

Screen::~Screen()
{
	for (std::size_t i = 0; i < digitImages.size(); ++i) {
		SDL_FreeSurface(digitImages[i]);
	}

	for (std::size_t j = 0; j < screenImages.size(); ++j) {
		SDL_FreeSurface(screenImages[j]);
	}

	closeGUI();
}
