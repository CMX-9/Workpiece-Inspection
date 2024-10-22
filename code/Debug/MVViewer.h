// MVViewer.h : main header file for the MVViewer application
//

#if !defined(AFX_MVViewer_H__572C5FA4_4480_45D2_8AF5_6B4EB4BE114F__INCLUDED_)
#define AFX_MVViewer_H__572C5FA4_4480_45D2_8AF5_6B4EB4BE114F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMVViewerApp:
// See MVViewer.cpp for the implementation of this class
//

//自定义消息ID号
#define WM_CHANGE_SNAP		(WM_USER + 100)
#define WM_GET_RATIO		(WM_USER + 101)
#define WM_SNAP_ERROR		(WM_USER + 102)
#define WM_SNAP_STOP		(WM_USER + 103)

#define WIDTH_BYTES(bits)	(((bits) + 31) / 32 * 4)


class CMVViewerApp : public CWinApp
{
public:
	CMVViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVViewerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMVViewerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	HANDLE m_hOneInstance;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVViewer_H__572C5FA4_4480_45D2_8AF5_6B4EB4BE114F__INCLUDED_)
