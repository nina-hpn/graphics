/*
	Cáp Phạm Đình Thăng
*/

#pragma once
#include <atlimage.h>


/*
	Lớp : Stack
	Mô tả: Cài đặt cấu trúc Stack dùng để khử đệ quy
*/
class Stack
{
public:
	Stack(int size); //Khởi tạo stack với kích thước là size
	~Stack();
	void Push(int xc, int yc);

	void Pop(int& xc, int& yc);
	bool IsEmpty();

private:
	int n;
	int* x;
	int* y;
};
//***********************************************************************************


/*
	Lớp: CPolygon
	Mô tả: Lớp biểu diễn đa giác
		+ Không thể đặt tên Polugon T_T do trùng với hàm của hệ thống
*/
class CPolygon
{
public:
	CPolygon();
	//Thêm vào một điểm
	void Add(CPoint A);
	void Add(int x, int y);

	int GetSize();
	CPoint& GetAt(int iIndex);

	void DeletePolygon();

	//Vẽ lại đa giác
	void Draw(CDC* pDC);

private:
	int n;
	CPoint p[100]; //Tối đa đa giác có thể vẽ 100 điểm
};
//------------------------------------------------------------------------


/*
	Lớp: Array
	Mô tả: Lớp dùng để lưu lại các giao điểm với dòng quét
*/
class Array
{
public:
	Array();
	int  GetAt(int iIndex);
	void Add(int a);
	void Sort();
	int  GetSize();

private:
	int n;
	int x[100]; //Tối đa 1 dòng quét có 100 giao điểm
};
//***********************************************************************************


/*
	Lớp: CFill
	Mô tả: Lớp phụ trách việc tô
*/
class CFill
{
public:
	/*
		Tô theo đường biên
	*/
	//Thuật toán gốc - Dùng đệ quy
	static void BoundaryFill(CDC* pDC, int xc, int yc, COLORREF FillColor, COLORREF BoundaryColor);

	//Cải tiến thuật toán gốc - Khử đệ quy
	static void BoundaryFillEnhanced(CDC* pDC, int xc, int yc, COLORREF FillColor, COLORREF BoundaryColor);

	//Cải tiến thuật toán gốc - Tô không phụ thuộc màu biên
	static void BoundaryFillEnhanced(CDC* pDC, int xc, int yc, COLORREF FillColor);
	//--------------------------------------------------------------------------------

	/*
		Tô theo dòng quét cải tiến - Tô khi biết các cạnh đa giác
	*/
	//Tô theo màu đặc
	static void ScanLineFill(CDC* pDC, CPolygon& poly, COLORREF color);

	//Tô theo mẫu
	static void ScanLineFill_Pattern(CDC* pDC, CPolygon& poly, int pattern[][8], int m, int n, COLORREF color);

	//Tô theo hình
	static void ScanLineFill_Image(CDC* pDC, CPolygon& poly, CImage image);

private:

	//Bước 1: Tim ymin, ymax
	static void _FindMinMax(CPolygon& polygon, int& ymin, int& ymax);

	//Bước 2: Tìm các giao điểm với từng cạnh đa giác
	static void _FindIntersects(CPolygon& polygon, int ymin, int ymax, Array line[]);

	//Bước 3: Sắp xếp các giao điểm theo chiều tăng hoành độ
	static void _SortIntersects(Array line[], int n);
	//******************************************************************************

	//Bước 4: Tô từng cặp giao điểm

	/*
		Hàm hỗ trợ tô theo màu đặc
	*/
	static void _SolidFillLine(CDC* pDC, Array line[], int numLine, COLORREF color);
	//-------------------------------------------------------------------------------


	/*
		Hàm hỗ trợ tô theo mẫu
	*/
	static void _PatternFillLine(CDC* pDC, Array line[], int numLine, int pattern[][8], int m, int n, COLORREF color);
	//-------------------------------------------------------------------------------


	/*
		Hàm hỗ trợ tô theo ảnh
	*/
	static void _ImageFillLine(CDC* pDC, Array line[], int numLine, CImage image);
};
