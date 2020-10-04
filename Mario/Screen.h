#ifndef Screen_H
#define Screen_H

#include <chrono>
#include <array>
#include <memory>
#include "SDL_Utility.h"

class Player;
class World;


class Screen
{
private:
	class Camera 
	{
	public:
		int beginningOfCamera;
		int endOfCamera;
		Camera();
		Camera(int begX, int endX);
	};

	static constexpr int INITIAL_TIME = 403;
	std::shared_ptr<Player> player;
	static bool coinImage;
	int initStatus;
	int time;
	int level;
	std::chrono::steady_clock::time_point timeBegin;
	std::array<SDL_Surface*, 10> digitImages;
	std::array<SDL_Surface*, 15> screenImages;
	std::array<SDL_Surface*, 8> worldImages;
	SDL_Surface* display;
	SDL_Surface* charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera camera;
	bool isPlayerExceedingCameraReferencePoint() const;
	int computeCoinBaseIndex() const;
	int computeDifference() const;
	int computeTime() const;
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
	static constexpr int CAMERA_REFERENCE_POINT = 320;
	Screen();
	int getInitStatus() const;
	int getTime() const;
	int getBeginningOfCamera() const;
	int getEndOfCamera() const;
	bool isTimePassed() const;
	SDL_Surface* getDisplay() const;
	void setPlayer(std::shared_ptr<Player> player);
	void setPositionOfTheScreen(int begX, int endX);
	void setLevel(int level);
	static void resetCoinImage();
	static void changeCoinImage();
	void resetScreen();
	void drawStartScreen();
	void drawGameOverScreen();
	void drawTimeUpScreen();
	void drawDeadMario(World &world);
	void drawWorldFinishedScreen(World &world);
	void updateScreen(World &world);
	~Screen();
};

#endif //Screen_H