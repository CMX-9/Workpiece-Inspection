// MVRealtime.h : main header file for the MVRealtime application
//

#if !defined(AFX_MVRealtime_H__1A68C5BC_3467_49FD_9988_86700432C4B7__INCLUDED_)
#define AFX_MVRealtime_H__1A68C5BC_3467_49FD_9988_86700432C4B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeApp:
// See MVRealtime.cpp for the implementation of this class
//

class CMVRealtimeApp : public CWinApp
{
public:
	CMVRealtimeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVRealtimeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMVRealtimeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVRealtime_H__1A68C5BC_3467_49FD_9988_86700432C4B7__INCLUDED_)
