/*
	Cáp Phạm Đình Thăng
*/

#pragma once


/*
	Lớp: CShape
	Mô tả: Dùng để vẽ các hình cơ bản
*/
class CShape
{
public:
	//Vẽ ngũ giác đều
	static void Pentagon(CDC* pDC, int xc, int yc, int r, COLORREF color);

	//Vẽ lục giác đều
	static void Hexagon(CDC* pDC, int xc, int yc, int r, COLORREF color);

	//Vẽ ngôi sao n cánh - mặc định vẽ ngôi sao 5 cánh
	static void Star(CDC* pDC, CPoint I, int R, COLORREF color, int n = 5);
	static void Star(CDC* pDC, int xc, int yc, int R, COLORREF color, int n = 5);
};
