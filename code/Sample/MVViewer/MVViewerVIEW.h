// MVViewerView.h : interface of the CMVViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVViewerVIEW_H__6DD2740D_267A_48D4_B6BE_E61469366256__INCLUDED_)
#define AFX_HVViewerVIEW_H__6DD2740D_267A_48D4_B6BE_E61469366256__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMVViewerView : public CView
{
protected: // create from serialization only
	CMVViewerView();
	DECLARE_DYNCREATE(CMVViewerView)

// Attributes
public:
	CMVViewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVViewerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMVViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVViewerView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRecognize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MVViewerView.cpp
inline CMVViewerDoc* CMVViewerView::GetDocument()
   { return (CMVViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVViewerVIEW_H__6DD2740D_267A_48D4_B6BE_E61469366256__INCLUDED_)
