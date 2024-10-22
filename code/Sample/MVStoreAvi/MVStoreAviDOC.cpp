// MVStoreAviDoc.cpp : implementation of the CMVStoreAviDoc class
//

#include "stdafx.h"
#include "MVStoreAvi.h"

#include "MVStoreAviDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviDoc

IMPLEMENT_DYNCREATE(CMVStoreAviDoc, CDocument)

BEGIN_MESSAGE_MAP(CMVStoreAviDoc, CDocument)
	//{{AFX_MSG_MAP(CMVStoreAviDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviDoc construction/destruction

CMVStoreAviDoc::CMVStoreAviDoc()
{
	// TODO: add one-time construction code here

}

CMVStoreAviDoc::~CMVStoreAviDoc()
{
}

BOOL CMVStoreAviDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviDoc serialization

void CMVStoreAviDoc::Serialize(CArchive& ar)
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
// CMVStoreAviDoc diagnostics

#ifdef _DEBUG
void CMVStoreAviDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMVStoreAviDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviDoc commands
