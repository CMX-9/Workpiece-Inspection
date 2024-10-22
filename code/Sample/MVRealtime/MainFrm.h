// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EB02BF30_EAF6_4BC5_9BD4_B266FB8C9988__INCLUDED_)
#define AFX_MAINFRM_H__EB02BF30_EAF6_4BC5_9BD4_B266FB8C9988__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//���������SDK��HVVideoģ��ͷ�ļ�
#include "..\..\inc\HVDAILT.h"
#include "..\..\inc\Raw2Rgb.h"

//�Զ�����ϢID��
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

	HHV	m_hhv;			//������������
	
	BOOL m_bOpen;		//��ʼ����־
	BOOL m_bStart;		//������־
	
	BITMAPINFO *m_pBmpInfo;		//BITMAPINFO �ṹָ�룬��ʾͼ��ʱʹ��
	BYTE *m_pRawBuffer;			//�ɼ�ͼ��ԭʼ���ݻ�����
	BYTE *m_pImageBuffer;		//Bayerת���󻺳���
    char m_chBmpBuf[2048];		//BIMTAPINFO �洢��������m_pBmpInfo��ָ��˻�����

	int *m_pPatternBuf;    //��������ģ����ԵĻ�����
	int m_nTempTimes;       //ȡģ��Ĵ���
	BYTE *m_pBadPixel;

	BOOL m_bIsToGetBadPixel;
	BOOL m_bIsToRemoveBadPixel;	
	BOOL m_bIsToGetTemplate;
	BOOL m_bIsUseTemplate;
	/*
	 *	Snap �ص��������û�Ҳ���Զ���Ϊȫ�ֺ����� 
	 *	�����Ϊ��ĳ�Ա����������Ϊ��̬��Ա������
	 */
	static int CALLBACK SnapThreadCallback(HV_SNAP_INFO *pInfo); 
	
	BOOL m_bNegative;
	
	//��ɫ���ұ�
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










































