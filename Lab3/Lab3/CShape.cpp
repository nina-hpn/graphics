#include "CLine.h"
#include "CShape.h"
#include "math.h"


void CShape::Pentagon(CDC* pDC, int xc, int yc, int r, COLORREF color)
{
	int x[5];
	int y[5];

	float alpha = -PI / 2;
	float const1 = 2 * PI / 5;
	int i;

	for (i = 0; i < 5; ++i)
	{
		x[i] = r * cos(alpha) + xc;
		y[i] = r * sin(alpha) + yc;
		alpha += const1;
	}

	for (i = 0; i < 4; i++)
		CLine::LineDDA(pDC, x[i], y[i], x[i + 1], y[i + 1], color);
	CLine::LineDDA(pDC, x[4], y[4], x[0], y[0], color);
}
//***********************************************************************************

void CShape::Hexagon(CDC* pDC, int xc, int yc, int r, COLORREF color)
{
	int x[6];
	int y[6];

	float alpha = 0;
	float const1 = PI / 3;

	int i;
	for (i = 0; i < 6; ++i)
	{
		x[i] = r * cos(alpha) + xc;
		y[i] = r * sin(alpha) + yc;
		alpha += const1;
	}

	for (i = 0; i < 5; i++)
		CLine::LineDDA(pDC, x[i], y[i], x[i + 1], y[i + 1], color);
	CLine::LineDDA(pDC, x[5], y[5], x[0], y[0], color);
}
//***********************************************************************************


void CShape::Star(CDC* pDC, CPoint I, int R, COLORREF color, int n)
{
	Star(pDC, I.x, I.y, R, color, n);
}

void CShape::Star(CDC* pDC, int xc, int yc, int R, COLORREF color, int n)
{
	float r = R * sin(PI / (2 * n)) / sin(PI - 3 * PI / (2 * n));
	int* x = new int[2 * n];
	int* y = new int[2 * n];

	float alpha = -PI / 2;
	float const1 = PI / n;
	float const2 = 2 * PI / n;

	int i;
	for (i = 0; i < 2 * n; i += 2)
	{
		x[i] = R * cos(alpha) + xc;
		y[i] = R * sin(alpha) + yc;
		x[i + 1] = r * cos(alpha) + xc; // Dùng hai dòng này để vẽ phi tiêu
		y[i + 1] = r * sin(alpha) + yc;
		//x[i+1] = r * cos(alpha + const1) + xc; //Dùng hai dòng này để vẽ sao như bình thường
		//y[i+1] = r * sin(alpha + const1) + yc;

		alpha += const2;
	}

	for (i = 0; i < 2 * n - 1; ++i)
		CLine::LineBresenham(pDC, x[i], y[i], x[i + 1], y[i + 1], color);
	CLine::LineBresenham(pDC, x[2 * n - 1], y[2 * n - 1], x[0], y[0], color);
}