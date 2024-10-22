// MVStoreAviDoc.h : interface of the CMVStoreAviDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVStoreAviDOC_H__926800FB_4B2C_4650_AE90_BBD68270E8CA__INCLUDED_)
#define AFX_HVStoreAviDOC_H__926800FB_4B2C_4650_AE90_BBD68270E8CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMVStoreAviDoc : public CDocument
{
protected: // create from serialization only
	CMVStoreAviDoc();
	DECLARE_DYNCREATE(CMVStoreAviDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVStoreAviDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMVStoreAviDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVStoreAviDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVStoreAviDOC_H__926800FB_4B2C_4650_AE90_BBD68270E8CA__INCLUDED_)
