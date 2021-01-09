#ifndef Button_H
#define Button_H

#include <array>
#include "InanimateObject.h"

class Player;
struct SDL_Surface;


class Button : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 3> buttonImages;
	static int buttonImage;

public:
	Button(Position position);
	static void loadButtonImages(SDL_Surface* display);
	static void resetButtonImage();
	static void changeButtonImage();
	bool isPlayerHittingThisButton(const Player &player);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Button_H