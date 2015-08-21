// MyView.cpp : implementation file
//

#include "stdafx.h"
#include "mymenu.h"
#include "MyView.h"
#include "BCMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

CMyView::CMyView()
{
}

CMyView::~CMyView()
{
}


BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers


void CMyView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
  static UINT toolbars[]={
    IDR_MAINFRAME,
    IDR_TOOLBAR
  };

  BCMenu menuPopup;
  menuPopup.CreatePopupMenu();
  menuPopup.AppendMenu(MF_STRING,ID_EDIT_CUT,_T("Cu&t\tCtrl+X"));
  menuPopup.AppendMenu(MF_STRING,ID_EDIT_COPY,_T("&Copy\tCtrl+C"));
  menuPopup.AppendMenu(MF_STRING,ID_EDIT_PASTE,_T("&Paste\tCtrl+V"));
  menuPopup.AppendMenu(MF_SEPARATOR,0,NULL);
  menuPopup.AppendMenu(MF_STRING,ID_ZOOM,_T("&Zoom"));
  menuPopup.LoadToolbars(toolbars,2); 
  ClientToScreen(&point);
  menuPopup.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
  menuPopup.DestroyMenu();
}

void CMyView::OnDraw(CDC* /*pDC*/) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}
