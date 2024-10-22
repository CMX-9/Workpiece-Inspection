// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MVViewer.h"
#include "ErrorBox.h"
#include "MainFrm.h"
#include "..\..\inc\hvutil.h"

#include "Adjustdlg.h"
#include "WBDlg.h"
#include "Shlwapi.h"
#include "math.h"
#include "DlgGamma.h"

#define  WHITEPIXEL   255
#define  BLACKPIXEL   0
#define  UP           0
#define  DOWN         1
#define  LEFT         2
#define  RIGHT        3
#define  COIN         2               //Ӳ��
#define  NUT          1               //��ĸ
#define  SCREW        0               //�ݶ�
#define  INVALID      3               //��ЧĿ��

typedef struct ClassInFomation{
	unsigned int         centerX;   //����ļ������ĺ�����
	unsigned int         centerY;   //����ļ�������������
	unsigned int          length;   //������ռ����ĳ���
	unsigned int            wide;   //������ռ����Ŀ��
	BYTE            grayOfCenter;   //���༸������λ�õ�����ֵ
	float              classDuty;   //����Ԫ���ڸ���������ռ�ձ�
	float           lengthToWide;   //������ռ����ĳ����
	float        membershipGrade;   //�����ȣ�Ϊ0������ĸ��Ϊ1�����ݶ�;
}ClassInfo;

ClassInfo g_imageClassInfo[256] = {0};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern unsigned int recognitionFlag;

//#define  GAMMA_CORRECT 1
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_PAINT()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_ADJUST, OnViewAdjust)
	ON_COMMAND(ID_VIEW_SNAP, OnViewSnap)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SNAP, OnUpdateViewSnap)
	ON_COMMAND(ID_FILE_OPEN_ONE, OnFileOpenOne)
	ON_COMMAND(ID_FILE_SAVE_AS_ONE, OnFileSaveAsOne)
	ON_COMMAND(ID_VIEW_WB, OnViewWb)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_COMMAND(ID_VIEW_CONVERSION_BG, OnViewConversionBg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONVERSION_BG, OnUpdateViewConversionBg)
	ON_COMMAND(ID_VIEW_CONVERSION_GB, OnViewConversionGb)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONVERSION_GB, OnUpdateViewConversionGb)
	ON_COMMAND(ID_VIEW_CONVERSION_GR, OnViewConversionGr)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONVERSION_GR, OnUpdateViewConversionGr)
	ON_COMMAND(ID_VIEW_CONVERSION_RG, OnViewConversionRg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONVERSION_RG, OnUpdateViewConversionRg)
	ON_COMMAND(ID_VIEW_COLOR, OnViewColor)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COLOR, OnUpdateViewColor)
	ON_COMMAND(ID_VIEW_BW, OnViewBw)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BW, OnUpdateViewBw)
	ON_COMMAND(ID_HELP_WEBSITE, OnHelpWebsite)
	ON_COMMAND(ID_HELP_MAILTO, OnHelpMailto)
	ON_COMMAND(ID_VIEW_CONTINUATION, OnViewContinuation)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONTINUATION, OnUpdateViewContinuation)
	ON_COMMAND(ID_VIEW_TRIGGER, OnViewTrigger)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TRIGGER, OnUpdateViewTrigger)
	ON_COMMAND(ID_VIEW_SNAPSHOT, OnViewSnapshot)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SNAPSHOT, OnUpdateViewSnapshot)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WB, OnUpdateViewWb)
	ON_COMMAND(ID_CONVERSION_BEST, OnConversionBest)
	ON_UPDATE_COMMAND_UI(ID_CONVERSION_BEST, OnUpdateConversionBest)
	ON_COMMAND(ID_CONVERSION_FAST, OnConversionFast)
	ON_UPDATE_COMMAND_UI(ID_CONVERSION_FAST, OnUpdateConversionFast)
	ON_COMMAND(ID_CONVERSION_NORMAL, OnConversionNormal)
	ON_UPDATE_COMMAND_UI(ID_CONVERSION_NORMAL, OnUpdateConversionNormal)
	ON_COMMAND(ID_VIEW_MODE0, OnViewMode0)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE0, OnUpdateViewMode0)
	ON_COMMAND(ID_VIEW_MODE1, OnViewMode1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE1, OnUpdateViewMode1)
	ON_COMMAND(ID_VIEW_MODE2, OnViewMode2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE2, OnUpdateViewMode2)
	ON_COMMAND(ID_GAMMA_CORRECT, OnGammaCorrect)
	ON_UPDATE_COMMAND_UI(ID_GAMMA_CORRECT, OnUpdateGammaCorrect)
	ON_COMMAND(ID_CANCEL_GAMMA, OnCancelGamma)
	ON_UPDATE_COMMAND_UI(ID_CANCEL_GAMMA, OnUpdateCancelGamma)
	ON_COMMAND(ID_GET_BAD_PIEXES, OnGetBadPiexes)
	ON_UPDATE_COMMAND_UI(ID_GET_BAD_PIEXES, OnUpdateGetBadPiexes)
	ON_COMMAND(ID_ELIMINATE_BAD_PIXELS, OnEliminateBadPixels)
	ON_UPDATE_COMMAND_UI(ID_ELIMINATE_BAD_PIXELS, OnUpdateEliminateBadPixels)
	ON_COMMAND(ID_GET_TEMPLATE, OnGetTemplate)
	ON_UPDATE_COMMAND_UI(ID_GET_TEMPLATE, OnUpdateGetTemplate)
	ON_COMMAND(ID_TEMPLATE_CORRECT, OnTemplateCorrect)
	ON_UPDATE_COMMAND_UI(ID_TEMPLATE_CORRECT, OnUpdateTemplateCorrect)
	ON_COMMAND(ID_SNAPSPEED_NORMAL, OnSnapspeedNormal)
	ON_UPDATE_COMMAND_UI(ID_SNAPSPEED_NORMAL, OnUpdateSnapspeedNormal)
	ON_COMMAND(ID_SNPASPEED_HIGH, OnSnpaspeedHigh)
	ON_UPDATE_COMMAND_UI(ID_SNPASPEED_HIGH, OnUpdateSnpaspeedHigh)
	ON_COMMAND(ID_MENUITEM32828, OnMenuitem32828)
	ON_COMMAND(ID_MENUITEM32829, OnMenuitem32829)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CHANGE_SNAP, OnSnapMessage)
	ON_MESSAGE(WM_GET_RATIO, OnGetRatioMessage)
	ON_MESSAGE(WM_SNAP_ERROR, OnSnapError)
	ON_MESSAGE(WM_SNAP_STOP, OnSnapStop)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	this->m_bAutoMenuEnable = FALSE;
	// TODO: add member initialization code here
	m_hhv			= NULL;
	m_nLostNum		= 0;
	m_nErrorNum		= 0;
	m_SnapMode		= CONTINUATION;	
	m_Resolution	= RES_MODE0;
	m_lADCLevel		= ADC_LEVEL2;
	
	
	for (int i = 0; i < 4; i++)
	{
		m_lGain[i]	= 8;
	}
	
	m_rcOutputWindow.SetRect(0, 0, 0, 0);
	
	m_ImageMode		= HV_COLOR;
	m_Layout	= BAYER_GB;
	
	m_dRatioR		= 1.0;
	m_dRatioG		= 1.0;
	m_dRatioB		= 1.0;
	
	m_nMaxWidth		= 0;
	m_nMaxHeight	= 0;

	m_nScreenWidth	= 0;
	m_nScreenHeight = 0;
	m_nScreenBits	= 0;

	m_pBmpInfo		= (BITMAPINFO *)m_chBmpBuf;

	m_hPalette		= NULL;
	m_hOldPal		= NULL;

	m_dwCount		= 0;
	m_dwStart		= 0;

	m_nMarginLeft	= 0;
	m_nMarginTop	= 0;
	m_nMarginRight	= 0;
	m_nMarginBottom	= 0;
	
	m_bMinimized	= FALSE;
	m_bSnapping		= FALSE;

	//��ɫ��ֵ��
	for(i=0;i<256;i++)
	{
		m_pLutGamma[i] = i;		

		m_pLutR[i] = i;
		m_pLutG[i] = i;
		m_pLutB[i] = i;	
	}
	m_bIsGammaCorrect = FALSE;
	m_dGammRatio = 1.0;

	//ӳ���ļ����
	m_hFileMapping = NULL;
	m_pLutMapping = NULL;;

	m_ExposureMode = SIMULTANEITY;
	m_lTintUpper =60;
	m_lTintLower = 1000;
	m_ConversionType = BAYER2RGB_NEIGHBOUR1;

	m_bIsToGetBadPixel = FALSE;
	m_bIsToRemoveBadPixel = FALSE;
	m_bIsToGetTemplate = FALSE;
	m_bIsTemplateCorrect = FALSE;
	m_nTempTimes =0;

	m_SnapSpeed = HIGH_SPEED;
	m_nHBlanking = 0;
	m_nVBlanking = 0;

	m_bIsSnapSpeedSprted = FALSE;		//��������Ƿ�֧�����òɼ��ٶ�
	m_bIsBlkSizeSprted = FALSE;			//��������Ƿ�֧������ȡ������ȡֵ��Χ	
	m_bIsExposureModeSprted = FALSE;	//��������Ƿ�֧�������ع�ģʽ
}



CMainFrame::~CMainFrame()
{
	if (m_pImageBuffer) {
		delete []m_pImageBuffer;
	}
	if (m_pRawBuffer) {
		delete []m_pRawBuffer;
	}
	if (m_hPalette) {
		DeleteObject(m_hPalette);
	}

	if(m_pLutMapping)
	{
		// �ӽ��̵ĵ�ַ�ռ䳷���ļ�����ӳ��
		UnmapViewOfFile(m_pLutMapping);		
	}
	if(m_hFileMapping)
	{
		// �ر��ļ�ӳ�����
		CloseHandle(m_hFileMapping);
	}

	if(m_pPatternBuf)
	{
		delete[] m_pPatternBuf;
	}
	if(m_pBadPixelBuf)
	{
		delete[] m_pBadPixelBuf;
	}

}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here	
	CString strTitle;
	strTitle.Format("%s Viewer [%d x %d]", m_strDeviceType, m_rcOutputWindow.Width(), m_rcOutputWindow.Height());
	SetWindowText(strTitle);	
	// Do not call CFrameWnd::OnPaint() for painting messages
}

void CMainFrame::AdjustHBlanking()
{
	int size = sizeof(HVTYPE);
	HVTYPE type;
	HVGetDeviceInfo(m_hhv,DESC_DEVICE_TYPE, &type, &size);	
	if(type == GV400UMTYPE || type == GV400UCTYPE)
	{
		int rate = 0;
		switch(m_Resolution)
		{
		case RES_MODE0:
			rate = 1;
			break;
		case RES_MODE1:
			rate = 2;
			break;
		default:
			break;
		}
		if (m_nHBlanking + m_rcOutputWindow.Width()*rate <= 0x236)
		{
			//ȡ�������ı߽�ֵ
			DWORD pBlankSize[4];
			int nBufSize = 0;
			int nHmin = 0;
			int nHmax = 0;
			HVGetDeviceInfo(m_hhv,DESC_DEVICE_BLANKSIZE,NULL,&nBufSize);	
			HVGetDeviceInfo(m_hhv,DESC_DEVICE_BLANKSIZE,pBlankSize,&nBufSize);	
			nHmin = (int)pBlankSize[0];
			nHmax = (int)pBlankSize[2];
			int tHor = 0x236-m_rcOutputWindow.Width()*rate+1;
			m_nHBlanking = max(nHmin,min(tHor, nHmax));
			HVSetBlanking(m_hhv,m_nHBlanking,m_nVBlanking);
		}			
	}
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);	

	// TODO: Add your message handler code here
	CView *pView = GetActiveView();
	if (pView){
		CRect rcClient;
		pView->GetClientRect(rcClient);
		m_rcOutputWindow = rcClient;
		//The video output window is invalid , and then adjust it
		m_rcOutputWindow.right	-= rcClient.Width() %4;
		m_rcOutputWindow.bottom -= rcClient.Height() % 2;

		//�������������ǰ��ֹͣ�ɼ�
		if (m_bSnapping)
		{
			HVStopSnap(m_hhv);
		}

		AdjustHBlanking();

		HVSTATUS status = HVSetOutputWindow(m_hhv, 
									m_rcOutputWindow.left,
									m_rcOutputWindow.top,
									m_rcOutputWindow.Width(),
									m_rcOutputWindow.Height()			
									);  
		//������������ں󣬿�ʼ�ɼ�
		if (m_bSnapping)
		{
			//ֻ����һ��������,
			BYTE * ppBuffer[1];
			ppBuffer[0] = m_pRawBuffer;
			status = HVStartSnap(m_hhv,ppBuffer,1);	
		}

		HV_VERIFY(status);
		TRACE("%d : %d\n", m_rcOutputWindow.Width(), m_rcOutputWindow.Height());
		
		//Reset frame count
		m_dwCount = 0;
		m_dwStart = GetTickCount();
		
		//When outputwindow changes, change the exposure 
		SetExposureTime(GetOutputWinWdith(),m_lTintUpper,m_lTintLower);

	}  
}




void CMainFrame::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	int nMaxWidth = 0, nMaxHeight = 0;
	
	CFrameWnd::OnWindowPosChanging(lpwndpos);
	
	// TODO: Add your message handler code here
	TRACE("Call OnWindowPosChanging \n");
	
	if (m_Resolution == RES_MODE0){
		nMaxWidth	= m_nScreenWidth - m_nMarginLeft - m_nMarginRight;
		nMaxHeight	= m_nScreenHeight - m_nMarginTop - m_nMarginBottom;
	}
	else{
		nMaxWidth	= m_nMaxWidth;
		nMaxHeight	= m_nMaxHeight;
	}
	
	if ( IsIconic()) {
		m_bMinimized = TRUE;	
	}
	else{
		if (IsZoomed()) {
			if (m_Resolution == RES_MODE0){
				lpwndpos->x		= 0;
				lpwndpos->y		= 0;
			}
			lpwndpos->cx	= nMaxWidth + m_nMarginLeft + m_nMarginRight;
			lpwndpos->cy	= nMaxHeight + m_nMarginTop + m_nMarginBottom;
		}
		
		if (m_bMinimized ) {
			m_bMinimized = FALSE;
		}
		else {
			if ((lpwndpos->cx - m_nMarginLeft - m_nMarginRight) > m_nMaxWidth) {
				lpwndpos->cx = m_nMaxWidth + m_nMarginLeft + m_nMarginRight;
			}
			lpwndpos->cx -= (lpwndpos->cx - m_nMarginLeft - m_nMarginRight) % 4;	
			TRACE("cx : %d, cy : %d \n", lpwndpos->cx, lpwndpos->cy);
			
			if ((lpwndpos->cy - m_nMarginTop - m_nMarginBottom) > m_nMaxHeight) {
				lpwndpos->cy = m_nMaxHeight + m_nMarginTop + m_nMarginBottom;
			}
			lpwndpos->cy -= (lpwndpos->cy - m_nMarginTop - m_nMarginBottom) % 2;
		}
	}

}



void CMainFrame::UpdateMargin()
{
	CRect rcView, rcFrame;

	CView *pView = GetActiveView();
	if(pView){
		pView->GetClientRect(&rcView);
		pView->ClientToScreen(&rcView);
		
		GetWindowRect(&rcFrame);
		
		m_nMarginLeft	= rcView.left - rcFrame.left;
		m_nMarginTop	= rcView.top - rcFrame.top;
		m_nMarginRight	= rcFrame.right - rcView.right;
		m_nMarginBottom = rcFrame.bottom - rcView.bottom;		
	}
}




void CMainFrame::AdjustWindow()
{
	CRect rcFrame;
	GetWindowRect(&rcFrame);
	MoveWindow(&rcFrame);
}





void CMainFrame::InitParamFromINI()
{
	int n = 0;

	m_Resolution	= (HV_RESOLUTION)GetPrivateProfileInt("Video Parameter", "Resolution", RES_MODE0, "MVViewer.ini" );

	m_SnapMode	= (HV_SNAP_MODE)GetPrivateProfileInt("Video Parameter", "SnapMode", CONTINUATION, "MVViewer.ini" );
	
	m_ImageMode		= (HV_IMAGE_MODE)GetPrivateProfileInt("Video Parameter", "ImageMode", HV_COLOR, "MVViewer.ini" );
	
	m_Layout	= (HV_BAYER_LAYOUT)GetPrivateProfileInt("Video Parameter", "BayerLayout", BAYER_GR, "MVViewer.ini" );

	m_lTintUpper	= (long)GetPrivateProfileInt("Video Parameter", "TintUpper", 60, "MVViewer.ini" );
	m_lTintLower	= (long)GetPrivateProfileInt("Video Parameter", "TintLower", 1000, "MVViewer.ini" );

	m_lADCLevel	= (long)GetPrivateProfileInt("Video Parameter", "ADCLevel", ADC_LEVEL1, "MVViewer.ini" );
	
	m_lGain[0]	= (long)GetPrivateProfileInt("Video Parameter", "GainRCh", 8, "MVViewer.ini" );
	m_lGain[1]	= (long)GetPrivateProfileInt("Video Parameter", "GainRChG", 8, "MVViewer.ini" );
	m_lGain[2]	= (long)GetPrivateProfileInt("Video Parameter", "GainBChG", 8, "MVViewer.ini" );
	m_lGain[3]	= (long)GetPrivateProfileInt("Video Parameter", "GainBCh", 8, "MVViewer.ini" );
	
	n = GetPrivateProfileInt("Video Parameter", "RatioRL", 0, "MVViewer.ini" );
	CopyMemory(&m_dRatioR, &n, sizeof(int));
	n = GetPrivateProfileInt("Video Parameter", "RatioRH", 0, "MVViewer.ini" );
	CopyMemory((char *)&m_dRatioR + sizeof(int), &n, sizeof(int));

	n = GetPrivateProfileInt("Video Parameter", "RatioGL", 0, "MVViewer.ini" );
	CopyMemory(&m_dRatioG, &n, sizeof(int));
	n = GetPrivateProfileInt("Video Parameter", "RatioGH", 0, "MVViewer.ini" );
	CopyMemory((char *)&m_dRatioG + sizeof(int), &n, sizeof(int));

	n = GetPrivateProfileInt("Video Parameter", "RatioBL", 0, "MVViewer.ini" );
	CopyMemory(&m_dRatioB, &n, sizeof(int));
	n = GetPrivateProfileInt("Video Parameter", "RatioBH", 0, "MVViewer.ini" );
	CopyMemory((char *)&m_dRatioB + sizeof(int), &n, sizeof(int));

	m_nHBlanking	= (long)GetPrivateProfileInt("Video Parameter", "HBlanking", 0, "MVViewer.ini" );
	m_nVBlanking	= (long)GetPrivateProfileInt("Video Parameter", "VBlanking", 0, "MVViewer.ini" );
	m_SnapSpeed =  (HV_SNAP_SPEED )GetPrivateProfileInt("Video Parameter", "SnapSpeed", HIGH_SPEED, "MVViewer.ini" );
	m_ExposureMode  = (HV_EXPOSURE_MODE)GetPrivateProfileInt("Video Parameter", "ExposureMode", SIMULTANEITY, "MVViewer.ini" );
}




void CMainFrame::SaveParamToINI()
{
	CString strValue;

	strValue.Format("%d", m_Resolution);
	WritePrivateProfileString("Video Parameter", "Resolution", strValue, "MVViewer.ini");

	strValue.Format("%d", m_SnapMode);
	WritePrivateProfileString("Video Parameter", "SnapMode", strValue, "MVViewer.ini");

	strValue.Format("%d", m_ImageMode);
	WritePrivateProfileString("Video Parameter", "ImageMode", strValue, "MVViewer.ini");
	strValue.Format("%d", m_Layout);
	WritePrivateProfileString("Video Parameter", "BayerLayout", strValue, "MVViewer.ini");
	
	strValue.Format("%d", m_lTintLower);
	WritePrivateProfileString("Video Parameter", "TintLower", strValue, "MVViewer.ini");

	strValue.Format("%d", m_lTintUpper);
	WritePrivateProfileString("Video Parameter", "TintUpper", strValue, "MVViewer.ini");

	strValue.Format("%d", m_lADCLevel);
	WritePrivateProfileString("Video Parameter", "ADCLevel", strValue, "MVViewer.ini");

	strValue.Format("%d", m_lGain[0]);
	WritePrivateProfileString("Video Parameter", "GainRCh", strValue, "MVViewer.ini");
	strValue.Format("%d", m_lGain[1]);
	WritePrivateProfileString("Video Parameter", "GainRChG", strValue, "MVViewer.ini");
	strValue.Format("%d", m_lGain[2]);
	WritePrivateProfileString("Video Parameter", "GainBChG", strValue, "MVViewer.ini");
	strValue.Format("%d", m_lGain[3]);
	WritePrivateProfileString("Video Parameter", "GainBCh", strValue, "MVViewer.ini");

	strValue.Format("%d", *((int *)&m_dRatioR));
	WritePrivateProfileString("Video Parameter", "RatioRL", strValue, "MVViewer.ini");
	strValue.Format("%d", *((int *)&m_dRatioR + 1));
	WritePrivateProfileString("Video Parameter", "RatioRH", strValue, "MVViewer.ini");

	strValue.Format("%d", *((int *)&m_dRatioG));
	WritePrivateProfileString("Video Parameter", "RatioGL", strValue, "MVViewer.ini");
	strValue.Format("%d", *((int *)&m_dRatioG + 1));
	WritePrivateProfileString("Video Parameter", "RatioGH", strValue, "MVViewer.ini");

	strValue.Format("%d", *((int *)&m_dRatioB));
	WritePrivateProfileString("Video Parameter", "RatioBL", strValue, "MVViewer.ini");
	strValue.Format("%d", *((int *)&m_dRatioB + 1));
	WritePrivateProfileString("Video Parameter", "RatioBH", strValue, "MVViewer.ini");

	strValue.Format("%d", m_nHBlanking);
	WritePrivateProfileString("Video Parameter", "HBlanking", strValue, "MVViewer.ini");
	strValue.Format("%d", m_nVBlanking);
	WritePrivateProfileString("Video Parameter", "VBlanking", strValue, "MVViewer.ini");

	strValue.Format("%d", m_SnapSpeed);
	WritePrivateProfileString("Video Parameter", "SnapSpeed", strValue, "MVViewer.ini");	

	strValue.Format("%d", m_ExposureMode);
	WritePrivateProfileString("Video Parameter", "ExposureMode", strValue, "MVViewer.ini" );
}




void CMainFrame::InitSystemInfo()
{
	CDC *pDC = NULL;
	CView *pView = NULL;

	LOGPALETTE *pLGPal = NULL;
	BYTE Palbuf[2048];

	int i = 0;

	pDC = GetDC();
	if (pDC != NULL) {
		m_nScreenWidth	= pDC->GetDeviceCaps(HORZRES);
		m_nScreenHeight	= pDC->GetDeviceCaps(VERTRES);
		m_nScreenBits	= pDC->GetDeviceCaps(PLANES) * pDC->GetDeviceCaps(BITSPIXEL);
		
		pLGPal					= (LOGPALETTE *)Palbuf;
		pLGPal->palVersion		= 0x300;
		pLGPal->palNumEntries	= 256;
		for (i = 0; i < pLGPal->palNumEntries; i++){
			pLGPal->palPalEntry[i].peRed	= (BYTE)i + 10;
			pLGPal->palPalEntry[i].peGreen	= (BYTE)i + 10;
			pLGPal->palPalEntry[i].peBlue	= (BYTE)i + 10;
			pLGPal->palPalEntry[i].peFlags	= 0;		//PC_NOCOLLAPSE;
		}
		m_hPalette = ::CreatePalette(pLGPal);

		ReleaseDC(pDC);
		pDC = NULL;
	}
	
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biWidth			= 0;
	m_pBmpInfo->bmiHeader.biHeight			= 0;
	m_pBmpInfo->bmiHeader.biPlanes			= 1;
	m_pBmpInfo->bmiHeader.biBitCount		= 0;
	m_pBmpInfo->bmiHeader.biCompression		= BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage		= 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biClrUsed			= 0;
	m_pBmpInfo->bmiHeader.biClrImportant	= 0;

	for (i = 0; i < 256; i++){
		m_pBmpInfo->bmiColors[i].rgbBlue		= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbGreen		= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbRed			= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbReserved	= 0;	
	}

}




void CMainFrame::InitHVDevice()
{
	if(m_hhv == NULL) return;

	//get the max size of the output window
	int nBuffSize = 0;
	HVSTATUS status = HVGetDeviceInfo(m_hhv, DESC_RESOLUTION, NULL,&nBuffSize);	
	if( !HV_SUCCESS(status))
		return;

	BYTE *pbContext = new BYTE[nBuffSize];
	DWORD *pdContext = (DWORD *)(pbContext);
	status = HVGetDeviceInfo(m_hhv, DESC_RESOLUTION, pdContext,&nBuffSize);	
	m_nMaxWidth = *(pdContext + 2 * m_Resolution);
	m_nMaxHeight = *(pdContext + 2* m_Resolution + 1);

	int nMaxWidMd0 = *(pdContext + 2*RES_MODE0);
	int nMaxHeiMd0 = *(pdContext + 2*RES_MODE0 +1);
	delete []pbContext;

	int size = sizeof(HVTYPE);
	HVTYPE type;
	HVGetDeviceInfo(m_hhv,DESC_DEVICE_TYPE, &type, &size);
	if (type != HV1300UCTYPE && type != HV2000UCTYPE)
	{
		m_bIsSnapSpeedSprted = TRUE;		//��������Ƿ�֧�����òɼ��ٶ�
		m_bIsBlkSizeSprted = TRUE;			//��������Ƿ�֧������ȡ������ȡֵ��Χ	

	}
	if (type == GV400UMTYPE || type == GV400UCTYPE)
	{
		m_bIsExposureModeSprted = TRUE;//��������Ƿ�֧�������ع�ģʽ

		CMenu*  pmenu = GetMenu()->GetSubMenu(1); 
		pmenu->EnableMenuItem(ID_VIEW_MODE2, MF_DISABLED|MF_GRAYED); //GV400Ux��֧��mode2
	}
	
	HVSetResolution(m_hhv, m_Resolution);
	HVSetSnapMode(m_hhv, m_SnapMode);
	HVSetBlanking(m_hhv,m_nHBlanking,m_nVBlanking);
	AdjustHBlanking();
	HVSetOutputWindow(m_hhv, 0, 0, m_nMaxWidth, m_nMaxHeight);
	if(m_bIsSnapSpeedSprted)
		HVSetSnapSpeed(m_hhv,m_SnapSpeed);
	
	for (int i = 0; i < 4; i++){
		HVAGCControl(m_hhv, RED_CHANNEL + i, m_lGain[i]);
	}

	HVADCControl(m_hhv, ADC_BITS, m_lADCLevel);

	//�����ع�ģʽ
	if(m_bIsExposureModeSprted)
	{
		int nlength = sizeof(m_ExposureMode);
		HVCommand(m_hhv,CMD_SET_EXPOSURE_MODE, &m_ExposureMode, &nlength);
	}
	//�����ع�ʱ��
	SetExposureTime(m_nMaxWidth,m_lTintUpper,m_lTintLower);

	//��ʼ�����ұ�
	SetLutTable(m_dRatioR,m_dRatioG,m_dRatioB);	

	//allocate the memeor accord to the resolution fo RES_MODE0
	m_pImageBuffer = new BYTE[nMaxWidMd0 * nMaxHeiMd0 * 3];

	if (m_pImageBuffer) {
		FillMemory(m_pImageBuffer, nMaxWidMd0 * nMaxHeiMd0  * 3, 0xff);
	}
	
	m_pRawBuffer = new BYTE[nMaxWidMd0 * nMaxHeiMd0 ];
	if (m_pRawBuffer) {
		FillMemory(m_pRawBuffer, nMaxWidMd0 * nMaxHeiMd0 , 0xff);
	}


	m_pPatternBuf = new int [nMaxWidMd0 * nMaxHeiMd0 ];  
	if (m_pPatternBuf) {
		FillMemory(m_pPatternBuf, nMaxWidMd0 * nMaxHeiMd0*sizeof(int) , 0x00);
	}
	m_pBadPixelBuf = new BYTE[nMaxWidMd0 * nMaxHeiMd0 ];  
	if (m_pBadPixelBuf) {
		FillMemory(m_pBadPixelBuf, nMaxWidMd0 * nMaxHeiMd0 , 0xff);
	}

}

/*
����:
		SetExposureTime
�������:
		int nWindWidth			��ǰͼ����		
		int lTintUpper			�ع�ʱ��ķ��ӣ�shutter��ȡֵ
		int lTintLower			�ع�ʱ��ķ�ĸ����shutter�ĵ�λ���
								��ms:1000��s:1��
�������:
		��						
˵��:
		�����ع�ʱ�䣨�����Ĳ����������ʱ��Ƶ�ʣ�����ֵ��ȡĬ��ֵ��
*/

void CMainFrame::SetExposureTime(int nWindWidth,long lTintUpper,long lTintLower)
{
	int size = sizeof(HVTYPE);
	HVTYPE type;
	HVGetDeviceInfo(m_hhv,DESC_DEVICE_TYPE, &type, &size);	
	
	//��ο��ع�ϵ��ת����ʽ
	int nOutputWid;
	long lClockFreq; 
	double dExposure = 0.0;
	double dTint = max((double)lTintUpper/(double)lTintLower,MY_ZERO);
	if (type == GV400UMTYPE || type == GV400UCTYPE)
	{
		long rate = 0;
		switch(m_Resolution)
		{
		case RES_MODE0:
			rate = 1;
			break;
		case RES_MODE1:
			rate = 2;
			break;
		default:
			return;
		}
		nOutputWid = nWindWidth*rate;
		lClockFreq = (m_SnapSpeed == HIGH_SPEED)? 26600000:13300000; 
		long lTb = m_nHBlanking;
		lTb += 0x5e;
		if(lTb <= 0) lTb =0;
		if (dTint* lClockFreq <= ((double)nOutputWid + lTb - 255))
		{
			dExposure = 1;
		}
		dExposure = (dTint* lClockFreq - ((double)nOutputWid + lTb - 255))/((double)nOutputWid + lTb);
		if (dExposure > 32767) 
			dExposure = 32767;
	}
	else
	{
		nOutputWid = nWindWidth;
		lClockFreq = (m_SnapSpeed == HIGH_SPEED)? 24000000:12000000; 
		if(type == HV1300UCTYPE || type == HV1301UCTYPE)	
		{
			if(type == HV1300UCTYPE) 
				lClockFreq = 24000000;   //HV1300UCTYPE �ݲ�֧�ָ��������ʱ��Ƶ��
			long lTb = m_nHBlanking;
			lTb -= 10;	
			if(lTb <= 0) lTb =0;
			dExposure = (dTint* lClockFreq + 180.0)/((double)nOutputWid + 244.0 + lTb);
		}
		else
		{
			if(type == HV2000UCTYPE) 
				lClockFreq = 24000000;   //HV2000UCTYPE �ݲ�֧�ָ��������ʱ��Ƶ��	
			
			long lTb = m_nHBlanking;
			lTb += 36;
			if(lTb <= 0) lTb =0;
			dExposure = (dTint* lClockFreq + 180.0)/((double)nOutputWid + 305.0 + lTb) + 1;
		}
		
		if (dExposure > 16383) 
			dExposure = 16383;
	}
	HVAECControl(m_hhv, AEC_EXPOSURE_TIME, (long)dExposure);
	
}
//�����������ͳ�����,
//��Ϊ���ʱ���Ӱ���ع�ʱ��,����ͬʱҪ�����ع�ʱ��
void CMainFrame::SetBlanking(int nHBlanking,int nVBlanking)
{

	DWORD pBlankSize[4];
	int nBufSize = 0;
	int nHmin = -9;
	int nVmin = -9;
	int nHmax = 1930;
	int nVmax = 1930;		

	if(m_bIsBlkSizeSprted)
	{
		HVGetDeviceInfo(m_hhv,DESC_DEVICE_BLANKSIZE,NULL,&nBufSize);	
		HVGetDeviceInfo(m_hhv,DESC_DEVICE_BLANKSIZE,pBlankSize,&nBufSize);	
		
		//�õ������ı߽�ֵ
		nHmin = (int)pBlankSize[0];
		nVmin = (int)pBlankSize[1];
		nHmax = (int)pBlankSize[2];
		nVmax = (int)pBlankSize[3];	
	}

	nHBlanking = max(min(nHmax,nHBlanking),nHmin);
	nVBlanking = max(min(nVmax,nVBlanking),nVmin);

	m_nHBlanking = nHBlanking;
	m_nVBlanking = nVBlanking;

	HVSetBlanking(m_hhv,nHBlanking,nVBlanking);
	SetExposureTime(GetOutputWinWdith(),m_lTintUpper,m_lTintLower);	
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	InitParamFromINI();
	InitSystemInfo();

	//����Ǻڰ�ͼ����Ҫ�������ұ��ӳ���ļ�
	if(m_ImageMode	== HV_BW && m_pLutMapping == NULL)
	{
		char lpStrExePath[MAX_PATH];
		GetModuleFileName(NULL,lpStrExePath,MAX_PATH);	
		CString strPath = CString(lpStrExePath);	
		CString m_strFilePath = strPath.Left(strPath.ReverseFind('\\')) + "\\YUVLut.dat";	
		m_pLutMapping = CreateLutMapFile(m_strFilePath);
	}	

	HVSTATUS status = BeginHVDevice(1, &m_hhv);
	HV_MESSAGE(status);
	if (HV_SUCCESS(status)){
		InitHVDevice();
	}

	HVTYPE type; 	
	int nSize = sizeof(HVTYPE);
	status = HVGetDeviceInfo(m_hhv, DESC_DEVICE_TYPE, &type,&nSize);	

	if ( ! HV_SUCCESS(status)) {
		m_strDeviceType = "HVDevice";
	}
	else{
		switch(type) {
		case HV1300UCTYPE:
			m_strDeviceType = "HV1300UC";
			break;
		case HV2000UCTYPE:
			m_strDeviceType = "HV2000UC";
			break;
		case HV1301UCTYPE:
			m_strDeviceType = "HV1301UC";
			break;			
		default:
			m_strDeviceType = "HVDevice";
			break;
		}
	}
	if (type == GV400UCTYPE || type == GV400UMTYPE)	//GV400UM��GV400UC֧��Bayer��ʽ��ѯ����
	{
		char buffer[16];
		int  nBuffSize;

		status = HVGetDeviceInfo(m_hhv, DESC_DEVICE_BAYER_LAYOUT, NULL, &nBuffSize);	
		if(status == STATUS_OK)
		{
			HVGetDeviceInfo(m_hhv, DESC_DEVICE_BAYER_LAYOUT, buffer, &nBuffSize);	
			m_Layout = (HV_BAYER_LAYOUT)*buffer;
		}
	}

	return 0;
}


void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bSnapping) {
		SendMessage(WM_COMMAND, ID_VIEW_SNAP);
	}

	SaveParamToINI();
	EndHVDevice(m_hhv);
	
	CFrameWnd::OnClose();
}



void CMainFrame::OnViewColor() 
{
	// TODO: Add your command handler code here
	m_ImageMode	= HV_COLOR;
}

void CMainFrame::OnUpdateViewColor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_ImageMode == HV_COLOR);
}

void CMainFrame::OnViewBw() 
{
	// TODO: Add your command handler code here
	m_ImageMode	= HV_BW;

	if(m_pLutMapping == NULL)
	{
		char lpStrExePath[MAX_PATH];
		GetModuleFileName(NULL,lpStrExePath,MAX_PATH);	
		CString strPath = CString(lpStrExePath);	
		CString m_strFilePath = strPath.Left(strPath.ReverseFind('\\')) + "\\YUVLut.dat";	
		m_pLutMapping = CreateLutMapFile(m_strFilePath);
	}

}

void CMainFrame::OnUpdateViewBw(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_ImageMode == HV_BW);

}



void CMainFrame::OnViewConversionBg() 
{
	// TODO: Add your command handler code here
	m_Layout = BAYER_BG;
}

void CMainFrame::OnUpdateViewConversionBg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_Layout == BAYER_BG);
}




void CMainFrame::OnViewConversionGb() 
{
	// TODO: Add your command handler code here
	m_Layout = BAYER_GB;
}

void CMainFrame::OnUpdateViewConversionGb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Layout == BAYER_GB);
}

void CMainFrame::OnViewConversionGr() 
{
	// TODO: Add your command handler code here
	m_Layout = BAYER_GR;
}



void CMainFrame::OnUpdateViewConversionGr(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Layout == BAYER_GR);
}



void CMainFrame::OnViewConversionRg() 
{
	// TODO: Add your command handler code here
	m_Layout = BAYER_RG;
}




void CMainFrame::OnUpdateViewConversionRg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Layout == BAYER_RG);
}




void CMainFrame::OnViewAdjust() 
{
	// TODO: Add your command handler code here
	CAdjustDlg dlg;

	if (dlg.DoModal() == IDOK){
	}
}





void CMainFrame::OnViewSnap() 
{
	// TODO: Add your command handler code here
	HVSTATUS status = STATUS_OK;
	
	if (m_bSnapping) {
		status = HVCloseSnap(m_hhv);
		m_bSnapping = FALSE;
		Invalidate(TRUE);
	}
	else{
		if(m_pImageBuffer && m_pRawBuffer){
			HVSTATUS status = HVOpenSnap(m_hhv, SnapCallback, this);
			if (HV_SUCCESS(status)) {

				//ֻ����һ��������,
				BYTE * ppBuffer[1];
				ppBuffer[0] = m_pRawBuffer;
				status = HVStartSnap(m_hhv,ppBuffer, 1);

				if ( ! HV_SUCCESS(status))
				{
					HVCloseSnap(m_hhv);
				}
				else{
					m_bSnapping	= TRUE;
					m_dwStart	= ::GetTickCount();
					m_dwCount	= 0;
				}
			}
			HV_MESSAGE(status);
		}
	}
}




void CMainFrame::OnUpdateViewSnap(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bSnapping);
}




int CALLBACK CMainFrame::SnapCallback(HV_SNAP_INFO *pInfo)
{
	CMainFrame *pFrame = (CMainFrame *)(pInfo->pParam);
	ASSERT(pFrame);
	
	HVSTATUS status = pFrame->GetLastStatus();	// ��ȡ�����ͼ��ɼ�����״̬
	
	if(!HV_SUCCESS(status)){	//����������ò��ɹ��������ֹͣͼ��ɼ���
		pFrame->PostMessage(WM_SNAP_STOP, 0, 0);
		return 1;
	}
	
	if(pFrame->dwLastStatus == 0)	// ��״ֵ̬����0ʱ����ʾ�����ͼ��ɼ������������SendMessage��ʾͼ��
	{
	   /*
	    *	�����Զ�����ϢWM_SNAP_EX_CHANGE�������ڣ�	
	    *	ͬʱ���뵱ǰ���Դ����ͼ�����
	    *	ע�⣺��SendMessage������Ϣ������ȴ���Ϣ������Ϻ󣬲����˳�����SendMessage����
		*/
		pFrame->SendMessage(WM_CHANGE_SNAP, 0, 0);
		return 1;
		
	}
	else if(pFrame->dwLastStatus == STATUS_FILE_INVALID) // ��״ֵ̬����-18ʱ����ʾ���������һ�ζ�֡��Ϊ
	{
		pFrame->m_nLostNum++;	//��֡����
	}
	else if (pFrame->dwLastStatus==0xc0000012 || pFrame->dwLastStatus==0xc0000011)
	{
		pFrame->m_nErrorNum++;		//�������
	}
	else // ��״ֵ̬Ϊ������0ֵʱ����ʾ�����ͼ��ɼ��쳣�������PostMessage���д���
	{
	   /*
	    *	�����Զ�����Ϣ WM_SNAP_ERROR �������ڣ�	
	    *	ע�⣺��PostMessage������Ϣ�����صȴ���Ϣ�����꣬�Ϳ��Է��ء�
	    */
		pFrame->PostMessage(WM_SNAP_ERROR, 0, pFrame->dwLastStatus);
	}		
	return 1;
}

LRESULT CMainFrame::OnSnapMessage(WPARAM wParam, LPARAM lParam)
{
	float fps = 0;
	CString strTitle;
	
	ShowImage();
	
	m_dwCount++;
	fps = (float)(m_dwCount * 1000) / (::GetTickCount() - m_dwStart + 1);
	strTitle.Format("%s Viewer [%d x %d]  %f(fps)", m_strDeviceType,
		m_pBmpInfo->bmiHeader.biWidth,  m_pBmpInfo->bmiHeader.biHeight, fps);

	if (m_nLostNum > 0 )
	{
		CString str;
		str.Format("    (Lost: %d)",m_nLostNum);
		strTitle += str;
	}
	if (m_nErrorNum > 0 )
	{
		CString str;
		str.Format("    (Error: %d)",m_nErrorNum);
		strTitle += str;
	}
		
	SetWindowText(strTitle);
		
	return 1;
}

void CMainFrame::DecodeImage()
{
	if (m_ImageMode	== HV_COLOR) {
		m_pBmpInfo->bmiHeader.biBitCount = 24;
		CSize Size;
		Size.cx  = m_pBmpInfo->bmiHeader.biWidth;
		Size.cy = m_pBmpInfo->bmiHeader.biHeight;
		
		
		//ÿ��֡����һ��
		if(m_ConversionType != BAYER2RGB_NEIGHBOUR)
		{
			static int nTemp = 1;
			if(nTemp%2 ==0 )
			{
				nTemp =1;
				return;
			}
			else
				nTemp = 2;
		}
		
						
		if(m_bIsToGetBadPixel)
		{
			DetectDeadPixel(m_pRawBuffer,m_pBadPixelBuf,m_nMaxWidth,m_nMaxHeight);
			m_bIsToGetBadPixel = FALSE;

			/*�õ�����λ�ú�,�ָ�ԭ���ɼ�����*/

			//�������������ǰ��ֹͣ�ɼ�
			if (m_bSnapping)
			{
				HVStopSnap(m_hhv);
			}	
			AdjustHBlanking();
			HVSTATUS status = HVSetOutputWindow(m_hhv, 
				m_rcOutputWindow.left,
				m_rcOutputWindow.top,
				m_rcOutputWindow.Width(),
				m_rcOutputWindow.Height()			
				);   
			
			//������������ں󣬿�ʼ�ɼ�
			if (m_bSnapping)
			{
				//ֻ����һ��������,
				BYTE * ppBuffer[1];
				ppBuffer[0] = m_pRawBuffer;
				status = HVStartSnap(m_hhv,ppBuffer,1);	
			}
			
		}

		if(m_bIsToRemoveBadPixel) //ȥ������
		{
			EraseDeadPixel(m_pRawBuffer,m_pBadPixelBuf,m_rcOutputWindow.left,m_rcOutputWindow.top,Size.cx,Size.cy,m_nMaxWidth,m_nMaxHeight);
		}

		if(m_bIsToGetTemplate)
		{
			if(m_nTempTimes ==0)  //��һ������ʱ���������
				memset(m_pPatternBuf,'\0',sizeof(int)*m_nMaxWidth * m_nMaxHeight);
			GetPatternNoise(m_pRawBuffer,m_pPatternBuf,m_nMaxWidth,m_nMaxHeight);
			m_nTempTimes ++ ;
			if(m_nTempTimes >= 10)
			{
				AvgPatternNoise(m_pPatternBuf,m_nMaxWidth,m_nMaxHeight,m_nTempTimes);
				m_bIsToGetTemplate = FALSE;
				m_nTempTimes =0;

				
				/*�õ�ģ���,�ָ�ԭ���ɼ�����*/				
				//�������������ǰ��ֹͣ�ɼ�
				if (m_bSnapping)
				{
					HVStopSnap(m_hhv);
				}		
				AdjustHBlanking();
				HVSTATUS status = HVSetOutputWindow(m_hhv, 
					m_rcOutputWindow.left,
					m_rcOutputWindow.top,
					m_rcOutputWindow.Width(),
					m_rcOutputWindow.Height()			
					);   
				
				//������������ں󣬿�ʼ�ɼ�
				if (m_bSnapping)
				{
					//ֻ����һ��������,
					BYTE * ppBuffer[1];
					ppBuffer[0] = m_pRawBuffer;
					status = HVStartSnap(m_hhv,ppBuffer,1);	
				}
				

			}
		}
		if(m_bIsTemplateCorrect)
		{
			FixPatternNoise(m_pRawBuffer,m_pPatternBuf,m_rcOutputWindow.left,m_rcOutputWindow.top,Size.cx,Size.cy,m_nMaxWidth,m_nMaxHeight);
		}

		ConvertBayer2Rgb(m_pImageBuffer, m_pRawBuffer,Size.cx,Size.cy, m_ConversionType,m_pLutR,m_pLutG,m_pLutB,true,m_Layout);

		
	} 

	else
	{
		m_pBmpInfo->bmiHeader.biBitCount = 8;
		//CopyMemory(m_pImageBuffer, m_pRawBuffer, m_pBmpInfo->bmiHeader.biWidth * m_pBmpInfo->bmiHeader.biHeight);
		
		CSize Size;
		Size.cx  = m_pBmpInfo->bmiHeader.biWidth;
		Size.cy = m_pBmpInfo->bmiHeader.biHeight;	
		ConvertBayer2Rgb(m_pImageBuffer, m_pRawBuffer,Size.cx,Size.cy, m_ConversionType,m_pLutR,m_pLutG,m_pLutB,true,m_Layout);
	
		long lImageSize = m_pBmpInfo->bmiHeader.biWidth * m_pBmpInfo->bmiHeader.biHeight;
		BYTE *pTmpBit8 = new BYTE[lImageSize];
		if(pTmpBit8 == NULL)
			return ;

		//ת����8λ�ڰ�ͼ��
		Format24To8(pTmpBit8,m_pImageBuffer, m_pBmpInfo->bmiHeader.biWidth,m_pBmpInfo->bmiHeader.biHeight);	
		memcpy(m_pImageBuffer,pTmpBit8,lImageSize);

		if(pTmpBit8)
		{
			delete []pTmpBit8;
			pTmpBit8 = NULL;
		}
		
	}
}

void CMainFrame::ShowImage()
{
	CView *pView = NULL;
	CDC *pDC  = NULL;


	pView = GetActiveView();
	ASSERT(pView);
	pDC = pView->GetDC(); //GetDC ����:��ȡ�豸ָ�� pDC���򴫵ݿ���ϵͳ
	ASSERT(pDC);
	
	m_pBmpInfo->bmiHeader.biWidth	= m_rcOutputWindow.Width();
	m_pBmpInfo->bmiHeader.biHeight	= m_rcOutputWindow.Height();	
	DecodeImage();
	

	if (m_hPalette && (m_pBmpInfo->bmiHeader.biBitCount == 8)) {
		m_hOldPal = ::SelectPalette(pDC->GetSafeHdc(), m_hPalette, FALSE);			
		::RealizePalette(pDC->GetSafeHdc());
	}
	
	SetStretchBltMode(pDC->GetSafeHdc(),COLORONCOLOR);
//*************************************************����Ϊ�Լ��Ĳ���*************************************************************//
	if (recognitionFlag)    						       //��־λ:����Recognition����Ŀ��ʶ��
	{
		g_imageWidth = m_pBmpInfo->bmiHeader.biWidth;      //ͼ���� 
	    g_imageHeight = m_pBmpInfo->bmiHeader.biHeight;    //ͼ��߶�
		g_imageRow = m_pBmpInfo->bmiHeader.biWidth;        //һ��ͼ�����ظ���
		ImageProcess(pDC);   							   //ͼ����
	}
//************************************************����Ϊ�Լ��Ĳ���******************************************************************//

	StretchDIBits(pDC->GetSafeHdc(),
		0,
		0,
		m_pBmpInfo->bmiHeader.biWidth,
		m_pBmpInfo->bmiHeader.biHeight,
		0,
		0,
		m_pBmpInfo->bmiHeader.biWidth,
		m_pBmpInfo->bmiHeader.biHeight,
		m_pImageBuffer,
		m_pBmpInfo,
		DIB_RGB_COLORS,
		SRCCOPY
		);	
	
	if (m_hOldPal && (m_pBmpInfo->bmiHeader.biBitCount == 8)) {
		::SelectPalette(pDC->GetSafeHdc(), m_hOldPal, FALSE);
		::RealizePalette(pDC->GetSafeHdc());
	}
//*************************************************����Ϊ�Լ��Ĳ���*************************************************************//
    if (recognitionFlag)
	{
		TargetObject(pDC);   				              //Ŀ���ע
	}
//************************************************����Ϊ�Լ��Ĳ���******************************************************************//

	pView->ReleaseDC(pDC);
}


void CMainFrame::ImageProcess(CDC *pDC)
{
	unsigned int  width = 0;
	unsigned int height = 0;      

	width = g_imageWidth;
	height = g_imageHeight;

	pImageBuffer = new BYTE[width * height];              //Ԥ��ָ������ڴ�
    pImageBuffer0 = new BYTE[width * height];

    GrayOrRGBTo2();         //ͼ��ת������ֵ��
	PreProcess();           //ͼ��Ԥ����
    FindClass();            //������ͨ��
	corrode();				//ͼ��ʴ
	FindClass();			
	ImageRecognize();       //Ŀ��ʶ��
	PourObject();           //Ŀ�����
	delete(pImageBuffer);   //��������
	delete(pImageBuffer0);   //��������
}

///////////////////////////////////////
//������:GrayOrRGBTo2
//�������:��
//�������:��						
//��������:��ͼ����лҶȻ�����ֵ��
///////////////////////////////////////

void CMainFrame::GrayOrRGBTo2()   
{ 
	unsigned int           x = 0;
	unsigned int           y = 0;
    unsigned int    max_gray = 0;
	unsigned int  min_gray = 255;
	unsigned int   threshold = 0;          //��ֵ
	unsigned int bwith = g_imageWidth;
	unsigned int bhight = g_imageHeight;
	
	unsigned int H[256] = {0};            //�Ҷ�ֱ��ͼ
	double sum0 = 0;          			  //ǰ���ҶȺ�
	double sum1 = 0;          			  //�����ҶȺ�

	double N0 = 0;           		      //ǰ��������
	double N1 = 0;          			  //����������

	double u0 = 0;            			  //ƽ���Ҷ� 
	double u1 = 1;

	double w0 = 0;                        //����ռ��
	double w1 = 0;

	double g = -1;            			  //��䷽��
	double max = -1;                      //�����䷽��
	double temp = 0;
	double N = (double)bwith*bhight;

     /*����Ϊͼ��ת�����㷨ʵ�֡��ü�Ȩƽ����ʵ��RGB��ɫ�ռ䵽YUV��ɫ�ռ�ı任����ʽΪ��Y = 0.299*R+0.587*G+0.114*B 
	  *���洢��Ԥ����ڴ���
	  */
	for (x=0;x<g_imageWidth;x++)           
	{
		for (y=0;y<g_imageHeight;y++)
		{
			pImageBuffer[y * g_imageRow + x] = (BYTE)(m_pImageBuffer[(y*g_imageRow+x)*3+0]*0.3          
													 +m_pImageBuffer[(y*g_imageRow+x)*3+1]*0.59
													 +m_pImageBuffer[(y*g_imageRow+x)*3+2]*0.11);
			pImageBuffer0[y * g_imageRow + x] = (BYTE)(m_pImageBuffer[(y*g_imageRow+x)*3+0]*0.3          
													 +m_pImageBuffer[(y*g_imageRow+x)*3+1]*0.59
													 +m_pImageBuffer[(y*g_imageRow+x)*3+2]*0.11);
			H[pImageBuffer[y * g_imageRow + x]]++;                                                    
		}//for����
	}//for����
	
	/*���²���ȷ����ֵ����ֵ*/
	for(int i=0;i<256;i++)
	{
		sum0 = 0;                        
		sum1 = 0;
		N0 += H[i];                      
		N1 = N - N0;
		if(N1 == 0)
		{
			break;
		}

		w0 = N0/N;                       
		w1 =  1-w0;
		for(int j = 0;j<=i;j++)
		{
			sum0 += j*H[j];              
		}
		u0 = sum0/N0;                    
		for(int k = i+1;k<256;k++)
		{
			sum1 += k*H[k];              
		}
		u1 = sum1/N1;                    
		g = w0*w1*(u0-u1)*(u0-u1);       
		if(max<g)
		{
			max = g;
			threshold = i;
		}
	}//for����    

   /*���²���Ϊ��ֵ������*/
	for (x=0;x<g_imageWidth;x++)                 
	{
		for (y=0;y<g_imageHeight;y++)
		{
		    if (pImageBuffer[y*g_imageRow+x] >threshold)
			{
				pImageBuffer[y*g_imageRow+x] = 255;
				pImageBuffer0[y*g_imageRow+x] = 255;
			}
			else
			{
                pImageBuffer[y*g_imageRow+x] = 0;
				pImageBuffer0[y*g_imageRow+x] = 0;
			}
		}//for����
	}//for����
}  

///////////////////////////////////////
//������:PreProcess
//�������:��
//�������:��						
//��������:ͼ��Ԥ��������ȥ��
///////////////////////////////////////
void CMainFrame::PreProcess()
{
	unsigned int             x = 0;
	unsigned int             y = 0;
	unsigned int         width = 0;
	unsigned int        height = 0; 
	unsigned int   pixelCounter = 0;    //�����ںڵ�����ۼ�

	for (x=0;x<g_imageWidth;x++)    
	{
		for (y=0;y<g_imageHeight;y++)
		{
			/*���²���ʵ�ֶ�ͼ���Ե�ĺڵ�����
			*ʵ�ֺڵ������ںڵ���������*/
			if(0 == x || 0 == y)                                     
			{
				pImageBuffer[y*g_imageRow+x] = WHITEPIXEL;
			}
		    if (BLACKPIXEL == pImageBuffer0[y*g_imageRow+x])        
			{
				pixelCounter = 0;                                   
				for (width=x-1;width<=x+1;width++)
				{
					for (height=y-1;height<=y+1;height++)
					{
						if (BLACKPIXEL == pImageBuffer0[height*g_imageRow+width])
						{
							pixelCounter++;
						}
					}//for����
				}//for����
				
				/*����ʵ�ֶ�����������*/
				if (pixelCounter <= 2)    
				{
					pImageBuffer[y*g_imageRow+x] = WHITEPIXEL;
					pImageBuffer0[y*g_imageRow+x] = WHITEPIXEL;
				}
			}//if����
		}//for����
	}//for����
	
	
}

///////////////////////////////////////
//������:FindClass
//�������:��
//�������:��						
//��������:��ͼ���и�����ͨ�������ҳ���
//˵��������˳�򣺴������ң���������
///////////////////////////////////////
void CMainFrame::FindClass()
{
	unsigned int pixelClass = 0;
    unsigned int          x = 0;
	unsigned int          y = 0;
	unsigned int    HeaderX = 0;        //������ʼ�������
	unsigned int    HeaderY = 0;        //������ʼ��������
	unsigned int  classFlag = 0;        //0:��û���ҵ�����ĵ�һ���㣻1�����ҵ��������ʼ�㣬��׼��������ͨ�㣻2�����ҵ�������

	g_classCoordinate[pixelClass][UP] = g_imageHeight-1;
	g_classCoordinate[pixelClass][DOWN] = 1;
	g_classCoordinate[pixelClass][LEFT] = 1;
	g_classCoordinate[pixelClass][RIGHT] = g_imageWidth-1;
	g_targetPixelLeft = 0; 
	g_targetPixelDown = 0;
	while (classFlag != 2)                                       
	{
		/*���²���ʵ�ֲ��ҵ�ǰ�����ʼ�㲢�ж�ͼ�����кڵ��Ƿ�ȫ������
		*������ʼ��ʱÿ��y�����ϸ�������½翪ʼ��Ѱ��x��1��ʼ��Ѱ
		*����MarkerNeighbourhood������Ѱ��ǰ������ĺڵ�
		*/
		if(0 == classFlag)																  
		{           
			pixelClass++;																  
            if (pixelClass > 255)														 
			{
				g_imageClass[0] = 255;
				return;																	  
			}

			/*��������ʵ�ֶԵ�ǰ�����ص�������㼰����߽�ĳ�ʼ��*/
			g_imageClass[pixelClass] = 0;                                                
			g_classCoordinate[pixelClass][UP] = 1;                                       
            g_classCoordinate[pixelClass][DOWN] = g_imageHeight-1;                       
			g_classCoordinate[pixelClass][LEFT] = g_imageWidth-1;                         
			g_classCoordinate[pixelClass][RIGHT] = 1;                                     

			for (y=g_classCoordinate[pixelClass-1][DOWN];y<g_imageHeight-1;y++)          
			{
				for (x=1;x<g_imageWidth-1;x++)                                            
				{
					if (BLACKPIXEL == pImageBuffer[y*g_imageRow+x])                       
					{
						HeaderX = x;                                                       
						HeaderY = y;
						g_classCoordinate[pixelClass][DOWN] = HeaderY;                    
						pImageBuffer[y*g_imageRow+x] = pixelClass;                       
						MarkerNeighbourhood(pixelClass,HeaderX,HeaderY);                  
						classFlag = 1;                                                    
						break;
					}
				}//for x 
				if(1 == classFlag)
				{
					break;     
				}
			}//for y
            if(0 == classFlag)               //ͼ�����кڵ���ѹ���
			{
				pixelClass--;
				g_imageClass[0] = pixelClass;
				classFlag = 2;               //ͼ���ѱ�����ȫ
			}
		}//if����
		
		/*���²���ͨ������ȫͼ�ҵ���ǰ�����ͨ��*/
        else if (1 == classFlag)
		{
		    for (y=g_classCoordinate[pixelClass][DOWN];y<g_imageHeight-1;y++)
			{
				g_rowTargetPixelNum = 0;                                   
				for (x=1;x<g_imageWidth-1;x++)
				{
					if(pixelClass == pImageBuffer[y*g_imageRow+x])       
					{
                        MarkerNeighbourhood(pixelClass,x,y);  
					}
					if (1 == g_targetPixelLeft)
					{
						x = 1;
						g_targetPixelLeft = 0;
					}
					if (1 == g_targetPixelDown)
					{
						y = y - 1;
						x = 1;
						if (y < 1)
						{
							y = 1;
						}
						g_targetPixelDown = 0;
					}
				}//for x����
			}//for y����
			classFlag = 0;           
		}//else if����
	}//while����
}


///////////////////////////////////////
//������:MarkerNeighbourhood
//�������:unsigned int pixelClass��ʾ��ǰ������
///////////unsigned int width��ʾ��ǰ���x
///////////unsigned int height��ʾ��ǰ���y
//�������:��						
//��������:��Ѱ��ǰ������(��������������)�ĺڵ㣬���Ҳ����Ϊ��ǰ����Ԫ��
///////////ͬʱͨ������UpdateBound����ʵ�ֶԱ߽�ĸ���
///////////////////////////////////////
void CMainFrame::MarkerNeighbourhood(unsigned int pixelClass,unsigned int width,unsigned int height)  
{
    unsigned int x = 0;
    unsigned int y = 0;

	x = width;
	y = height;

	g_rowTargetPixelNum++;                                     //��ǰ��Ŀ����ۼ�
	UpdateBound(pixelClass,width,height);                      

	if (BLACKPIXEL == pImageBuffer[(y-1)*g_imageRow+x])        
	{
		pImageBuffer[(y-1)*g_imageRow+x] = pixelClass;
		g_targetPixelDown = 1;                                 
	}
	if (BLACKPIXEL == pImageBuffer[(y+1)*g_imageRow+x])        
	{
		pImageBuffer[(y+1)*g_imageRow+x] = pixelClass;
	}
	if (BLACKPIXEL == pImageBuffer[y*g_imageRow+x-1])          
	{
		pImageBuffer[y*g_imageRow+x-1] = pixelClass;
		g_targetPixelDown = 1;
	}
	if (BLACKPIXEL == pImageBuffer[y*g_imageRow+x+1])         
	{
		pImageBuffer[y*g_imageRow+x+1] = pixelClass;
	}
}


///////////////////////////////////////
//������:UpdateBound
//�������:unsigned int pixelClass��ʾ��ǰ������
///////////unsigned int width��ʾ��ǰ���x
///////////unsigned int height��ʾ��ǰ���y
//�������:��						
//��������:��ǰ��Ϊ�����еĵ�ʱ���ж����Ƿ�Ϊ����߽�㲢���±߽�
///////////////////////////////////////
void CMainFrame::UpdateBound(unsigned int pixelClass,unsigned int width,unsigned int height)
{
	if (width < g_classCoordinate[pixelClass][LEFT])
	{
		g_classCoordinate[pixelClass][LEFT] = width;             
	}
	else if (width > g_classCoordinate[pixelClass][RIGHT])
	{
		g_classCoordinate[pixelClass][RIGHT] = width;            
	}

    if (height > g_classCoordinate[pixelClass][UP])          
	{ 
	   	g_classCoordinate[pixelClass][UP] = height;              
	}
}

///////////////////////////////////////
//������:UpdateBound
//�������:��
//�������:��						
//��������:ͳ�Ƹ������жϲ���ʴͼ��ȥճ����
///////////////////////////////////////
void CMainFrame::corrode()
{
	unsigned int        width = 0;
	unsigned int       height = 0;
    unsigned int   pixelClass = 0;
	unsigned int pixelCounter = 0;
	unsigned int   x,y;

	/*���²���ʵ�ֶ����ҵ�������Ŀ���ĸ�������ͳ��*/
	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)   
	{
		g_imageClass[pixelClass] = 0;
		for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)   
		{
			for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
			{
				if (pixelClass == pImageBuffer[height*g_imageRow+width])       
				{
					g_imageClass[pixelClass]++; 
				}
			}
		}
	
	/*���²���ʵ�ֶ������ݶ�����һ��Ĳ��ֽ��и�ʴ
	*ʵ�ַ��������������ҽ���8���ڵ㣨�������������������*/
	if((g_imageClass[pixelClass]>700)&&(g_imageClass[pixelClass]<2500))  
	{
		for (int a=0;a<=2;a++)
		{
			for (x=g_classCoordinate[pixelClass][LEFT];x<g_classCoordinate[pixelClass][RIGHT];x++)    
			{
				for (y=g_classCoordinate[pixelClass][DOWN];y<g_classCoordinate[pixelClass][UP];y++)
				{
				   if (pImageBuffer0[y*g_imageRow+x]<128)         
					{
						pixelCounter = 0;                                   
						for (width=x-1;width<=x+1;width++)
						{
							for (height=y-1;height<=y+1;height++)
							{
								if (pImageBuffer0[height*g_imageRow+width]<128)
								{
									pixelCounter++;
								}
							}//for����
						}//for����
						if (pixelCounter < 9)    
						{
							pImageBuffer[y*g_imageRow+x] = WHITEPIXEL;
						}
					}//if����
				}//for����
			}//for����
			for (x=1;x<g_imageWidth-1;x++)    
			{
				for (y=1;y<g_imageHeight-1;y++)
				{
					pImageBuffer0[y*g_imageRow+x] = pImageBuffer[y*g_imageRow+x]; 
				}
			}
		}
	}

	}//for����


	for (x=0;x<g_imageWidth;x++)           
	{
		for (y=0;y<g_imageHeight;y++)
		{
			if(pImageBuffer[y*g_imageRow+x]<128)
			{
				pImageBuffer[y*g_imageRow+x] = BLACKPIXEL;
			}
		}
	}
	
}
	

///////////////////////////////////////
//������:ImageRecognize
//�������:��
//�������:��						
//��������:Ŀ��ʶ��
///////////////////////////////////////
void CMainFrame::ImageRecognize()
{
	unsigned int        width = 0;
	unsigned int       height = 0;
    unsigned int   pixelClass = 0;
	unsigned int pixelCounter = 0;
	float             centerX = 0;
	float             centerY = 0;

	g_objectNum[SCREW] = 0;
	g_objectNum[NUT] = 0;
	g_objectNum[COIN] = 0;
	/*���²���ʵ�ֶԸ���Ŀ����������Ե�򳤿�ȡ����ĻҶ�ֵ����Ե����Ŀ����ռ�����������ռ�ձȣ��ļ���
	*ͬʱ���ݶ�����ĸ����Ч�����ʶ��*/
	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)    
	{
		g_imageClass[pixelClass] = 0;
		for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)   
		{
			for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
			{
				if (pixelClass == pImageBuffer[height*g_imageRow+width])       
				{
					g_imageClass[pixelClass]++; 
				}
			}
		}
		if (g_imageClass[pixelClass] >100 && g_imageClass[pixelClass] < 20000)         
		{
			g_imageClassInfo[pixelClass].length = (unsigned int)(g_classCoordinate[pixelClass][RIGHT] - g_classCoordinate[pixelClass][LEFT]);
			g_imageClassInfo[pixelClass].wide = (unsigned int)(g_classCoordinate[pixelClass][UP] - g_classCoordinate[pixelClass][DOWN]);
			if (g_imageClassInfo[pixelClass].length > 0 && g_imageClassInfo[pixelClass].wide > 0)
			{
				if (g_imageClassInfo[pixelClass].length >g_imageClassInfo[pixelClass].wide)
				{
					g_imageClassInfo[pixelClass].lengthToWide = (float)((float)g_imageClassInfo[pixelClass].length/(float)g_imageClassInfo[pixelClass].wide);     
				}
				else
				{
					g_imageClassInfo[pixelClass].lengthToWide = (float)((float)g_imageClassInfo[pixelClass].wide/(float)g_imageClassInfo[pixelClass].length);     
				}
				g_imageClassInfo[pixelClass].classDuty = (float)((float)g_imageClass[pixelClass]/((float)g_imageClassInfo[pixelClass].length*(float)g_imageClassInfo[pixelClass].wide));    
				centerX = 0;
				centerY = 0;
				g_imageClassInfo[pixelClass].centerX = 0;
				g_imageClassInfo[pixelClass].centerY = 0;
				centerX = (float)(g_classCoordinate[pixelClass][LEFT] + g_classCoordinate[pixelClass][RIGHT])/2;
				centerY = (float)(g_classCoordinate[pixelClass][UP] + g_classCoordinate[pixelClass][DOWN])/2;
				g_imageClassInfo[pixelClass].centerX = (unsigned int)(centerX);
				g_imageClassInfo[pixelClass].centerY = (unsigned int)(centerY);
				g_imageClassInfo[pixelClass].grayOfCenter = (BYTE)((float)pImageBuffer[g_imageClassInfo[pixelClass].centerY*g_imageRow+g_imageClassInfo[pixelClass].centerX] * 0.2            
																 + (float)pImageBuffer[g_imageClassInfo[pixelClass].centerY*g_imageRow+g_imageClassInfo[pixelClass].centerX+1] * 0.2
																 + (float)pImageBuffer[g_imageClassInfo[pixelClass].centerY*g_imageRow+g_imageClassInfo[pixelClass].centerX-1] * 0.2
					                                             + (float)pImageBuffer[(g_imageClassInfo[pixelClass].centerY+1)*g_imageRow+g_imageClassInfo[pixelClass].centerX] * 0.2
																 + (float)pImageBuffer[(g_imageClassInfo[pixelClass].centerY-1)*g_imageRow+g_imageClassInfo[pixelClass].centerX] * 0.2);//���ĵ�Ҷ�ֵȡ���������Ҽӱ���������ƽ��ֵ
			   

				if ((g_imageClassInfo[pixelClass].grayOfCenter > 128)&&(g_imageClassInfo[pixelClass].lengthToWide<1.2)&&(g_imageClass[pixelClass] <2000))
				{
					g_classCategory[pixelClass] = NUT;                     //ʶ����ĸ
					g_objectNum[NUT]++;
				}
				else if(g_imageClass[pixelClass] <1500)
				{
					g_classCategory[pixelClass] = SCREW;                    //ʶ���ݶ�
					g_objectNum[SCREW]++;	
				}
				else 
				{
                    g_classCategory[pixelClass] = INVALID;                 //��Ч��
				}
			}//if����
			else 
			{
				g_imageClassInfo[pixelClass].lengthToWide = 0;
                g_imageClassInfo[pixelClass].classDuty = 0;
				g_imageClassInfo[pixelClass].centerX = 0;
				g_imageClassInfo[pixelClass].centerY = 0;
				g_imageClassInfo[pixelClass].grayOfCenter = 125;
				g_classCategory[pixelClass] = INVALID;         			  //��Ч��
			}
		}//if����
		else
		{
			g_classCategory[pixelClass] = INVALID;
		}
	}//for count����
}

///////////////////////////////////////////
//������:PourObject
//�������:��
//�������:��						
//��������:��ԭͼ���ж���ȷ����Ŀ��������
///////////////////////////////////////////
void CMainFrame::PourObject()
{
    unsigned int pixelClass = 0;               
    unsigned int      count = 0;
	unsigned int      width = 0;
	unsigned int     height = 0;

	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)
	{
		/* ��Ѱ�ݶ�������ĳ���ɫ*/
        if (SCREW == g_classCategory[pixelClass])         
		{
            for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)   
			{
				for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
				{
					if (pixelClass == pImageBuffer[height*g_imageRow+width])      
					{
						m_pImageBuffer[(height*g_imageRow+width)*3+0] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+1] = 255;
						m_pImageBuffer[(height*g_imageRow+width)*3+2] = 0;
					}
				}//for height����
			}//for width����
		}//if SCREW����
		/* ��Ѱ��ĸ������ĳɺ�ɫ*/
		else if(NUT == g_classCategory[pixelClass])        
		{
            for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)
			{
				for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
				{
					if (pixelClass == pImageBuffer[height*g_imageRow+width])
					{
						m_pImageBuffer[(height*g_imageRow+width)*3+0] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+1] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+2] = 255;
					}
				}//for height����
			}//for width����
		}//else if NUT����
	}//for pixelClass����
}



///////////////////////////////////////
//������:TargetObject
//�������:CDC *pDC
//�������:��						
//��������:��ԭͼ���б�ע��ȷ����Ŀ��
///////////////////////////////////////
void CMainFrame::TargetObject(CDC *pDC)
{

	unsigned int pixelClass = 0;
	char           str[5] = {0};

	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)
	{
		
		if (NUT == g_classCategory[pixelClass])
		{
            pDC->TextOut(g_classCoordinate[pixelClass][LEFT],g_imageHeight - g_classCoordinate[pixelClass][DOWN],"��ĸ");
			itoa(g_imageClass[pixelClass],str,10);
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT]+40,g_imageHeight - g_classCoordinate[pixelClass][DOWN],str);
		}
		else if (SCREW == g_classCategory[pixelClass])
		{
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT],g_imageHeight - g_classCoordinate[pixelClass][DOWN],"�ݶ�");
			itoa(g_imageClass[pixelClass],str,10);
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT]+40,g_imageHeight - g_classCoordinate[pixelClass][DOWN],str);
		}
	}
	pDC->TextOut(30,30,"ͼ���У�");
	pDC->TextOut(30,50,"�ݶ���");
	itoa(g_objectNum[SCREW],str,10);
	pDC->TextOut(90,50,str);
    pDC->TextOut(110,50,"��");
	pDC->TextOut(30,70,"��ĸ��");
	itoa(g_objectNum[NUT],str,10);
	pDC->TextOut(90,70,str);
    pDC->TextOut(110,70,"��");
}

BOOL CMainFrame::OpenBMPFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pImageBuffer)
{
	BOOL bRVal = TRUE;
	DWORD dwBytesRead = 0;
	DWORD dwSize = 0;
	BITMAPFILEHEADER bfh;

	HANDLE hFile = ::CreateFile(lpFileName,
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL
								);
	if (hFile == INVALID_HANDLE_VALUE) {
		bRVal = FALSE;
	}
	else{
		dwSize = sizeof(BITMAPFILEHEADER);
		::ReadFile(hFile, &bfh, dwSize, &dwBytesRead, NULL );
		if (bfh.bfType != ((WORD)'M' << 8 | 'B')) {
			bRVal = FALSE;
		}
		else{
			dwSize = sizeof(BITMAPINFOHEADER);
			::ReadFile(hFile, pBmpInfo, dwSize, &dwBytesRead, NULL);
			if (pBmpInfo->bmiHeader.biBitCount <= 8) {
				dwSize = bfh.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
				ReadFile(hFile,
					(char *)pBmpInfo + sizeof(BITMAPINFOHEADER),
					dwSize,
					&dwBytesRead,
					NULL
					);
			}
			
			dwSize = WIDTH_BYTES(pBmpInfo->bmiHeader.biWidth * pBmpInfo->bmiHeader.biBitCount) *
					pBmpInfo->bmiHeader.biHeight;

			SetFilePointer(hFile, bfh.bfOffBits, 0, FILE_BEGIN);	//���õ�ͼ�����ݵ�λ��(2009.08.27)

			ReadFile(hFile, pImageBuffer, dwSize, &dwBytesRead, NULL);
		}
		
		CloseHandle(hFile);
	}
	
	return bRVal;
}




BOOL CMainFrame::SaveBMPFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pImageBuffer)
{
	BOOL bRVal				= TRUE;
	DWORD dwBytesRead		= 0;
	DWORD dwSize			= 0;
	BITMAPFILEHEADER bfh	= {0};
	int nTable				= 0;
	DWORD dwImageSize		= 0;

	if (pBmpInfo->bmiHeader.biBitCount > 8) {
		nTable = 0;
	}
	else{
		nTable = 256;
	}

	dwImageSize =  WIDTH_BYTES(pBmpInfo->bmiHeader.biWidth * pBmpInfo->bmiHeader.biBitCount) * 
					pBmpInfo->bmiHeader.biHeight;
	
	if (dwImageSize <= 0) {
		bRVal = FALSE;
	}
	else{
		bfh.bfType		= (WORD)'M' << 8 | 'B';
		bfh.bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nTable * sizeof(RGBQUAD);
		bfh.bfSize		= bfh.bfOffBits + dwImageSize;			
		
		HANDLE hFile = ::CreateFile(lpFileName,
			GENERIC_WRITE ,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (hFile == INVALID_HANDLE_VALUE) {
			bRVal = FALSE;
		}
		else{
			dwSize = sizeof(BITMAPFILEHEADER);
			::WriteFile(hFile, &bfh, dwSize, &dwBytesRead, NULL );
			
			dwSize = sizeof(BITMAPINFOHEADER) + nTable * sizeof(RGBQUAD);
			::WriteFile(hFile, pBmpInfo, dwSize, &dwBytesRead, NULL );
			
			dwSize = dwImageSize;
			WriteFile(hFile, pImageBuffer, dwSize, &dwBytesRead, NULL );
			
			CloseHandle(hFile);
		}
	}
	
	return bRVal;
}



BOOL CMainFrame::OpenRawFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pRawBuffer)
{
	BOOL bRVal = TRUE;
	DWORD dwBytesRead = 0;

	HANDLE hFile = ::CreateFile(lpFileName,
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL
								);
	if (hFile == INVALID_HANDLE_VALUE) {
		bRVal = FALSE;
	}
	else{
		::ReadFile(hFile, &(pBmpInfo->bmiHeader.biWidth), sizeof(DWORD), &dwBytesRead, NULL);
		::ReadFile(hFile, &(pBmpInfo->bmiHeader.biHeight), sizeof(DWORD), &dwBytesRead, NULL);
			
		::ReadFile(hFile, pRawBuffer, pBmpInfo->bmiHeader.biWidth * pBmpInfo->bmiHeader.biHeight, &dwBytesRead, NULL);
		
		CloseHandle(hFile);
	}
	
	return bRVal;
}




BOOL CMainFrame::SaveRawFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pRawBuffer)	
{
	BOOL bRVal				= TRUE;
	DWORD dwBytesRead		= 0;
	DWORD dwImageSize		= 0;

	dwImageSize =  pBmpInfo->bmiHeader.biWidth * pBmpInfo->bmiHeader.biHeight;
	
	if (dwImageSize <= 0) {
		bRVal = FALSE;
	}
	else{
		HANDLE hFile = ::CreateFile(lpFileName,
			GENERIC_WRITE ,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (hFile == INVALID_HANDLE_VALUE) {
			bRVal = FALSE;
		}
		else{	
			::WriteFile(hFile, &(pBmpInfo->bmiHeader.biWidth), sizeof(DWORD), &dwBytesRead, NULL );
			::WriteFile(hFile, &(pBmpInfo->bmiHeader.biHeight), sizeof(DWORD), &dwBytesRead, NULL );
			::WriteFile(hFile, pRawBuffer, dwImageSize, &dwBytesRead, NULL );
			
			CloseHandle(hFile);
		}
	}
	
	return bRVal;
}




int CMainFrame::GetFileExt(LPCSTR lpFileName)
{
	int nRVal = 0;

	int nLength			= 0;
	char cFileExt[5]	= {0};

	nLength = strlen(lpFileName);
	CopyMemory(cFileExt, (lpFileName + nLength - 4), 4);
	strupr(cFileExt);
	if (strcmp(cFileExt, ".BMP") == 0) {
		nRVal = 0;
	}
	else if(strcmp(cFileExt, ".JPG") == 0){
		nRVal = 1;
	}
	else if(strcmp(cFileExt, ".RAW") == 0){
		nRVal = 2;
	}

	return nRVal;
}





void CMainFrame::OnFileOpenOne() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE , "*.bmp", NULL ,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY, "Bitmap Files(*.bmp)|*.bmp|JPEG Files(*.jpg)|*.jpg|Raw Files(*.raw)|*.raw||", this);	
	
	if (dlg.DoModal() == IDOK) {
		if (m_pImageBuffer && m_pRawBuffer) {
			int nFileExt = GetFileExt(dlg.GetPathName());
			switch(nFileExt) {
			case 0:
				OpenBMPFile(dlg.GetPathName(), m_pBmpInfo, m_pImageBuffer);
				break;
			case 1:
				HVLoadJPEG((char *)(LPCSTR)dlg.GetPathName(), m_pImageBuffer, (int *)&(m_pBmpInfo->bmiHeader.biWidth), 
					(int *)&(m_pBmpInfo->bmiHeader.biHeight), (int *)&(m_pBmpInfo->bmiHeader.biBitCount), TRUE);
				break;
			case 2:
				OpenRawFile(dlg.GetPathName(), m_pBmpInfo, m_pRawBuffer);
				DecodeImage();
				break;
			default:
				break;
			}		
			Invalidate(TRUE);
		} 
	}
}



void CMainFrame::OnFileSaveAsOne() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE , "*.bmp", NULL ,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY, "Bitmap Files(*.bmp)|*.bmp|JPEG Files(*.jpg)|*.jpg|Raw Files(*.raw)|*.raw||", this);	

	if (dlg.DoModal() == IDOK) {
		if (m_pImageBuffer && m_pRawBuffer) {
			int nFileExt = GetFileExt(dlg.GetPathName());
			switch(nFileExt) {
			case 0:
				SaveBMPFile(dlg.GetPathName(), m_pBmpInfo, m_pImageBuffer);
				break;
			case 1:
				HVSaveJPEG((char *)(LPCSTR)dlg.GetPathName(), m_pImageBuffer, (int)(m_pBmpInfo->bmiHeader.biWidth), 
					(int)(m_pBmpInfo->bmiHeader.biHeight), (int)(m_pBmpInfo->bmiHeader.biBitCount), TRUE, 100);
				break;
			case 2:
				SaveRawFile(dlg.GetPathName(), m_pBmpInfo, m_pRawBuffer);
				break;
			default:
				break;
			}	
		} 
	}
}





void CMainFrame::OnViewWb() 
{
	// TODO: Add your command handler code here
	CWBDlg dlg;

	if (dlg.DoModal() == IDOK) {
	} 
}

void CMainFrame::OnUpdateViewWb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ImageMode == HV_COLOR);
}




LRESULT CMainFrame::OnGetRatioMessage(WPARAM wParam, LPARAM lParam)
{
	if (m_pImageBuffer) {
		if (m_ImageMode	== HV_COLOR)
		{


			SetLutTable(1.0,1.0,1.0);

			m_pBmpInfo->bmiHeader.biBitCount = 24;
			CSize Size;
			Size.cx  = m_pBmpInfo->bmiHeader.biWidth;
			Size.cy = m_pBmpInfo->bmiHeader.biHeight;

			ConvertBayer2Rgb(m_pImageBuffer, m_pRawBuffer,Size.cx,Size.cy, m_ConversionType,m_pLutR,m_pLutG,m_pLutB,true,m_Layout);


			GetWhiteBalanceRatio(m_pImageBuffer, 
				(int)m_pBmpInfo->bmiHeader.biWidth, (int)m_pBmpInfo->bmiHeader.biHeight, 
				&m_dRatioR, &m_dRatioG, &m_dRatioB);
			

		} 
		else {
				return 1;
		}

	} 
	
	return 1;
}




void CMainFrame::OnHelpWebsite() 
{
	// TODO: Add your command handler code here
	// For URL, open it in the browser
    HINSTANCE h = ShellExecute(NULL, "open", "http://www.Microvision.com.cn/", NULL, NULL, SW_SHOWNORMAL);
    if(!((UINT)h > 32)) {
		AfxMessageBox("Sorry: cannot access web location", MB_OK | MB_ICONEXCLAMATION);
	}
}


void CMainFrame::OnHelpMailto() 
{
	// TODO: Add your command handler code here
	HINSTANCE h = ShellExecute(NULL, "open", "mailto:HVDAILT Applications <support@Microvisione.com.cn>", NULL, NULL, SW_SHOWNORMAL);
    if(!((UINT)h > 32)) {
		AfxMessageBox("Sorry: cannot access email", MB_OK | MB_ICONEXCLAMATION);
	}
}

void CMainFrame::OnViewContinuation() 
{
	// TODO: Add your command handler code here
	HVSTATUS status = HVSetSnapMode(m_hhv, CONTINUATION);
	if (HV_SUCCESS(status)) {
		m_SnapMode = CONTINUATION;
	}
}


void CMainFrame::OnUpdateViewContinuation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_SnapMode == CONTINUATION);
	pCmdUI->Enable( ! m_bSnapping);
}



void CMainFrame::OnViewTrigger() 
{
	// TODO: Add your command handler code here
	HVSTATUS status = HVSetSnapMode(m_hhv, TRIGGER);
	if (HV_SUCCESS(status)){
		m_SnapMode = TRIGGER;
	}
}


void CMainFrame::OnUpdateViewTrigger(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_SnapMode == TRIGGER);
	pCmdUI->Enable( ! m_bSnapping);
}



void CMainFrame::OnViewSnapshot() 
{
	// TODO: Add your command handler code here
	BYTE *ppBuff[1] ;
	ppBuff[0] = m_pRawBuffer;
	HVSTATUS status= HVSnapShot(m_hhv, ppBuff, 1);
	HV_MESSAGE(status);
	if (HV_SUCCESS(status)) {
		ShowImage();
	}
}



void CMainFrame::OnUpdateViewSnapshot(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ! m_bSnapping);
}


BOOL CMainFrame::SetLutTable(double dRatioR,double dRatioG,double dRatioB)
{
	if(dRatioR <=0)
		return FALSE;
	if(dRatioG <=0)
		return FALSE;
	if(dRatioB <=0)
		return FALSE;

	for(int i=0;i<256;i++)
	{
		if(m_bIsGammaCorrect)
		{
			m_pLutR[i] = min((int)(m_pLutGamma[i]*dRatioR),255);
			m_pLutG[i] = min((int)(m_pLutGamma[i]*dRatioG),255);
			m_pLutB[i] = min((int)(m_pLutGamma[i]*dRatioB),255);

		}
		else
		{
			m_pLutR[i] = min((int)(i*dRatioR),255);
			m_pLutG[i] = min((int)(i*dRatioG),255);
			m_pLutB[i] = min((int)(i*dRatioB),255);
		}
	}

	return TRUE;
}

//�õ�������ڴ�С
int CMainFrame::GetOutputWinWdith()
{
	return m_rcOutputWindow.Width();
}


void CMainFrame::OnConversionBest() 
{
	m_ConversionType = BAYER2RGB_PIXELGROUPING;
	
}

void CMainFrame::OnUpdateConversionBest(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ConversionType == BAYER2RGB_PIXELGROUPING);
	
}

void CMainFrame::OnConversionFast() 
{
	m_ConversionType = BAYER2RGB_NEIGHBOUR;
	
}

void CMainFrame::OnUpdateConversionFast(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ConversionType == BAYER2RGB_NEIGHBOUR);
	
}

void CMainFrame::OnConversionNormal() 
{
	m_ConversionType = BAYER2RGB_PATTERN;
	
}

void CMainFrame::OnUpdateConversionNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ConversionType == BAYER2RGB_PATTERN);
	
}

void CMainFrame::OnViewMode0() 
{
	HVSTATUS status = STATUS_OK;
	
	m_Resolution = RES_MODE0;

	//get the max size of the output window
	int nBuffSize;
	HVGetDeviceInfo(m_hhv, DESC_RESOLUTION, NULL,&nBuffSize);	
	
	BYTE *pbContext = new BYTE[nBuffSize];
	DWORD *pdContext =(DWORD *)(pbContext);
	HVGetDeviceInfo(m_hhv, DESC_RESOLUTION, pdContext,&nBuffSize);	
	
	m_nMaxWidth = *(pdContext + 2*RES_MODE0);
	m_nMaxHeight = *(pdContext + 2*RES_MODE0 + 1);

	delete []pbContext;
	
	AdjustWindow();

	//�������������ǰ��ֹͣ�ɼ�
	if (m_bSnapping)
	{
		HVStopSnap(m_hhv);
	}

	status = HVSetResolution(m_hhv, RES_MODE0);
	AdjustHBlanking();
	status = HVSetOutputWindow(m_hhv, 
		m_rcOutputWindow.left,
		m_rcOutputWindow.top,
		m_rcOutputWindow.Width(),
		m_rcOutputWindow.Height()			
		);  

	//������������ں󣬿�ʼ�ɼ�
	if (m_bSnapping)
	{
		//ֻ����һ��������,
		BYTE * ppBuffer[1];
		ppBuffer[0] = m_pRawBuffer;
		status = HVStartSnap(m_hhv,ppBuffer,1);	
	}
}

void CMainFrame::OnUpdateViewMode0(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Resolution == RES_MODE0);	
}

void CMainFrame::OnViewMode1() 
{
	HVSTATUS status = STATUS_OK;
	
	m_Resolution = RES_MODE1;
	
	//get the max size of the output window
	int nBuffSize;
	HVGetDeviceInfo(m_hhv, DESC_RESOLUTION, NULL,&nBuffSize);	
	
	BYTE *pbContext = new BYTE[nBuffSize];
	DWORD *pdContext =(DWORD *)(pbContext);
	HVGetDeviceInfo(m_hhv, DESC_RESOLUTION, pdContext,&nBuffSize);	
	
	m_nMaxWidth = *(pdContext + 2*RES_MODE1);
	m_nMaxHeight = *(pdContext + 2*RES_MODE1 + 1);
	
	delete []pbContext;

	AdjustWindow();
	//�������������ǰ��ֹͣ�ɼ�
	if (m_bSnapping)
	{
		HVStopSnap(m_hhv);
	}
	
	status = HVSetResolution(m_hhv, RES_MODE1);
	AdjustHBlanking();
	status = HVSetOutputWindow(m_hhv, 
		m_rcOutputWindow.left,
		m_rcOutputWindow.top,
		m_rcOutputWindow.Width(),
		m_rcOutputWindow.Height()			
		);  
	//������������ں󣬿�ʼ�ɼ�
	if (m_bSnapping)
	{
		//ֻ����һ��������,
		BYTE * ppBuffer[1];
		ppBuffer[0] = m_pRawBuffer;
		status = HVStartSnap(m_hhv,ppBuffer,1);	
	}		
}

void CMainFrame::OnUpdateViewMode1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Resolution == RES_MODE1);	
}

void CMainFrame::OnViewMode2() 
{
	HVSTATUS status = STATUS_OK;

	m_Resolution = RES_MODE2;

	//get the max size of the output window
	int nBuffSize;
	HVGetDeviceInfo(m_hhv, DESC_RESOLUTION, NULL,&nBuffSize);	

	BYTE *pbContext = new BYTE[nBuffSize];
	DWORD *pdContext =(DWORD *)(pbContext);
	HVGetDeviceInfo(m_hhv, DESC_RESOLUTION, pdContext,&nBuffSize);	

	m_nMaxWidth = *(pdContext + 2*RES_MODE2);
	m_nMaxHeight = *(pdContext + 2*RES_MODE2 + 1);
	
	delete []pbContext;	

	AdjustWindow();
	
	//�������������ǰ��ֹͣ�ɼ�
	if (m_bSnapping)
	{
		HVStopSnap(m_hhv);
	}

	status = HVSetResolution(m_hhv, RES_MODE2);
	AdjustHBlanking();
	status = HVSetOutputWindow(m_hhv, 
		m_rcOutputWindow.left,
		m_rcOutputWindow.top,
		m_rcOutputWindow.Width(),
		m_rcOutputWindow.Height()			
		);  

	//������������ں󣬿�ʼ�ɼ�
	if (m_bSnapping)
	{
		//ֻ����һ��������,
		BYTE * ppBuffer[1];
		ppBuffer[0] = m_pRawBuffer;
		status = HVStartSnap(m_hhv,ppBuffer,1);	
	}
}

void CMainFrame::OnUpdateViewMode2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Resolution == RES_MODE2);	
}

void CMainFrame:: Format24To8(BYTE *pDestBit8,BYTE *pSrceBit24, int nWid,int nHei)
{
	if(pDestBit8 == NULL)
		return;
	if(pSrceBit24 == NULL)
		return;
	if(nWid <=0 || nHei <=0)
		return;
	if(m_pLutMapping == NULL)
		return;


	int i=0,j=0;
	int nPos=0;
	PBYTE pYUVLut;
	for(i=0;i<nHei;i++)
	{
		nPos = i*nWid*3;	
		for(j=0;j<nWid;j++)
		{
			//��������Ϊ GBR
			pYUVLut = m_pLutMapping + 256*256*pSrceBit24[nPos+2] + 256*pSrceBit24[nPos+1] + pSrceBit24[nPos];
			*pDestBit8 = *pYUVLut;
			pDestBit8 ++;
			nPos +=3;
		}
	}


}


PBYTE CMainFrame::CreateLutMapFile(LPCTSTR lpFileName)
{
	if(strlen(lpFileName)<=0)
		return NULL;

	//����ļ��Ѿ�����
	if(PathFileExists(lpFileName))
	{
		HANDLE hFile = CreateFile(lpFileName,   // 
			GENERIC_WRITE |GENERIC_READ,
			FILE_SHARE_READ, 
			NULL,
			OPEN_EXISTING, 
			FILE_FLAG_SEQUENTIAL_SCAN, 
			NULL);
		
		// �����ļ�ӳ���ں˶��󣬾��������hFileMapping,���16M
		m_hFileMapping = CreateFileMapping(hFile,NULL,PAGE_READWRITE, 
			0, 0x1000000, NULL);
		// �ͷ��ļ��ں˶���
		CloseHandle(hFile);

		// ���ļ�����ӳ�䵽���̵ĵ�ַ�ռ�, ��СΪ16M
		PBYTE pData = (PBYTE)MapViewOfFile(m_hFileMapping,
			FILE_MAP_ALL_ACCESS,
			0, 0, 0x1000000);

		return pData;
				
	}	
	else //����ļ������ڣ������ļ���д������
	{
		HANDLE hFile = CreateFile(lpFileName,
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ, 
			NULL,
			CREATE_ALWAYS, 
			FILE_FLAG_SEQUENTIAL_SCAN, 
			NULL);
		
		// �����ļ�ӳ���ں˶��󣬾��������hFileMapping,���16M
		m_hFileMapping = CreateFileMapping(hFile,NULL,PAGE_READWRITE, 
			0, 0x1000000, NULL);
		// �ͷ��ļ��ں˶���
		CloseHandle(hFile);
		
		// ���ļ�����ӳ�䵽���̵ĵ�ַ�ռ�, ��СΪ16M
		PBYTE pData = (PBYTE)MapViewOfFile(m_hFileMapping,
			FILE_MAP_ALL_ACCESS,
			0, 0, 0x1000000);
	
		if(pData == NULL)
			return NULL;
		//YUV ת����ֵ�� ��ʼ��
		PBYTE pYUVLut;
		for(int i=0;i<256;i++)
		{
			for(int j=0;j<256;j++)
			{
				for(int k=0;k<256;k++)
				{
					pYUVLut = pData + i*256*256 + j*256 + k;
					*pYUVLut = (BYTE)(0.299*i + 0.587*j + 0.114*k);   //�ο�RGB->YUVת����ʽ
				}
			}
		}
		return pData;		
	}

}



void CMainFrame::OnGammaCorrect() 
{
	
	m_bIsGammaCorrect = TRUE;	
	CDlgGamma dlg;
	dlg.m_dGammRatio = m_dGammRatio;
	if(dlg.DoModal() == IDOK)
	{
		m_dGammRatio = dlg.m_dGammRatio;
		//����Gamma��ֵ���ֵ
		SetGammaLut(m_pLutGamma,m_dGammRatio);
		//������ɫ��ֵ��
		SetLutTable(m_dRatioR,m_dRatioG,m_dRatioB);	
	}	
}

void CMainFrame::OnUpdateGammaCorrect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bIsGammaCorrect);		
}

void CMainFrame::OnCancelGamma() 
{
	m_bIsGammaCorrect = FALSE;		
	SetLutTable(m_dRatioR,m_dRatioG,m_dRatioB);	
	
}

void CMainFrame::OnUpdateCancelGamma(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!m_bIsGammaCorrect);	
}


void CMainFrame::OnGetBadPiexes() 
{
	CString strMsg = "��ȷ���Ѿ�����ͷ��ȫ�ڸ�!";
	
	if(MessageBox(strMsg, "Notice", MB_OKCANCEL) != IDOK)
		return;

	m_bIsToGetBadPixel = TRUE;
	//�õ������ʱ��,���������������ó����
	//�������������ǰ��ֹͣ�ɼ�
	if (m_bSnapping)
	{
		HVStopSnap(m_hhv);
	}
	AdjustHBlanking();
	HVSTATUS status = HVSetOutputWindow(m_hhv, 
		0,
		0,
		m_nMaxWidth,
		m_nMaxHeight			
		);  

	//������������ں󣬿�ʼ�ɼ�
	if (m_bSnapping)
	{
		//ֻ����һ��������,
		BYTE * ppBuffer[1];
		ppBuffer[0] = m_pRawBuffer;
		status = HVStartSnap(m_hhv,ppBuffer,1);	
	}
	
}

void CMainFrame::OnUpdateGetBadPiexes(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_bSnapping));
	pCmdUI->SetCheck(m_bIsToGetBadPixel);
	
}

void CMainFrame::OnEliminateBadPixels() 
{
	m_bIsToRemoveBadPixel = !m_bIsToRemoveBadPixel;
	
}

void CMainFrame::OnUpdateEliminateBadPixels(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_bSnapping) );
	pCmdUI->SetCheck(m_bIsToRemoveBadPixel);
	
}

void CMainFrame::OnGetTemplate() 
{
	CString strMsg = "��ȷ���Ѿ�����ͷ��Ծ��ȹ���!";
	
	if(MessageBox(strMsg, "Notice", MB_OKCANCEL) != IDOK)
		return;
	
	m_bIsToGetTemplate = TRUE;
	//�õ������ʱ��,���������������ó����
	//�������������ǰ��ֹͣ�ɼ�
	if (m_bSnapping)
	{
		HVStopSnap(m_hhv);
	}
	AdjustHBlanking();
	HVSTATUS status = HVSetOutputWindow(m_hhv, 
		0,
		0,
		m_nMaxWidth,
		m_nMaxHeight			
		);  
	
	//������������ں󣬿�ʼ�ɼ�
	if (m_bSnapping)
	{
		//ֻ����һ��������,
		BYTE * ppBuffer[1];
		ppBuffer[0] = m_pRawBuffer;
		status = HVStartSnap(m_hhv,ppBuffer,1);	
	}
}

void CMainFrame::OnUpdateGetTemplate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_bSnapping)  );
	pCmdUI->SetCheck(m_bIsToGetTemplate);
	
}

void CMainFrame::OnTemplateCorrect() 
{
	m_bIsTemplateCorrect = !m_bIsTemplateCorrect;	
	
}

void CMainFrame::OnUpdateTemplateCorrect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_bSnapping) && !m_bIsToGetTemplate);
	pCmdUI->SetCheck(m_bIsTemplateCorrect);
}

void CMainFrame::OnSnapspeedNormal() 
{
	if(m_bIsSnapSpeedSprted)
	{
		m_SnapSpeed = NORMAL_SPEED;
		HVSTATUS status = HVSetSnapSpeed(m_hhv,m_SnapSpeed);
		SetExposureTime(GetOutputWinWdith(),m_lTintUpper,m_lTintLower);
	}	
}

void CMainFrame::OnUpdateSnapspeedNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_SnapSpeed == NORMAL_SPEED);	
	pCmdUI->Enable(m_bIsSnapSpeedSprted);
}

void CMainFrame::OnSnpaspeedHigh() 
{
	if(m_bIsSnapSpeedSprted)
	{
		m_SnapSpeed = HIGH_SPEED;
		HVSTATUS status = HVSetSnapSpeed(m_hhv,m_SnapSpeed);
		SetExposureTime(GetOutputWinWdith(),m_lTintUpper,m_lTintLower);
	}
	
}

void CMainFrame::OnUpdateSnpaspeedHigh(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_SnapSpeed == HIGH_SPEED);	
	pCmdUI->Enable(m_bIsSnapSpeedSprted);	
}

LRESULT CMainFrame::OnSnapError(WPARAM wParam, LPARAM lParam)
{	
	CErrorBox ErrDlg;
	ErrDlg.m_dwStatus = lParam;
	if (ErrDlg.DoModal()==IDOK)
	{
		OnSnapStop(0,0);

		//ֻ����һ��������,
		BYTE * ppBuffer[1];
		ppBuffer[0] = m_pRawBuffer;
		HVSTATUS status = HVStartSnap(m_hhv,ppBuffer,1);	
		HV_VERIFY(status);
		if (HV_SUCCESS(status)) {
			m_bSnapping = TRUE;
		}

	}	
	return 1;
}

LRESULT CMainFrame::OnSnapStop(WPARAM wParam, LPARAM lParam)
{
	if (m_bSnapping){
		HVSTATUS status = HVStopSnap(m_hhv);
		HV_VERIFY(status);
		if (HV_SUCCESS(status)) {
			m_bSnapping = FALSE;
		}
	}
	return 1;
}

HVSTATUS CMainFrame::GetLastStatus()
{
	HV_ARG_GET_LAST_STATUS ArgFeature;
	ArgFeature.type = HV_LAST_STATUS_TRANSFER;
	
	HV_RES_GET_LAST_STATUS ResFeature;
	
	HVAPI_CONTROL_PARAMETER  p;
	p.pInBuf		 = &ArgFeature;
	p.dwInBufSize	 = sizeof(ArgFeature);	
	p.pOutBuf		 = &ResFeature;
	p.dwOutBufSize	 = sizeof(ResFeature);
	p.pBytesRet		 = NULL;		
	p.code			 = ORD_GET_LAST_STATUS;
	int	dwSize = sizeof(p);
	
	HVSTATUS status = HVCommand(m_hhv, CMD_HVAPI_CONTROL, &p, &dwSize);
	if(status != STATUS_OK)
	{
		TRACE("HVCommand return status is %d", status);
	}
	
	dwLastStatus = 0;
	
	if (HV_SUCCESS(status)) {
		dwLastStatus = ResFeature.status;
	}
	
	return status;
}

void CMainFrame::OnMenuitem32828() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuitem32829() 
{
	// TODO: Add your command handler code here
	
}
