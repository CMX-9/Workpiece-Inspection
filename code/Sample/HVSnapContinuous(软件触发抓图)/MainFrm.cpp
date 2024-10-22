// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "HVSnapContinuous.h"
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
	ON_WM_CLOSE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//定义自己的0
#define  MY_ZERO 0.000000001

//const
const HV_RESOLUTION Resolution          = RES_MODE0;
const HV_SNAP_MODE SnapMode             = CONTINUATION;
const HV_BAYER_LAYOUT Layout            = BAYER_GR;//GV400Ux(BAYER_BG)
const HV_BAYER_CONVERT_TYPE ConvertType = BAYER2RGB_NEIGHBOUR;

const long Gain               = 8;
const long ExposureTint_Upper = 60;
const long ExposureTint_Lower = 1000;
const long ADCLevel           = ADC_LEVEL2;
const int XStart              = 0;
const int YStart              = 0;
const int Width               = 752;
const int Height              = 480;
const long lHBlanking         = 0;
const long lVBlanking         = 0;
const HV_SNAP_SPEED SnapSpeed = HIGH_SPEED;

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
	for (int i = 0; i < 4; i++){
		HVAGCControl(m_hhv, RED_CHANNEL + i, Gain);
	}

	//  设置ADC的级别
	HVADCControl(m_hhv, ADC_BITS, ADCLevel);
	
	/*
	*	视频输出窗口，即视频输出范围，输出窗口取值范围必须在输入窗口范围以内，
	*  视频窗口左上角X坐标和窗口宽度应为4的倍数，左上角Y坐标和窗口高度应为2的倍数
	*	输出窗口的起始位置一般设置为(0, 0)即可。
	*/
	HVSetOutputWindow(m_hhv, XStart, YStart, Width, Height);

	//设置水平消隐。
	HVSetBlanking(m_hhv, lHBlanking, lVBlanking);
	
	//设置采集速度
	HVSetSnapSpeed(m_hhv, SnapSpeed);

	//设置曝光时间
	SetExposureTime(Width, ExposureTint_Upper, ExposureTint_Lower, lHBlanking, SnapSpeed, Resolution);	

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
	 *	指定回调函数SnapThreadCallback和this指针
	 */
	status = HVOpenSnap(m_hhv, SnapThreadCallback, this);					
	HV_VERIFY(status);
	if (HV_SUCCESS(status)) {
		m_bOpen = TRUE;		//标志已经打开Snap环境
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
	//设置采集模式
	
//	HVSTATUS status = STATUS_OK;
	
	status = HVSetSnapMode(m_hhv,TRIGGER);//连续采集
		
	HV_VERIFY(status);
	
	
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
	CMainFrame *This = (CMainFrame *)(pInfo->pParam);
	HWND hwnd = This->m_hWnd;

	HVSTATUS status = This->GetLastStatus();	// 读取摄像机图像采集工作状态
	
	if(!HV_SUCCESS(status)){	//如果函数调用不成功，摄像机停止图像采集。
;//		::PostMessage(hwnd, WM_SNAP_STOP, 0, 0);
		return 1;
	}
	
	TRACE("LastStatus is %X", This->dwLastStatus);
	
	if(This->dwLastStatus == 0)	// 当状态值等于0时，表示摄像机图像采集正常，则调用SendMessage显示图像；
	{
	   /*
		*	发送自定义消息WM_SNAP_EX_CHANGE到主窗口，	
		*	同时传入当前可以处理的图像序号
		*	注意：用SendMessage发送消息，必须等待消息处理完毕后，才能退出整个SendMessage函数
		*/
		::PostMessage(hwnd, WM_SNAP_CHANGE, 0, 0);
		return 1;
		
	}
	else if(This->dwLastStatus == STATUS_FILE_INVALID)// 当状态值不等于-18时，表示摄像机发生1次丢帧行为
												//在连续高速采集时，1次丢帧行为可能包括1帧以上图像。
	{
		This->m_nLost++;	//丢帧计数
	}
	else if (This->dwLastStatus==0xc0000012 || This->dwLastStatus==0xc0000011)
	{
		This->m_nError++;	//错误计数
	}
	else // 当状态值为其他非0值时，表示摄像机图像采集异常
	{
	   /*
		*	发送自定义消息 WM_SNAP_ERROR 到主窗口，	
		*	注意：用PostMessage发送消息，不必等待消息处理完，就可以返回。
		*/
		::PostMessage(hwnd, WM_SNAP_ERROR, 0, This->dwLastStatus);
	}
	
	return 1;
}

/*
	函数:
		OnSnapError
	输入参数:
		WPARAM wParam			没有使用		
		LPARAM lParam			异常状态码
	输出参数:
		LRESULT						
	说明:
		摄像机采集异常错误报告
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
	
	//	将原始图像数据进行Bayer转换，转换后为24位。
    //同时将原始数据进行上下翻转
	ConvertBayer2Rgb(m_pImageBuffer,m_pRawBuffer,Width,Height,ConvertType,m_pLutR,m_pLutG,m_pLutB,true,Layout);
	
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

	SYSTEMTIME time;
	GetLocalTime(&time);
	CString strb,strj;
	strb.Format("e:\\%d%d%d-%d%d%d%d.bmp",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
	strj.Format("e:\\%d%d%d-%d%d%d%d.jpg",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
	if (m_pImageBuffer && m_pRawBuffer)
	{
		SaveBMPFile(strb, m_pBmpInfo, m_pImageBuffer);
		HVSaveJPEG((char *)(LPCSTR)strj, m_pImageBuffer, (int)(m_pBmpInfo->bmiHeader.biWidth),(int)(m_pBmpInfo->bmiHeader.biHeight), (int)(m_pBmpInfo->bmiHeader.biBitCount), TRUE, 100);
	}
	
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
HVSTATUS CMainFrame::SetExposureTime(int nWindWidth,
								 long lTintUpper,
								 long lTintLower,
								 long HBlanking,
								 HV_SNAP_SPEED SnapSpeed, 
								 HV_RESOLUTION Resolution)
{
	HVTYPE type;
	int size    = sizeof(HVTYPE);
	HVGetDeviceInfo(m_hhv,DESC_DEVICE_TYPE, &type, &size);	

	int nOutputWid = nWindWidth;

	double dExposure = 0.0;
	double dTint = max((double)lTintUpper/(double)lTintLower,MY_ZERO);

	double lClockFreq = 0.0;  
	if (IS_USB_GV400(type))
	{
		long lTb = HBlanking;
		lTb += 0x5e;	
		lClockFreq = (SnapSpeed == HIGH_SPEED)? 26600000.0:13300000.0; 		
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
			return STATUS_PARAMETER_OUT_OF_BOUND;
		}
		
		nOutputWid = nOutputWid * rate;	//width*rate
		if ((dTint * lClockFreq) <= (nOutputWid+ lTb - 255))
		{
			dExposure = 1;
		}
		else
			dExposure = ((dTint * lClockFreq) - (nOutputWid + lTb - 255) ) / (nOutputWid + lTb);				

		if (dExposure < 3) 
			dExposure = 3;
		else if (dExposure > 32766)
			dExposure = 32766;

	}
	else if( IS_USB_HV300(type))
	{
		lClockFreq = (SnapSpeed == HIGH_SPEED)? 24000000:12000000;
		long lTb = HBlanking;
		lTb += 142;
		if(lTb<21)
			lTb = 21;
		long lP1 = 331, lP2 = 38;
		long lp4 = 316;
		if(Resolution == RES_MODE1)
		{
			lP1 = 673;
			lP2 = 22;
			lp4 = 316*2;
		}
		long lAQ = (long)(nOutputWid + lP1 + lP2 + lTb);
		long lTrow = max(lAQ,(lP1+lp4));
		dExposure = ((dTint* lClockFreq)+ lP1 - 132.0)/lTrow;	
		
		if((dExposure-(int)dExposure) >0.5)
			dExposure += 1.0;		
		if(dExposure <= 0)
			dExposure = 1;
		else if(dExposure > 1048575) 
			dExposure = 1048575;
	}
	else if(IS_USB_HV200(type))
	{
		lClockFreq = (SnapSpeed == HIGH_SPEED)? 24000000:12000000;
		long lTb = HBlanking;
		lTb += 53;
		if(lTb<19)
			lTb = 19;
		long lAQ = (long)(nOutputWid + 305.0 + lTb);
		long lTrow = max(617,lAQ);
		dExposure = (dTint* lClockFreq + 180.0)/lTrow + 1;
		
		if((dExposure-(int)dExposure) >0.5)//四舍五入
			dExposure += 1.0;
		if(dExposure <= 0)
			dExposure = 1;
		else if(dExposure > 16383) 
			dExposure = 16383;
	}
	//else if(IS_USB_HV5051(type))
	//{
	//	SHUTTER_UNIT_VALUE nUnit = SHUTTER_MS;
	//	HVSTATUS status          = STATUS_OK;

	//	if (lTintLower == 1000000)
	//	{
	//		nUnit = SHUTTER_US;
	//	}
	//	
	//	//设置曝光时间单位
	//	status = HVAECControl(m_hhv, AEC_SHUTTER_UNIT, nUnit);
	//	if (!HV_SUCCESS(status))
	//	{
	//		return status;
	//	}
	//	
	//	//设置曝光时间。
	//	return HVAECControl(m_hhv, AEC_SHUTTER_SPEED, lTintUpper);			
	//}
	else
	{		
		lClockFreq = (SnapSpeed == HIGH_SPEED)? 24000000:12000000;
		long lTb = HBlanking;
		lTb += 9;
		lTb -= 19;	
		if(lTb <= 0) lTb =0;
		if(((double)nOutputWid + 244.0 + lTb ) > 552)	
			dExposure = (dTint* lClockFreq + 180.0)/((double)nOutputWid + 244.0 + lTb);
		else
			dExposure = ((dTint * lClockFreq)+ 180.0) / 552 ;

		if((dExposure-(int)dExposure) >0.5)
			dExposure += 1.0;
		if(dExposure <= 0)
			dExposure = 1;
		else if(dExposure > 16383) 
			dExposure = 16383;
	}

	return HVAECControl(m_hhv, AEC_EXPOSURE_TIME, (long)dExposure);
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

void CMainFrame::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HVSTATUS status = HVTriggerShot(m_hhv); //软触发命令
	
	HV_VERIFY(status);
	
	
	CFrameWnd::OnRButtonDown(nFlags, point);
}
void CMainFrame::SoftTrigger()
{
	HVSTATUS status = HVTriggerShot(m_hhv); //软触发命令
	
	HV_VERIFY(status);
	
}

bool CMainFrame::SaveBMPFile(LPCSTR lpFileName, BITMAPINFO* pBmpInfo, BYTE* pImageBuffer)
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
