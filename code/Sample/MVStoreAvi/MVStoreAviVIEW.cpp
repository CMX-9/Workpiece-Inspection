// MVStoreAviView.cpp : implementation of the CMVStoreAviView class
//

#include "stdafx.h"
#include "MVStoreAvi.h"

#include "MVStoreAviDoc.h"
#include "MVStoreAviView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviView

IMPLEMENT_DYNCREATE(CMVStoreAviView, CView)

BEGIN_MESSAGE_MAP(CMVStoreAviView, CView)
	//{{AFX_MSG_MAP(CMVStoreAviView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviView construction/destruction

CMVStoreAviView::CMVStoreAviView()
{
	// TODO: add construction code here

}

CMVStoreAviView::~CMVStoreAviView()
{
}

BOOL CMVStoreAviView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviView drawing

void CMVStoreAviView::OnDraw(CDC* pDC)
{
	CMVStoreAviDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviView printing

BOOL CMVStoreAviView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMVStoreAviView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMVStoreAviView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviView diagnostics

#ifdef _DEBUG
void CMVStoreAviView::AssertValid() const
{
	CView::AssertValid();
}

void CMVStoreAviView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMVStoreAviDoc* CMVStoreAviView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMVStoreAviDoc)));
	return (CMVStoreAviDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVStoreAviView message handlers
