#ifndef MenuManager_H
#define MenuManager_H

#include <array>
#include "SDL_Utility.h"

class Screen;
struct SDL_Surface;


class MenuManager
{
private:
	static std::array<SDL_Surface*, 2> menuImages;
	int optionNumber;
	bool startGameStatus;
	bool exitStatus;

public:
	MenuManager();
	static void loadMenuImages(SDL_Surface* display);
	bool isStillOpen() const;
	bool getExitStatus() const;
	void drawMenu(Screen &screen) const;
	void handleKeys(const Uint8* state);
};

#endif //MenuManager_H