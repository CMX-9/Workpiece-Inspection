// MVRealtimeDoc.h : interface of the CMVRealtimeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVRealtimeDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_)
#define AFX_HVRealtimeDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMVRealtimeDoc : public CDocument
{
protected: // create from serialization only
	CMVRealtimeDoc();
	DECLARE_DYNCREATE(CMVRealtimeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVRealtimeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMVRealtimeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVRealtimeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVRealtimeDOC_H__3520DEDF_105E_49B9_9F53_2396615E4FDA__INCLUDED_)
