// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__4B30C2A7_6EF2_4E39_8536_4A56F405A510__INCLUDED_)
#define AFX_MAINFRM_H__4B30C2A7_6EF2_4E39_8536_4A56F405A510__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\inc\hvdailt.h"
#include "..\..\inc\Raw2Rgb.h"




//定义彩色图像还是黑白图像
typedef enum  tagHV_IMAGE_MODE
{
		HV_COLOR = 0,
		HV_BW = 1
}HV_IMAGE_MODE;

class CMainFrame : public CFrameWnd
{
	friend class CAdjustDlg;
	friend class CDelayDlg;
	friend class CWBDlg;
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewAdjust();
	afx_msg void OnViewSnap();
	afx_msg void OnUpdateViewSnap(CCmdUI* pCmdUI);
	afx_msg void OnFileOpenOne();
	afx_msg void OnFileSaveAsOne();
	afx_msg void OnViewSaveSerials();
	afx_msg void OnUpdateViewSaveSerials(CCmdUI* pCmdUI);
	afx_msg void OnViewWb();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnViewConversionBg();
	afx_msg void OnUpdateViewConversionBg(CCmdUI* pCmdUI);
	afx_msg void OnViewConversionGb();
	afx_msg void OnUpdateViewConversionGb(CCmdUI* pCmdUI);
	afx_msg void OnViewConversionGr();
	afx_msg void OnUpdateViewConversionGr(CCmdUI* pCmdUI);
	afx_msg void OnViewConversionRg();
	afx_msg void OnUpdateViewConversionRg(CCmdUI* pCmdUI);
	afx_msg void OnViewColor();
	afx_msg void OnUpdateViewColor(CCmdUI* pCmdUI);
	afx_msg void OnViewBw();
	afx_msg void OnUpdateViewBw(CCmdUI* pCmdUI);
	afx_msg void OnHelpWebsite();
	afx_msg void OnHelpMailto();
	afx_msg void OnViewContinuation();
	afx_msg void OnUpdateViewContinuation(CCmdUI* pCmdUI);
	afx_msg void OnViewTrigger();
	afx_msg void OnUpdateViewTrigger(CCmdUI* pCmdUI);
	afx_msg void OnViewSnapshot();
	afx_msg void OnUpdateViewSnapshot(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewWb(CCmdUI* pCmdUI);
	afx_msg void OnConversionBest();
	afx_msg void OnUpdateConversionBest(CCmdUI* pCmdUI);
	afx_msg void OnConversionFast();
	afx_msg void OnUpdateConversionFast(CCmdUI* pCmdUI);
	afx_msg void OnConversionNormal();
	afx_msg void OnUpdateConversionNormal(CCmdUI* pCmdUI);
	afx_msg void OnViewMode0();
	afx_msg void OnUpdateViewMode0(CCmdUI* pCmdUI);
	afx_msg void OnViewMode1();
	afx_msg void OnUpdateViewMode1(CCmdUI* pCmdUI);
	afx_msg void OnViewMode2();
	afx_msg void OnUpdateViewMode2(CCmdUI* pCmdUI);
	afx_msg void OnGammaCorrect();
	afx_msg void OnUpdateGammaCorrect(CCmdUI* pCmdUI);
	afx_msg void OnCancelGamma();
	afx_msg void OnUpdateCancelGamma(CCmdUI* pCmdUI);
	afx_msg void OnGetBadPiexes();
	afx_msg void OnUpdateGetBadPiexes(CCmdUI* pCmdUI);
	afx_msg void OnEliminateBadPixels();
	afx_msg void OnUpdateEliminateBadPixels(CCmdUI* pCmdUI);
	afx_msg void OnGetTemplate();
	afx_msg void OnUpdateGetTemplate(CCmdUI* pCmdUI);
	afx_msg void OnTemplateCorrect();
	afx_msg void OnUpdateTemplateCorrect(CCmdUI* pCmdUI);
	afx_msg void OnSnapspeedNormal();
	afx_msg void OnUpdateSnapspeedNormal(CCmdUI* pCmdUI);
	afx_msg void OnSnpaspeedHigh();
	afx_msg void OnUpdateSnpaspeedHigh(CCmdUI* pCmdUI);
	afx_msg void OnMenuitem32828();
	afx_msg void OnMenuitem32829();
	//}}AFX_MSG

	LRESULT OnSnapMessage(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetRatioMessage(WPARAM wParam, LPARAM lParam);
	LRESULT OnSnapError(WPARAM wParam, LPARAM lParam);
	LRESULT OnSnapStop(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

public:
	BOOL m_bSnapping;
	
	HPALETTE m_hPalette; 
	HPALETTE m_hOldPal;

	BITMAPINFO *m_pBmpInfo;  
	BYTE *m_pImageBuffer;   
	BYTE *pImageBuffer0;   //定义一个常量来储存转换前的灰度图
	BYTE *pImageBuffer;    //定义一个常量用来存储转换后的灰度图  
	unsigned int    g_imageWidth;               //图像宽度
    unsigned int    g_imageHeight;              //图像高度
	unsigned int    g_imageRow;                 //一行图像像素个数
	unsigned int    g_rowTargetPixelNum;        //已搜索的一行包含的目标点的像素个数
	unsigned int    g_targetPixelLeft;          //标志位：目标点的左侧发现黑点，应从当前行从头搜索
	unsigned int    g_targetPixelDown;          //标志位：目标点的下侧发现黑点，应退到前一行重新搜索
	unsigned int    g_imageClass[256];          //各类中黑点数目;g_imageClass[0]代表图像中目标个数
	unsigned int    g_objectNum[3];             //图像中目标的数目：0：螺母；1：螺钉
	unsigned int    g_classCoordinate[256][4];  //各类的边界
    unsigned char   g_classCategory[256];       //各类的类别：0：螺母；1：螺钉；2：无效目标

	int dwLastStatus; 
	int m_nLostNum;
	int m_nErrorNum;
	
private:
	HHV m_hhv;
	
	//Max video window
	int m_nMaxWidth;
	int m_nMaxHeight;
	
	//Child view margin
	int m_nMarginLeft;
	int m_nMarginTop;
	int m_nMarginRight;
	int m_nMarginBottom;

	BOOL m_bMinimized;

	//Screen parameters
	int m_nScreenWidth;
	int m_nScreenHeight;
	int m_nScreenBits;

	HV_RESOLUTION m_Resolution;
	HV_SNAP_MODE m_SnapMode;

	long m_lGain[4];
	int m_lADCLevel;
	CRect m_rcOutputWindow;
	
	//White balance ratio
	double m_dRatioR;
	double m_dRatioG;
	double m_dRatioB;
	
	HV_IMAGE_MODE m_ImageMode;
	HV_BAYER_LAYOUT m_Layout;

	char m_chBmpBuf[2048];
	BYTE *m_pRawBuffer;

	DWORD m_dwCount;
	DWORD m_dwStart;

	CString m_strDeviceType;

	//颜色查找表
	BYTE m_pLutR[256] ;
	BYTE m_pLutG[256] ;
	BYTE m_pLutB[256] ;

	BYTE m_pLutGamma[256] ;
	BOOL m_bIsGammaCorrect;

	//曝光时间的分子和分母
	long m_lTintUpper;
	long m_lTintLower;

	//曝光模式
	HV_EXPOSURE_MODE m_ExposureMode;
	
	//the conversion method of raw to rgb
	HV_BAYER_CONVERT_TYPE m_ConversionType;
	//the variable to control the snap speed
	HV_SNAP_SPEED m_SnapSpeed;
	int m_nHBlanking;
	int m_nVBlanking;


	//映射文件句柄
	HANDLE m_hFileMapping;
	//映射内存指针
	PBYTE m_pLutMapping;


	double m_dGammRatio;    //gamma 校正系数
	int *m_pPatternBuf;    //用来进行模板测试的缓冲区
	BYTE *m_pBadPixelBuf;	//保存坏点位置的内存
	int m_nTempTimes;       //取模板的次数

	
	BOOL m_bIsToGetBadPixel;
	BOOL m_bIsToRemoveBadPixel;	
	BOOL m_bIsToGetTemplate;
	BOOL m_bIsTemplateCorrect;

	BOOL m_bIsSnapSpeedSprted;    //本摄像机是否支持设置采集速度
	BOOL m_bIsBlkSizeSprted;      //本摄像机是否支持设置取得消隐取值范围
	BOOL m_bIsExposureModeSprted; //本摄像机是否支持设置曝光模式

public:
	HVSTATUS GetLastStatus();
	//Get view window margin
	void UpdateMargin();		
	//call back function
	static int CALLBACK SnapCallback(HV_SNAP_INFO *pInfo);
	//Move window
	void AdjustWindow();
	void AdjustHBlanking();
private:
	void InitSystemInfo();
	void InitHVDevice();
	void InitParamFromINI();
	
	void FreeSystemResource();
	void SaveParamToINI();

	void DecodeImage();
	void ShowImage();

	//*******************自定义函数********************************//
	void ImageProcess(CDC *pDC);                                                                                  //图像处理
	void GrayOrRGBTo2();                                                                                          //图像二值化                                                                                        
	void PreProcess();                                                                                            //图像预处理
	void FindClass();                                                                                             //查找类别
	void MarkerNeighbourhood(unsigned int pixelClass,unsigned int width,unsigned int height);                     //查找3X3邻域联通点并予以标记    
	void UpdateBound(unsigned int pixelClass,unsigned int width,unsigned int height);                             //更新边界，判断当前点是否为该类的边界点
	void ImageRecognize();                                                                                        //模式识别
	void PourObject();                                                                                            //在原图上填充目标
    void TargetObject(CDC *pDC);                                                                                  //在原图中标注出目标
	void ObjectBlock(unsigned int upBound,unsigned int downBound,unsigned int leftBound,unsigned int rightBound); //框出目标
	void corrode();
	//*************************************************************//

	int GetFileExt(LPCSTR lpFileName);	
	BOOL OpenBMPFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pImageBuffer);
	BOOL SaveBMPFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pImageBuffer);
	BOOL OpenRawFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pRawBuffer);
	BOOL SaveRawFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pRawBuffer);	

	BOOL SetLutTable(double dRatioR,double dRatioG,double dRatioB);
	int GetOutputWinWdith();

	void Format24To8(BYTE *pDestBit8,BYTE *pSrceBit24, int nWid,int nHei);
	PBYTE CreateLutMapFile(LPCTSTR lpFileName);
	void SetExposureTime(int nWindWidth,long lTintUpper,long lTintLower);
	void SetBlanking(int nHBlanking,int nVBlanking);

	
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4B30C2A7_6EF2_4E39_8536_4A56F405A510__INCLUDED_)
