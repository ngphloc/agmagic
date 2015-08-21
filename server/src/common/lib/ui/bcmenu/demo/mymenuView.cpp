// mymenuView.cpp : implementation of the CMymenuView class
//

#include "stdafx.h"
#include "mymenu.h"
#include "MainFrm.h"
#include "mymenuDoc.h"
#include "mymenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMymenuView

IMPLEMENT_DYNCREATE(CMymenuView, CView)

BEGIN_MESSAGE_MAP(CMymenuView, CView)
//{{AFX_MSG_MAP(CMymenuView)
ON_WM_RBUTTONDOWN()
ON_WM_MEASUREITEM()
ON_WM_MENUCHAR()
ON_COMMAND(ID_HOMEPAGE, OnHomepage)
ON_COMMAND(ID_MEDIA, OnMedia)
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMymenuView construction/destruction

CMymenuView::CMymenuView()
{
}

CMymenuView::~CMymenuView()
{
}

BOOL CMymenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMymenuView drawing

void CMymenuView::OnDraw(CDC* /*pDC*/) //SK: removed warning C4100: 'pDC' : unreferenced formal parameter
{
	CMymenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMymenuView printing

BOOL CMymenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMymenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMymenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMymenuView diagnostics

#ifdef _DEBUG
void CMymenuView::AssertValid() const
{
	CView::AssertValid();
}

void CMymenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMymenuDoc* CMymenuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMymenuDoc)));
	return (CMymenuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMymenuView message handlers

void CMymenuView::OnRButtonDown(UINT /*nFlags*/, CPoint point) //SK: removed warning C4100: 'nFlags' : unreferenced formal parameter
{
	popmenu.LoadMenu(IDR_RIGHT_CLICK);
	popmenu.LoadToolbar(IDR_TOOLBAR);
	popmenu.LoadToolbar(IDR_MAINFRAME);
	ClientToScreen(&point);
	BCMenu *psub = (BCMenu *)popmenu.GetSubMenu(0);
	BCMenu *pSelect = (BCMenu *)psub->GetSubMenu(1);
	if(pSelect){
		pSelect->AppendMenu(MF_STRING,ID_WINDOW_TILE_HORZ,_T("&Tile"));
		pSelect->ModifyODMenu(NULL,ID_WINDOW_TILE_HORZ,IDB_WINDOW_TILE);
	}
	psub->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
	popmenu.DestroyMenu();
}

void CMymenuView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	BOOL setflag=FALSE;
	if(lpMeasureItemStruct->CtlType==ODT_MENU){
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID)&&BCMenu::IsMenu((HMENU)lpMeasureItemStruct->itemID)){
			popmenu.MeasureItem(lpMeasureItemStruct);
			setflag=TRUE;
		}
	}
	if(!setflag)CView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CMymenuView::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lresult;
	if(BCMenu::IsMenu(pMenu))
		lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
		lresult=CView::OnMenuChar(nChar, nFlags, pMenu);
	return(lresult);
}

void CMymenuView::OnHomepage() 
{
	ShellExecute(::GetDesktopWindow(),_T("open"),//SK modified for Unicode
		_T("http://www.rocscience.com/~corkum/BCMenu.html"),NULL,NULL,//SK modified for Unicode
		SW_MAXIMIZE);
}

void CMymenuView::OnMedia() 
{
}
