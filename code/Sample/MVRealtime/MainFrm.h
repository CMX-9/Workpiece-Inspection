// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EB02BF30_EAF6_4BC5_9BD4_B266FB8C9988__INCLUDED_)
#define AFX_MAINFRM_H__EB02BF30_EAF6_4BC5_9BD4_B266FB8C9988__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//数字摄像机SDK的HVVideo模块头文件
#include "..\..\inc\HVDAILT.h"
#include "..\..\inc\Raw2Rgb.h"

//自定义消息ID号
#define WM_SNAP_CHANGE		(WM_USER + 100)


class CMainFrame : public CFrameWnd
{
	
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

protected:  // control bar embedded members
	

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSnapexOpen();
	afx_msg void OnUpdateSnapexOpen(CCmdUI* pCmdUI);
	afx_msg void OnSnapexStart();
	afx_msg void OnUpdateSnapexStart(CCmdUI* pCmdUI);
	afx_msg void OnSnapexStop();
	afx_msg void OnUpdateSnapexStop(CCmdUI* pCmdUI);
	afx_msg void OnSnapexClose();
	afx_msg void OnUpdateSnapexClose(CCmdUI* pCmdUI);
	afx_msg LRESULT OnSnapChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnNegative();
	afx_msg void OnUpdateNegative(CCmdUI* pCmdUI);
	afx_msg void OnGetBadpixel();
	afx_msg void OnUpdateGetBadpixel(CCmdUI* pCmdUI);
	afx_msg void OnGetTemplate();
	afx_msg void OnUpdateGetTemplate(CCmdUI* pCmdUI);
	afx_msg void OnRemoveBadpixel();
	afx_msg void OnUpdateRemoveBadpixel(CCmdUI* pCmdUI);
	afx_msg void OnUseTemplate();
	afx_msg void OnUpdateUseTemplate(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	HHV	m_hhv;			//数字摄像机句柄
	
	BOOL m_bOpen;		//初始化标志
	BOOL m_bStart;		//启动标志
	
	BITMAPINFO *m_pBmpInfo;		//BITMAPINFO 结构指针，显示图像时使用
	BYTE *m_pRawBuffer;			//采集图像原始数据缓冲区
	BYTE *m_pImageBuffer;		//Bayer转换后缓冲区
    char m_chBmpBuf[2048];		//BIMTAPINFO 存储缓冲区，m_pBmpInfo即指向此缓冲区

	int *m_pPatternBuf;    //用来进行模板测试的缓冲区
	int m_nTempTimes;       //取模板的次数
	BYTE *m_pBadPixel;

	BOOL m_bIsToGetBadPixel;
	BOOL m_bIsToRemoveBadPixel;	
	BOOL m_bIsToGetTemplate;
	BOOL m_bIsUseTemplate;
	/*
	 *	Snap 回调函数，用户也可以定义为全局函数， 
	 *	如果作为类的成员函数，必须为静态成员函数。
	 */
	static int CALLBACK SnapThreadCallback(HV_SNAP_INFO *pInfo); 
	
	BOOL m_bNegative;
	
	//颜色查找表
	BYTE m_pLutR[256] ;
	BYTE m_pLutG[256] ;
	BYTE m_pLutB[256] ;

	void SetExposureTime(int nWindWidth,long lTintUpper,long lTintLower);
	

public:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EB02BF30_EAF6_4BC5_9BD4_B266FB8C9988__INCLUDED_)










































