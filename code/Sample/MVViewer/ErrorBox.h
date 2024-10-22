#if !defined(AFX_ERRORBOX_H__BF05A912_BF1D_4C4C_B146_BDEC600D9CA6__INCLUDED_)
#define AFX_ERRORBOX_H__BF05A912_BF1D_4C4C_B146_BDEC600D9CA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErrorBox dialog

class CErrorBox : public CDialog
{
// Construction
public:
	int m_dwStatus;
	void ReportError(int dwStatus);
	CErrorBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CErrorBox)
	enum { IDD = IDD_ERRORBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CErrorBox)
	virtual BOOL OnInitDialog();
	afx_msg void OnRestartSnap();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORBOX_H__BF05A912_BF1D_4C4C_B146_BDEC600D9CA6__INCLUDED_)
