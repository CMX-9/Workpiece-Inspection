#if !defined(AFX_ADJUSTDLG_H__6C6708DC_A72D_471A_9050_B26FF68E933C__INCLUDED_)
#define AFX_ADJUSTDLG_H__6C6708DC_A72D_471A_9050_B26FF68E933C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjustDlg.h : header file
//

//定义自己的0
#define  MY_ZERO 0.000000001

/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg dialog

class CAdjustDlg : public CDialog
{
	friend class CMainFrame;
// Construction
public:
	CAdjustDlg(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CAdjustDlg)
	enum { IDD = IDD_DLG_ADJUST };
	CComboBox	m_ctlCMExposureMode;
	CScrollBar	m_ctrVBlk;
	CScrollBar	m_ctrHBlk;
	CComboBox	m_ctlCMADC;
	CComboBox	m_ctlCMGain;
	CScrollBar	m_ctlGain;
	CString	m_strGain;
	long	m_lTintLower;
	long	m_lTintUpper;
	int		m_nHBlanking;
	int		m_nVBlanking;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdjustDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdjustDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAdjustDefault();
	afx_msg void OnAdjustReset();
	afx_msg void OnSelchangeCmGain();
	afx_msg void OnSelchangeCmAdc();
	afx_msg void OnChangeEditTintUpper();
	afx_msg void OnChangeEditTintLower();
	afx_msg void OnChangeEditHblanking();
	afx_msg void OnChangeEditVblanking();
	afx_msg void OnSelchangeExposureMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	long m_lRstTintUpper;
	long m_lRstTintLower;
	long m_lExposureMode;
	long m_lADCLevel;
	long m_lGain[5];	
	int m_nGainChannel;

	int m_nRstVBlanking;
	int m_nRstHBlanking ;	
private:
	void ResetData();
	void SetDefaultData();
	void ResetControl();
	void ResetHVDevice();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADJUSTDLG_H__6C6708DC_A72D_471A_9050_B26FF68E933C__INCLUDED_)
