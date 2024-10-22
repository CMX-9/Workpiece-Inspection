// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MVRealtime.h"

#include "MainFrm.h"
//#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//#define max(a,b)    (((a) > (b)) ? (a) : (b))

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SNAP_OPEN, OnSnapexOpen)
	ON_UPDATE_COMMAND_UI(ID_SNAP_OPEN, OnUpdateSnapexOpen)
	ON_COMMAND(ID_SNAP_START, OnSnapexStart)
	ON_UPDATE_COMMAND_UI(ID_SNAP_START, OnUpdateSnapexStart)
	ON_COMMAND(ID_SNAP_STOP, OnSnapexStop)
	ON_UPDATE_COMMAND_UI(ID_SNAP_STOP, OnUpdateSnapexStop)
	ON_COMMAND(ID_SNAP_CLOSE, OnSnapexClose)
	ON_UPDATE_COMMAND_UI(ID_SNAP_CLOSE, OnUpdateSnapexClose)
	ON_MESSAGE(WM_SNAP_CHANGE, OnSnapChange)
	ON_WM_CLOSE()
	ON_COMMAND(ID_NEGATIVE, OnNegative)
	ON_UPDATE_COMMAND_UI(ID_NEGATIVE, OnUpdateNegative)
	ON_COMMAND(DI_GET_BADPIXEL, OnGetBadpixel)
	ON_UPDATE_COMMAND_UI(DI_GET_BADPIXEL, OnUpdateGetBadpixel)
	ON_COMMAND(ID_GET_TEMPLATE, OnGetTemplate)
	ON_UPDATE_COMMAND_UI(ID_GET_TEMPLATE, OnUpdateGetTemplate)
	ON_COMMAND(ID_REMOVE_BADPIXEL, OnRemoveBadpixel)
	ON_UPDATE_COMMAND_UI(ID_REMOVE_BADPIXEL, OnUpdateRemoveBadpixel)
	ON_COMMAND(ID_USE_TEMPLATE, OnUseTemplate)
	ON_UPDATE_COMMAND_UI(ID_USE_TEMPLATE, OnUpdateUseTemplate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//�����Լ���0
#define  MY_ZERO 0.000000001

//const
const int DeviceNum = 1;
const HV_RESOLUTION Resolution = RES_MODE0;
const HV_SNAP_MODE SnapMode = CONTINUATION;
const HV_BAYER_LAYOUT Layout = BAYER_GR; //GV400Ux(BAYER_BG) 
const HV_BAYER_CONVERT_TYPE ConvertType = BAYER2RGB_NEIGHBOUR;
const long Gain = 8;
const long ExposureTint_Upper = 60;
const long ExposureTint_Lower = 1000;

const long ShutterDelay = 0;
const long ADCLevel = ADC_LEVEL2;
const int XStart = 0;
const int YStart = 0;
const int Width = 1280;
const int Height = 1024;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction


CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
	/*
	 *	��ʼ�����г�Ա������ͬʱ�����������
	 */
	
	HVSTATUS status = STATUS_OK;
	
	m_bOpen			= FALSE;
	m_bStart		= FALSE;

	m_bNegative		= FALSE;

	m_pBmpInfo		= NULL;
	m_pRawBuffer	= NULL;
	m_pImageBuffer	= NULL;

	for(int i=0;i<256;i++)
	{
		m_pLutR[i] = i;
		m_pLutG[i] = i;
		m_pLutB[i] = i;
	}


	
	m_bIsToGetBadPixel = FALSE;
	m_bIsToGetTemplate = FALSE;
	m_bIsToRemoveBadPixel = FALSE;
	m_bIsUseTemplate = FALSE;
	m_nTempTimes = 0;

	//	����������� 1
	status = BeginHVDevice(1, &m_hhv);
	//	���麯��ִ��״̬�����ʧ�ܣ��򷵻ش���״̬��Ϣ��
	HV_VERIFY(status);
}




CMainFrame::~CMainFrame()
{
	HVSTATUS status = STATUS_OK;
	
	//	�ر�������������ͷ�����������ڲ���Դ
	status = EndHVDevice(m_hhv);
	HV_VERIFY(status);

	//	����ͼ�񻺳���
	delete []m_pRawBuffer;
	delete []m_pImageBuffer;

	if(m_pPatternBuf)
		delete[] m_pPatternBuf;
	if(m_pBadPixel)
		delete[] m_pBadPixel;

}



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
		/*
		*	��ʼ�����������Ӳ��״̬���û�Ҳ����������λ�ó�ʼ�������������
		*	��Ӧ��֤����������Ѿ��򿪣������û���Ӧ�ó����ʼ��ʱ��
		*	ͬʱ��ʼ�����������Ӳ����
	*/
	
	//	��������������ֱ���
	HVSetResolution(m_hhv, Resolution);		
	
	//	�ɼ�ģʽ������ CONTINUATION(����)��TRIGGER(�ⴥ��)
	HVSetSnapMode(m_hhv, SnapMode);
	
	//  ���ø�������������
	for (int i = 0; i < 4; i++)
	{
		HVAGCControl(m_hhv, RED_CHANNEL + i, Gain);
	}
	
	//	�����ع�ʱ��
	SetExposureTime(Width,ExposureTint_Upper,ExposureTint_Lower);	
	
	//  ����ADC�ļ���
	HVADCControl(m_hhv, ADC_BITS, ADCLevel);
	
	/*
	*	��Ƶ������ڣ�����Ƶ�����Χ���������ȡֵ��Χ���������봰�ڷ�Χ���ڣ�
	*  ��Ƶ�������Ͻ�X����ʹ��ڿ��ӦΪ4�ı��������Ͻ�Y����ʹ��ڸ߶�ӦΪ2�ı���
	*	������ڵ���ʼλ��һ������Ϊ(0, 0)���ɡ�
	*/
	HVSetOutputWindow(m_hhv, XStart, YStart, Width, Height);
	
	//	m_pBmpInfo��ָ��m_chBmpBuf���������û������Լ�����BTIMAPINFO������	
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	//	��ʼ��BITMAPINFO �ṹ���˽ṹ�ڱ���bmp�ļ�����ʾ�ɼ�ͼ��ʱʹ��
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	//	ͼ���ȣ�һ��Ϊ������ڿ��
	m_pBmpInfo->bmiHeader.biWidth			= Width;
	//	ͼ���ȣ�һ��Ϊ������ڸ߶�
	m_pBmpInfo->bmiHeader.biHeight			= Height;
	
	/*
	*	��������һ����ͬ��
	*	���ڵ���8λ��λͼ����Ӧ������Ӧ��λͼ��ɫ��
	*/
	m_pBmpInfo->bmiHeader.biPlanes			= 1;
	m_pBmpInfo->bmiHeader.biBitCount		= 24;
	m_pBmpInfo->bmiHeader.biCompression		= BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage		= 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biClrUsed			= 0;
	m_pBmpInfo->bmiHeader.biClrImportant	= 0;
	
	/*
	*	����ԭʼͼ�񻺳�����һ�������洢�ɼ�ͼ��ԭʼ����
	*  һ��ͼ�񻺳�����С��������ڴ�С����Ƶ��ʽȷ����
	*/
	m_pRawBuffer = new BYTE[Width * Height];
	ASSERT(m_pRawBuffer);

	m_pPatternBuf = new int[Width * Height];    //��������ģ����ԵĻ�����
	memset(m_pPatternBuf,0,Width * Height*sizeof(int));


	m_pBadPixel  = new BYTE[Width * Height];   //������¼����,

	/*
	����Bayerת����ͼ�����ݻ���
	*/
	m_pImageBuffer = new BYTE[Width * Height * 3];
	ASSERT(m_pImageBuffer);

	return 0;
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



void CMainFrame::OnSnapexOpen() 
{
	// TODO: Add your command handler code here
	HVSTATUS status = STATUS_OK;

	/*
	 *	��ʼ������������ɼ�ͼ���ڴ�Ŀ��ƣ�
	 *	ָ���ص�����SnapThreadCallback���û�����m_hWnd
	 */
	status = HVOpenSnap(m_hhv, SnapThreadCallback, m_hWnd);					
	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bOpen = TRUE;		//��־�Ѿ���SnapEx����
	}


	
}



void CMainFrame::OnUpdateSnapexOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bOpen);		
	pCmdUI->SetCheck(m_bOpen);
}



void CMainFrame::OnSnapexStart() 
{
	// TODO: Add your command handler code here
	HVSTATUS status = STATUS_OK;

	/*
	 *	��������������ɼ�ͼ���ڴ�
	 */
	BYTE *ppBuf[1];
	ppBuf[0] = m_pRawBuffer;
	status = HVStartSnap(m_hhv, ppBuf,1);
	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bStart = TRUE;
	}
}



void CMainFrame::OnUpdateSnapexStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (!m_bStart) && (m_bOpen));
	pCmdUI->SetCheck(m_bStart);
}



void CMainFrame::OnSnapexStop() 
{
	// TODO: Add your command handler code here
	HVSTATUS status =STATUS_OK;
	
	//	ֹͣ�ɼ�ͼ���ڴ棬�����ٴε���HVStartSnapEx��������������ɼ�
	status = HVStopSnap(m_hhv);
	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bStart = FALSE;
	}
}



void CMainFrame::OnUpdateSnapexStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_bStart);
}



void CMainFrame::OnSnapexClose() 
{
	// TODO: Add your command handler code here
	HVSTATUS status = STATUS_OK;

	/*
	 *	��ֹ����������ɼ�ͼ���ڴ棬ͬʱ�ͷ����вɼ�������
	 *	�ٴ���������������ɼ����������³�ʼ��	
	 */
	status = HVCloseSnap(m_hhv);
	HV_VERIFY(status);

	if (HV_SUCCESS(status)) {
		m_bOpen		= FALSE;
		m_bStart	= FALSE;
	}
}




void CMainFrame::OnUpdateSnapexClose(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_bOpen);
}



/*
	����:
		SnapThreadCallback
	�������:
		SNAP_INFO *pInfo		SNAP_INFO�ṹ������ǰ���������SNAPִ��״̬
	�������:
		int						
	˵��:
		����������ɼ����ڴ�ص����������û�һ�㲻�õ��ã����û��ṩ��SDKʹ�ã�
		�û��ڻص�������ʵ�ֶԲɼ����ݵĴ������ʾ����
 */
int CALLBACK CMainFrame::SnapThreadCallback(HV_SNAP_INFO *pInfo)
{
	HWND hwnd = (HWND)(pInfo->pParam);
	
	/*
	 *	�����Զ�����ϢWM_SNAP_EX_CHANGE�������ڣ�	
	 *	ͬʱ���뵱ǰ���Դ����ͼ�����
	 *	ע�⣺��SendMessage������Ϣ������ȴ���Ϣ������Ϻ󣬲����˳�����SendMessage����
	 */
	::SendMessage(hwnd, WM_SNAP_CHANGE, 0, 0);

	return 1;
}




/*
	����:
		OnSnapChange
	�������:
		WPARAM wParam			�ֲ���������Ϣ��Ϊ��ǰ���Դ����ͼ�����		
		LPARAM lParam			û��ʹ��
	�������:
		LRESULT						
	˵��:
		ʵ�ֶԲɼ����ݵĴ������ʾ
 */
LRESULT CMainFrame::OnSnapChange(WPARAM wParam, LPARAM lParam)
{
	HVSTATUS status = STATUS_OK;
	
	CView *pView		= GetActiveView();		//��ȡ��ǰVIEW��ͼ
	CDC *pDC			= pView->GetDC();		//�õ�VIEW��DC

	
	if(m_bIsToGetBadPixel)
	{
		//�õ�����λ��
		DetectDeadPixel(m_pRawBuffer,m_pBadPixel,Width,Height);
		m_bIsToGetBadPixel = FALSE;
	}
	if(m_bIsToRemoveBadPixel)
	{   
		//��������
		EraseDeadPixel(m_pRawBuffer,m_pBadPixel,0,0,Width,Height,Width,Height);
	}

	if(m_bIsToGetTemplate)
	{
		if(m_nTempTimes ==0)  //��һ������ʱ���������
			memset(m_pPatternBuf,'\0',sizeof(int)*Width * Height);		
		//ȡ10��ģ��,Ȼ��ƽ��
		GetPatternNoise(m_pRawBuffer,m_pPatternBuf,Width,Height);
		m_nTempTimes ++ ;
		if(m_nTempTimes >= 10)
		{
			AvgPatternNoise(m_pPatternBuf,Width,Height,m_nTempTimes);
			m_bIsToGetTemplate = FALSE;
		}
	}
	
	if(m_bIsUseTemplate)
	{
		//ʹ��ģ���ͼ�����ݽ���У��
		FixPatternNoise(m_pRawBuffer,m_pPatternBuf,0,0,Width,Height,Width,Height);
	}
	
    //ͬʱ��ԭʼ���ݽ������·�ת
	ConvertBayer2Rgb(m_pImageBuffer,m_pRawBuffer,Width,Height,ConvertType,m_pLutR,m_pLutG,m_pLutB,true,Layout);


	BYTE *p = NULL, * q = NULL;	
	//	����ͼ��ɫ
	if (m_bNegative) {
		for (int i = 0; i < Height; i++){
			p = m_pImageBuffer + i * Width * 3;
			for(int j = 0; j < Width; j++){
				q = p + j * 3;
				*(q + 0) = ~(*(q + 0));
				*(q + 1) = ~(*(q + 1));
				*(q + 2) = ~(*(q + 2));
			}	
		}
	}
	
	SetStretchBltMode(pDC->GetSafeHdc(),COLORONCOLOR);
	//����ͼ�ͻ�����ʾͼ��
	StretchDIBits(pDC->GetSafeHdc(),
					0,						
					0,
					Width,					//��ʾ���ڿ��
					Height,					//��ʾ���ڸ߶�
					0,
					0,
					Width,					//ͼ����
					Height,					//ͼ��߶�
					m_pImageBuffer,			//ͼ�񻺳���
					m_pBmpInfo,				//BMPͼ��������Ϣ
					DIB_RGB_COLORS,
					SRCCOPY
					);	

	
	
	pView->ReleaseDC(pDC);
	
	return 1;
}



void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	/*
	 *	�û���û��ͨ���˵��������ر�����������ɼ���	
	 *	��ֱ�ӹر�Ӧ�ó���ʱ��Ӧ��֤����������ɼ����ر�
	 */
	if (m_bOpen) {
		HVCloseSnap(m_hhv);
	}

	CFrameWnd::OnClose();
}

void CMainFrame::OnNegative() 
{
	// TODO: Add your command handler code here
	m_bNegative = !m_bNegative;			//����ͼ��ɫ��־
}

void CMainFrame::OnUpdateNegative(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bNegative);
}

void CMainFrame::OnGetBadpixel() 
{

	CString strMsg = "��ȷ���Ѿ�����ͷ��ȫ�ڸ�!";
	
	if(MessageBox(strMsg, "Notice", MB_OKCANCEL) != IDOK)
		return;
	
	m_bIsToGetBadPixel = TRUE;
	
}

void CMainFrame::OnUpdateGetBadpixel(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_bStart) && (m_bOpen));
	pCmdUI->SetCheck(m_bIsToGetBadPixel);
}

void CMainFrame::OnGetTemplate() 
{
	CString strMsg = "��ȷ���Ѿ�����ͷ��Ծ��ȹ���!";
	
	if(MessageBox(strMsg, "Notice", MB_OKCANCEL) != IDOK)
		return;
	m_bIsToGetTemplate = TRUE;	
	
}

void CMainFrame::OnUpdateGetTemplate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_bStart) && (m_bOpen) );
	pCmdUI->SetCheck(m_bIsToGetTemplate);
	
}
void CMainFrame::OnRemoveBadpixel() 
{
	m_bIsToRemoveBadPixel = !m_bIsToRemoveBadPixel;	
}

void CMainFrame::OnUpdateRemoveBadpixel(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_bStart) && (m_bOpen));
	pCmdUI->SetCheck(m_bIsToRemoveBadPixel);
	
}
void CMainFrame::OnUseTemplate() 
{
	m_bIsUseTemplate = !m_bIsUseTemplate;
	
}

void CMainFrame::OnUpdateUseTemplate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_bStart) && (m_bOpen) && !m_bIsToGetTemplate);
	pCmdUI->SetCheck(m_bIsUseTemplate);
	
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
	long lClockFreq; 
	int nOutputWid;
	double dExposure = 0.0;
	double dTint = max((double)lTintUpper/(double)lTintLower,MY_ZERO);
	if (type == GV400UMTYPE || type == GV400UCTYPE)
	{
		long rate = 0;
		switch(Resolution)
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
		lClockFreq = 26600000; 
		long lTb = 0x5e;
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
		lClockFreq = 24000000;
		if(type == HV1300UCTYPE || type == HV1301UCTYPE)	
		{
			long lTb = 0;
			dExposure = (dTint* lClockFreq + 180.0)/((double)nOutputWid + 244.0 + lTb);
		}
		else
		{		
			long lTb = 0;
			dExposure = (dTint* lClockFreq + 180.0)/((double)nOutputWid + 305.0 + lTb) + 1 ;
		}
		
		if (dExposure > 16383) 
			dExposure = 16383;
	}

	HVAECControl(m_hhv, AEC_EXPOSURE_TIME, (long)dExposure);
	
}



















































































































































