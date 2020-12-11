#ifndef MenuManager_H
#define MenuManager_H

#include <array>
#include "SDL_Utility.h"

class Screen;
struct SDL_Surface;


enum class CustomWorld
{
	WinterWorld,
	SummerWorld
};


class MenuManager
{
private:
	class SubmenuManager
	{
	private:
		static std::array<SDL_Surface*, 9> submenuImages;
		static std::array<SDL_Surface*, 9> digitImages;
		int submenuOptionNumber;
		static void loadSubmenuSprites(SDL_Surface* display);
		static void loadSubmenuDigits(SDL_Surface* display);
		int getCustomWorldIndex() const;
		void changeCustomWorld();
		void handleArrowUpKey();
		void handleArrowDownKey();
		void handleArrowRightKey();
		void handleArrowLeftKey();

	public:
		int gameSpeed;
		bool customGame;
		bool returnStatus;
		CustomWorld customWorld;
		SubmenuManager();
		static void loadSubmenuImages(SDL_Surface* display);
		void resetOptionAndReturnStatus();
		void drawSubmenu(Screen &screen) const;
		void handleSubmenuKeys(const Uint8* state);
	};

	static std::array<SDL_Surface*, 2> menuImages;
	bool startGameStatus;
	bool exitStatus;
	int optionNumber;
	bool submenu;
	SubmenuManager submenuManager;
	void drawMainMenu(Screen &screen) const;
	void handleEnterKey();
	void handleArrowUpKey();
	void handleArrowDownKey();
	void handleMenuKeys(const Uint8* state);

public:
	MenuManager();
	static void loadMenuImages(SDL_Surface* display);
	bool isStillOpen() const;
	bool getExitStatus() const;
	int getGameSpeed() const;
	int getLevel() const;
	void drawMenu(Screen &screen);
	void handleKeys(const Uint8* state);
};

#endif //MenuManager_H