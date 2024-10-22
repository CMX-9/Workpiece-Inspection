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

//定义自己的0
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
	 *	初始化所有成员变量，同时打开数字摄像机
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

	//	打开数字摄像机 1
	status = BeginHVDevice(1, &m_hhv);
	//	检验函数执行状态，如果失败，则返回错误状态消息框
	HV_VERIFY(status);
}




CMainFrame::~CMainFrame()
{
	HVSTATUS status = STATUS_OK;
	
	//	关闭数字摄像机，释放数字摄像机内部资源
	status = EndHVDevice(m_hhv);
	HV_VERIFY(status);

	//	回收图像缓冲区
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
		*	初始化数字摄像机硬件状态，用户也可以在其他位置初始化数字摄像机，
		*	但应保证数字摄像机已经打开，建议用户在应用程序初始化时，
		*	同时初始化数字摄像机硬件。
	*/
	
	//	设置数字摄像机分辨率
	HVSetResolution(m_hhv, Resolution);		
	
	//	采集模式，包括 CONTINUATION(连续)、TRIGGER(外触发)
	HVSetSnapMode(m_hhv, SnapMode);
	
	//  设置各个分量的增益
	for (int i = 0; i < 4; i++)
	{
		HVAGCControl(m_hhv, RED_CHANNEL + i, Gain);
	}
	
	//	设置曝光时间
	SetExposureTime(Width,ExposureTint_Upper,ExposureTint_Lower);	
	
	//  设置ADC的级别
	HVADCControl(m_hhv, ADC_BITS, ADCLevel);
	
	/*
	*	视频输出窗口，即视频输出范围，输出窗口取值范围必须在输入窗口范围以内，
	*  视频窗口左上角X坐标和窗口宽度应为4的倍数，左上角Y坐标和窗口高度应为2的倍数
	*	输出窗口的起始位置一般设置为(0, 0)即可。
	*/
	HVSetOutputWindow(m_hhv, XStart, YStart, Width, Height);
	
	//	m_pBmpInfo即指向m_chBmpBuf缓冲区，用户可以自己分配BTIMAPINFO缓冲区	
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	//	初始化BITMAPINFO 结构，此结构在保存bmp文件、显示采集图像时使用
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	//	图像宽度，一般为输出窗口宽度
	m_pBmpInfo->bmiHeader.biWidth			= Width;
	//	图像宽度，一般为输出窗口高度
	m_pBmpInfo->bmiHeader.biHeight			= Height;
	
	/*
	*	以下设置一般相同，
	*	对于低于8位的位图，还应设置相应的位图调色板
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
	*	分配原始图像缓冲区，一般用来存储采集图像原始数据
	*  一般图像缓冲区大小由输出窗口大小和视频格式确定。
	*/
	m_pRawBuffer = new BYTE[Width * Height];
	ASSERT(m_pRawBuffer);

	m_pPatternBuf = new int[Width * Height];    //用来进行模板测试的缓冲区
	memset(m_pPatternBuf,0,Width * Height*sizeof(int));


	m_pBadPixel  = new BYTE[Width * Height];   //用来记录坏点,

	/*
	分配Bayer转换后图像数据缓冲
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
	 *	初始化数字摄像机采集图像到内存的控制，
	 *	指定回调函数SnapThreadCallback和用户参数m_hWnd
	 */
	status = HVOpenSnap(m_hhv, SnapThreadCallback, m_hWnd);					
	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bOpen = TRUE;		//标志已经打开SnapEx环境
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
	 *	启动数字摄像机采集图像到内存
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
	
	//	停止采集图像到内存，可以再次调用HVStartSnapEx启动数字摄像机采集
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
	 *	终止数字摄像机采集图像到内存，同时释放所有采集环境，
	 *	再次启动数字摄像机采集，必须重新初始化	
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
	函数:
		SnapThreadCallback
	输入参数:
		SNAP_INFO *pInfo		SNAP_INFO结构包括当前数字摄像机SNAP执行状态
	输出参数:
		int						
	说明:
		数字摄像机采集到内存回调函数，但用户一般不用调用，由用户提供给SDK使用，
		用户在回调函数内实现对采集数据的处理和显示即可
 */
int CALLBACK CMainFrame::SnapThreadCallback(HV_SNAP_INFO *pInfo)
{
	HWND hwnd = (HWND)(pInfo->pParam);
	
	/*
	 *	发送自定义消息WM_SNAP_EX_CHANGE到主窗口，	
	 *	同时传入当前可以处理的图像序号
	 *	注意：用SendMessage发送消息，必须等待消息处理完毕后，才能退出整个SendMessage函数
	 */
	::SendMessage(hwnd, WM_SNAP_CHANGE, 0, 0);

	return 1;
}




/*
	函数:
		OnSnapChange
	输入参数:
		WPARAM wParam			字参数，在消息中为当前可以处理的图像序号		
		LPARAM lParam			没有使用
	输出参数:
		LRESULT						
	说明:
		实现对采集数据的处理和显示
 */
LRESULT CMainFrame::OnSnapChange(WPARAM wParam, LPARAM lParam)
{
	HVSTATUS status = STATUS_OK;
	
	CView *pView		= GetActiveView();		//获取当前VIEW视图
	CDC *pDC			= pView->GetDC();		//得到VIEW的DC

	
	if(m_bIsToGetBadPixel)
	{
		//得到坏点位置
		DetectDeadPixel(m_pRawBuffer,m_pBadPixel,Width,Height);
		m_bIsToGetBadPixel = FALSE;
	}
	if(m_bIsToRemoveBadPixel)
	{   
		//消除坏点
		EraseDeadPixel(m_pRawBuffer,m_pBadPixel,0,0,Width,Height,Width,Height);
	}

	if(m_bIsToGetTemplate)
	{
		if(m_nTempTimes ==0)  //第一次作的时候必须清零
			memset(m_pPatternBuf,'\0',sizeof(int)*Width * Height);		
		//取10次模板,然后平均
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
		//使用模板对图像数据进行校正
		FixPatternNoise(m_pRawBuffer,m_pPatternBuf,0,0,Width,Height,Width,Height);
	}
	
    //同时将原始数据进行上下翻转
	ConvertBayer2Rgb(m_pImageBuffer,m_pRawBuffer,Width,Height,ConvertType,m_pLutR,m_pLutG,m_pLutB,true,Layout);


	BYTE *p = NULL, * q = NULL;	
	//	进行图像反色
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
	//在视图客户区显示图像
	StretchDIBits(pDC->GetSafeHdc(),
					0,						
					0,
					Width,					//显示窗口宽度
					Height,					//显示窗口高度
					0,
					0,
					Width,					//图像宽度
					Height,					//图像高度
					m_pImageBuffer,			//图像缓冲区
					m_pBmpInfo,				//BMP图像描述信息
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
	 *	用户在没有通过菜单项正常关闭数字摄像机采集，	
	 *	而直接关闭应用程序时，应保证数字摄像机采集被关闭
	 */
	if (m_bOpen) {
		HVCloseSnap(m_hhv);
	}

	CFrameWnd::OnClose();
}

void CMainFrame::OnNegative() 
{
	// TODO: Add your command handler code here
	m_bNegative = !m_bNegative;			//重置图像反色标志
}

void CMainFrame::OnUpdateNegative(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bNegative);
}

void CMainFrame::OnGetBadpixel() 
{

	CString strMsg = "请确认已经将镜头完全遮盖!";
	
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
	CString strMsg = "请确认已经将镜头面对均匀光线!";
	
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
	函数:
		SetExposureTime
	输入参数:
		int nWindWidth			当前图像宽度		
		int lTintUpper			曝光时间的分子，shutter的取值
		int lTintLower			曝光时间的分母，与shutter的单位相关
								（ms:1000；s:1）
	输出参数:
		无						
	说明:
		设置曝光时间（其他的参数如摄像机时钟频率，消隐值都取默认值）
 */
void CMainFrame::SetExposureTime(int nWindWidth,long lTintUpper,long lTintLower)
{
	int size = sizeof(HVTYPE);
	HVTYPE type;
	HVGetDeviceInfo(m_hhv,DESC_DEVICE_TYPE, &type, &size);	
	
	//请参考曝光系数转换公式
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



















































































































































