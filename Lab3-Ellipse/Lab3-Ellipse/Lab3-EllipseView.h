
// Lab3-EllipseView.h : interface of the CLab3EllipseView class
//

#pragma once


class CLab3EllipseView : public CView
{
protected: // create from serialization only
	CLab3EllipseView() noexcept;
	DECLARE_DYNCREATE(CLab3EllipseView)

// Attributes
public:
	CLab3EllipseDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLab3EllipseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Lab3-EllipseView.cpp
inline CLab3EllipseDoc* CLab3EllipseView::GetDocument() const
   { return reinterpret_cast<CLab3EllipseDoc*>(m_pDocument); }
#endif

