#pragma once
class Circle
{
public:
	float r = 100;
	COLORREF color = RGB(255, 0, 0);
	int x = 0;
	int y = 0;

	Circle(float radius, int x1 = 0, int y1 = 0) {
		r = radius;
		x = x1;
		y = y1;
	}
	void draw(CDC* pDC, COLORREF color = RGB(255,0,0));
};

