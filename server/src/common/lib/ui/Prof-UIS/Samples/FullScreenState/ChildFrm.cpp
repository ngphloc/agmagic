// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "FullScreenState.h"

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
		ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
		ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
	m_hChildFrameIcon = NULL;
HINSTANCE hInstResource =
		AfxFindResourceHandle(
			MAKEINTRESOURCE(IDR_MDITYPE),
			RT_GROUP_ICON
			);
	ASSERT( hInstResource != NULL );
	if( hInstResource != NULL )
	{
		m_hChildFrameIcon =
			(HICON)::LoadImage(
				hInstResource,
				MAKEINTRESOURCE(IDR_MDITYPE),
				IMAGE_ICON,
				16,
				16,
				0
				);
		ASSERT( m_hChildFrameIcon != NULL );
	}
}

CChildFrame::~CChildFrame()
{

	if( m_hChildFrameIcon != NULL )
	{
		::DestroyIcon( m_hChildFrameIcon );
	}

}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
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
void CChildFrame::OnFileClose() 
{
	// To close the frame, just send a WM_CLOSE, which is the equivalent
	// choosing close from the system menu.

	SendMessage(WM_CLOSE);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ASSERT( m_hChildFrameIcon != NULL );
	SetIcon( m_hChildFrameIcon, FALSE );
	SetIcon( m_hChildFrameIcon, TRUE );

	return 0;
}

BOOL CChildFrame::PreTranslateMessage(MSG* pMsg) 
{
CMainFrame * pMainFrame =
		DYNAMIC_DOWNCAST(
			CMainFrame,
			::AfxGetMainWnd()
			);
	ASSERT_VALID( pMainFrame );
	if( pMainFrame->m_wndMenuBar.TranslateMainFrameMessage(pMsg) )
		return TRUE;
	
	return CMDIChildWnd::PreTranslateMessage(pMsg);
}

BOOL CChildFrame::OnEraseBkgnd(CDC* pDC) 
{
	pDC;
	return TRUE;
}

void CChildFrame::OnPaint() 
{
CPaintDC dc( this );
CRect rcClipBox;
	dc.GetClipBox( &rcClipBox );
	dc.FillSolidRect(
		&rcClipBox,
		g_PaintManager->GetColor(COLOR_3DFACE)
		);
}

BOOL CChildFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if( nHitTest == HTCLIENT )
	{
		SetCursor( ::LoadCursor(NULL,IDC_ARROW) );
		return TRUE;
	}
	return CMDIChildWnd::OnSetCursor(pWnd, nHitTest, message);
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