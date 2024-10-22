// MVRealtimeView.h : interface of the CMVRealtimeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVRealtimeVIEW_H__71E71718_5D25_464E_BE95_83C685C21665__INCLUDED_)
#define AFX_HVRealtimeVIEW_H__71E71718_5D25_464E_BE95_83C685C21665__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMVRealtimeView : public CView
{
protected: // create from serialization only
	CMVRealtimeView();
	DECLARE_DYNCREATE(CMVRealtimeView)

// Attributes
public:
	CMVRealtimeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVRealtimeView)
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
	virtual ~CMVRealtimeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVRealtimeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MVRealtimeView.cpp
inline CMVRealtimeDoc* CMVRealtimeView::GetDocument()
   { return (CMVRealtimeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVRealtimeVIEW_H__71E71718_5D25_464E_BE95_83C685C21665__INCLUDED_)
