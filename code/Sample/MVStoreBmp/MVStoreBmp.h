// MVStoreBmp.h : main header file for the MVStoreBmp application
//

#if !defined(AFX_MVStoreBmp_H__4A0D2865_F48F_4044_A9D1_BAF088EEAA26__INCLUDED_)
#define AFX_MVStoreBmp_H__4A0D2865_F48F_4044_A9D1_BAF088EEAA26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMVStoreBmpApp:
// See MVStoreBmp.cpp for the implementation of this class
//

class CMVStoreBmpApp : public CWinApp
{
public:
	CMVStoreBmpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVStoreBmpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMVStoreBmpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVStoreBmp_H__4A0D2865_F48F_4044_A9D1_BAF088EEAA26__INCLUDED_)
