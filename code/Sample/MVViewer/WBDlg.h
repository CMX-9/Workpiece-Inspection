#if !defined(AFX_WBDLG_H__7F591510_0D00_4F63_A5E6_24F5ED2118A4__INCLUDED_)
#define AFX_WBDLG_H__7F591510_0D00_4F63_A5E6_24F5ED2118A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WBDlg.h : header file
//

#include "mainfrm.h"

/////////////////////////////////////////////////////////////////////////////
// CWBDlg dialog

class CWBDlg : public CDialog
{
// Construction
public:
	CWBDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWBDlg)
	enum { IDD = IDD_DLG_WB };
	double	m_dRatioR;
	double	m_dRatioG;
	double	m_dRatioB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWBDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnWbRatio();
	afx_msg void OnWbSet();
	afx_msg void OnSetfocusEditRedRatio();
	afx_msg void OnSetfocusEditBlueRatio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	double	m_dRstRatioR;
	double	m_dRstRatioG;
	double	m_dRstRatioB;

	long m_lGain[4];
	BOOL m_bApply;

	void ApplyRatio(CMainFrame *pFrame);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WBDLG_H__7F591510_0D00_4F63_A5E6_24F5ED2118A4__INCLUDED_)
