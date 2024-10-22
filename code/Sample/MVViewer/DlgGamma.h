#if !defined(AFX_DLGGAMMA_H__B123C881_D0AA_4FAA_B1E4_C6D3DF3A518F__INCLUDED_)
#define AFX_DLGGAMMA_H__B123C881_D0AA_4FAA_B1E4_C6D3DF3A518F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGamma.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGamma dialog

class CDlgGamma : public CDialog
{
// Construction
public:
	CDlgGamma(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGamma)
	enum { IDD = IDD_DLG_GAMMA };
	double	m_dGammRatio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGamma)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGamma)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGAMMA_H__B123C881_D0AA_4FAA_B1E4_C6D3DF3A518F__INCLUDED_)
