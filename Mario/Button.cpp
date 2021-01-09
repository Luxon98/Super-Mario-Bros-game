#include "Button.h"

#include "SDL_Utility.h"
#include "Player.h"
#include "UtilityFunctions.h"


std::array<SDL_Surface*, 3> Button::buttonImages;

int Button::buttonImage = 1;

Button::Button(Position position)
{
	this->position = position;
	size = Size(13, 21);
}

void Button::loadButtonImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < buttonImages.size(); ++i) {
		std::string filename = "./img/other_imgs/button";
		filename += std::to_string(i + 1);
		filename += ".png";
		buttonImages[i] = loadPNG(filename, display);
	}
}

void Button::resetButtonImage()
{
	Button::buttonImage = 1;
}

void Button::changeButtonImage()
{
	++Button::buttonImage;
	if (Button::buttonImage == 4) {
		Button::buttonImage = 1;
	}
}

bool Button::isPlayerHittingThisButton(const Player &player)
{
	if (areAtTheSameWidth(player, *this) && areAtTheSameHeight(player, *this)) {
		return true;
	}

	return false;
}

void Button::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		drawSurface(display, buttonImages[buttonImage - 1], position.getX() - beginningOfCamera, position.getY());
	}
}