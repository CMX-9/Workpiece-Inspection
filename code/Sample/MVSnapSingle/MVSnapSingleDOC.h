// MVSnapSingleDoc.h : interface of the CMVSnapSingleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVSnapSingleDOC_H__DC282528_965C_4D38_8860_970B4AE20963__INCLUDED_)
#define AFX_HVSnapSingleDOC_H__DC282528_965C_4D38_8860_970B4AE20963__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMVSnapSingleDoc : public CDocument
{
protected: // create from serialization only
	CMVSnapSingleDoc();
	DECLARE_DYNCREATE(CMVSnapSingleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVSnapSingleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMVSnapSingleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVSnapSingleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVSnapSingleDOC_H__DC282528_965C_4D38_8860_970B4AE20963__INCLUDED_)
