#include "Screen.h"

#include <string>
#include <thread>
#include "Player.h"
#include "World.h"
#include "SoundController.h"
#include "LayoutStyle.h"
#include "Camera.h"


bool Screen::coinImage = true;

bool Screen::isPlayerExceedingCameraReferencePoint() const
{
	if (player->getX() - camera->getBeginningOfCamera() > Screen::SCREEN_WIDTH - Camera::CAMERA_REFERENCE_POINT) {
		return true;
	}

	return false;
}

int Screen::computeCoinBaseIndex() const
{
	return (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 2);
}

int Screen::computeDifference() const
{
	return (player->getX() - camera->getBeginningOfCamera() - (SCREEN_WIDTH - Camera::CAMERA_REFERENCE_POINT));
}

int Screen::computeTime() const
{
	auto timePoint = std::chrono::steady_clock::now();

	int initialTime = (level < 3 ? 403 : 303);
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
		std::string filename = "./img/";
		filename += std::to_string(i);
		filename += ".png";
		digitImages[i] = loadPNG(filename, display);
	}
}

void Screen::loadOtherImages()
{
	screenImages[0] = loadPNG("./img/mario.png", display);
	screenImages[1] = loadPNG("./img/time.png", display);
	screenImages[2] = loadPNG("./img/x.png", display);

	screenImages[7] = loadPNG("./img/mario_right1.png", display);
	screenImages[8] = loadPNG("./img/timeup.png", display);
	screenImages[9] = loadPNG("./img/gameover.png", display);
}

void Screen::loadWorldImages()
{
	for (std::size_t i = 0; i < worldImages.size() / 2; ++i) {
		std::string filename = "./img/world1";
		filename += std::to_string(i + 1);
		filename += ".png";
		worldImages[i] = loadPNG(filename, display);
	}

	for (std::size_t j = worldImages.size() / 2; j < worldImages.size(); ++j) {
		std::string filename = "./img/world_start1";
		filename += std::to_string(j - 3);
		filename += ".png";
		worldImages[j] = loadPNG(filename, display);
	}
}

void Screen::loadCoinImages()
{
	for (int j = 3; j < 7; ++j) {
		std::string filename = "./img/s_coin";
		filename += std::to_string(j - 2);
		filename += ".png";
		screenImages[j] = loadPNG(filename, display);
	}
}

void Screen::loadDeadMarioImages()
{
	for (std::size_t k = 10; k < screenImages.size(); ++k) {
		std::string filename = "./img/mario_dead";
		filename += std::to_string(k - 9);
		filename += ".png";
		screenImages[k] = loadPNG(filename, display);
	}
}

void Screen::loadScreenImages()
{
	loadDigitImages();
	loadOtherImages();
	loadCoinImages();
	loadDeadMarioImages();
	loadWorldImages();
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
	if (World::LAYOUT_STYLE == LayoutStyle::OpenWorld) {
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
	SDL_Surface* worldImg = worldImages[level - 1];
	drawSurface(display, worldImg, SCREEN_WIDTH - 227, 30);
	SDL_Surface* timeImg = screenImages[1];
	drawSurface(display, timeImg, SCREEN_WIDTH - 100, 19);
}

void Screen::drawStartScreenElements(int lives)
{
	SDL_Surface* worldImg = worldImages[3 + level];
	drawSurface(display, worldImg, 303, 162);

	SDL_Surface* marioImg = screenImages[7];
	drawSurface(display, marioImg, 261, 215);

	SDL_Surface* xImg = screenImages[2];
	drawSurface(display, xImg, 310, 217);

	SDL_Surface* livesImg = digitImages[lives];
	drawSurface(display, livesImg, 360, 215);
}

void Screen::drawGameOver()
{
	SDL_Surface* img = screenImages[9];
	drawSurface(display, img, 310, 200);
}

void Screen::drawTimeUp()
{
	SDL_Surface* img = screenImages[8];
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

void Screen::updateView()
{
	SDL_UpdateTexture(scrtex, nullptr, display->pixels, display->pitch);
	SDL_RenderCopy(renderer, scrtex, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void Screen::drawAddingPointsAnimation(World& world)
{
	for (int i = time; i >= 0; --i) {
		fillBackground();
		world.performActions();
		world.draw(display, false);
		player->addPoints(100);
		drawScreenElements();
		drawTime(time);
		drawPoints(player->getPoints());
		drawCoins(player->getCoins());
		--time;
		updateView();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
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
	time = 403;
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

void Screen::resetScreen(bool resetTimeFlag)
{
	if (resetTimeFlag) {
		timeBegin = std::chrono::steady_clock::now();
	}
	camera->setBeginningOfCamera(0);
	camera->setEndOfCamera(SCREEN_WIDTH);
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

	int index = player->getDeadMarioImageIndex() + 10;
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

void Screen::drawWorldFinishedScreen(World &world)
{
	SoundController::playWorldFinishedMusic();

	while (player->getStepsRight() != 0) {
		updateScreen(world);
	}

	drawAddingPointsAnimation(world);
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
