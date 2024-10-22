// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MVSnapContinuous.h"
#include "ErrorBox.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	ON_MESSAGE(WM_SNAP_ERROR, OnSnapError)
	//ON_MESSAGE(WM_SNAP_STOP, OnSnapexStop)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//�����Լ���0
#define  MY_ZERO 0.000000001

//const
const HV_RESOLUTION Resolution = RES_MODE0;
const HV_SNAP_MODE SnapMode = CONTINUATION;
const HV_BAYER_LAYOUT Layout = BAYER_GR;//GV400Ux(BAYER_BG)
const HV_BAYER_CONVERT_TYPE ConvertType = BAYER2RGB_NEIGHBOUR;
const long Gain = 8;
const long ExposureTint_Upper = 60;
const long ExposureTint_Lower = 1000;

const long ADCLevel = ADC_LEVEL2;
const int XStart = 0;
const int YStart = 0;
const int Width = 752;
const int Height = 480;

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

	m_pBmpInfo		= NULL;
	m_pRawBuffer	= NULL;
	m_pImageBuffer	= NULL;

	m_nError = 0;
	m_nLost  = 0;

	for(int i=0;i<256;i++)
	{
		m_pLutR[i] = i;
		m_pLutG[i] = i;
		m_pLutB[i] = i;
	}

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
	
	HVSetSnapSpeed(m_hhv, HIGH_SPEED);
	
	//	�ɼ�ģʽ������ CONTINUATION(����)��TRIGGER(�ⴥ��)
	HVSetSnapMode(m_hhv, SnapMode);
	
	//  ���ø�������������
	for (int i = 0; i < 4; i++){
		HVAGCControl(m_hhv, RED_CHANNEL + i, Gain);
	}

	//	�����ع�ʱ��
	SetExposureTime(Width,ExposureTint_Upper,ExposureTint_Lower);	

	//  ����ADC�ļ���
	HVADCControl(m_hhv, ADC_BITS, ADCLevel);
	
	/*
	*	��Ƶ������ڣ�����Ƶ�����Χ���������ȡֵ��Χ���������봰�ڷ�Χ���ڣ�
	*  ��Ƶ�������Ͻ�X����ʹ��ڿ���ӦΪ4�ı��������Ͻ�Y����ʹ��ڸ߶�ӦΪ2�ı���
	*	������ڵ���ʼλ��һ������Ϊ(0, 0)���ɡ�
	*/
	HVSetOutputWindow(m_hhv, XStart, YStart, Width, Height);
	
	//	m_pBmpInfo��ָ��m_chBmpBuf���������û������Լ�����BTIMAPINFO������	
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	//	��ʼ��BITMAPINFO �ṹ���˽ṹ�ڱ���bmp�ļ�����ʾ�ɼ�ͼ��ʱʹ��
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	//	ͼ����ȣ�һ��Ϊ������ڿ���
	m_pBmpInfo->bmiHeader.biWidth			= Width;
	//	ͼ����ȣ�һ��Ϊ������ڸ߶�
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
	 *	ָ���ص�����SnapThreadCallback��thisָ��
	 */
	status = HVOpenSnap(m_hhv, SnapThreadCallback, this);					
	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bOpen = TRUE;		//��־�Ѿ���Snap����
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
		m_nError = 0;
		m_nLost  = 0;
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
		�û��ڻص�������ʵ�ֶԲɼ����ݵĴ�������ʾ����
 */
int CALLBACK CMainFrame::SnapThreadCallback(HV_SNAP_INFO *pInfo)
{
	CMainFrame *This = (CMainFrame *)(pInfo->pParam);
	HWND hwnd = This->m_hWnd;

	HVSTATUS status = This->GetLastStatus();	// ��ȡ�����ͼ��ɼ�����״̬
	
	if(!HV_SUCCESS(status)){	//����������ò��ɹ��������ֹͣͼ��ɼ���
		::PostMessage(hwnd, WM_SNAP_STOP, 0, 0);
		return 1;
	}
	
	TRACE("LastStatus is %X", This->dwLastStatus);
	
	if(This->dwLastStatus == 0)	// ��״ֵ̬����0ʱ����ʾ�����ͼ��ɼ������������SendMessage��ʾͼ��
	{
	   /*
		*	�����Զ�����ϢWM_SNAP_EX_CHANGE�������ڣ�	
		*	ͬʱ���뵱ǰ���Դ�����ͼ�����
		*	ע�⣺��SendMessage������Ϣ������ȴ���Ϣ������Ϻ󣬲����˳�����SendMessage����
		*/
		::SendMessage(hwnd, WM_SNAP_CHANGE, 0, 0);
		return 1;
		
	}
	else if(This->dwLastStatus == STATUS_FILE_INVALID)// ��״ֵ̬������-18ʱ����ʾ���������1�ζ�֡��Ϊ
												//���������ٲɼ�ʱ��1�ζ�֡��Ϊ���ܰ���1֡����ͼ��
	{
		This->m_nLost++;	//��֡����
	}
	else if (This->dwLastStatus==0xc0000012 || This->dwLastStatus==0xc0000011)
	{
		This->m_nError++;	//�������
	}
	else // ��״ֵ̬Ϊ������0ֵʱ����ʾ�����ͼ��ɼ��쳣
	{
	   /*
		*	�����Զ�����Ϣ WM_SNAP_ERROR �������ڣ�	
		*	ע�⣺��PostMessage������Ϣ�����صȴ���Ϣ�����꣬�Ϳ��Է��ء�
		*/
		::PostMessage(hwnd, WM_SNAP_ERROR, 0, This->dwLastStatus);
	}
	
	return 1;
}

/*
	����:
		OnSnapError
	�������:
		WPARAM wParam			û��ʹ��		
		LPARAM lParam			�쳣״̬��
	�������:
		LRESULT						
	˵��:
		������ɼ��쳣���󱨸�
*/
LRESULT CMainFrame::OnSnapError(WPARAM wParam, LPARAM lParam)
{	
	CErrorBox ErrDlg;
	ErrDlg.m_dwStatus = lParam;
	if (ErrDlg.DoModal()==IDOK)
	{
		OnSnapexStop();
		OnSnapexStart();
	}	
	return 1;
}

/*
	����:
		OnSnapChange
	�������:
		WPARAM wParam			�ֲ���������Ϣ��Ϊ��ǰ���Դ�����ͼ�����		
		LPARAM lParam			û��ʹ��
	�������:
		LRESULT						
	˵��:
		ʵ�ֶԲɼ����ݵĴ�������ʾ
 */
LRESULT CMainFrame::OnSnapChange(WPARAM wParam, LPARAM lParam)
{
	HVSTATUS status = STATUS_OK;
	
	CView *pView		= GetActiveView();		//��ȡ��ǰVIEW��ͼ
	CDC *pDC			= pView->GetDC();		//�õ�VIEW��DC
	
	//	��ԭʼͼ�����ݽ���Bayerת����ת����Ϊ24λ��
    //ͬʱ��ԭʼ���ݽ������·�ת
	ConvertBayer2Rgb(m_pImageBuffer,m_pRawBuffer,Width,Height,ConvertType,m_pLutR,m_pLutG,m_pLutB,true,Layout);
	
		
	//����ͼ�ͻ�����ʾͼ��
	StretchDIBits(pDC->GetSafeHdc(),
					0,						
					0,
					Width,					//��ʾ���ڿ���
					Height,					//��ʾ���ڸ߶�
					0,
					0,
					Width,					//ͼ�����
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


/*
����:
		SetExposureTime
�������:
		int nWindWidth			��ǰͼ�����		
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