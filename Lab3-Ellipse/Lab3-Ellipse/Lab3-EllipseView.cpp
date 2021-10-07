
// Lab3-EllipseView.cpp : implementation of the CLab3EllipseView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab3-Ellipse.h"
#endif

#include "Lab3-EllipseDoc.h"
#include "Lab3-EllipseView.h"
#include "Ellipse.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab3EllipseView

IMPLEMENT_DYNCREATE(CLab3EllipseView, CView)

BEGIN_MESSAGE_MAP(CLab3EllipseView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLab3EllipseView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CLab3EllipseView construction/destruction

CLab3EllipseView::CLab3EllipseView() noexcept
{
	// TODO: add construction code here

}

CLab3EllipseView::~CLab3EllipseView()
{
}

BOOL CLab3EllipseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab3EllipseView drawing

void CLab3EllipseView::OnDraw(CDC* pDC)
{
	CLab3EllipseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	COLORREF black = RGB(225, 225, 255);
	COLORREF red = RGB(225, 0, 0);
	COLORREF yellow = RGB(225, 225, 0);
	Ellipse1 e(30, 20, 100, 100);
	e.draw(pDC, black);
	e.scanLineFill(pDC, yellow, black);
	//e.boundaryFill(pDC, red, black);
}


// CLab3EllipseView printing


void CLab3EllipseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLab3EllipseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab3EllipseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab3EllipseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLab3EllipseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLab3EllipseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLab3EllipseView diagnostics

#ifdef _DEBUG
void CLab3EllipseView::AssertValid() const
{
	CView::AssertValid();
}

void CLab3EllipseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab3EllipseDoc* CLab3EllipseView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab3EllipseDoc)));
	return (CLab3EllipseDoc*)m_pDocument;
}
#endif //_DEBUG


// CLab3EllipseView message handlers
