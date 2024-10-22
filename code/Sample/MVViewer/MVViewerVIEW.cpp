// MVViewerView.cpp : implementation of the CMVViewerView class
//

#include "stdafx.h"
#include "MVViewer.h"

#include "MVViewerDoc.h"
#include "MVViewerView.h"

#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

unsigned int recognitionFlag;

/////////////////////////////////////////////////////////////////////////////
// CMVViewerView

IMPLEMENT_DYNCREATE(CMVViewerView, CView)

BEGIN_MESSAGE_MAP(CMVViewerView, CView)
	//{{AFX_MSG_MAP(CMVViewerView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDRecognize, OnRecognize)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVViewerView construction/destruction

CMVViewerView::CMVViewerView()
{
	// TODO: add construction code here

}

CMVViewerView::~CMVViewerView()
{
}

BOOL CMVViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMVViewerView drawing

void CMVViewerView::OnDraw(CDC* pDC)
{


	CMainFrame *pFrame = NULL;
	int nCxCoef = 1, nCyCoef = 1;
	int nWidth = 0, nHeight = 0;
	
	CMVViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// TODO: add draw code for native data here
	pFrame = (CMainFrame *)AfxGetMainWnd();
	if (pFrame && pFrame->m_pImageBuffer){
		if ( ! pFrame->m_bSnapping){
			if ((pFrame->m_hPalette) && (pFrame->m_pBmpInfo->bmiHeader.biBitCount == 8)) {
				pFrame->m_hOldPal = ::SelectPalette(pDC->GetSafeHdc(), pFrame->m_hPalette, FALSE);			
				::RealizePalette(pDC->GetSafeHdc());
			}
			
			SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
			if (pDC->IsPrinting()) {				
				nCxCoef = pDC->GetDeviceCaps(LOGPIXELSX);
				nCyCoef	= pDC->GetDeviceCaps(LOGPIXELSY);
				nWidth = (int)((float)pFrame->m_pBmpInfo->bmiHeader.biWidth / 96 * nCxCoef);
				nHeight	= (int)((float)pFrame->m_pBmpInfo->bmiHeader.biHeight / 96 * nCyCoef);
				
				StretchDIBits(pDC->GetSafeHdc(),
					0,
					0,
					nWidth,
					nHeight,
					0,
					0,
					pFrame->m_pBmpInfo->bmiHeader.biWidth,
					pFrame->m_pBmpInfo->bmiHeader.biHeight,
					pFrame->m_pImageBuffer,
					pFrame->m_pBmpInfo,
					DIB_RGB_COLORS,
					SRCCOPY
					);
				
			}
			else{
				StretchDIBits(pDC->GetSafeHdc(),
					0,
					0,
					pFrame->m_pBmpInfo->bmiHeader.biWidth,
					pFrame->m_pBmpInfo->bmiHeader.biHeight,
					0,
					0,
					pFrame->m_pBmpInfo->bmiHeader.biWidth,
					pFrame->m_pBmpInfo->bmiHeader.biHeight,
					pFrame->m_pImageBuffer,
					pFrame->m_pBmpInfo,
					DIB_RGB_COLORS,
					SRCCOPY
					);
			}
			
			if ((pFrame->m_hOldPal) && (pFrame->m_pBmpInfo->bmiHeader.biBitCount == 8)) {
				::SelectPalette(pDC->GetSafeHdc(), pFrame->m_hOldPal, FALSE);
				::RealizePalette(pDC->GetSafeHdc());
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMVViewerView printing

BOOL CMVViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMVViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMVViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMVViewerView diagnostics

#ifdef _DEBUG
void CMVViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CMVViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMVViewerDoc* CMVViewerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMVViewerDoc)));
	return (CMVViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVViewerView message handlers

void CMVViewerView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	
	pFrame->SendMessage(WM_SIZE);
}



void CMVViewerView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	
	pFrame->SendMessage(WM_LBUTTONDOWN);
	
	CView::OnLButtonDown(nFlags, point);
}


void CMVViewerView::OnRecognize() 
{
	// TODO: Add your command handler code here
	static unsigned char counter = 0;

	counter++;
	if (1 == counter)
	{
		recognitionFlag = 1;
	}
	else if (2 == counter)
	{
		recognitionFlag = 0;
		counter = 0;
	}
}
