#ifndef WorldInteractionFunctions_H
#define WorldInteractionFunctions_H

class Player;
class World;
class Mushroom;
class Position;
enum class TextType;


TextType getTextTypeFromPoints(int points);

void addTextAndPoints(Player &player, World &world, int points);

void addTextAndPoints(Player &player, World &world, int points, Position position);

void collectMushroom(Player &player, World &world, Mushroom &mushroom, int index);

void collectFlower(Player &player, World &world, int index);

void collectStar(Player &player, World &world, int index);

void collectCoin(Player &player, World &world, int index);


#endif //WorldInteractionFunctions_H
