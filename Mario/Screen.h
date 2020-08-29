#ifndef _Screen_H
#define _Screen_H

#include <chrono>
#include "SDL_Utility.h"

class Player;
class World;

#define CAMERA_REFERENCE_POINT 240


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

	static const int INITIAL_TIME = 403;
	Player* player;
	bool coinImage;
	int initStatus;
	int time;
	std::chrono::steady_clock::time_point timeBegin;
	std::chrono::steady_clock::time_point lastColoursUpdateTime;
	static SDL_Surface* digitImages[10];
	static SDL_Surface* screenImages[12];
	SDL_Surface* display;
	SDL_Surface* charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera camera;
	bool isPlayerExceedingCameraReferencePoint();
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
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	Screen();
	int getInitStatus() const;
	int getTime() const;
	int getBeginningOfCamera() const;
	int getEndOfCamera() const;
	bool isTimePassed() const;
	SDL_Surface* getDisplay() const;
	void setPlayer(Player* player);
	void setTimeBegin(std::chrono::steady_clock::time_point timeBegin);
	void setPositionOfTheScreen(int begX, int endX);
	void resetScreen();
	void drawStartScreen();
	void drawGameOverScreen();
	void drawTimeUpScreen();
	void drawDeadMario(World& world);
	void drawWorldFinishedScreen(World& world);
	void updateScreen(World& world);
	~Screen();
};

#endif //_Screen_H