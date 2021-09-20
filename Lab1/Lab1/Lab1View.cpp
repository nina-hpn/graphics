
// Lab1View.cpp : implementation of the CLab1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab1.h"
#endif

#include "Lab1Doc.h"
#include "Lab1View.h"

#include "Cline.h"

#include "stdio.h"
#include "math.h"
#include "dos.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab1View

IMPLEMENT_DYNCREATE(CLab1View, CView)

BEGIN_MESSAGE_MAP(CLab1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLab1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CLab1View construction/destruction

CLab1View::CLab1View() noexcept
{
	// TODO: add construction code here

}

CLab1View::~CLab1View()
{
}

BOOL CLab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab1View drawing

void CLab1View::OnDraw(CDC* pDC)
{
	CLab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	COLORREF lineColorDefault = RGB(0, 0, 0);
	COLORREF lineColorRed = RGB(255, 0, 0);

	CPen qLinePen(PS_SOLID, 7, lineColorDefault);
	pDC->SelectObject(&qLinePen);

	pDC->MoveTo(100, 500);
	pDC->LineTo(500, 600);
	// Draw a thick black line

	// Bigger slope
	CPoint A(100, 400);
	CPoint B(400, 500);

	//Smaller slope
	CPoint C(200, 500);
	CPoint D(500, 600);

	//Very big slope
	CPoint E(100, 300);
	CPoint F(150, 500);

	//Very small slope
	CPoint G(200, 400);
	CPoint H(400, 405);

	// Draw a not so thick black line from A-> B
	CLine::LineBreseham(pDC, B, A, lineColorDefault); 
	
	//Draw a not so thick black line from E-> F
	CLine::LineBreseham(pDC, E, F, lineColorDefault);
	
	//Draw a red line from C->D
	CLine::LineDDA(pDC, C, D, lineColorRed); 
	
	//Draw a red line from H->G
	CLine::LineDDA(pDC, H, G, lineColorRed);

	//Insight:
	//The smaller the slope the more fragile the line look
	//Best see in the line draw by DDA from H-> G
}


// CLab1View printing


void CLab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLab1View diagnostics

#ifdef _DEBUG
void CLab1View::AssertValid() const
{
	CView::AssertValid();
}

void CLab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab1Doc* CLab1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab1Doc)));
	return (CLab1Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab1View message handlers
