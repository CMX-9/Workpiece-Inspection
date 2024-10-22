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

//�����Լ���0
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
	 *	��ʼ�����г�Ա������ͬʱ�����������
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

	//	����������� 1
	HVSTATUS status = BeginHVDevice(1, &m_hhv);
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
			
			//	����AVI�ļ�
			hr = AVIFileOpen(&m_pFile, // returned file pointer
							dlg.GetPathName(), // file name
							OF_WRITE | OF_CREATE, // mode to open file with
							NULL); // use handler determined
			// from file extension....
			if (hr != AVIERR_OK){
				bRVal = FALSE;
			}
			else{
				AVISTREAMINFO strhdr;		//AVI�ļ���Ϣ
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
			 *	��ʼ������������ɼ�ͼ���ڴ�Ŀ��ƣ�
			 *	ָ���ص�����SnapThreadCallbackEx���û�����m_hWnd
			 */
			status = HVOpenSnap(m_hhv, SnapThreadCallback, m_hWnd);					
			HV_VERIFY(status);
			if ( HV_SUCCESS(status)) {			//�Ѿ���SnapEx����				
				//	��������������ɼ�ͼ���ڴ�
				BYTE *ppBuf[1];
				ppBuf[0] = m_pRawBuffer;
				status = HVStartSnap(m_hhv, ppBuf,1);
				
				HV_VERIFY(status);
				if (HV_SUCCESS(status)) {
					m_bStart = TRUE;			//��־��ʼͼ��Ĳɼ���ѹ��
				}
				else{
					HVCloseSnap(m_hhv);
				}
			}
		}
		
		//	��ֹAVI�ļ�
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

	//	�رղɼ�ͼ���ڴ���ƣ��ͷ������������Դ
	HVCloseSnap(m_hhv);

	//	��ֹAVI�ļ�
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
	 *	�����Զ�����ϢWM_SNAPCHANGE�������ڣ�	
	 *	ע�⣺��SendMessage������Ϣ������ȴ���Ϣ������Ϻ󣬲����˳�����SendMessage����
	 */
	::SendMessage(hwnd, WM_SNAP_CHANGE, 0, 0);
	
	return 1;
}



/*
	����:
		OnSnapExChange
	�������:
		WPARAM wParam			�ֲ���������Ϣ��Ϊ��ǰ���Դ����ͼ�����		
		LPARAM lParam			û��ʹ��
	�������:
		LRESULT						
	˵��:
		ʵ�ֶԲɼ����ݵĴ������ʾ
 */
LRESULT CMainFrame::OnSnapExChange(WPARAM wParam, LPARAM lParam)
{
	//	��ԭʼͼ�����ݽ���Bayerת����ת����Ϊ24λ��
    //ͬʱ��ԭʼ���ݽ������·�ת
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
	 *	�û���û��ͨ���˵��������ر�����������ɼ���	
	 *	��ֱ�ӹر�Ӧ�ó���ʱ��Ӧ��֤����������ɼ����ر�
	 */
	if (m_bStart) {
		SendMessage(WM_COMMAND, ID_AVI_STOP, 0);
	}
	
	CFrameWnd::OnClose();
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
