// MVStoreAviView.h : interface of the CMVStoreAviView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVStoreAviVIEW_H__F54CE9A4_6EC3_439F_B112_F15848704D74__INCLUDED_)
#define AFX_HVStoreAviVIEW_H__F54CE9A4_6EC3_439F_B112_F15848704D74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMVStoreAviView : public CView
{
protected: // create from serialization only
	CMVStoreAviView();
	DECLARE_DYNCREATE(CMVStoreAviView)

// Attributes
public:
	CMVStoreAviDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVStoreAviView)
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
	virtual ~CMVStoreAviView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVStoreAviView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MVStoreAviView.cpp
inline CMVStoreAviDoc* CMVStoreAviView::GetDocument()
   { return (CMVStoreAviDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVStoreAviVIEW_H__F54CE9A4_6EC3_439F_B112_F15848704D74__INCLUDED_)
