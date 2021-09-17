#include "stdafx.h" ;
#include "math.h" ;
#include "CLine.h" ;
#include <iostream>;

using namespace std;
using namespace CLine;


void CLine::LineDDA(CDC* pDC, CPoint A, CPoint B, COLORREF color) {
    LineDDA(pDC, A.x, A.y, B.x, B.y, color);
}

void CLine::LineBresenham(CDC* pDC, CPoint A, CPoint B, COLORREF color) {
    LineBresenham(pDC, A.x, A.y, B.x, B.y, color);    
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
        
        Then all round the next x or y
    */

    if(x1 == x2) && (y1 == y2) { 
        //If the two point is coincide
        pDC->SetPixel(x1, y1, color);
        return;
        //Draw one point then go back
    }

    if(abs(x2 - x1) >= abs(y2 - y1)) { //If it is slower
        if(x1 <= x2) { //If it is on the left hand side
            //Case 1
            _LineDDA1(pDC, x1, y1, x2, y2, color);
        }
        else
            _LineDDA1(pDC, x2, y2, x1, y1, color); 
    }
    else { //If it is faster
        if(y1 <= y2) //If the first point is lower
            _LineDDA2(pDC, x1, y1, x2, y2, color); //Case 2
        else 
            _LineDDA2(pDC, x2, y2, x1, y1, color)
    }
}

void CLine::_LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
    pDC->SetPixel(x1, y1, color);
    float n = (float)(y2 - y1) / (x2 - x1);

    while(x1 < x2) {
        x1++;
        y += n;
        pDC-> SetPixel(x1, Round(y), color);
    }
}

void CLine::_LineDDA2(CDC* pDC, int x1, int x2, int y2, COLORREF color) {
    pDC->SetPixel(x1, y1, color);
    float n = (float)(x2 - x1) / (y2 - y1);

    while (y1 < y2) {
        y1++;
        x += n;
        pDC->SetPixel(Round(x), y1, color);
    }
}

void CLine::LineBresenham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
    /*
    Bresenham mindset:
    The thing is we need to predict the next point:
        It is divided into 2 cases as the above algorithm DDA
        We first initialize the first point 
        Then we pick the second one due to p_i which will
            be changed in virtue of the closeness of line and our next point
    
    */

    if(x1 == x2) && (y1 == y2) { 
        //If the two point is coincide
        pDC->SetPixel(x1, y1, color);
        return;
        //Draw one point then go back
    }

    if(abs(x2 - x1) >= abs(y2 - y1)) { 
        //If it is slower
        if(x1 <= x2) { 
            //If the first point is on the left hand side
            _LineBresenham(pDC, x1, y1, x2, y2, color);
        }
        else {
            _LineBresenham(pDC, x2, y2, x2, y2, color)
        }
    }
    else { //If it is faster
        if(y1 <= y2) {
            _LineBresenham(pDC, x1, y1, x2, y2, color)
        }
        else
            _LineBresenham(pDC, x2, y2, x1, y1, color)
    }

}

