// MVViewerDoc.h : interface of the CMVViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVViewerDOC_H__307BE5D1_5B54_4A95_826E_C66DC54DAE96__INCLUDED_)
#define AFX_HVViewerDOC_H__307BE5D1_5B54_4A95_826E_C66DC54DAE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMVViewerDoc : public CDocument
{
protected: // create from serialization only
	CMVViewerDoc();
	DECLARE_DYNCREATE(CMVViewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMVViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVViewerDOC_H__307BE5D1_5B54_4A95_826E_C66DC54DAE96__INCLUDED_)
