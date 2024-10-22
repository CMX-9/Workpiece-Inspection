// AdjustDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MVViewer.h"
#include "AdjustDlg.h"


#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg dialog


CAdjustDlg::CAdjustDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdjustDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdjustDlg)
	m_strGain = _T("");
	m_lTintLower = 1000;
	m_lTintUpper = 60;
	m_nHBlanking = 0;
	m_nVBlanking = 0;
	//}}AFX_DATA_INIT
	
	SetDefaultData();
}



void CAdjustDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjustDlg)
	DDX_Control(pDX, IDC_CM_EXPOSUREMODE, m_ctlCMExposureMode);
	DDX_Control(pDX, IDC_SB_VBLANKING, m_ctrVBlk);
	DDX_Control(pDX, IDC_SB_HBLANKING, m_ctrHBlk);
	DDX_Control(pDX, IDC_CM_ADC, m_ctlCMADC);
	DDX_Control(pDX, IDC_CM_GAIN, m_ctlCMGain);
	DDX_Control(pDX, IDC_SB_GAIN, m_ctlGain);
	DDX_Text(pDX, IDC_TEXT_GAIN, m_strGain);
	DDX_Text(pDX, IDC_EDIT_TINT_LOWER, m_lTintLower);
	DDV_MinMaxLong(pDX, m_lTintLower, 1, 1000000);
	DDX_Text(pDX, IDC_EDIT_TINT_UPPER, m_lTintUpper);
	DDV_MinMaxLong(pDX, m_lTintUpper, 1, 10000);
	DDX_Text(pDX, IDC_EDIT_HBLANKING, m_nHBlanking);
	DDV_MinMaxInt(pDX, m_nHBlanking, -9, 1930);
	DDX_Text(pDX, IDC_EDIT_VBLANKING, m_nVBlanking);
	DDV_MinMaxInt(pDX, m_nVBlanking, -9, 1930);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjustDlg, CDialog)
	//{{AFX_MSG_MAP(CAdjustDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(ID_ADJUST_DEFAULT, OnAdjustDefault)
	ON_BN_CLICKED(ID_ADJUST_RESET, OnAdjustReset)
	ON_CBN_SELCHANGE(IDC_CM_GAIN, OnSelchangeCmGain)
	ON_CBN_SELCHANGE(IDC_CM_ADC, OnSelchangeCmAdc)
	ON_EN_CHANGE(IDC_EDIT_TINT_UPPER, OnChangeEditTintUpper)
	ON_EN_CHANGE(IDC_EDIT_TINT_LOWER, OnChangeEditTintLower)
	ON_EN_CHANGE(IDC_EDIT_HBLANKING, OnChangeEditHblanking)
	ON_EN_CHANGE(IDC_EDIT_VBLANKING, OnChangeEditVblanking)
	ON_CBN_SELCHANGE(IDC_CM_EXPOSUREMODE, OnSelchangeExposureMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg message handlers
//从MainFrame类中得到值
void CAdjustDlg::ResetData()
{
	BOOL bEqual = TRUE;
	int i = 0;
	
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	
	//m_lRstTintUpper = pFrame->m_lTintUpper;
	//m_lRstTintLower = pFrame->m_lTintLower;	
	m_lADCLevel = pFrame->m_lADCLevel;
	m_lExposureMode = pFrame->m_ExposureMode;

	m_nVBlanking = m_nRstVBlanking;
	m_nHBlanking = m_nRstHBlanking;

	m_lTintLower = m_lRstTintLower;
	m_lTintUpper = m_lRstTintUpper;

	CopyMemory(m_lGain, pFrame->m_lGain, sizeof(long) * 4);	
	m_lGain[4] = 0;
	for (i = 0; i < 4; i++){
		m_lGain[4] += m_lGain[i];
	}
	m_lGain[4] /= 4;
	
	m_nGainChannel = (m_lGain[4] == m_lGain[0]) ? 4 : 0;
}



//设置默认值
void CAdjustDlg::SetDefaultData()
{

	m_lTintLower = 1000;
	m_lTintUpper = 60;	
	m_lExposureMode = 1;
	m_lADCLevel			= ADC_LEVEL2;
	
	for (int i = 0; i < 5; i++){
		m_lGain[i]	= 8;
	}

	m_nGainChannel		= 4;

	m_nVBlanking = 0;
	m_nHBlanking = 0;
	

}



void CAdjustDlg::ResetControl()
{	
	m_ctlGain.SetScrollPos(m_lGain[m_nGainChannel]);	
	m_strGain.Format("%d", m_lGain[m_nGainChannel]);


	//m_lTintLower = m_lRstTintLower;
	//m_lTintUpper = m_lRstTintUpper;

	
	m_ctlCMGain.SetCurSel(m_nGainChannel);
	m_ctlCMADC.SetCurSel(m_lADCLevel);
	m_ctlCMExposureMode.SetCurSel(m_lExposureMode);

	m_ctrVBlk.SetScrollPos(m_nVBlanking);
	m_ctrHBlk.SetScrollPos(m_nHBlanking);
	
	UpdateData(FALSE);
}




BOOL CAdjustDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_ctlGain.SetScrollRange(0, 127, TRUE);
	
	m_ctlCMGain.AddString("Red  channel");
	m_ctlCMGain.AddString("Red  channel green");
	m_ctlCMGain.AddString("Blue channel green");
	m_ctlCMGain.AddString("Blue channel");
	m_ctlCMGain.AddString("All  channel");

	m_ctlCMADC.AddString("Level 0");
	m_ctlCMADC.AddString("Level 1");
	m_ctlCMADC.AddString("Level 2");
	m_ctlCMADC.AddString("Level 3");

	m_ctlCMExposureMode.AddString("Sequence");
	m_ctlCMExposureMode.AddString("Simultaneity");

	m_nGainChannel = 4;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);

	//取得消隐的边界值
	DWORD pBlankSize[4];
	int nBufSize = 0;
	int nHmin = -9;
	int nVmin = -9;
	int nHmax = 1930;
	int nVmax = 1930;		
	
	if(pFrame->m_bIsBlkSizeSprted)
	{
		HVGetDeviceInfo(pFrame->m_hhv,DESC_DEVICE_BLANKSIZE,NULL,&nBufSize);	
		HVGetDeviceInfo(pFrame->m_hhv,DESC_DEVICE_BLANKSIZE,pBlankSize,&nBufSize);	
		
		nHmin = (int)pBlankSize[0];
		nVmin = (int)pBlankSize[1];
		nHmax = (int)pBlankSize[2];
		nVmax = (int)pBlankSize[3];	
	}

	
	m_ctrVBlk.SetScrollRange(nVmin, nVmax, TRUE);
	m_ctrHBlk.SetScrollRange(nHmin, nHmax, TRUE);


	m_nRstHBlanking = pFrame->m_nHBlanking;	
	m_nRstVBlanking = pFrame->m_nVBlanking;

	m_lRstTintUpper = pFrame->m_lTintUpper;
	m_lRstTintLower = pFrame->m_lTintLower;	

	
	ResetData();
	ResetControl();
	
	m_ctlCMExposureMode.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}






void CAdjustDlg::ResetHVDevice()
{
	long lValue = 0;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);

	//设置曝光模式
	if(pFrame->m_bIsExposureModeSprted)
	{
		int nlength = sizeof(m_lExposureMode);
		HVCommand(pFrame->m_hhv,CMD_SET_EXPOSURE_MODE, &m_lExposureMode, &nlength);
	}

	pFrame->SetBlanking(m_nHBlanking,m_nVBlanking);
	pFrame->SetExposureTime(pFrame->GetOutputWinWdith(),m_lTintUpper,m_lTintLower);

	HVADCControl(pFrame->m_hhv, ADC_BITS, m_lADCLevel);
	
	for (int i = 0; i < 4; i++){
		lValue = (m_nGainChannel < 4) ? m_lGain[i] : m_lGain[4];
		HVAGCControl(pFrame->m_hhv, RED_CHANNEL + i, lValue);
	}
}




void CAdjustDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nCurPos = 0;
	int i = 0;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);

	nCurPos = pScrollBar->GetScrollPos();
	switch( nSBCode ){
	case SB_THUMBPOSITION:
		pScrollBar->SetScrollPos( nPos );
		break;
	case SB_LINERIGHT:
		nCurPos = pScrollBar->GetScrollPos();
		nCurPos++;
		pScrollBar->SetScrollPos( nCurPos );
		break;
	case SB_LINELEFT:
		nCurPos = pScrollBar->GetScrollPos();
		nCurPos--;
		pScrollBar->SetScrollPos( nCurPos );
		break;
	case SB_PAGERIGHT:
		nCurPos = pScrollBar->GetScrollPos();
		nCurPos += 10;
		pScrollBar->SetScrollPos( nCurPos );
		break;
	case SB_PAGELEFT:
		nCurPos = pScrollBar->GetScrollPos();
		nCurPos -= 10;
		pScrollBar->SetScrollPos( nCurPos );
		break;
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos( nPos );
		break;
	default:
		break;
	}

	 if (pScrollBar == &m_ctlGain) {
		m_lGain[m_nGainChannel] = nCurPos;
		m_strGain.Format("%d", nCurPos);
		if (m_nGainChannel < 4) {
			HVAGCControl(pFrame->m_hhv, RED_CHANNEL + m_nGainChannel, nCurPos);
		} else {
			for (i = 0; i < 4; i++){
				HVAGCControl(pFrame->m_hhv, RED_CHANNEL + i, nCurPos);
			}
		}
	}
	 
	 else if (pScrollBar == (CScrollBar* )GetDlgItem(IDC_SB_HBLANKING)) 
	 {
		m_nHBlanking = nCurPos;
		 pFrame->SetBlanking(m_nHBlanking,m_nVBlanking);
		 
	 }

	 else if (pScrollBar == (CScrollBar* )GetDlgItem(IDC_SB_VBLANKING)) 
	 {
		 m_nVBlanking = nCurPos;
		 pFrame->SetBlanking(m_nHBlanking,m_nVBlanking);
	 }

	UpdateData(FALSE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CAdjustDlg::OnOK() 
{
	// TODO: Add extra validation here
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
		
	pFrame->m_lTintLower = m_lTintLower;
	pFrame->m_lTintUpper = m_lTintUpper;
	pFrame->m_ExposureMode = (HV_EXPOSURE_MODE)m_lExposureMode;
	pFrame->m_lADCLevel		= m_lADCLevel;
	
	for (int i = 0; i < 4; i++){
		pFrame->m_lGain[i] = (m_nGainChannel < 4) ? m_lGain[i] : m_lGain[4];
	}
	
	CDialog::OnOK();
}


void CAdjustDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	ResetData();
	ResetHVDevice();

	CDialog::OnCancel();
}



void CAdjustDlg::OnAdjustDefault() 
{
	// TODO: Add your control notification handler code here
	SetDefaultData();
	ResetControl();
	ResetHVDevice();
}



void CAdjustDlg::OnAdjustReset() 
{
	// TODO: Add your control notification handler code here
	ResetData();
	ResetControl();
	ResetHVDevice();
}

void CAdjustDlg::OnSelchangeCmGain() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);

	m_nGainChannel = m_ctlCMGain.GetCurSel();
	m_strGain.Format("%d", m_lGain[m_nGainChannel]);
	m_ctlGain.SetScrollPos(m_lGain[m_nGainChannel], TRUE);

	UpdateData(FALSE);

	if (m_nGainChannel < 4) {
		HVAGCControl(pFrame->m_hhv, RED_CHANNEL + m_nGainChannel, m_lGain[m_nGainChannel]);
	} else {
		for (int i = 0; i < 4; i++){
			HVAGCControl(pFrame->m_hhv, RED_CHANNEL + i, m_lGain[4]);
		}
	}
}



void CAdjustDlg::OnSelchangeCmAdc() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	
	m_lADCLevel = m_ctlCMADC.GetCurSel();
	HVADCControl(pFrame->m_hhv, ADC_BITS, m_lADCLevel);
}

void CAdjustDlg::OnChangeEditTintUpper() 
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	UpdateData(TRUE);

	pFrame->m_lTintUpper = m_lTintUpper;		
	//When outputwindow changes, change the exposure 
	pFrame->SetExposureTime(pFrame->GetOutputWinWdith(),m_lTintUpper,m_lTintLower);
	
}

void CAdjustDlg::OnChangeEditTintLower() 
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	UpdateData(TRUE);

	pFrame->m_lTintLower = m_lTintLower;	
	//When outputwindow changes, change the exposure 
	pFrame->SetExposureTime(pFrame->GetOutputWinWdith(),m_lTintUpper,m_lTintLower);
	
}


void CAdjustDlg::OnChangeEditHblanking() 
{

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	UpdateData(TRUE);
	pFrame->SetBlanking(m_nHBlanking,m_nVBlanking);
	m_ctrHBlk.SetScrollPos(m_nHBlanking);
	
}

void CAdjustDlg::OnChangeEditVblanking() 
{

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	UpdateData(TRUE);
	pFrame->SetBlanking(m_nHBlanking,m_nVBlanking);
	m_ctrVBlk.SetScrollPos(m_nVBlanking);
	
}


void CAdjustDlg::OnSelchangeExposureMode() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	
	m_lExposureMode = m_ctlCMExposureMode.GetCurSel();
	int nlength = sizeof(m_lExposureMode);
	HVCommand(pFrame->m_hhv,CMD_SET_EXPOSURE_MODE, &m_lExposureMode, &nlength);
}
