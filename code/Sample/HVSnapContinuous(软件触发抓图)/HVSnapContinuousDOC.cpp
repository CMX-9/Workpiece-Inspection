// HVSnapContinuousDoc.cpp : implementation of the CHVSnapContinuousDoc class
//

#include "stdafx.h"
#include "HVSnapContinuous.h"

#include "HVSnapContinuousDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousDoc

IMPLEMENT_DYNCREATE(CHVSnapContinuousDoc, CDocument)

BEGIN_MESSAGE_MAP(CHVSnapContinuousDoc, CDocument)
	//{{AFX_MSG_MAP(CHVSnapContinuousDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousDoc construction/destruction

CHVSnapContinuousDoc::CHVSnapContinuousDoc()
{
	// TODO: add one-time construction code here

}

CHVSnapContinuousDoc::~CHVSnapContinuousDoc()
{
}

BOOL CHVSnapContinuousDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousDoc serialization

void CHVSnapContinuousDoc::Serialize(CArchive& ar)
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
// CHVSnapContinuousDoc diagnostics

#ifdef _DEBUG
void CHVSnapContinuousDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHVSnapContinuousDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousDoc commands
