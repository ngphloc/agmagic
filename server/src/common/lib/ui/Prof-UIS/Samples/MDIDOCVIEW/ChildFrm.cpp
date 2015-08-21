// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "MDIDOCVIEW.h"

#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Modify this function to change how the frame is activated.

	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::PreTranslateMessage(MSG* pMsg) 
{
CMainFrame * pMainFrame =
		STATIC_DOWNCAST( CMainFrame, GetParentFrame() );
	ASSERT_VALID( pMainFrame );
	if( pMainFrame->m_wndMenuBar.TranslateMainFrameMessage(pMsg) )
		return TRUE;
	return CMDIChildWnd::PreTranslateMessage(pMsg);
}

void CChildFrame::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	// OnWindowPosChanged() and OnNcPaint() methods
	// implemented to fix WinXP MDI interface flicker bug
CMDIFrameWnd * pMdiFrame =
		STATIC_DOWNCAST( CMDIFrameWnd, GetParentFrame() );
	ASSERT_VALID( pMdiFrame );
BOOL bMax = FALSE;
CMDIChildWnd * pActive = pMdiFrame->MDIGetActive( &bMax );
	pActive;
	if( ! bMax )
	{
		CMDIChildWnd::OnWindowPosChanged(lpwndpos);
		return;
	} // if( ! bMax )
	SetRedraw( FALSE );
	CMDIChildWnd::OnWindowPosChanged(lpwndpos);
	SetRedraw( TRUE );
	RedrawWindow(
		NULL, NULL,
		RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN|RDW_FRAME
		);
}

void CChildFrame::OnNcPaint() 
{
	// OnWindowPosChanged() and OnNcPaint() methods
	// implemented to fix WinXP MDI interface flicker bug
CMDIFrameWnd * pMdiFrame =
		STATIC_DOWNCAST( CMDIFrameWnd, GetParentFrame() );
	ASSERT_VALID( pMdiFrame );
BOOL bMax = FALSE;
CMDIChildWnd * pActive = pMdiFrame->MDIGetActive( &bMax );
	pActive;
	if( bMax )
		return;
	CMDIChildWnd::OnNcPaint();
}
