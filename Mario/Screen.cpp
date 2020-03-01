#include "Screen.h"

Screen::Camera::Camera() {
	this->beginningOfCamera = 0;
	this->endOfCamera = SCREEN_WIDTH;
}

Screen::Camera::Camera(int begX, int endX) {
	this->beginningOfCamera = begX;
	this->endOfCamera = endX;
}

int Screen::Camera::getBeginningOfCamera() const {
	return this->beginningOfCamera;
}

int Screen::Camera::getEndOfCamera() const {
	return this->endOfCamera;
}

void Screen::Camera::setBegginingOfCamera(int begX) {
	this->beginningOfCamera = begX;
}

void Screen::Camera::setEndOfCamera(int endX) {
	this->endOfCamera = endX;
}

Screen::Camera::~Camera() {}

SDL_Surface* Screen::digitImages[10] = { nullptr };

SDL_Surface* Screen::screenImages[12] = { nullptr };

void Screen::loadScreenImages() {
	for (int i = 0; i < 10; ++i) {
		std::string filename = "./img/";
		filename += std::to_string(i);
		filename += ".png";
		this->digitImages[i] = loadPNG(filename, this->screen);
	}

	this->screenImages[0] = loadPNG("./img/mario.png", this->screen);
	this->screenImages[1] = loadPNG("./img/world11.png", this->screen);
	this->screenImages[2] = loadPNG("./img/time.png", this->screen);
	this->screenImages[3] = loadPNG("./img/x.png", this->screen);
	this->screenImages[4] = loadPNG("./img/coin1.png", this->screen);
	this->screenImages[5] = loadPNG("./img/coin2.png", this->screen);
	this->screenImages[6] = loadPNG("./img/mario_right1.png", this->screen);
	this->screenImages[7] = loadPNG("./img/world_start.png", this->screen);
	this->screenImages[8] = loadPNG("./img/timeup.png", this->screen);
	this->screenImages[9] = loadPNG("./img/gameover.png", this->screen);
	this->screenImages[10] = loadPNG("./img/mario_dead1.png", this->screen);
	this->screenImages[11] = loadPNG("./img/mario_dead2.png", this->screen);
}

void Screen::changeCoinImageIfAvailable(std::chrono::steady_clock::time_point timePoint) {
	if (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastColoursUpdateTime).count() >= 750) {
		this->lastColoursUpdateTime = timePoint;
		this->coinImage = !this->coinImage;
	}
}

void Screen::fillWorldBackground() {
	// 90 149 252
	SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0x5A, 0x95, 0xFC));
}

void Screen::fillScreenBackground() {
	// 0 0 0
	SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0x00, 0x00, 0x00));
}

void Screen::drawScreenElements() {
	SDL_Surface* marioImg = this->screenImages[0];
	drawSurface(this->screen, marioImg, 114, 30);
	SDL_Surface* worldImg = this->screenImages[1];
	drawSurface(this->screen, worldImg, SCREEN_WIDTH - 227, 30);
	SDL_Surface* timeImg = this->screenImages[2];
	drawSurface(this->screen, timeImg, SCREEN_WIDTH - 100, 19);
}

void Screen::drawStartScreenElements(int lives) {
	SDL_Surface* worldImg = this->screenImages[7];
	drawSurface(this->screen, worldImg, 303, 162);
	SDL_Surface* marioImg = this->screenImages[6];
	drawSurface(this->screen, marioImg, 261, 215);
	SDL_Surface* xImg = this->screenImages[3];
	drawSurface(this->screen, xImg, 310, 217);
	SDL_Surface* livesImg = this->digitImages[lives];
	drawSurface(this->screen, livesImg, 360, 215);
}

void Screen::drawGameOver() {
	SDL_Surface* img = this->screenImages[9];
	drawSurface(this->screen, img, 310, 200);
}

void Screen::drawTimeUp() {
	SDL_Surface* img = this->screenImages[8];
	drawSurface(this->screen, img, 310, 200);
}

void Screen::drawTime(long long int time) {
	std::string timeStr = std::to_string(time);
	for (int i = timeStr.length() - 1, j = 1; i >= 0; --i, ++j) {
		SDL_Surface* img = this->digitImages[timeStr[i] - '0'];
		drawSurface(this->screen, img, SCREEN_WIDTH - (61 + j * 16), 40);
	}
}

void Screen::drawPoints(int points) {
	std::string pointsStr = std::to_string(points);
	for (int i = pointsStr.length() - 1, j = 1; i >= 0; --i, ++j) {
		SDL_Surface* img = this->digitImages[pointsStr[i] - '0'];
		drawSurface(this->screen, img, 168 - j * 16, 40);
	}
	if (pointsStr.length() < 6) {
		SDL_Surface* img = this->digitImages[0];
		for (int m = 6 - pointsStr.length() - 1, n = 1; m >= 0; --m, ++n) {
			drawSurface(this->screen, img, 56 + n * 16, 40);
		}
	}
}

void Screen::drawCoins(int coins) {
	std::string coinsStr = std::to_string(coins);
	SDL_Surface* img1, * img2;
	img1 = this->screenImages[4 + this->coinImage];
	drawSurface(this->screen, img1, 230, 41);
	img1 = this->screenImages[3];
	drawSurface(this->screen, img1, 250, 42);

	if (coinsStr.length() == 2) {
		img1 = this->digitImages[coinsStr[0] - '0'];
		img2 = this->digitImages[coinsStr[1] - '0'];
	}
	else {
		img1 = this->digitImages[0];
		img2 = this->digitImages[coinsStr[0] - '0'];
	}
	drawSurface(this->screen, img1, 270, 40);
	drawSurface(this->screen, img2, 286, 40);
}

void Screen::updateView() {
	SDL_UpdateTexture(this->scrtex, NULL, this->screen->pixels, this->screen->pitch);
	SDL_RenderCopy(this->renderer, this->scrtex, NULL, NULL);
	SDL_RenderPresent(this->renderer);
}

int Screen::initGUI() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return 1;
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	int status = SDL_CreateWindowAndRenderer(Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, 0, &this->window, &this->renderer);

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(this->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(this->window, "MyGame");

	scrtex = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);
	return status;
}

void Screen::closeGUI() {
	SDL_FreeSurface(this->charset);
	SDL_FreeSurface(this->screen);
	SDL_DestroyTexture(this->scrtex);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	IMG_Quit();
	SDL_Quit();
}

Screen::Screen() {
	this->player = nullptr;
	this->coinImage = true;
	this->lastColoursUpdateTime = std::chrono::steady_clock::now();
	this->screen = nullptr;
	this->charset = nullptr;
	this->scrtex = nullptr;
	this->window = nullptr;
	this->renderer = nullptr;
	this->camera = Camera();
	this->camera.setBegginingOfCamera(0);
	this->camera.setEndOfCamera(SCREEN_WIDTH);
	this->initStatus = this->initGUI();
	this->time = 403;
	this->loadScreenImages();
}

int Screen::getInitStatus() const {
	return this->initStatus;
}

int Screen::getTime() const {
	return this->time;
}

int Screen::getBeginningOfCamera() const {
	return this->camera.getBeginningOfCamera();
}

int Screen::getEndOfCamera() const {
	return this->camera.getEndOfCamera();
}

bool Screen::isTimePassed() const {
	return this->time <= 0;
}

SDL_Surface* Screen::getScreen() const {
	return this->screen;
}

void Screen::setPlayer(Player* playerPointer) {
	this->player = playerPointer;
}

void Screen::setTimeBegin(std::chrono::steady_clock::time_point timeBegin) {
	this->timeBegin = timeBegin;
}

void Screen::setPositionOfTheScreen(int begX, int endX) {
	this->camera.setBegginingOfCamera(begX);
	this->camera.setEndOfCamera(endX);
}

void Screen::resetScreen() {
	this->timeBegin = std::chrono::steady_clock::now();
	this->camera.setBegginingOfCamera(0);
	this->coinImage = true;
}

void Screen::drawStartScreen(World& world) {
	this->fillScreenBackground();
	this->drawScreenElements();
	this->drawStartScreenElements(this->player->getLives());
	this->drawPoints(this->player->getPoints());
	this->drawCoins(this->player->getCoins());
	this->updateView();
}

void Screen::drawGameOverScreen(World& world) {
	this->fillScreenBackground();
	this->drawScreenElements();
	this->drawGameOver();
	this->drawPoints(this->player->getPoints());
	this->drawCoins(this->player->getCoins());
	this->updateView();
}

void Screen::drawTimeUpScreen(World& world) {
	this->fillScreenBackground();
	this->drawScreenElements();
	this->drawTimeUp();
	this->drawPoints(this->player->getPoints());
	this->drawCoins(this->player->getCoins());
	this->updateView();
}

void Screen::drawDeadMario(World& world) {
	SoundController::stopMusic();
	SoundController::playMarioDeadEffect();
	
	int index = (this->player->getCurrentState() <= Tall ? 10 : 11);
	SDL_Surface* img = this->screenImages[index];
	int shift = 0;
	for (int i = 0; i < 3000; ++i) {
		if (i % 3 == 0) {
			std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
			this->time = (int)(403 - std::chrono::duration_cast<std::chrono::seconds> (timePoint - this->timeBegin).count());
			this->fillWorldBackground();
			this->drawScreenElements();
			this->drawTime(this->time);
			this->drawPoints(this->player->getPoints());
			this->drawCoins(this->player->getCoins());
			world.draw(this->screen, getBeginningOfCamera(), false);

			drawSurface(this->screen, img, this->player->getCameraX(), this->player->getPositionY() + shift);
			this->updateView();

			shift += (i <= 450 ? -1 : 1);
		}
	}
}

void Screen::drawWorldFinishedScreen(World& world) {
	SoundController::stopMusic();
	SoundController::playWorldFinishedMusic();

	for (int i = this->time; i >= 0; --i) {
		this->player->addPoints(100);
		this->fillWorldBackground();
		this->drawScreenElements();
		this->drawTime(this->time);
		this->drawPoints(this->player->getPoints());
		this->drawCoins(this->player->getCoins());
		world.draw(this->screen, getBeginningOfCamera(), false);
		this->updateView();
		--this->time;
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

void Screen::updateScreen(World& world) {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	this->time = (int)(403 - std::chrono::duration_cast<std::chrono::seconds> (timePoint - this->timeBegin).count());
	this->changeCoinImageIfAvailable(timePoint);
	this->fillWorldBackground();
	this->drawScreenElements();
	this->drawTime(this->time);
	this->drawPoints(this->player->getPoints());

	world.performActions();
	world.draw(this->screen, getBeginningOfCamera());
	this->drawCoins(this->player->getCoins());
	this->updateView();
}

Screen::~Screen() {
	for (int i = 0; i < 10; ++i) {
		SDL_FreeSurface(this->digitImages[i]);
	}

	for (int i = 0; i < 12; ++i) {
		SDL_FreeSurface(this->screenImages[i]);
	}

	this->closeGUI();
}
