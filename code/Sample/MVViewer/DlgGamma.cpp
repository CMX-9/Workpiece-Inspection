// DlgGamma.cpp : implementation file
//

#include "stdafx.h"
#include "MVViewer.h"
#include "DlgGamma.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGamma dialog


CDlgGamma::CDlgGamma(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGamma::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGamma)
	m_dGammRatio = 1.0;
	//}}AFX_DATA_INIT
}


void CDlgGamma::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGamma)
	DDX_Text(pDX, IDC_GAMMA_RATIO, m_dGammRatio);
	DDV_MinMaxDouble(pDX, m_dGammRatio, 0.3, 3.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGamma, CDialog)
	//{{AFX_MSG_MAP(CDlgGamma)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGamma message handlers

void CDlgGamma::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CDlgGamma::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
