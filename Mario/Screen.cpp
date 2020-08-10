#include "Screen.h"

Screen::Camera::Camera()
{
	beginningOfCamera = 0;
	endOfCamera = SCREEN_WIDTH;
}

Screen::Camera::Camera(int begX, int endX)
{
	beginningOfCamera = begX;
	endOfCamera = endX;
}

int Screen::Camera::getBeginningOfCamera() const
{
	return beginningOfCamera;
}

int Screen::Camera::getEndOfCamera() const
{
	return endOfCamera;
}

void Screen::Camera::setBegginingOfCamera(int begX)
{
	beginningOfCamera = begX;
}

void Screen::Camera::setEndOfCamera(int endX)
{
	endOfCamera = endX;
}

Screen::Camera::~Camera() {}

SDL_Surface* Screen::digitImages[10] = { nullptr };

SDL_Surface* Screen::screenImages[12] = { nullptr };

void Screen::loadScreenImages()
{
	for (int i = 0; i < 10; ++i) {
		std::string filename = "./img/";
		filename += std::to_string(i);
		filename += ".png";
		digitImages[i] = loadPNG(filename, display);
	}

	screenImages[0] = loadPNG("./img/mario.png", display);
	screenImages[1] = loadPNG("./img/world11.png", display);
	screenImages[2] = loadPNG("./img/time.png", display);
	screenImages[3] = loadPNG("./img/x.png", display);
	screenImages[4] = loadPNG("./img/coin1.png", display);
	screenImages[5] = loadPNG("./img/coin2.png", display);
	screenImages[6] = loadPNG("./img/mario_right1.png", display);
	screenImages[7] = loadPNG("./img/world_start.png", display);
	screenImages[8] = loadPNG("./img/timeup.png", display);
	screenImages[9] = loadPNG("./img/gameover.png", display);
	screenImages[10] = loadPNG("./img/mario_dead1.png", display);
	screenImages[11] = loadPNG("./img/mario_dead2.png", display);
}

void Screen::changeCoinImageIfAvailable(std::chrono::steady_clock::time_point timePoint)
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastColoursUpdateTime).count() >= 750) {
		lastColoursUpdateTime = timePoint;
		coinImage = !coinImage;
	}
}

void Screen::fillWorldBackground()
{
	// 90 149 252
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0x5A, 0x95, 0xFC));
}

void Screen::fillScreenBackground()
{
	// 0 0 0
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0x00, 0x00, 0x00));
}

void Screen::drawScreenElements()
{
	SDL_Surface* marioImg = screenImages[0];
	drawSurface(display, marioImg, 114, 30);
	SDL_Surface* worldImg = screenImages[1];
	drawSurface(display, worldImg, SCREEN_WIDTH - 227, 30);
	SDL_Surface* timeImg = screenImages[2];
	drawSurface(display, timeImg, SCREEN_WIDTH - 100, 19);
}

void Screen::drawStartScreenElements(int lives)
{
	SDL_Surface* worldImg = screenImages[7];
	drawSurface(display, worldImg, 303, 162);
	SDL_Surface* marioImg = screenImages[6];
	drawSurface(display, marioImg, 261, 215);
	SDL_Surface* xImg = screenImages[3];
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
	std::string coinsStr = std::to_string(coins);
	SDL_Surface* img1, * img2;
	img1 = screenImages[4 + coinImage];
	drawSurface(display, img1, 230, 41);
	img1 = screenImages[3];
	drawSurface(display, img1, 250, 42);

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
	SDL_UpdateTexture(scrtex, NULL, display->pixels, display->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
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

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

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
	player = nullptr;
	coinImage = true;
	lastColoursUpdateTime = std::chrono::steady_clock::now();
	display = nullptr;
	charset = nullptr;
	scrtex = nullptr;
	window = nullptr;
	renderer = nullptr;
	camera = Camera();
	camera.setBegginingOfCamera(0);
	camera.setEndOfCamera(SCREEN_WIDTH);
	initStatus = initGUI();
	time = 403;
	loadScreenImages();
}

int Screen::getInitStatus() const
{
	return initStatus;
}

int Screen::getTime() const
{
	return time;
}

int Screen::getBeginningOfCamera() const
{
	return camera.getBeginningOfCamera();
}

int Screen::getEndOfCamera() const
{
	return camera.getEndOfCamera();
}

bool Screen::isTimePassed() const
{
	return time <= 0;
}

SDL_Surface* Screen::getDisplay() const
{
	return display;
}

void Screen::setPlayer(Player* playerPointer)
{
	player = playerPointer;
}

void Screen::setTimeBegin(std::chrono::steady_clock::time_point timeBegin)
{
	timeBegin = timeBegin;
}

void Screen::setPositionOfTheScreen(int begX, int endX)
{
	camera.setBegginingOfCamera(begX);
	camera.setEndOfCamera(endX);
}

void Screen::resetScreen()
{
	timeBegin = std::chrono::steady_clock::now();
	camera.setBegginingOfCamera(0);
	coinImage = true;
}

void Screen::drawStartScreen()
{
	fillScreenBackground();
	drawScreenElements();
	drawStartScreenElements(player->getLives());
	drawPoints(player->getPoints());
	drawCoins(player->getCoins());
	updateView();
}

void Screen::drawGameOverScreen()
{
	fillScreenBackground();
	drawScreenElements();
	drawGameOver();
	drawPoints(player->getPoints());
	drawCoins(player->getCoins());
	updateView();
}

void Screen::drawTimeUpScreen()
{
	fillScreenBackground();
	drawScreenElements();
	drawTimeUp();
	drawPoints(player->getPoints());
	drawCoins(player->getCoins());
	updateView();
}

void Screen::drawDeadMario(World& world)
{
	SoundController::stopMusic();
	SoundController::playMarioDeadEffect();

	int index = (player->getCurrentState() <= Tall ? 10 : 11);
	SDL_Surface* img = screenImages[index];
	int shift = 0;
	for (int i = 0; i < 3000; ++i) {
		if (i % 3 == 0) {
			std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
			time = (int)(403 - std::chrono::duration_cast<std::chrono::seconds> (timePoint - timeBegin).count());
			fillWorldBackground();
			drawScreenElements();
			drawTime(time);
			drawPoints(player->getPoints());
			drawCoins(player->getCoins());
			world.draw(display, getBeginningOfCamera(), false);

			drawSurface(display, img, player->getCameraX(), player->getY() + shift);
			updateView();

			shift += (i <= 450 ? -1 : 1);
		}
	}
}

void Screen::drawWorldFinishedScreen(World& world)
{
	SoundController::stopMusic();
	SoundController::playWorldFinishedMusic();

	for (int i = time; i >= 0; --i) {
		player->addPoints(100);
		fillWorldBackground();
		drawScreenElements();
		drawTime(time);
		drawPoints(player->getPoints());
		drawCoins(player->getCoins());
		world.draw(display, getBeginningOfCamera(), false);
		updateView();
		--time;
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

void Screen::updateScreen(World& world)
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	time = (int)(403 - std::chrono::duration_cast<std::chrono::seconds> (timePoint - timeBegin).count());
	changeCoinImageIfAvailable(timePoint);
	fillWorldBackground();
	drawScreenElements();
	drawTime(time);
	drawPoints(player->getPoints());

	world.performActions();
	world.draw(display, getBeginningOfCamera());
	drawCoins(player->getCoins());
	updateView();
}

Screen::~Screen()
{
	for (int i = 0; i < 10; ++i) {
		SDL_FreeSurface(digitImages[i]);
	}

	for (int i = 0; i < 12; ++i) {
		SDL_FreeSurface(screenImages[i]);
	}

	closeGUI();
}
