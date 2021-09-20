#include "pch.h"
#include "CLine.h"

#include "math.h" ;
#include "stdio.h"
#include "dos.h"

#define Round(x) (int) (x + 0.5)


void CLine::LineDDA(CDC* pDC, CPoint A, CPoint B, COLORREF color) {
    LineDDA(pDC, A.x, A.y, B.x, B.y, color);
}

void CLine::LineBreseham(CDC* pDC, CPoint A, CPoint B, COLORREF color) {
    LineBreseham(pDC, A.x, A.y, B.x, B.y, color);
}

void CLine::LineDDA(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
    /*
    DDA mindset:
    We see whether it increase or decrease
    Then find out do it goes sharply or steadily

    For the first step:
        We are going to identify the first point and call it x1,y1

    For the second step:
        We identify the next point by looping:
            If it is a fast-paced one: Loop on Y -> More point
            If it is a slow-paced one: Loop on X

        Then depend on which axis you choose, for a given m that is constant
            Increase your choose-axis point increase to 1
            If you choose x, then y = mx + b
            If you choose y, then x = y/m -b/m

        Then all Round the next x or y
    */

    if ((x1 == x2) && (y1 == y2)) {
        //If the two point is coincide
        pDC->SetPixel(x1, y1, color);
        return;
        //Draw one point then go back
    }

    if (abs(x2 - x1) >= abs(y2 - y1)) { //If it has a slower slope
        if (x1 <= x2) { //If it is on the left hand side
            //Case 1
            _LineDDA1(pDC, x1, y1, x2, y2, color);
        }
        else
            _LineDDA1(pDC, x2, y2, x1, y1, color);
    }
    else { //If it is faster
        if (y1 <= y2) //If the first point is lower
            _LineDDA2(pDC, x1, y1, x2, y2, color); //Case 2
        else
            _LineDDA2(pDC, x2, y2, x1, y1, color);
    }
}

void CLine::_LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
    //This is a function for drawing the slower slope line

    pDC->SetPixel(x1, y1, color); //Set the pixel at (x1,y1) a specific color
    float a = (float)(y2 - y1) / (x2 - x1); //a is the slope of the line 
    float y = y1;

    while (x1 < x2) {
        x1++;
        y += a;
        pDC->SetPixel(x1, Round(y), color);
    }
}

void CLine::_LineDDA2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
    pDC->SetPixel(x1, y1, color);
    float a = (float)(x2 - x1) / (y2 - y1);
    float x = x1;

    while (y1 < y2) {
        y1++;
        x += a;
        pDC->SetPixel(Round(x), y1, color);
    }
}

void CLine::LineBreseham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
    /*
    Breseham mindset:
    The thing is we need to predict the next point:
        It is divided into 2 cases as the above algorithm DDA
        We first initialize the first point
        Then we pick the second one due to p_i which will
            be changed in virtue of the closeness of line and our next point

    */

    if ((x1 == x2) && (y1 == y2)) {
        //If the two point is coincide
        pDC->SetPixel(x1, y1, color);
        return;
        //Draw one point then go back
    }

    if (abs(x2 - x1) >= abs(y2 - y1)) {
        //If it is slower
        if (x1 <= x2) {
            //If the first point is on the left hand side
            _LineBreseham1(pDC, x1, y1, x2, y2, color);
        }
        else {
            _LineBreseham1(pDC, x2, y2, x1, y1, color);
        }
    }
    else { //If it is faster
        if (y1 <= y2) {
            _LineBreseham2(pDC, x1, y1, x2, y2, color);
        }
        else
            _LineBreseham2(pDC, x2, y2, x1, y1, color);
    }

}

void CLine::_LineBreseham1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
    int Dx = x2 - x1;
    int Dy = y2 - y1;

    int yStep = (Dy >= 0) ? 1 : -1;
    Dx = abs(Dx);
    Dy = abs(Dy);

    int Const1 = Dy << 1; //Shift 1 bit to the left -> * 2
    int Const2 = (Dy - Dx) << 1;
    int p = Const1 - Dx;

    pDC->SetPixel(x1, y1, color);

    for (int i = 0; i < Dx; i++) {
        if (p < 0)
            p += Const1;
        else {
            p += Const2;
            y1 += yStep;
        }

        ++x1;
        pDC->SetPixel(x1, y1, color);
    }
}

void CLine::_LineBreseham2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {

    int Dx = x2 - x1;
    int Dy = y2 - y1;

    int xStep = (Dx >= 0) ? 1 : -1;

    Dx = abs(Dx);
    Dy = abs(Dy);

    int Const1 = Dx << 1;
    int Const2 = (Dx - Dy) << 1;

    int p = Const1 - Dy;

    pDC->SetPixel(x1, y1, color);

    for (int i = 0; i < Dy; i++) {
        if (p < 0)
            p += Const1;

        else {
            p += Const2;
            x1 += xStep;
        }

        ++y1;
        pDC->SetPixel(x1, y1, color);
    }
}