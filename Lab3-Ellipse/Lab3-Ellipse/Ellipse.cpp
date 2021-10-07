#include "pch.h"
#include "Ellipse.h"

void draw4Points(CDC* pDC, int x, int y, COLORREF color, int sx, int sy) {

    pDC->SetPixel(CPoint(sx + x, sy + y), color);
    pDC->SetPixel(CPoint(sx + x, sy + -y), color);
    pDC->SetPixel(CPoint(sx + -x, sy + y), color);
    pDC->SetPixel(CPoint(sx + -x, sy + -y), color);

}

void Ellipse1::draw(CDC* pDC, COLORREF color) {
    int a = this->a;
    int b = this->b;
    int xc = this->x;
    int yc = this->y;

    int x = 0;
    int y = b;

    int f = ((pow(b, 2)) - (pow(a, 2) * b) + (0.25 * pow(a, 2)));
    int M = 2 * pow(b, 2) * x;
    int N = 2 * pow(a, 2) * y;

    while (M < N) {
        draw4Points(pDC, x, y, color, xc, yc);

        if (f < 0) {
            M = M + (2 * pow(b, 2));
            f = f + M + (pow(b, 2));

            x += 1;
        }
        else {
            M = M + (2 * pow(b, 2));
            N = N - (2 * pow(a, 2));
            f = f + M - N + (pow(b, 2));

            x += 1;
            y -= 1;
        }
    }

    f = (pow(b, 2) * pow((x + 0.5), 2) + (pow(a, 2) * pow((y - 1), 2)) - (pow(a, 2) * pow(b, 2)));

    while (y >= 0) {
        draw4Points(pDC, x, y, color, xc, yc);

        if (f > 0) {
            N = N - (2 * pow(a, 2));
            f = f + (pow(a, 2)) - N;

            y -= 1;
        }
        else {
            M = M + (2 * pow(b, 2));
            N = N - (2 * pow(a, 2));
            f = f + M - N + (pow(a, 2));

            y -= 1;
            x += 1;
        }
    }
}

void Ellipse1::boundaryFill1(CDC* pDC, int x, int y, COLORREF fill_color, COLORREF boundary_color) {
    COLORREF color;
    color = pDC->GetPixel(x, y);
    if ((color != fill_color) && (color != boundary_color))
    {
        pDC->SetPixel(x, y, fill_color);
        boundaryFill1(pDC, x - 1, y, fill_color, boundary_color);
        boundaryFill1(pDC, x, y + 1, fill_color, boundary_color);
        boundaryFill1(pDC, x + 1, y, fill_color, boundary_color);
        boundaryFill1(pDC, x, y - 1, fill_color, boundary_color);
    }
    else
        return;
}

void Ellipse1::boundaryFill(CDC* pDC, COLORREF fill_color, COLORREF boundary_color) {
    int x = this->x;
    int y = this->y;

    this->boundaryFill1(pDC, x, y, fill_color, boundary_color);
}

void color4Points(CDC* pDC, int x, int y, COLORREF color, int sx, int sy) {
    pDC->SetPixel(CPoint(x, y), color);

    int xi = x - sx;
    int yi = y - sy;

    pDC->SetPixel(CPoint(x, sy - yi), color);
    pDC->SetPixel(CPoint(sx - xi, y), color);
    pDC->SetPixel(CPoint(sx - xi, sy - yi), color);
}


void Ellipse1::scanLineFill(CDC* pDC, COLORREF fill_color, COLORREF boundary_color) {

    // We know that ellipse is symmetric
    for (int x = this->x; x < this->x + this->a; x++) {
        for (int y = this->y; y < this->y + this->b; y++) {
            COLORREF color;
            color = pDC->GetPixel(CPoint(x, y));
            if (color == boundary_color) {
                break;
            }
            else {
                color4Points(pDC, x, y, fill_color, this->x, this->y);
            }
        }
    }
}