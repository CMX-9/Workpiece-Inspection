// MVSnapContinuousView.cpp : implementation of the CMVSnapContinuousView class
//

#include "stdafx.h"
#include "MVSnapContinuous.h"

#include "MVSnapContinuousDoc.h"
#include "MVSnapContinuousView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousView

IMPLEMENT_DYNCREATE(CMVSnapContinuousView, CView)

BEGIN_MESSAGE_MAP(CMVSnapContinuousView, CView)
	//{{AFX_MSG_MAP(CMVSnapContinuousView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousView construction/destruction

CMVSnapContinuousView::CMVSnapContinuousView()
{
	// TODO: add construction code here

}

CMVSnapContinuousView::~CMVSnapContinuousView()
{
}

BOOL CMVSnapContinuousView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousView drawing

void CMVSnapContinuousView::OnDraw(CDC* pDC)
{
	CMVSnapContinuousDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousView printing

BOOL CMVSnapContinuousView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMVSnapContinuousView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMVSnapContinuousView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousView diagnostics

#ifdef _DEBUG
void CMVSnapContinuousView::AssertValid() const
{
	CView::AssertValid();
}

void CMVSnapContinuousView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMVSnapContinuousDoc* CMVSnapContinuousView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMVSnapContinuousDoc)));
	return (CMVSnapContinuousDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVSnapContinuousView message handlers
