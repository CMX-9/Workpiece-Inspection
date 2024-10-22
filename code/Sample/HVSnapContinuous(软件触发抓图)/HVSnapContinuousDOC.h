// HVSnapContinuousDoc.h : interface of the CHVSnapContinuousDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVSnapContinuousDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_)
#define AFX_HVSnapContinuousDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHVSnapContinuousDoc : public CDocument
{
protected: // create from serialization only
	CHVSnapContinuousDoc();
	DECLARE_DYNCREATE(CHVSnapContinuousDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHVSnapContinuousDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHVSnapContinuousDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHVSnapContinuousDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVSnapContinuousDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_)
