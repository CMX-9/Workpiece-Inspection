// MVRealtimeView.cpp : implementation of the CMVRealtimeView class
//

#include "stdafx.h"
#include "MVRealtime.h"

#include "MVRealtimeDoc.h"
#include "MVRealtimeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeView

IMPLEMENT_DYNCREATE(CMVRealtimeView, CView)

BEGIN_MESSAGE_MAP(CMVRealtimeView, CView)
	//{{AFX_MSG_MAP(CMVRealtimeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeView construction/destruction

CMVRealtimeView::CMVRealtimeView()
{
	// TODO: add construction code here

}

CMVRealtimeView::~CMVRealtimeView()
{
}

BOOL CMVRealtimeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeView drawing

void CMVRealtimeView::OnDraw(CDC* pDC)
{
	CMVRealtimeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeView printing

BOOL CMVRealtimeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMVRealtimeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMVRealtimeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeView diagnostics

#ifdef _DEBUG
void CMVRealtimeView::AssertValid() const
{
	CView::AssertValid();
}

void CMVRealtimeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMVRealtimeDoc* CMVRealtimeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMVRealtimeDoc)));
	return (CMVRealtimeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVRealtimeView message handlers
