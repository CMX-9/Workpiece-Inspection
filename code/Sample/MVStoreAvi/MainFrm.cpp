// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MVStoreAvi.h"

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
	ON_COMMAND(ID_AVI_START, OnAviStart)
	ON_UPDATE_COMMAND_UI(ID_AVI_START, OnUpdateAviStart)
	ON_COMMAND(ID_AVI_STOP, OnAviStop)
	ON_UPDATE_COMMAND_UI(ID_AVI_STOP, OnUpdateAviStop)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	
	ON_MESSAGE(WM_SNAP_CHANGE, OnSnapExChange)

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

//定义自己的0
#define  MY_ZERO 0.000000001
//const
//const
const int DeviceNum = 1;
const HV_RESOLUTION Resolution = RES_MODE0;
const HV_SNAP_MODE SnapMode = CONTINUATION;
const HV_BAYER_LAYOUT Layout = BAYER_GR;//GV400Ux(BAYER_BG)
const HV_BAYER_CONVERT_TYPE ConvertType = BAYER2RGB_NEIGHBOUR;
const long Gain = 8;
const long ExposureTint_Upper = 60;
const long ExposureTint_Lower = 1000;

const long ShutterDelay = 0;
const long ADCLevel = ADC_LEVEL2;
const int XStart = 0;
const int YStart = 0;
const int Width = 752;
const int Height = 480;


CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	/*
	 *	初始化所有成员变量，同时打开数字摄像机
	 */
	m_bStart		= FALSE;
	
	m_pBmpInfo		= NULL;
	m_pImageBuffer	= NULL;

	m_pFile			= NULL;
	m_ps			= NULL;
	m_psCompressed	= NULL;

	m_nTimeFrame	= 0;

	for(int i=0;i<256;i++)
	{
		m_pLutR[i] = i;
		m_pLutG[i] = i;
		m_pLutB[i] = i;
	}	

	//	打开数字摄像机 1
	HVSTATUS status = BeginHVDevice(1, &m_hhv);
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


void CMainFrame::OnAviStart() 
{
	// TODO: Add your command handler code here
	HVSTATUS status = STATUS_OK;
	
	WORD wVer = 0;
	HRESULT hr = S_OK;
	BOOL bRVal = TRUE;

	CFileDialog dlg(FALSE , "*.avi", NULL ,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY, "AVI Files(*.avi)|*.avi", this);
	if (dlg.DoModal() == IDOK) {
		wVer = HIWORD(VideoForWindowsVersion());
		if ( !(wVer < 0x010a)){   /* oops, we are too old, blow out of here */
			AVIFileInit();

			// For some reason AVIFileOpen will not shrink the file even with OF_CREATE set
			::DeleteFile(dlg.GetPathName());
			
			//	创建AVI文件
			hr = AVIFileOpen(&m_pFile, // returned file pointer
							dlg.GetPathName(), // file name
							OF_WRITE | OF_CREATE, // mode to open file with
							NULL); // use handler determined
			// from file extension....
			if (hr != AVIERR_OK){
				bRVal = FALSE;
			}
			else{
				AVISTREAMINFO strhdr;		//AVI文件信息
				memset(&strhdr, 0, sizeof(strhdr));
				
				strhdr.fccType = streamtypeVIDEO;// stream type
				strhdr.fccHandler = 0;
				strhdr.dwScale = 1;
				strhdr.dwRate = 15; // rate fps
				strhdr.dwSuggestedBufferSize = Width * Height * 3;
				SetRect(&strhdr.rcFrame, 0, 0, Width, Height);// rectangle for stream
				
				// And create the stream;
				HRESULT hr = AVIFileCreateStream(m_pFile, // file pointer
												&m_ps, // returned stream pointer
												&strhdr); // stream header
				if (hr != AVIERR_OK){
					bRVal = FALSE;
				}
				else{
					AVICOMPRESSOPTIONS opts;
					AVICOMPRESSOPTIONS FAR * aopts[1] = {&opts};
					memset(&opts, 0, sizeof(opts));
					
					if (!AVISaveOptions(NULL, 0, 1, &m_ps, (LPAVICOMPRESSOPTIONS FAR *) &aopts)){
						bRVal = FALSE;
					}
					else{
						hr = AVIMakeCompressedStream(&m_psCompressed, m_ps, &opts, NULL);
						if (hr != AVIERR_OK) {
							bRVal = FALSE;
						}
						else{
							hr = AVIStreamSetFormat(m_psCompressed, 
								0,
								m_pBmpInfo, // stream format
								sizeof(BITMAPINFOHEADER) // format size
								);
							if (hr != AVIERR_OK) {
								bRVal = FALSE;
							}
						}
					}
				}
			}	
		}
			
		if ( bRVal) {
			/*
			 *	初始化数字摄像机采集图像到内存的控制，
			 *	指定回调函数SnapThreadCallbackEx和用户参数m_hWnd
			 */
			status = HVOpenSnap(m_hhv, SnapThreadCallback, m_hWnd);					
			HV_VERIFY(status);
			if ( HV_SUCCESS(status)) {			//已经打开SnapEx环境				
				//	启动数字摄像机采集图像到内存
				BYTE *ppBuf[1];
				ppBuf[0] = m_pRawBuffer;
				status = HVStartSnap(m_hhv, ppBuf,1);
				
				HV_VERIFY(status);
				if (HV_SUCCESS(status)) {
					m_bStart = TRUE;			//标志开始图像的采集和压缩
				}
				else{
					HVCloseSnap(m_hhv);
				}
			}
		}
		
		//	终止AVI文件
		if ( !m_bStart) {
			if (m_ps){
				AVIStreamClose(m_ps);
				m_ps = NULL;
			}
			if (m_psCompressed){
				AVIStreamClose(m_psCompressed);
				m_psCompressed = NULL;
			}
			if (m_pFile){
				AVIFileClose(m_pFile);
				m_pFile = NULL;
			}
			AVIFileExit();
		}		
	}
}



void CMainFrame::OnUpdateAviStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bStart);
	pCmdUI->SetCheck(m_bStart);
}

void CMainFrame::OnAviStop() 
{
	// TODO: Add your command handler code here

	//	关闭采集图像到内存控制，释放数字摄像机资源
	HVCloseSnap(m_hhv);

	//	终止AVI文件
	if (m_ps){
		AVIStreamClose(m_ps);
		m_ps = NULL;
	}
	if (m_psCompressed){
		AVIStreamClose(m_psCompressed);
		m_psCompressed = NULL;
	}
	if (m_pFile){
		AVIFileClose(m_pFile);
		m_pFile = NULL;
	}	
	AVIFileExit();

	m_nTimeFrame	= 0;
	m_bStart		= FALSE;
}


void CMainFrame::OnUpdateAviStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bStart);
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
	 *	发送自定义消息WM_SNAPCHANGE到主窗口，	
	 *	注意：用SendMessage发送消息，必须等待消息处理完毕后，才能退出整个SendMessage函数
	 */
	::SendMessage(hwnd, WM_SNAP_CHANGE, 0, 0);
	
	return 1;
}



/*
	函数:
		OnSnapExChange
	输入参数:
		WPARAM wParam			字参数，在消息中为当前可以处理的图像序号		
		LPARAM lParam			没有使用
	输出参数:
		LRESULT						
	说明:
		实现对采集数据的处理和显示
 */
LRESULT CMainFrame::OnSnapExChange(WPARAM wParam, LPARAM lParam)
{
	//	将原始图像数据进行Bayer转换，转换后为24位。
    //同时将原始数据进行上下翻转
	ConvertBayer2Rgb(m_pImageBuffer,m_pRawBuffer,Width,Height,ConvertType,m_pLutR,m_pLutG,m_pLutB,true,Layout);
	

	if (m_psCompressed) {
		HRESULT hr = AVIStreamWrite(m_psCompressed, // stream pointer
									m_nTimeFrame, // time of this frame
									1, // number to write
									m_pImageBuffer,
									Width * Height * 3, // lpbi->biSizeImage, // size of this frame
									AVIIF_KEYFRAME, // flags....
									NULL,
									NULL
									);
		if (hr == AVIERR_OK){
			m_nTimeFrame++;
		}
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
	if (m_bStart) {
		SendMessage(WM_COMMAND, ID_AVI_STOP, 0);
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
