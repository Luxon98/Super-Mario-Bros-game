#include "MenuManager.h"

#include "Screen.h"


std::array<SDL_Surface*, 2> MenuManager::menuImages;

MenuManager::MenuManager()
{
	optionNumber = 1;
	startGameStatus = false;
	exitStatus = false;
}

void MenuManager::loadMenuImages(SDL_Surface* display)
{
	menuImages[0] = loadPNG("./img/menu.png", display);
	menuImages[1] = loadPNG("./img/menuMushroom.png", display);
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

void MenuManager::drawMenu(Screen &screen) const
{
	drawSurface(screen.getDisplay(), menuImages[0], 320, 240);
	drawSurface(screen.getDisplay(), menuImages[1], 410 - (optionNumber * 20), 247 + (optionNumber * 30));
	screen.updateView();
}

void MenuManager::handleKeys(const Uint8* state)
{
	if (state[SDL_SCANCODE_RETURN]) {
		if (optionNumber == 1) {
			startGameStatus = true;
		}
		else if (optionNumber == 3) {
			exitStatus = true;
		}
		return;
	}

	if (state[SDL_SCANCODE_UP]) {
		--optionNumber;
		if (optionNumber == 0) {
			optionNumber = 3;
		}
	}
	else if (state[SDL_SCANCODE_DOWN]) {
		++optionNumber;
		if (optionNumber == 4) {
			optionNumber = 1;
		}
	}
}
