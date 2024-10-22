// MVSnapSingleDoc.cpp : implementation of the CMVSnapSingleDoc class
//

#include "stdafx.h"
#include "MVSnapSingle.h"

#include "MVSnapSingleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleDoc

IMPLEMENT_DYNCREATE(CMVSnapSingleDoc, CDocument)

BEGIN_MESSAGE_MAP(CMVSnapSingleDoc, CDocument)
	//{{AFX_MSG_MAP(CMVSnapSingleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleDoc construction/destruction

CMVSnapSingleDoc::CMVSnapSingleDoc()
{
	// TODO: add one-time construction code here

}

CMVSnapSingleDoc::~CMVSnapSingleDoc()
{
}

BOOL CMVSnapSingleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleDoc serialization

void CMVSnapSingleDoc::Serialize(CArchive& ar)
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
// CMVSnapSingleDoc diagnostics

#ifdef _DEBUG
void CMVSnapSingleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMVSnapSingleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleDoc commands
