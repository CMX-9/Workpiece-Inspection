// MVSnapSingleView.cpp : implementation of the CMVSnapSingleView class
//

#include "stdafx.h"
#include "MVSnapSingle.h"

#include "MVSnapSingleDoc.h"
#include "MVSnapSingleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleView

IMPLEMENT_DYNCREATE(CMVSnapSingleView, CView)

BEGIN_MESSAGE_MAP(CMVSnapSingleView, CView)
	//{{AFX_MSG_MAP(CMVSnapSingleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleView construction/destruction

CMVSnapSingleView::CMVSnapSingleView()
{
	// TODO: add construction code here

}

CMVSnapSingleView::~CMVSnapSingleView()
{
}

BOOL CMVSnapSingleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleView drawing

void CMVSnapSingleView::OnDraw(CDC* pDC)
{
	CMVSnapSingleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleView printing

BOOL CMVSnapSingleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMVSnapSingleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMVSnapSingleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleView diagnostics

#ifdef _DEBUG
void CMVSnapSingleView::AssertValid() const
{
	CView::AssertValid();
}

void CMVSnapSingleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMVSnapSingleDoc* CMVSnapSingleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMVSnapSingleDoc)));
	return (CMVSnapSingleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVSnapSingleView message handlers
