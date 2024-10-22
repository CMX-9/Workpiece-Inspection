// MVStoreBmpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MVStoreBmp.h"
#include "MVStoreBmpDlg.h"

#include "..\..\inc\HVDAILT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//定义自己的0
#define  MY_ZERO 0.000000001
#include "..\..\inc\Raw2Rgb.h"


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


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVStoreBmpDlg dialog

CMVStoreBmpDlg::CMVStoreBmpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMVStoreBmpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMVStoreBmpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMVStoreBmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMVStoreBmpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMVStoreBmpDlg, CDialog)
	//{{AFX_MSG_MAP(CMVStoreBmpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_SAVE_BMP, OnSaveBmp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVStoreBmpDlg message handlers

BOOL CMVStoreBmpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMVStoreBmpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMVStoreBmpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMVStoreBmpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




void CMVStoreBmpDlg::OnSaveBmp() 
{
	// TODO: Add your control notification handler code here
	
	HVSTATUS status = STATUS_OK;
	HHV hhv = NULL;

	/*
	 *	初始化所有成员变量，同时打开数字摄像机
	 */

	//	打开数字摄像机 1，返回状态值
	status = BeginHVDevice(DeviceNum, &hhv);
	//	检验函数执行状态，如果失败，则返回错误状态消息框
	HV_VERIFY(status);

	
	/*
	 *	初始化数字摄像机硬件状态，用户也可以在其他位置初始化数字摄像机，
	 *	但应保证数字摄像机已经打开，建议用户在应用程序初始化时，
	 *	同时初始化数字摄像机硬件。
	 */

	//	设置数字摄像机分辨率
	HVSetResolution(hhv, Resolution);		

	//	采集模式，包括 CONTINUATION(连续)、TRIGGER(外触发)
	HVSetSnapMode(hhv, SnapMode);

	//  设置各个分量的增益
	for (int i = 0; i < 4; i++){
		HVAGCControl(hhv, RED_CHANNEL + i, Gain);
	}
	
	//	设置曝光时间
	SetExposureTime(hhv,Width,ExposureTint_Upper,ExposureTint_Lower);
	//  设置ADC的级别
	HVADCControl(hhv, ADC_BITS, ADCLevel);
	
	/*
	 *	视频输出窗口，即视频输出范围，输出窗口取值范围必须在输入窗口范围以内，
	 *  视频窗口左上角X坐标和窗口宽度应为4的倍数，左上角Y坐标和窗口高度应为2的倍数
	 *	输出窗口的起始位置一般设置为(0, 0)即可。
	 */
	HVSetOutputWindow(hhv, XStart, YStart, Width, Height);

	/*
	 *	分配原始图像缓冲区，一般用来存储采集图像原始数据
	 *  一般图像缓冲区大小由输出窗口大小和视频格式确定。
	 */
	BYTE *pRawBuffer = new BYTE[Width * Height];
	ASSERT(pRawBuffer);

	/*
		分配Bayer转换后图像数据缓冲
	*/
	BYTE *pImageBuffer = new BYTE[Width * Height * 3];
	ASSERT(pImageBuffer);

	//	分配BITMAPINFO缓冲 
	BYTE *pInfoBuffer = new BYTE[sizeof(BITMAPINFO)];
	ASSERT(pInfoBuffer);

	/*
	 *	初始化BITMAPINFO 结构，此结构在保存bmp文件、显示采集图像时使用
	 */
	//	m_pBmpInfo即指向m_chBmpBuf缓冲区，用户可以自己分配BTIMAPINFO缓冲区	
	BITMAPINFO *pBmpInfo				= (BITMAPINFO *)pInfoBuffer;	
	pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	// 	图像宽度，一般为输出窗口宽度
	pBmpInfo->bmiHeader.biWidth			= Width;
	//	图像宽度，一般为输出窗口高度
	pBmpInfo->bmiHeader.biHeight		= Height;
	//	图像位深度，数字摄像机采集的原始数据为8位，Bayer转换后为24位
	pBmpInfo->bmiHeader.biBitCount		= 24;
	//	以下设置一般相同，对于低于8位的位图，还应设置相应的位图调色板
	pBmpInfo->bmiHeader.biPlanes		= 1;
	pBmpInfo->bmiHeader.biCompression	= BI_RGB;
	pBmpInfo->bmiHeader.biSizeImage		= 0;
	pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	pBmpInfo->bmiHeader.biClrUsed		= 0;
	pBmpInfo->bmiHeader.biClrImportant	= 0;
		
	// 	采集1帧图像到内存，采集完成后停止
	BYTE *ppBuf[1];
	ppBuf[0] = pRawBuffer;
	status = HVSnapShot(hhv, ppBuf,1);
	HV_VERIFY(status);

	if (HV_SUCCESS(status)) {
		//	将原始图像数据进行Bayer转换，转换后为24位。
		//同时将原始数据进行上下翻转

		//颜色查找表
		BYTE pLutR[256] ;
		BYTE pLutG[256] ;
		BYTE pLutB[256] ;
		for(int i=0;i<256;i++)
		{
			pLutR[i] = i;
			pLutG[i] = i;
			pLutB[i] = i;
		}		
		ConvertBayer2Rgb(pImageBuffer,pRawBuffer,Width,Height,ConvertType,pLutR,pLutG,pLutB,true,Layout);
		
		/*	
		 *	以下保存BMP文件设置基本相同
		 */
		CFileDialog dlg(FALSE , "*.bmp", NULL ,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY, "Bitmap Files(*.bmp)|*.bmp", this);
		if (dlg.DoModal() == IDOK) {
			BITMAPFILEHEADER bfh	= {0};
			DWORD dwImageSize		= 0;
			DWORD dwBytesRead		= 0;
			BOOL bRVal				= TRUE;

			dwImageSize		=  Width * Height * 3;	//计算图像大小，由视频输出窗口和视频格式确定

			bfh.bfType		= (WORD)'M' << 8 | 'B';			//定义文件类型
			bfh.bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	//定义文件头大小

			bfh.bfSize		= bfh.bfOffBits + dwImageSize;		//文件大小

			HANDLE hFile = ::CreateFile(dlg.GetPathName(),
										GENERIC_WRITE ,
										0,
										NULL,
										CREATE_ALWAYS,														FILE_ATTRIBUTE_NORMAL,
										NULL
										);
			if (hFile == INVALID_HANDLE_VALUE) {
				bRVal = FALSE;
			}
			else{
				::WriteFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwBytesRead, NULL );
				::WriteFile(hFile, pBmpInfo, sizeof(BITMAPINFOHEADER), &dwBytesRead, NULL );
				::WriteFile(hFile, pImageBuffer, dwImageSize, &dwBytesRead, NULL );
				
				CloseHandle(hFile);
			}
		}
	}

	delete []pRawBuffer;	
	delete []pImageBuffer;	
	delete []pInfoBuffer;

	//	关闭数字摄像机1
	status = EndHVDevice(hhv);
	HV_VERIFY(status);
	
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
void CMVStoreBmpDlg::SetExposureTime(HHV hhv,int nWindWidth,long lTintUpper,long lTintLower)
{
	int size = sizeof(HVTYPE);
	HVTYPE type;
	HVGetDeviceInfo(hhv,DESC_DEVICE_TYPE, &type, &size);	
	
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
	HVAECControl(hhv, AEC_EXPOSURE_TIME, (long)dExposure);
}