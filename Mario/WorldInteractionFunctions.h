#ifndef WorldInteractionFunctions_H
#define WorldInteractionFunctions_H

class Player;
class World;
class Position;
enum class TextType;


TextType getTextTypeFromPoints(int points);

void addTextAndPoints(Player &player, World &world, int points);

void addTextAndPoints(Player &player, World &world, int points, Position position);

void collectCoinByCollision(Player &player, World &world, int index);

void getPointsFromFlag(Player &player, World &world);

#endif //WorldInteractionFunctions_H