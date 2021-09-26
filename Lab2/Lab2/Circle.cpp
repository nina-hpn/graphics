#include "pch.h"
#include "Circle.h"

void draw8Points(CDC* pDC, int x, int y, COLORREF color, int sx, int sy) {
	pDC->SetPixel(CPoint(x + sx, y + sy), color);

	pDC->SetPixel(CPoint(-x + sx, y + sy), color);
	pDC->SetPixel(CPoint(x + sx, -y + sy), color);
	pDC->SetPixel(CPoint(-x + sx, -y + sy), color);

	pDC->SetPixel(CPoint(y + sx, x + sy), color);

	pDC->SetPixel(CPoint(-y + sx, x + sy), color);
	pDC->SetPixel(CPoint(y + sx, -x + sy), color);
	pDC->SetPixel(CPoint(-y + sx, -x + sy), color);

}

void Circle::draw(CDC *pDC, COLORREF color) {
	int x1 = 0;
	int y1 = this->r;
	int f1 = 1 - this->r;
	int fx = 0;
	int fy = 0;

	pDC->SetPixel(CPoint(x1 + this->x, y1 + this->y), color);

	while (x1 < (this->r / sqrt(2))) {
		if (f1 < 0) {
			f1 += 2 * x1 + 3;
			x1 += 1;
			draw8Points(pDC, x1, y1, color, this->x, this->y);
		}
		else {
			f1 += 2 * x1 - 2 * y1 + 5;
			x1 += 1;
			y1 -= 1;
			draw8Points(pDC, x1, y1, color, this->x, this->y);
		}
	}
}