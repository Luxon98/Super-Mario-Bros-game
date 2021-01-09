#include "MenuManager.h"

#include "SoundController.h"
#include "Screen.h"


std::array<SDL_Surface*, 9> MenuManager::SubmenuManager::submenuImages;
std::array<SDL_Surface*, 9> MenuManager::SubmenuManager::digitImages;
std::array<SDL_Surface*, 2> MenuManager::menuImages;

void MenuManager::SubmenuManager::loadSubmenuSprites(SDL_Surface* display)
{
	submenuImages[0] = loadPNG("./img/menu_imgs/submenu.png", display);
	submenuImages[1] = loadPNG("./img/menu_imgs/menu_ret1.png", display);
	submenuImages[2] = loadPNG("./img/menu_imgs/menu_ret2.png", display);
	submenuImages[3] = loadPNG("./img/menu_imgs/menu_classic.png", display);
	submenuImages[4] = loadPNG("./img/menu_imgs/menu_custom.png", display);
	submenuImages[5] = loadPNG("./img/menu_imgs/menu_rectangle.png", display);
	submenuImages[6] = loadPNG("./img/menu_imgs/menu_third_option.png", display);
	submenuImages[7] = loadPNG("./img/menu_imgs/menu_winter_world.png", display);
	submenuImages[8] = loadPNG("./img/menu_imgs/menu_summer_world.png", display);
}

void MenuManager::SubmenuManager::loadSubmenuDigits(SDL_Surface* display)
{
	for (std::size_t i = 0; i < digitImages.size(); ++i) {
		std::string filename = "./img/digit_imgs/";
		filename += std::to_string(i + 1);
		filename += ".png";
		digitImages[i] = loadPNG(filename, display);
	}
}

int MenuManager::SubmenuManager::getCustomWorldIndex() const
{
	return (customWorld == CustomWorld::WinterWorld ? 7 : 8);
}

void MenuManager::SubmenuManager::changeCustomWorld()
{
	if (customWorld == CustomWorld::WinterWorld) {
		customWorld = CustomWorld::SummerWorld;
	}
	else {
		customWorld = CustomWorld::WinterWorld;
	}
}

void MenuManager::SubmenuManager::handleArrowUpKey()
{
	--submenuOptionNumber;
	if (!customGame && submenuOptionNumber == 3) {
		--submenuOptionNumber;
	}

	if (submenuOptionNumber == 0) {
		submenuOptionNumber = 4;
	}
}

void MenuManager::SubmenuManager::handleArrowDownKey()
{
	++submenuOptionNumber;
	if (!customGame && submenuOptionNumber == 3) {
		++submenuOptionNumber;
	}

	if (submenuOptionNumber == 5) {
		submenuOptionNumber = 1;
	}
}

void MenuManager::SubmenuManager::handleArrowRightKey()
{
	if (submenuOptionNumber == 1) {
		++gameSpeed;
		if (gameSpeed == 10) {
			gameSpeed = 1;
		}
	}
	else if (submenuOptionNumber == 2) {
		customGame = !customGame;
	}
	else if (submenuOptionNumber == 3) {
		changeCustomWorld();
	}

	SoundController::playSubmenuEffect();
}

void MenuManager::SubmenuManager::handleArrowLeftKey()
{
	if (submenuOptionNumber == 1) {
		--gameSpeed;
		if (gameSpeed == 0) {
			gameSpeed = 9;
		}
	}
	else if (submenuOptionNumber == 2) {
		customGame = !customGame;
	}
	else if (submenuOptionNumber == 3) {
		changeCustomWorld();
	}

	SoundController::playSubmenuEffect();
}

MenuManager::SubmenuManager::SubmenuManager()
{
	submenuOptionNumber = 1;
	gameSpeed = 7;
	customGame = false;
	returnStatus = false;
	customWorld = CustomWorld::WinterWorld; 
}

void MenuManager::SubmenuManager::loadSubmenuImages(SDL_Surface* display)
{
	loadSubmenuSprites(display);
	loadSubmenuDigits(display);
}

void MenuManager::SubmenuManager::resetOptionAndReturnStatus()
{
	returnStatus = false;
	submenuOptionNumber = 1;
}

void MenuManager::SubmenuManager::drawSubmenu(Screen &screen) const
{
	drawSurface(screen.getDisplay(), submenuImages[0], 320, 240);
	drawSurface(screen.getDisplay(), submenuImages[3 + customGame], 475, 187);
	drawSurface(screen.getDisplay(), digitImages[gameSpeed - 1], 470, 133);
	if (customGame) {
		drawSurface(screen.getDisplay(), submenuImages[6], 250, 240);
		drawSurface(screen.getDisplay(), submenuImages[getCustomWorldIndex()], 474, 240);
	}

	if (submenuOptionNumber != 4) {
		drawSurface(screen.getDisplay(), submenuImages[1], 315, 345);
		drawSurface(screen.getDisplay(), submenuImages[5], 335, 81 + submenuOptionNumber * 53);
	}
	else {
		drawSurface(screen.getDisplay(), submenuImages[2], 315, 345);
	}

	screen.updateView();
}

void MenuManager::SubmenuManager::handleSubmenuKeys(const Uint8* state)
{
	if (state[SDL_SCANCODE_RETURN] && submenuOptionNumber == 4) {
		SoundController::playReturnedToMenuEffect();
		returnStatus = true;
		return;
	}

	if (state[SDL_SCANCODE_UP]) {
		handleArrowUpKey();
	}
	else if (state[SDL_SCANCODE_DOWN]) {
		handleArrowDownKey();
	}
	else if (state[SDL_SCANCODE_RIGHT]) {
		handleArrowRightKey();
	}
	else if (state[SDL_SCANCODE_LEFT]) {
		handleArrowLeftKey();
	}
}

void MenuManager::drawMainMenu(Screen &screen) const
{
	drawSurface(screen.getDisplay(), menuImages[0], 320, 240);
	drawSurface(screen.getDisplay(), menuImages[1], 410 - (optionNumber * 20), 254 + (optionNumber * 30));
	screen.updateView();
}

void MenuManager::handleEnterKey()
{
	if (optionNumber == 1) {
		startGameStatus = true;
	}
	else if (optionNumber == 2) {
		submenu = true;
	}
	else if (optionNumber == 3) {
		exitStatus = true;
	}
}

void MenuManager::handleArrowUpKey()
{
	--optionNumber;
	if (optionNumber == 0) {
		optionNumber = 3;
	}
}

void MenuManager::handleArrowDownKey()
{
	++optionNumber;
	if (optionNumber == 4) {
		optionNumber = 1;
	}
}

void MenuManager::handleMenuKeys(const Uint8* state)
{
	if (state[SDL_SCANCODE_RETURN]) {
		handleEnterKey();
		return;
	}

	if (state[SDL_SCANCODE_UP]) {
		handleArrowUpKey();
	}
	else if (state[SDL_SCANCODE_DOWN]) {
		handleArrowDownKey();
	}
}

MenuManager::MenuManager()
{
	startGameStatus = false;
	exitStatus = false;
	optionNumber = 1;
	submenu = false;
	submenuManager = SubmenuManager();
}

void MenuManager::loadMenuImages(SDL_Surface* display)
{
	menuImages[0] = loadPNG("./img/menu_imgs/menu.png", display);
	menuImages[1] = loadPNG("./img/menu_imgs/menu_mushroom.png", display);

	SubmenuManager::loadSubmenuImages(display);
}

bool MenuManager::isStillOpen() const
{
	if (!startGameStatus && !exitStatus) {
		return true;
	}

	return false;
}

bool MenuManager::getExitStatus() const
{
	return exitStatus;
}

int MenuManager::getGameSpeed() const
{
	return submenuManager.gameSpeed;
}

int MenuManager::getLevel() const
{
	if (submenuManager.customGame) {
		return (submenuManager.customWorld == CustomWorld::WinterWorld ? 77 : 88);
	}

	return 1;
}

void MenuManager::drawMenu(Screen &screen)
{
	if (submenuManager.returnStatus) {
		submenu = false;
		submenuManager.resetOptionAndReturnStatus();
	}

	if (!submenu) {
		drawMainMenu(screen);
	}
	else {
		submenuManager.drawSubmenu(screen);
	}
}

void MenuManager::handleKeys(const Uint8* state)
{
	if (!submenu) {
		handleMenuKeys(state);
	}
	else {
		submenuManager.handleSubmenuKeys(state);
	}
}