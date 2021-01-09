#ifndef Size_H
#define Size_H


class Size 
{
private:
	int width;
	int height;

public:
	Size() = default;
	Size(int width, int height);
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);
	void setSize(int width, int height);
};

#endif //Size_H