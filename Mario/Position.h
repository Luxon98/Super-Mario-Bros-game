#ifndef Position_H
#define Position_H


class Position 
{
private:
	int x;
	int y;

public:
	Position() = default;
	Position(int x, int y);
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	void setXY(int x, int y);
};

#endif //Position_H