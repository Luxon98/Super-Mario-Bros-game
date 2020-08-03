#ifndef _Size_H
#define _Size_H


class Size 
{
private:
	int width;
	int height;

public:
	Size(int width, int height);
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);
	void setSize(int width, int height);
};

#endif //_Size_H

