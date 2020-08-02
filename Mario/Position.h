#ifndef _Position_H
#define _Position_H


class Position {
private:
	int x;
	int y;

public:
	Position(int x, int y);
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	void setXY(int x, int y);
};

#endif
