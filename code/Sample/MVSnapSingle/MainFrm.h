// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__64EA849E_C7B7_442D_B8F8_558E0389B8CB__INCLUDED_)
#define AFX_MAINFRM_H__64EA849E_C7B7_442D_B8F8_558E0389B8CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\..\inc\HVDAILT.h"
#include "..\..\inc\Raw2Rgb.h"



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
	afx_msg void OnSnapShot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	HHV	m_hhv;			//������������

	BITMAPINFO *m_pBmpInfo;		//BITMAPINFO �ṹָ�룬��ʾͼ��ʱʹ��
	BYTE *m_pRawBuffer;			//�ɼ�ͼ��ԭʼ���ݻ�����
	BYTE *m_pImageBuffer;		//Bayerת���󻺳���
    char m_chBmpBuf[2048];		//BIMTAPINFO �洢��������m_pBmpInfo��ָ��˻�����

	//��ɫ���ұ�
	BYTE m_pLutR[256] ;
	BYTE m_pLutG[256] ;
	BYTE m_pLutB[256] ;	

	void SetExposureTime(int nWindWidth,long lTintUpper,long lTintLower);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__64EA849E_C7B7_442D_B8F8_558E0389B8CB__INCLUDED_)
