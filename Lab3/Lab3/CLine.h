class CLine {
public:
	static void LineDDA(CDC* pDC, CPoint A, CPoint B, COLORREF color);
	static void LineBreseham(CDC* pDC, CPoint A, CPoint B, COLORREF color);

	static void LineDDA(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	static void LineBreseham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);

private:
	static void _LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	static void _LineDDA2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);

	static void _LineBreseham1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	static void _LineBreseham2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);

};