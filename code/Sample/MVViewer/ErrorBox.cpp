// ErrorBox.cpp : implementation file
//

#include "stdafx.h"
#include "MVViewer.h"
#include "ErrorBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorBox dialog


CErrorBox::CErrorBox(CWnd* pParent /*=NULL*/)
	: CDialog(CErrorBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CErrorBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CErrorBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrorBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CErrorBox, CDialog)
	//{{AFX_MSG_MAP(CErrorBox)
	ON_BN_CLICKED(IDOK, OnRestartSnap)
	ON_BN_CLICKED(IDCLOSE, OnExit)
	ON_BN_CLICKED(IDCANCEL, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorBox message handlers

BOOL CErrorBox::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetActiveWindow();
	MessageBeep(0);
	ReportError(m_dwStatus);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CErrorBox::ReportError(int dwStatus)
{
	CString msg;	
	msg.Format("%s : 0x%08x"," Error", dwStatus);
	GetDlgItem(IDC_STATIC_ERROR)->SetWindowText(msg);
	UpdateWindow();
}

void CErrorBox::OnRestartSnap() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CErrorBox::OnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
