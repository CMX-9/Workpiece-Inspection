// HVSnapContinuousView.cpp : implementation of the CHVSnapContinuousView class
//

#include "stdafx.h"
#include "HVSnapContinuous.h"

#include "HVSnapContinuousDoc.h"
#include "HVSnapContinuousView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousView

IMPLEMENT_DYNCREATE(CHVSnapContinuousView, CView)

BEGIN_MESSAGE_MAP(CHVSnapContinuousView, CView)
	//{{AFX_MSG_MAP(CHVSnapContinuousView)
	ON_COMMAND(ID_MENUITEM32775, OnMenuitem32775)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousView construction/destruction

CHVSnapContinuousView::CHVSnapContinuousView()
{
	// TODO: add construction code here

}

CHVSnapContinuousView::~CHVSnapContinuousView()
{
}

BOOL CHVSnapContinuousView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousView drawing

void CHVSnapContinuousView::OnDraw(CDC* pDC)
{
	CHVSnapContinuousDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousView printing

BOOL CHVSnapContinuousView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHVSnapContinuousView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHVSnapContinuousView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousView diagnostics

#ifdef _DEBUG
void CHVSnapContinuousView::AssertValid() const
{
	CView::AssertValid();
}

void CHVSnapContinuousView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHVSnapContinuousDoc* CHVSnapContinuousView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHVSnapContinuousDoc)));
	return (CHVSnapContinuousDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHVSnapContinuousView message handlers

void CHVSnapContinuousView::OnMenuitem32775() 
{
	// TODO: Add your command handler code here
	
}

void CHVSnapContinuousView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* fp=(CMainFrame*)AfxGetMainWnd();
	fp->SoftTrigger();
	CView::OnRButtonDown(nFlags, point);
}
