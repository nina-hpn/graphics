#include "stdafx.h"
#include "CFill.h"

/*
	Xây dựng cấu trúc stack - Dùng trong tô màu theo đường biên
*/
Stack::Stack(int size)
{
	n = 0;
	x = new int[size];
	y = new int[size];
}

Stack::~Stack()
{
	delete[] x;
	delete[] y;
}

void Stack::Push(int xc, int yc)
{
	x[n] = xc; //Chưa kiểm tra tràn
	y[n] = yc;
	n++;
}

void Stack::Pop(int& xc, int& yc)
{
	--n; //Chưa kiểm tra stack rỗng hay chưa
	xc = x[n];
	yc = y[n];
}

bool Stack::IsEmpty()
{
	if (n == 0)
		return true;
	return false;
}
//**********************************************************************************


/*
	Xây dựng cấu trúc đa giác - Dùng trong tô theo dòng quét
*/
CPolygon::CPolygon()
{
	n = 0;
}

void CPolygon::DeletePolygon()
{
	n = 0;
}

//Thêm một điểm vào đa giác
void CPolygon::Add(CPoint A)
{
	Add(A.x, A.y);
}


void CPolygon::Add(int x, int y)
{
	p[n].x = x;
	p[n].y = y;
	++n;
}

//Lấy số cạnh của đa giác
int CPolygon::GetSize()
{
	return n;
}

CPoint& CPolygon::GetAt(int iIndex)
{
	return p[iIndex];
}

void CPolygon::Draw(CDC* pDC)
{
	pDC->MoveTo(p[n - 1]);

	for (int i = 0; i < n; ++i)
		pDC->LineTo(p[i]);
}
//---------------------------------------------------------------------


/*
	Xây dựng cấu trúc Array để lưu giao điểm - Dùng trong tô theo dòng quét
*/
Array::Array()
{
	n = 0;
}


int Array::GetAt(int iIndex)
{
	return x[iIndex];
}


//Thêm một phần tử vào mảng
void Array::Add(int a)
{
	x[n++] = a;
}


//Sắp xếp mảng tăng dần
void Array::Sort()
{
	int i, j;

	for (i = 0; i < n; ++i)
		for (j = i + 1; j < n; ++j)
			if (x[i] > x[j])
				Swap(x[i], x[j]);
}


int Array::GetSize()
{
	return n;
}
//**********************************************************************************


/*
	Tô theo đường biên
*/

//Thuật toán gốc - Dùng đệ quy
void CFill::BoundaryFill(CDC* pDC, int x, int y, COLORREF FillColor, COLORREF BoundaryColor)
{
	COLORREF CurrentColor = pDC->GetPixel(x, y);

	if ((CurrentColor != FillColor) &&   //Chưa tô
		(CurrentColor != BoundaryColor)) //Không phải là màu biên
	{
		pDC->SetPixel(x, y, FillColor);
		BoundaryFill(pDC, x - 1, y, FillColor, BoundaryColor);
		BoundaryFill(pDC, x + 1, y, FillColor, BoundaryColor);
		BoundaryFill(pDC, x, y - 1, FillColor, BoundaryColor);
		BoundaryFill(pDC, x, y + 1, FillColor, BoundaryColor);
	}
}

//Cải tiến thuật toán gốc - Khử đệ quy bằng stack
void CFill::BoundaryFillEnhanced(CDC* pDC, int x, int y, COLORREF FillColor, COLORREF BoundaryColor)
{
	Stack store(1024);
	store.Push(x, y);

	int left, right;
	COLORREF curentColor;

	while (!store.IsEmpty())
	{
		store.Pop(x, y);
		pDC->SetPixel(x, y, FillColor);

		//Tô trái nhất có thể
		left = x - 1;
		while (pDC->GetPixel(left, y) != BoundaryColor)
		{
			pDC->SetPixel(left, y, FillColor);
			--left;
		}

		//Tô phải nhất có thể
		right = x + 1;
		while (pDC->GetPixel(right, y) != BoundaryColor)
		{
			pDC->SetPixel(right, y, FillColor);
			++right;
		}

		//Tìm các điểm hạt giống khác
		++left;
		--right;
		for (x = left; x <= right; ++x)
		{
			//Xét bên trên dòng đang tô
			curentColor = pDC->GetPixel(x, y + 1);
			if ((curentColor != FillColor) && (curentColor != BoundaryColor)) //Chưa tô và không phải biên
				if ((x == left) || //Điểm trái đầu tiên
					(pDC->GetPixel(x - 1, y + 1) == BoundaryColor)) // Bên trái là điểm biên
					store.Push(x, y + 1);

			//Xét bên dưới dòng đang tô
			curentColor = pDC->GetPixel(x, y - 1);
			if ((curentColor != FillColor) && (curentColor != BoundaryColor)) //Chưa tô và không phải biên
				if ((x == left) || //Điểm trái đầu tiên
					(pDC->GetPixel(x - 1, y - 1) == BoundaryColor)) // Bên trái là điểm biên
					store.Push(x, y - 1);
		}
	}
}



//Cải tiến thuật toán khử đệ quy bằng stack - Tô không phụ thuộc màu biên
void CFill::BoundaryFillEnhanced(CDC* pDC, int x, int y, COLORREF FillColor)
{
	COLORREF BackColor = pDC->GetPixel(x, y);
	Stack store(1024);
	store.Push(x, y);

	int left, right;
	COLORREF curentColor;

	while (!store.IsEmpty())
	{
		store.Pop(x, y);
		pDC->SetPixel(x, y, FillColor);

		//Tô trái nhất có thể
		left = x - 1;
		while (pDC->GetPixel(left, y) == BackColor)
		{
			pDC->SetPixel(left, y, FillColor);
			--left;
		}

		//Tô phải nhất có thể
		right = x + 1;
		while (pDC->GetPixel(right, y) == BackColor)
		{
			pDC->SetPixel(right, y, FillColor);
			++right;
		}

		//Tìm các điểm hạt giống khác
		++left; --right;
		for (x = left; x <= right; ++x)
		{
			//Xét bên trên dòng đang tô
			curentColor = pDC->GetPixel(x, y + 1);
			if ((curentColor != FillColor) && (curentColor == BackColor)) //Chưa tô và không phải biên
				if ((x == left) || //Điểm trái đầu tiên
					(pDC->GetPixel(x - 1, y + 1) != BackColor)) // Bên trái là điểm biên
					store.Push(x, y + 1);

			//Xét bên dưới dòng đang tô
			curentColor = pDC->GetPixel(x, y - 1);
			if ((curentColor != FillColor) && (curentColor == BackColor)) //Chưa tô và không phải biên
				if ((x == left) || //Điểm trái đầu tiên
					(pDC->GetPixel(x - 1, y - 1) != BackColor)) // Bên trái là điểm biên
					store.Push(x, y - 1);
		}
	}
}
//************************************************************************************

/*
	Tô theo dòng quét - Thuật toán tô theo dòng quét cải tiến
*/

//Tô theo màu đặc theo dòng quét
#define MAXLINE 768

void CFill::ScanLineFill(CDC* pDC, CPolygon& polygon, COLORREF color)
{
	Array line[MAXLINE]; //Tùy vào màn hình ở chế độ nào để thiết lập số dòng tối đa
	int ymin, ymax;

	_FindMinMax(polygon, ymin, ymax);
	_FindIntersects(polygon, ymin, ymax, line);
	_SortIntersects(line, MAXLINE);
	_SolidFillLine(pDC, line, MAXLINE, color);
}

//Bước 1: Tim ymin, ymax
void CFill::_FindMinMax(CPolygon& polygon, int& ymin, int& ymax)
{
	ymin = polygon.GetAt(0).y;
	ymax = polygon.GetAt(0).y;

	int n = polygon.GetSize();

	for (int i = 1; i < n; ++i)
	{
		if (polygon.GetAt(i).y < ymin)
			ymin = polygon.GetAt(i).y;
		if (polygon.GetAt(i).y > ymax)
			ymax = polygon.GetAt(i).y;
	}
}


//Bước 2: Tìm các giao điểm với từng cạnh đa giác
void CFill::_FindIntersects(CPolygon& polygon, int ymin, int ymax, Array line[])
{
	int x1, y1, x2, y2;
	int n = polygon.GetSize();

	float x; int y;
	float k; //Hệ số góc nghịch đảo

	for (int i = 0; i < n; ++i)
	{
		x1 = polygon.GetAt(i).x;
		y1 = polygon.GetAt(i).y;
		x2 = polygon.GetAt((i + 1) % n).x;
		y2 = polygon.GetAt((i + 1) % n).y;

		if (y1 == y2) //Đoạn thẳng nằm ngang
			continue; //Bỏ qua

		if (y1 > y2) //Nếu điểm đầu nằm trên
		{
			Swap(x1, x2); //hoán vị hai điểm
			Swap(y1, y2);
		}

		k = (float)(x2 - x1) / (y2 - y1);

		for (y = y1, x = x1; y < y2; ++y, x += k)
			line[y].Add(Round(x));
	}
}


//Bước 3: Sắp xếp các giao điểm theo chiều tăng hoành độ
void CFill::_SortIntersects(Array line[], int n)
{
	for (int i = 0; i < n; ++i)
		line[i].Sort();
}


//Bước 4: Tô từng cặp giao điểm
void CFill::_SolidFillLine(CDC* pDC, Array line[], int numLine, COLORREF color)
{
	int x, y, i;
	int size;

	for (y = 0; y < numLine; ++y) //Quét qua từng dòng màn hình
	{
		size = line[y].GetSize();

		for (i = 0; i < size; i += 2) //Tô từng cặp giao điểm
		{
			for (x = line[y].GetAt(i); x <= line[y].GetAt(i + 1); ++x)
				pDC->SetPixel(x, y, color);
		}
	}
}
//-----------------------------------------------------------------------------------

//Tô theo mẫu
void CFill::ScanLineFill_Pattern(CDC* pDC, CPolygon& poly, int pattern[][8], int m, int n, COLORREF color)
{
	Array line[MAXLINE]; //Tùy vào màn hình ở chế độ nào để thiết lập số dòng tối đa
	int ymin, ymax;

	_FindMinMax(poly, ymin, ymax);
	_FindIntersects(poly, ymin, ymax, line);
	_SortIntersects(line, MAXLINE);
	_PatternFillLine(pDC, line, MAXLINE, pattern, m, n, color);
}

void CFill::_PatternFillLine(CDC* pDC, Array line[], int numLine, int pattern[][8], int m, int n, COLORREF color)
{
	int x, y, i;
	int size;

	for (y = 0; y < numLine; ++y) //Quét qua từng dòng màn hình
	{
		size = line[y].GetSize();

		for (i = 0; i < size; i += 2) //Tô từng cặp giao điểm
		{
			for (x = line[y].GetAt(i); x <= line[y].GetAt(i + 1); ++x)
				if (pattern[x % n][y % m] == 1)
					pDC->SetPixel(x, y, color);
		}
	}
}
//-----------------------------------------------------------------------------------


//Tô theo hình
void CFill::ScanLineFill_Image(CDC* pDC, CPolygon& poly, CImage image)
{
	Array line[MAXLINE]; //Tùy vào màn hình ở chế độ nào để thiết lập số dòng tối đa
	int ymin, ymax;

	_FindMinMax(poly, ymin, ymax);
	_FindIntersects(poly, ymin, ymax, line);
	_SortIntersects(line, MAXLINE);
	_ImageFillLine(pDC, line, MAXLINE, image);
}


void CFill::_ImageFillLine(CDC* pDC, Array line[], int numLine, CImage image)
{
	int width = image.GetWidth();
	int height = image.GetHeight();

	int x, y, i;
	int size;

	for (y = 0; y < numLine; ++y) //Quét qua từng dòng màn hình
	{
		size = line[y].GetSize();

		for (i = 0; i < size; i += 2) //Tô từng cặp giao điểm
		{
			for (x = line[y].GetAt(i); x <= line[y].GetAt(i + 1); ++x)
				pDC->SetPixel(x, y, image.GetPixel(x % width, y % height));
		}
	}
}