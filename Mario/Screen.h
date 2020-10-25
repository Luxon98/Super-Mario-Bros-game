#ifndef Screen_H
#define Screen_H

#include <chrono>
#include <array>
#include <memory>
#include "SDL_Utility.h"

class Player;
class World;
class Camera;


class Screen
{
private:
	static bool coinImage;
	int initStatus;
	int time;
	int level;
	std::chrono::steady_clock::time_point timeBegin;
	std::array<SDL_Surface*, 10> digitImages;
	std::array<SDL_Surface*, 15> screenImages;
	std::array<SDL_Surface*, 8> worldImages;
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;
	SDL_Surface* display;
	SDL_Surface* charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isPlayerExceedingCameraReferencePoint() const;
	int computeCoinBaseIndex() const;
	int computeDifference() const;
	int computeTime() const;
	void setPositionOfTheScreen(int begX, int endX);
	void loadDigitImages();
	void loadOtherImages();
	void loadWorldImages();
	void loadCoinImages();
	void loadDeadMarioImages();
	void loadScreenImages();
	void setBlueBackground();
	void setBlackBackground();
	void fillBackground();
	void drawScreenElements();
	void drawStartScreenElements(int lives);
	void drawGameOver();
	void drawTimeUp();
	void drawTime(long long int time);
	void drawPoints(int points);
	void drawCoins(int coins);
	void updateView();
	int initGUI();
	void closeGUI();

public:
	static constexpr int SCREEN_WIDTH = 640;
	static constexpr int SCREEN_HEIGHT = 480;
	Screen();
	int getInitStatus() const;
	int getTime() const;
	bool isTimePassed() const;
	SDL_Surface* getDisplay() const;
	void setPlayer(std::shared_ptr<Player> player);
	void setCamera(std::shared_ptr<Camera> camera);
	void setLevel(int level);
	static void resetCoinImage();
	static void changeCoinImage();
	void resetScreen(bool resetTimeFlag = true);
	void drawStartScreen();
	void drawChangeSubLevelScreen();
	void drawGameOverScreen();
	void drawTimeUpScreen();
	void drawDeadMario(World &world);
	void drawWorldFinishedScreen(World &world);
	void updateScreen(World &world);
	~Screen();
};

#endif //Screen_H