// MVViewerDoc.cpp : implementation of the CMVViewerDoc class
//

#include "stdafx.h"
#include "MVViewer.h"

#include "MVViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVViewerDoc

IMPLEMENT_DYNCREATE(CMVViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMVViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CMVViewerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVViewerDoc construction/destruction

CMVViewerDoc::CMVViewerDoc()
{
	// TODO: add one-time construction code here

}

CMVViewerDoc::~CMVViewerDoc()
{
}

BOOL CMVViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMVViewerDoc serialization

void CMVViewerDoc::Serialize(CArchive& ar)
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
// CMVViewerDoc diagnostics

#ifdef _DEBUG
void CMVViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMVViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVViewerDoc commands
