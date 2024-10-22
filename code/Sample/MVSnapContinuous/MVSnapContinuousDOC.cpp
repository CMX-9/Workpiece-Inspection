// MVSnapContinuousDoc.cpp : implementation of the CMVSnapContinuousDoc class
//

#include "stdafx.h"
#include "MVSnapContinuous.h"

#include "MVSnapContinuousDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousDoc

IMPLEMENT_DYNCREATE(CMVSnapContinuousDoc, CDocument)

BEGIN_MESSAGE_MAP(CMVSnapContinuousDoc, CDocument)
	//{{AFX_MSG_MAP(CMVSnapContinuousDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousDoc construction/destruction

CMVSnapContinuousDoc::CMVSnapContinuousDoc()
{
	// TODO: add one-time construction code here

}

CMVSnapContinuousDoc::~CMVSnapContinuousDoc()
{
}

BOOL CMVSnapContinuousDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousDoc serialization

void CMVSnapContinuousDoc::Serialize(CArchive& ar)
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
// CMVSnapContinuousDoc diagnostics

#ifdef _DEBUG
void CMVSnapContinuousDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMVSnapContinuousDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousDoc commands
