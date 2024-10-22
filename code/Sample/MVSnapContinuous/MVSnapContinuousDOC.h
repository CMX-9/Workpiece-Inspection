// MVSnapContinuousDoc.h : interface of the CMVSnapContinuousDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVSnapContinuousDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_)
#define AFX_HVSnapContinuousDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMVSnapContinuousDoc : public CDocument
{
protected: // create from serialization only
	CMVSnapContinuousDoc();
	DECLARE_DYNCREATE(CMVSnapContinuousDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVSnapContinuousDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMVSnapContinuousDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVSnapContinuousDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVSnapContinuousDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_)
