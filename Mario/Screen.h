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
	bool coinImage;
	int initStatus;
	int time;
	std::chrono::steady_clock::time_point timeBegin;
	std::chrono::steady_clock::time_point lastColoursUpdateTime;
	std::array<SDL_Surface*, 10> digitImages;
	std::array<SDL_Surface*, 15> screenImages;
	SDL_Surface* display;
	SDL_Surface* charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera camera;
	bool isPlayerExceedingCameraReferencePoint() const;
	int computeDifference();
	int computeTime();
	void loadScreenImages();
	void changeCoinImageIfAvailable();
	void fillWorldBackground();
	void fillScreenBackground();
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
	static constexpr int CAMERA_REFERENCE_POINT = 240;
	Screen();
	int getInitStatus() const;
	int getTime() const;
	int getBeginningOfCamera() const;
	int getEndOfCamera() const;
	bool isTimePassed() const;
	SDL_Surface* getDisplay() const;
	void setPlayer(std::shared_ptr<Player> player);
	void setPositionOfTheScreen(int begX, int endX);
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