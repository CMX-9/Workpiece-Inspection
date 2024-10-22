// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__55959B3C_1487_4680_966F_94508330A9E1__INCLUDED_)
#define AFX_STDAFX_H__55959B3C_1487_4680_966F_94508330A9E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#define IS_USB_HV130(type)	       ((type) == (HV1300UCTYPE) || (type) == (HV1300UMTYPE) ||\
									(type) == (HV1301UCTYPE) || (type) == (HV1302UMTYPE) ||\
									(type) == (HV1302UCTYPE) || (type) == (HV1303UMTYPE) ||\
									(type) == (HV1303UCTYPE) || (type) == (HV1350UMTYPE) ||\
									(type) == (HV1350UCTYPE) || (type) == (HV1351UMTYPE) ||\
									(type) == (HV1351UCTYPE))

#define IS_USB_HV200(type)		   ((type) == (HV2000UCTYPE) || (type) == (HV2001UCTYPE) ||\
									(type) == (HV2002UCTYPE) || (type) == (HV2003UCTYPE) ||\
									(type) == (HV2050UCTYPE) || (type) == (HV2051UCTYPE))

#define IS_USB_HV300(type)		   ((type) == (HV3000UCTYPE) || (type) == (HV3102UCTYPE) ||\
									(type) == (HV3103UCTYPE) || (type) == (HV3150UCTYPE) ||\
									(type) == (HV3151UCTYPE))

#define IS_USB_GV400(type)		   ((type) == (GV400UCTYPE) || (type) == (GV400UMTYPE))

#define IS_USB_HV5051(type)        ((type) == (HV5051UCTYPE) || (type) == (HV5051UMTYPE))


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__55959B3C_1487_4680_966F_94508330A9E1__INCLUDED_)
