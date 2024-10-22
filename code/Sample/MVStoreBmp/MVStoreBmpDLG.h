// MVStoreBmpDlg.h : header file
//

#if !defined(AFX_HVStoreBmpDLG_H__A095E99F_7070_4ED3_95E6_204A508B688F__INCLUDED_)
#define AFX_HVStoreBmpDLG_H__A095E99F_7070_4ED3_95E6_204A508B688F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMVStoreBmpDlg dialog

#include "..\..\inc\HVDAILT.h"

class CMVStoreBmpDlg : public CDialog
{
// Construction
public:
	CMVStoreBmpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMVStoreBmpDlg)
	enum { IDD = IDD_HVStoreBmp_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVStoreBmpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMVStoreBmpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSaveBmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:


private:
	void SetExposureTime(HHV hhv,int nWindWidth,long lTintUpper,long lTintLower);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HVStoreBmpDLG_H__A095E99F_7070_4ED3_95E6_204A508B688F__INCLUDED_)
