#ifndef Coin_H
#define Coin_H

#include <array>
#include "BonusObject.h"

class Position;
struct SDL_Surface;


class Coin : public BonusObject
{
private:
	static std::array<SDL_Surface*, 8> coinImages; 
	static bool coinImage;
	int computeBaseIndex() const;
	int computeImageIndex() const;

public:
	Coin(Position position);
	bool isCoin() const override;
	int getPointsForCollecting() const override;
	static void loadCoinImages(SDL_Surface* display);
	static void resetCoinImage();
	static void changeCoinImage();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void giveBonus(Player &player) override;
};

#endif //Coin_H

