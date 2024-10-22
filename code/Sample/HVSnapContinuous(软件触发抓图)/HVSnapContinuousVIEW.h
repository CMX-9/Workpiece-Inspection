// HVSnapContinuousView.h : interface of the CHVSnapContinuousView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVSnapContinuousVIEW_H__71E71718_5D25_464E_BE95_83C685C21665__INCLUDED_)
#define AFX_HVSnapContinuousVIEW_H__71E71718_5D25_464E_BE95_83C685C21665__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHVSnapContinuousView : public CView
{
protected: // create from serialization only
	CHVSnapContinuousView();
	DECLARE_DYNCREATE(CHVSnapContinuousView)

// Attributes
public:
	CHVSnapContinuousDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHVSnapContinuousView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHVSnapContinuousView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHVSnapContinuousView)
	afx_msg void OnMenuitem32775();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HVSnapContinuousView.cpp
inline CHVSnapContinuousDoc* CHVSnapContinuousView::GetDocument()
   { return (CHVSnapContinuousDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVSnapContinuousVIEW_H__71E71718_5D25_464E_BE95_83C685C21665__INCLUDED_)
