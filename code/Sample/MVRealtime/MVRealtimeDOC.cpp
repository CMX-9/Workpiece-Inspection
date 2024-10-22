// MVRealtimeDoc.cpp : implementation of the CMVRealtimeDoc class
//

#include "stdafx.h"
#include "MVRealtime.h"

#include "MVRealtimeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeDoc

IMPLEMENT_DYNCREATE(CMVRealtimeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMVRealtimeDoc, CDocument)
	//{{AFX_MSG_MAP(CMVRealtimeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeDoc construction/destruction

CMVRealtimeDoc::CMVRealtimeDoc()
{
	// TODO: add one-time construction code here

}

CMVRealtimeDoc::~CMVRealtimeDoc()
{
}

BOOL CMVRealtimeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeDoc serialization

void CMVRealtimeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeDoc diagnostics

#ifdef _DEBUG
void CMVRealtimeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMVRealtimeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeDoc commands
