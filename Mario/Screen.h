#ifndef _Screen_H
#define _Screen_H

#include <string>
#include <chrono>
#include <thread>
#include "SDL_Interface.h"
#include "Player.h"
#include "World.h"

#define CAMERA_REFERENCE_POINT 240


class Player;
class World;


class Screen {
private:
	class Camera {
	private:
		int beginningOfCamera;
		int endOfCamera;

	public:
		Camera();
		Camera(int begX, int endX);
		int getBeginningOfCamera() const;
		int getEndOfCamera() const;
		void setBegginingOfCamera(int begX);
		void setEndOfCamera(int endX);
		~Camera();
	};

	Player* player;
	bool coinImage;
	int initStatus;
	int time;
	std::chrono::steady_clock::time_point timeBegin;
	std::chrono::steady_clock::time_point lastColoursUpdateTime;
	static SDL_Surface* digitImages[10];
	static SDL_Surface* screenImages[12];
	SDL_Surface* screen;
	SDL_Surface* charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera camera;
	void loadScreenImages();
	void changeCoinImageIfAvailable(std::chrono::steady_clock::time_point timePoint);
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
	SDL_Surface* getScreen() const;
	void setPlayer(Player* playerPointer);
	void setTimeBegin(std::chrono::steady_clock::time_point timeBegin);
	void setPositionOfTheScreen(int begX, int endX);
	void resetScreen();
	void drawStartScreen(World& world);
	void drawGameOverScreen(World& world);
	void drawTimeUpScreen(World& world);
	void drawDeadMario(World& world);
	void drawWorldFinishedScreen(World& world);
	void updateScreen(World& world);
	~Screen();
};

#endif