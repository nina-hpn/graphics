#pragma once
class Ellipse1
{
private:
    void boundaryFill1(CDC* pDC, int x, int y, COLORREF fill_color, COLORREF boundary_color);

public:
    int a;
    int b;
    int x = 0;
    int y = 0;

    Ellipse1(int a1, int b1, int xc, int yc) {
        a = a1;
        b = b1;
        x = xc;
        y = yc;
    }
    Ellipse1(int a1, int b1) {
        a = a1;
        b = b1;
    }

    void draw(CDC* pDC, COLORREF color);
    void boundaryFill(CDC* pDC, COLORREF fill_color, COLORREF boundary_color);
    void scanLineFill(CDC* pDC, COLORREF fill_color, COLORREF boundary_color);


};

