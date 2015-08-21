// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "StatusPanes.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_LIKE_OFFICE_2K, OnViewLikeOffice2k)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIKE_OFFICE_2K, OnUpdateViewLikeOffice2k)
	ON_COMMAND(ID_VIEW_LIKE_OFFICE_XP, OnViewLikeOfficeXp)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIKE_OFFICE_XP, OnUpdateViewLikeOfficeXp)
	ON_COMMAND(ID_VIEW_LIKE_OFFICE_2003, OnViewLikeOffice2003)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIKE_OFFICE_2003, OnUpdateViewLikeOffice2003)
	//}}AFX_MSG_MAP

	ON_COMMAND_EX( ID_VIEW_MENUBAR, OnBarCheck )
	ON_UPDATE_COMMAND_UI( ID_VIEW_MENUBAR, OnUpdateControlBarMenu )

	ON_COMMAND_EX( IDR_TOOLBAR2, OnBarCheck )
	ON_UPDATE_COMMAND_UI( IDR_TOOLBAR2, OnUpdateControlBarMenu )

END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	g_PaintManager.InstallPaintManager( new CExtPaintManagerXP );

	// window placement persistence
	::memset( &m_dataFrameWP, 0, sizeof(WINDOWPLACEMENT) );
	m_dataFrameWP.length = sizeof(WINDOWPLACEMENT);
	m_dataFrameWP.showCmd = SW_HIDE;

	m_pWndView = NULL;
}

CMainFrame::~CMainFrame()
{
}

static UINT g_statBasicCommands[] =
{
	ID_APP_ABOUT,
	ID_APP_EXIT,
	ID_VIEW_MENUBAR,
	ID_VIEW_TOOLBAR,
	IDR_TOOLBAR2,
	ID_VIEW_STATUS_BAR,
	ID_VIEW_LIKE_OFFICE_2K,
	ID_VIEW_LIKE_OFFICE_XP,
	ID_VIEW_LIKE_OFFICE_2003,
	0, // end of list
};

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	m_pWndView = new CChildFormView;
	if (!m_pWndView->Create(
		NULL, 
		NULL, 
		AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), 
		this, 
		AFX_IDW_PANE_FIRST, 
		NULL)
		)
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
CWinApp * pApp = ::AfxGetApp();
	ASSERT( pApp != NULL );
	ASSERT( pApp->m_pszRegistryKey != NULL );
	ASSERT( pApp->m_pszRegistryKey[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );
	ASSERT( pApp->m_pszProfileName[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );

HICON hIcon = pApp->LoadIcon( IDR_MAINFRAME );
	ASSERT( hIcon != NULL );
	SetIcon( hIcon, TRUE );
	SetIcon( hIcon, FALSE );

	g_CmdManager->ProfileSetup(
		pApp->m_pszProfileName,
		GetSafeHwnd()
		);
	VERIFY(
		g_CmdManager->UpdateFromMenu(
			pApp->m_pszProfileName,
			IDR_MAINFRAME
			)
		);

	if( !m_wndMenuBar.Create(
			NULL,
			this,
			ID_VIEW_MENUBAR
			)
		)
    {
        TRACE0("Failed to create menubar\n");
        return -1;      // failed to create
    }

	if( !m_wndToolBar.Create(
			_T("ToolBar"),
			this,
			AFX_IDW_TOOLBAR
			)
		||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)
		)
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if( !m_wndToolBar2.Create(
			_T("ToolBar2"),
			this,
			IDR_TOOLBAR2
			)
		||
		!m_wndToolBar2.LoadToolBar(IDR_TOOLBAR2)
		)
	{
		TRACE0("Failed to create toolbar2\n");
		return -1;      // fail to create
	}

CExtCmdItem * pCmdItem;

	pCmdItem =
		g_CmdManager->CmdGetPtr(
			pApp->m_pszProfileName,
			ID_VIEW_LIKE_OFFICE_2K
			);
	ASSERT( pCmdItem != NULL );
	pCmdItem->m_sToolbarText = _T("MS Office 2000");

	pCmdItem =
		g_CmdManager->CmdGetPtr(
			pApp->m_pszProfileName,
			ID_VIEW_LIKE_OFFICE_XP
			);
	ASSERT( pCmdItem != NULL );
	pCmdItem->m_sToolbarText = _T("MS Office XP");

	pCmdItem =
		g_CmdManager->CmdGetPtr(
			pApp->m_pszProfileName,
			ID_VIEW_LIKE_OFFICE_2003
			);
	ASSERT( pCmdItem != NULL );
	pCmdItem->m_sToolbarText = _T("MS Office 2003");

	/////////////////////////////////////////////////////////////////

	if(		!m_wndStatusBar.Create(this)
		||	!m_wndStatusBar.SetIndicators(
				indicators,
				sizeof(indicators) / sizeof(UINT)
			)
		)
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(20);
	
    m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2.EnableDocking(CBRS_ALIGN_ANY);

	if( !CExtControlBar::FrameEnableDocking(this) )
	{
		ASSERT( FALSE );
		return -1;
	}
	
	VERIFY(
		g_CmdManager->SetBasicCommands(
			pApp->m_pszProfileName,
			g_statBasicCommands
			)
		);

	if( !CExtControlBar::ProfileBarStateLoad(
			this,
			pApp->m_pszRegistryKey,
			pApp->m_pszProfileName,
			pApp->m_pszProfileName,
			&m_dataFrameWP
			)
		)
	{
		DockControlBar( &m_wndMenuBar );
		DockControlBar( &m_wndToolBar );
		RecalcLayout();
		CRect wrAlredyDockedBar;
		m_wndToolBar.GetWindowRect( &wrAlredyDockedBar );
		wrAlredyDockedBar.OffsetRect( 1, 0 );
		DockControlBar( &m_wndToolBar2, AFX_IDW_DOCKBAR_TOP, &wrAlredyDockedBar );
	
		RecalcLayout();
	}
	g_CmdManager->SerializeState(
		pApp->m_pszProfileName,
		pApp->m_pszRegistryKey,
		pApp->m_pszProfileName,
		false
		);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	pOldWnd;
	// forward focus to the view window
	m_pWndView->SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_pWndView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if( m_wndMenuBar.TranslateMainFrameMessage(pMsg) )
		return TRUE;
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::DestroyWindow() 
{
CWinApp * pApp = ::AfxGetApp();
	ASSERT( pApp != NULL );
	ASSERT( pApp->m_pszRegistryKey != NULL );
	ASSERT( pApp->m_pszRegistryKey[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );
	ASSERT( pApp->m_pszProfileName[0] != _T('\0') );

	VERIFY(
		CExtControlBar::ProfileBarStateSave(
			this,
			pApp->m_pszRegistryKey,
			pApp->m_pszProfileName,
			pApp->m_pszProfileName
			)
		);
	VERIFY(
		g_CmdManager->SerializeState(
			pApp->m_pszProfileName,
			pApp->m_pszRegistryKey,
			pApp->m_pszProfileName,
			true
			)
		);
	g_CmdManager->ProfileWndRemove( GetSafeHwnd() );
	
	return CFrameWnd::DestroyWindow();
}

void CMainFrame::OnViewLikeOffice2k() 
{
	if( !g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerXP) ) )
		return;
	VERIFY(
		g_PaintManager.InstallPaintManager( new CExtPaintManager )
		);
	RecalcLayout();
	RedrawWindow(
		NULL,
		NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE
			| RDW_FRAME | RDW_ALLCHILDREN
		);
	CExtControlBar::stat_RedrawFloatingFrames( this );
	CExtControlBar::stat_RecalcBarMetrics( this );
}
void CMainFrame::OnUpdateViewLikeOffice2k(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerXP) )
			? FALSE
			: TRUE
		);
}
void CMainFrame::OnViewLikeOfficeXp() 
{
	if(		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerXP) )
		&&	(! g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerOffice2003) ) )
		)
		return;
	VERIFY(
		g_PaintManager.InstallPaintManager( new CExtPaintManagerXP )
		);
	RecalcLayout();
	RedrawWindow(
		NULL,
		NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE
			| RDW_FRAME | RDW_ALLCHILDREN
		);
	CExtControlBar::stat_RedrawFloatingFrames( this );
	CExtControlBar::stat_RecalcBarMetrics( this );
}
void CMainFrame::OnUpdateViewLikeOfficeXp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		(	g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerXP) )
		&&	(! g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerOffice2003) ) )
		)	? TRUE
			: FALSE
		);
}
void CMainFrame::OnViewLikeOffice2003() 
{
	if( g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerOffice2003) ) )
		return;
	VERIFY(
		g_PaintManager.InstallPaintManager( new CExtPaintManagerOffice2003 )
		);
	RecalcLayout();
	RedrawWindow(
		NULL,
		NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE
			| RDW_FRAME | RDW_ALLCHILDREN
		);
	CExtControlBar::stat_RedrawFloatingFrames( this );
	CExtControlBar::stat_RecalcBarMetrics( this );
}
void CMainFrame::OnUpdateViewLikeOffice2003(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerOffice2003) )
			? TRUE
			: FALSE
		);
}

void CMainFrame::ActivateFrame(int nCmdShow) 
{
	// window placement persistence
	if( m_dataFrameWP.showCmd != SW_HIDE )
	{
		SetWindowPlacement( &m_dataFrameWP );
		CFrameWnd::ActivateFrame( m_dataFrameWP.showCmd );
		m_dataFrameWP.showCmd = SW_HIDE;
		return;
	}
	
	CFrameWnd::ActivateFrame(nCmdShow);
}
