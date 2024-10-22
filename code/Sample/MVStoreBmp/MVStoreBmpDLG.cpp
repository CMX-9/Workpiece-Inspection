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

//�����Լ���0
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
	 *	��ʼ�����г�Ա������ͬʱ�����������
	 */

	//	����������� 1������״ֵ̬
	status = BeginHVDevice(DeviceNum, &hhv);
	//	���麯��ִ��״̬�����ʧ�ܣ��򷵻ش���״̬��Ϣ��
	HV_VERIFY(status);

	
	/*
	 *	��ʼ�����������Ӳ��״̬���û�Ҳ����������λ�ó�ʼ�������������
	 *	��Ӧ��֤����������Ѿ��򿪣������û���Ӧ�ó����ʼ��ʱ��
	 *	ͬʱ��ʼ�����������Ӳ����
	 */

	//	��������������ֱ���
	HVSetResolution(hhv, Resolution);		

	//	�ɼ�ģʽ������ CONTINUATION(����)��TRIGGER(�ⴥ��)
	HVSetSnapMode(hhv, SnapMode);

	//  ���ø�������������
	for (int i = 0; i < 4; i++){
		HVAGCControl(hhv, RED_CHANNEL + i, Gain);
	}
	
	//	�����ع�ʱ��
	SetExposureTime(hhv,Width,ExposureTint_Upper,ExposureTint_Lower);
	//  ����ADC�ļ���
	HVADCControl(hhv, ADC_BITS, ADCLevel);
	
	/*
	 *	��Ƶ������ڣ�����Ƶ�����Χ���������ȡֵ��Χ���������봰�ڷ�Χ���ڣ�
	 *  ��Ƶ�������Ͻ�X����ʹ��ڿ��ӦΪ4�ı��������Ͻ�Y����ʹ��ڸ߶�ӦΪ2�ı���
	 *	������ڵ���ʼλ��һ������Ϊ(0, 0)���ɡ�
	 */
	HVSetOutputWindow(hhv, XStart, YStart, Width, Height);

	/*
	 *	����ԭʼͼ�񻺳�����һ�������洢�ɼ�ͼ��ԭʼ����
	 *  һ��ͼ�񻺳�����С��������ڴ�С����Ƶ��ʽȷ����
	 */
	BYTE *pRawBuffer = new BYTE[Width * Height];
	ASSERT(pRawBuffer);

	/*
		����Bayerת����ͼ�����ݻ���
	*/
	BYTE *pImageBuffer = new BYTE[Width * Height * 3];
	ASSERT(pImageBuffer);

	//	����BITMAPINFO���� 
	BYTE *pInfoBuffer = new BYTE[sizeof(BITMAPINFO)];
	ASSERT(pInfoBuffer);

	/*
	 *	��ʼ��BITMAPINFO �ṹ���˽ṹ�ڱ���bmp�ļ�����ʾ�ɼ�ͼ��ʱʹ��
	 */
	//	m_pBmpInfo��ָ��m_chBmpBuf���������û������Լ�����BTIMAPINFO������	
	BITMAPINFO *pBmpInfo				= (BITMAPINFO *)pInfoBuffer;	
	pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	// 	ͼ���ȣ�һ��Ϊ������ڿ��
	pBmpInfo->bmiHeader.biWidth			= Width;
	//	ͼ���ȣ�һ��Ϊ������ڸ߶�
	pBmpInfo->bmiHeader.biHeight		= Height;
	//	ͼ��λ��ȣ�����������ɼ���ԭʼ����Ϊ8λ��Bayerת����Ϊ24λ
	pBmpInfo->bmiHeader.biBitCount		= 24;
	//	��������һ����ͬ�����ڵ���8λ��λͼ����Ӧ������Ӧ��λͼ��ɫ��
	pBmpInfo->bmiHeader.biPlanes		= 1;
	pBmpInfo->bmiHeader.biCompression	= BI_RGB;
	pBmpInfo->bmiHeader.biSizeImage		= 0;
	pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	pBmpInfo->bmiHeader.biClrUsed		= 0;
	pBmpInfo->bmiHeader.biClrImportant	= 0;
		
	// 	�ɼ�1֡ͼ���ڴ棬�ɼ���ɺ�ֹͣ
	BYTE *ppBuf[1];
	ppBuf[0] = pRawBuffer;
	status = HVSnapShot(hhv, ppBuf,1);
	HV_VERIFY(status);

	if (HV_SUCCESS(status)) {
		//	��ԭʼͼ�����ݽ���Bayerת����ת����Ϊ24λ��
		//ͬʱ��ԭʼ���ݽ������·�ת

		//��ɫ���ұ�
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
		 *	���±���BMP�ļ����û�����ͬ
		 */
		CFileDialog dlg(FALSE , "*.bmp", NULL ,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY, "Bitmap Files(*.bmp)|*.bmp", this);
		if (dlg.DoModal() == IDOK) {
			BITMAPFILEHEADER bfh	= {0};
			DWORD dwImageSize		= 0;
			DWORD dwBytesRead		= 0;
			BOOL bRVal				= TRUE;

			dwImageSize		=  Width * Height * 3;	//����ͼ���С������Ƶ������ں���Ƶ��ʽȷ��

			bfh.bfType		= (WORD)'M' << 8 | 'B';			//�����ļ�����
			bfh.bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	//�����ļ�ͷ��С

			bfh.bfSize		= bfh.bfOffBits + dwImageSize;		//�ļ���С

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

	//	�ر����������1
	status = EndHVDevice(hhv);
	HV_VERIFY(status);
	
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
void CMVStoreBmpDlg::SetExposureTime(HHV hhv,int nWindWidth,long lTintUpper,long lTintLower)
{
	int size = sizeof(HVTYPE);
	HVTYPE type;
	HVGetDeviceInfo(hhv,DESC_DEVICE_TYPE, &type, &size);	
	
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
	HVAECControl(hhv, AEC_EXPOSURE_TIME, (long)dExposure);
}