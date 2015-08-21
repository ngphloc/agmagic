// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "AviFrames.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTypedPtrArray< CPtrArray, CMainFrame::CZoomBarSliderButton* > CMainFrame::CZoomBarSliderButton::g_arrButtons;
CTypedPtrArray< CPtrArray, CMainFrame::CSeekBarSliderButton* > CMainFrame::CSeekBarSliderButton::g_arrButtons;
BOOL CMainFrame::CSeekBarSliderButton::g_bSinchronizing = FALSE; 
BOOL CMainFrame::CZoomBarSliderButton::g_bSinchronizing = FALSE; 

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
	ON_COMMAND(ID_PLAY, OnPlay)
	ON_UPDATE_COMMAND_UI(ID_PLAY, OnUpdatePlay)
	ON_COMMAND(ID_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(ID_STOP, OnUpdateStop)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdatePause)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_TIMER()
	ON_COMMAND(ID_MYEXTBTN_SLIDER, OnSlider)
	ON_COMMAND(ID_MYEXTBTN_SCROLLER, OnScroller)
	//}}AFX_MSG_MAP

	ON_COMMAND_EX( ID_VIEW_MENUBAR, OnBarCheck )
	ON_UPDATE_COMMAND_UI( ID_VIEW_MENUBAR, OnUpdateControlBarMenu )

	ON_COMMAND_EX( IDR_TOOLBAR_UISTYLE, OnBarCheck )
	ON_UPDATE_COMMAND_UI( IDR_TOOLBAR_UISTYLE, OnUpdateControlBarMenu )
	
	ON_COMMAND_EX( IDR_TOOLBAR_PLAYER, OnBarCheck )
	ON_UPDATE_COMMAND_UI( IDR_TOOLBAR_PLAYER, OnUpdateControlBarMenu )
	
	ON_COMMAND_EX( IDR_TOOLBAR_SEEK, OnBarCheck )
	ON_UPDATE_COMMAND_UI( IDR_TOOLBAR_SEEK, OnUpdateControlBarMenu )
	
	ON_COMMAND_EX( IDR_TOOLBAR_ZOOM, OnBarCheck )
	ON_UPDATE_COMMAND_UI( IDR_TOOLBAR_ZOOM, OnUpdateControlBarMenu )

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
	g_PaintManager.InstallPaintManager( new CExtPaintManagerOffice2003 );

	// window placement persistence
	::memset( &m_dataFrameWP, 0, sizeof(WINDOWPLACEMENT) );
	m_dataFrameWP.length = sizeof(WINDOWPLACEMENT);
	m_dataFrameWP.showCmd = SW_HIDE;

	m_pWndView = NULL;
	m_pAviPlayer = NULL;

	CExtPopupMenuWnd::g_bMenuWithShadows = false;
}

CMainFrame::~CMainFrame()
{
	if(m_pAviPlayer)
		delete m_pAviPlayer;
}

static UINT g_statBasicCommands[] =
{
	ID_APP_ABOUT,
	ID_APP_EXIT,
	ID_VIEW_MENUBAR,
	ID_VIEW_TOOLBAR,
	IDR_TOOLBAR_UISTYLE,
	IDR_TOOLBAR_PLAYER,
	IDR_TOOLBAR_SEEK,
	IDR_TOOLBAR_ZOOM,
	ID_VIEW_STATUS_BAR,
	ID_FILE_OPEN,
	ID_PLAY,
	ID_STOP,
	ID_PAUSE,
	ID_VIEW_LIKE_OFFICE_2K,
	ID_VIEW_LIKE_OFFICE_XP,
	ID_VIEW_LIKE_OFFICE_2003,
	0, // end of list
};

//////////////////////////////////////////////////////////////////////////

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	m_pWndView = new CAviView;
	if( ! m_pWndView->Create( this ) )
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

	if( !m_wndToolBarPlayer.Create(
			_T("Player"),
			this,
			IDR_TOOLBAR_PLAYER
			)
		||
		!m_wndToolBarPlayer.LoadToolBar(IDR_TOOLBAR_PLAYER)
		)
	{
		TRACE0("Failed to create toolbar m_wndToolBarPlayer \n");
		return -1;      // fail to create
	}

	if( !m_wndToolBarUIStyle.Create(
			_T("UI Style"),
			this,
			IDR_TOOLBAR_UISTYLE
			)
		||
		!m_wndToolBarUIStyle.LoadToolBar(IDR_TOOLBAR_UISTYLE)
		)
	{
		TRACE0("Failed to create toolbar m_wndToolBarUIStyle\n");
		return -1;      // fail to create
	}

	/////////////////////////////////////////////////////////////////

	if( !m_wndToolBarSeek.Create(
		_T("Seek Slider"),
		this,
		IDR_TOOLBAR_SEEK)
		)
	{
		TRACE0("Failed to create toolbar m_wndToolBarSeek \n");
		return -1;      // fail to create
	}
	m_wndToolBarSeek.InitContentExpandButton();

	if( !m_wndToolBarZoom.Create(
		_T("Zoom Slider"),
		this,
		IDR_TOOLBAR_ZOOM)
		)
	{
		TRACE0("Failed to create toolbar m_wndToolBarZoom \n");
		return -1;      // fail to create
	}
	m_wndToolBarZoom.InitContentExpandButton();
	
	CExtCmdItem * pCmdItemSlider =
		g_CmdManager->CmdAllocPtr(
		pApp->m_pszProfileName,
		ID_MYEXTBTN_SLIDER
		);
	ASSERT( pCmdItemSlider != NULL );
	pCmdItemSlider->m_sToolbarText = _T("Zoom:");
	pCmdItemSlider->m_sMenuText = _T("Zoom slider");
	pCmdItemSlider->m_sTipTool
		= pCmdItemSlider->m_sTipStatus
		= _T("Zoom slider");
	
	CExtCmdItem * pCmdItemScroller =
		g_CmdManager->CmdAllocPtr(
		pApp->m_pszProfileName,
		ID_MYEXTBTN_SCROLLER
		);
	ASSERT( pCmdItemScroller != NULL );
	pCmdItemScroller->m_sToolbarText = _T("Seek:");
	pCmdItemScroller->m_sMenuText = _T("Seek slider");
	pCmdItemScroller->m_sTipTool
		= pCmdItemScroller->m_sTipStatus
		= _T("Seek slider");
	
	CZoomBarSliderButton *pZoomSliderTBB =
		new CZoomBarSliderButton(
		/////////////////
		// standard CExtBarButton parms
		/////////////////
		&m_wndToolBarZoom,
		ID_MYEXTBTN_SLIDER,
		0,
		/////////////////
		// CExtBarSliderButton specific parms
		/////////////////
		//
		// scroll total/pos/page
		11, 4, 0,
		// button extent horz(left/right)/vert(up/down) in pixels
		// (if zeros - use slider-like layout instead of scrollbar-like)
		0, 0,
		// total slider control extent horz/vert in pixels
		100, 100
		);
	VERIFY(
		m_wndToolBarZoom.InsertSpecButton(
		-1,
		pZoomSliderTBB,
		FALSE
		)
		);

	CSeekBarSliderButton *pSeekScrollerTBB = new CSeekBarSliderButton(
		/////////////////
		// standard CExtBarButton parms
		/////////////////
		&m_wndToolBarSeek,
		ID_MYEXTBTN_SCROLLER,
		0,
		/////////////////
		// CExtBarScrollerButton specific parms
		/////////////////
		//
		// scroll total/pos/page
		0, 0, 0,
		// button extent horz(left/right)/vert(up/down) in pixels
		// (if zeros - use slider-like layout instead of scrollbar-like)
		10, 10,
		// total slider control extent horz/vert in pixels
		300, 300
		);
	VERIFY(
		m_wndToolBarSeek.InsertSpecButton(
		-1,
		pSeekScrollerTBB,
		FALSE
		)
		);

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
	m_wndStatusBar.m_bHideTextOnDisabledPanes = false;
	m_wndStatusBar.m_bDrawPaneSeparatorsInsteadOfBorders = true;
	
	m_wndStatusBar.SetPaneWidth(0, 90);
	m_wndStatusBar.AddPane(IDS_PANE_ZOOM, 1);
	m_wndStatusBar.SetPaneWidth(1, 40);
	m_wndStatusBar.AddPane(IDS_PANE_FRAMES_TOTAL, 2);
	m_wndStatusBar.SetPaneWidth(2, 120);
	m_wndStatusBar.AddPane(IDS_PANE_CURRENT_FRAME, 3);
	m_wndStatusBar.SetPaneWidth(3, 120);
	m_wndStatusBar.AddPane(IDS_PANE_FRAMES_SKIPPED, 4);
	m_wndStatusBar.SetPaneWidth(4, 120);

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarUIStyle.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarPlayer.EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBarZoom.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarSeek.EnableDocking(CBRS_ALIGN_ANY);

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

	g_CmdManager->SerializeState(
		pApp->m_pszProfileName,
		pApp->m_pszRegistryKey,
		pApp->m_pszProfileName,
		false
		);

	//////////////////////////////////////////////////////////////////////////

#if (!defined __EXT_MFC_NO_CUSTOMIZE)
	VERIFY(
		CExtCustomizeSite::MenuInfoAdd(
		this,
		_T("Default"),
		IDR_MAINFRAME,
		true
		)
		);
	VERIFY(
		CExtCustomizeSite::MenuInfoLoadAccelTable(
		_T("Default"),
		IDR_MAINFRAME
		)
		);
	if( !CExtCustomizeSite::EnableCustomization(
		this,
		__ECSF_DEFAULT|__ECSF_PARMS_DISABLE_PERSONALIZED
		)
		)
	{
		ASSERT( FALSE );
		return -1;
	}
	CExtCustomizeSite::CategoryUpdate( IDR_MAINFRAME );
	CExtCustomizeSite::CategoryMakeAllCmdsUnique();
	CExtCustomizeSite::CategoryAppendAllCommands();
	CExtCustomizeSite::CategoryAppendNewMenu();
	CExtCustomizeSite::CustomizeStateLoad(
		pApp->m_pszRegistryKey,
		pApp->m_pszProfileName,
		pApp->m_pszProfileName
		);
#endif // (!defined __EXT_MFC_NO_CUSTOMIZE)

	//////////////////////////////////////////////////////////////////////////
	
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
		DockControlBar( &m_wndToolBarZoom );
		DockControlBar( &m_wndToolBarPlayer );
		
		RecalcLayout();
		
		CRect wrAlredyDockedBar;

		m_wndToolBar.GetWindowRect( &wrAlredyDockedBar );
		wrAlredyDockedBar.OffsetRect( 1, 0 );
		DockControlBar( &m_wndToolBarUIStyle, AFX_IDW_DOCKBAR_TOP, &wrAlredyDockedBar );
		RecalcLayout();
		
		m_wndToolBarZoom.GetWindowRect( &wrAlredyDockedBar );
		wrAlredyDockedBar.OffsetRect( 1, 0 );
		DockControlBar( &m_wndToolBarSeek, AFX_IDW_DOCKBAR_TOP, &wrAlredyDockedBar );
		RecalcLayout();
	}

	SetTimer(1, 200, NULL);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////

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
//////////////////////////////////////////////////////////////////////////

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
	if( m_pWndView->GetSafeHwnd() != NULL )
		m_pWndView->SetFocus();
}

//////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{

//	// let the view have first crack at the command
//	if( m_pWndView->GetSafeHwnd() != NULL )
//		if (m_pWndView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
//			return TRUE;

	if( ID_MYEXTBTN_SLIDER == nID )
	{
		if( nCode == CN_UPDATE_COMMAND_UI )
		{
#if (defined __EXT_MFC_NO_CUSTOMIZE)
			CWinApp * pApp = ::AfxGetApp();
			ASSERT( pApp != NULL );
			CExtCmdItem * pCmdItemSlider =
				g_CmdManager->CmdGetPtr(
				pApp->m_pszProfileName,
				ID_MYEXTBTN_SLIDER
				);
			ASSERT( pCmdItemSlider != NULL );
			CZoomBarSliderButton * pZoomSliderTBB = (CZoomBarSliderButton *)
				STATIC_DOWNCAST(
						CExtBarSliderButton,
						m_wndToolBarZoom.GetButton(
							m_wndToolBarZoom.CommandToIndex(ID_MYEXTBTN_SLIDER)
							)
					);
			ULONG nPos = pZoomSliderTBB->ScrollPosGet();
			pCmdItemSlider->m_sTipTool.Format(
				_T("SliderPos = %lu"),
				nPos
				);
#endif // (defined __EXT_MFC_NO_CUSTOMIZE)
			CCmdUI * pCmdUI = (CCmdUI*)pExtra;
			ASSERT( pCmdUI != NULL );
			pCmdUI->Enable( m_pAviPlayer != NULL && m_pAviPlayer->IsOpen() );
			return TRUE;
		}
	} // if( ID_MYEXTBTN_SLIDER == nID )

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	if( ID_MYEXTBTN_SCROLLER == nID )
	{
		if( nCode == CN_UPDATE_COMMAND_UI )
		{
#if (defined __EXT_MFC_NO_CUSTOMIZE)
			CWinApp * pApp = ::AfxGetApp();
			ASSERT( pApp != NULL );
			CExtCmdItem * pCmdItemScroller =
				g_CmdManager->CmdGetPtr(
				pApp->m_pszProfileName,
				ID_MYEXTBTN_SCROLLER
				);
			ASSERT( pCmdItemScroller != NULL );
			CSeekBarSliderButton *pSeekScrollerTBB = (CSeekBarSliderButton *)
				STATIC_DOWNCAST(
					CExtBarSliderButton,
					m_wndToolBarSeek.GetButton(
						m_wndToolBarSeek.CommandToIndex(ID_MYEXTBTN_SCROLLER)
						)
					);
			ULONG nPos = pSeekScrollerTBB->ScrollPosGet();
			pCmdItemScroller->m_sTipTool.Format(
				_T("ScrollerPos = %lu"),
				nPos
				);
#endif // (defined __EXT_MFC_NO_CUSTOMIZE)
			CCmdUI * pCmdUI = (CCmdUI*)pExtra;
			ASSERT( pCmdUI != NULL );
			pCmdUI->Enable( m_pAviPlayer != NULL && m_pAviPlayer->IsOpen() );
			return TRUE;
		}
	} // if( ID_MYEXTBTN_SCROLLER == nID )

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{

	if( m_wndMenuBar.TranslateMainFrameMessage(pMsg) )
		return TRUE;

	return CFrameWnd::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::DestroyWindow() 
{
CWinApp * pApp = ::AfxGetApp();
	ASSERT( pApp != NULL );
	ASSERT( pApp->m_pszRegistryKey != NULL );
	ASSERT( pApp->m_pszRegistryKey[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );
	ASSERT( pApp->m_pszProfileName[0] != _T('\0') );

#if (!defined __EXT_MFC_NO_CUSTOMIZE)
	VERIFY(
		CExtCustomizeSite::CustomizeStateSave(
		pApp->m_pszRegistryKey,
		pApp->m_pszProfileName,
		pApp->m_pszProfileName
		)
		);
#endif // (!defined __EXT_MFC_NO_CUSTOMIZE)

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

//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateViewLikeOffice2k(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerXP) )
			? FALSE
			: TRUE
		);
}

//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateViewLikeOffice2003(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerOffice2003) )
			? TRUE
			: FALSE
		);
}

//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////

#if (!defined __EXT_MFC_NO_CUSTOMIZE)
CExtBarButton * CMainFrame::OnCreateToolbarButton(
	CExtToolControlBar * pBar,
	CExtCustomizeCmdTreeNode * pNodeI,
	CExtCustomizeCmdTreeNode * pNodeC
	)
{
	ASSERT_VALID( this );
	ASSERT_VALID( pBar );
#ifdef _DEBUG
	if( pNodeI != NULL )
	{
		ASSERT_VALID( pNodeI );
		ASSERT( pNodeI->GetCmdID(false) != ID_SEPARATOR );
	}
#endif // _DEBUG
	ASSERT_VALID( pNodeC );
	ASSERT( pNodeC->GetCmdID(false) != ID_SEPARATOR );
	if( pNodeC->GetCmdID(false) == ID_MYEXTBTN_SLIDER )
	{
		int nScrollPos = 4;
		int nScrollPage = 0;
		int nScrollTotal = 11;
		int nCount = CMainFrame::CZoomBarSliderButton::g_arrButtons.GetSize();
		if( nCount > 0 )
		{
			CZoomBarSliderButton * pZoomSliderTBBExists =
				CMainFrame::CZoomBarSliderButton::g_arrButtons[0];
			ASSERT_VALID( pZoomSliderTBBExists );
			nScrollPos = pZoomSliderTBBExists->ScrollPosGet();
			nScrollPage = pZoomSliderTBBExists->ScrollPageSizeGet();
			nScrollTotal = pZoomSliderTBBExists->ScrollTotalRangeGet();
		}

		CZoomBarSliderButton * pSliderTBB =
			new CZoomBarSliderButton(
			/////////////////
			// standard CExtBarButton parms
			/////////////////
			pBar,
			ID_MYEXTBTN_SLIDER,
			0,
			/////////////////
			// CExtBarSliderButton specific parms
			/////////////////
			//
			// scroll total/pos/page
			nScrollTotal, nScrollPos, nScrollPage,
			// button extent horz(left/right)/vert(up/down) in pixels
			// (if zeros - use slider-like layout instead of scrollbar-like)
			0, 0,
			// total slider control extent horz/vert in pixels
			100, 100
			);
		ASSERT_VALID( pSliderTBB );
		if( pNodeI != NULL )
		{
			pSliderTBB->SetBasicCmdNode( pNodeI );
			pSliderTBB->OnCustomizeUpdateProps( pNodeI );
		} // if( pNodeI != NULL )
		else
			pSliderTBB->OnCustomizeUpdateProps( pNodeC );
		pSliderTBB->SetCustomizedCmdNode( pNodeC );
		return pSliderTBB;
	} // if( pNodeC->GetCmdID(false) == ID_MYEXTBTN_SLIDER )
	if( pNodeC->GetCmdID(false) == ID_MYEXTBTN_SCROLLER )
	{
		int nScrollPos = 0;
		int nScrollPage = 0;
		int nScrollTotal = 0;
		int nCount = CMainFrame::CSeekBarSliderButton::g_arrButtons.GetSize();
		if( nCount > 0 )
		{
			CSeekBarSliderButton *pSeekScrollerTBBExists = CMainFrame::CSeekBarSliderButton::g_arrButtons[0];
			ASSERT_VALID(pSeekScrollerTBBExists);
			nScrollPos = pSeekScrollerTBBExists->ScrollPosGet();
			nScrollPage = pSeekScrollerTBBExists->ScrollPageSizeGet();
			nScrollTotal = pSeekScrollerTBBExists->ScrollTotalRangeGet();
		}
		CSeekBarSliderButton * pScrollerTBB =
			new CSeekBarSliderButton(
			/////////////////
			// standard CExtBarButton parms
			/////////////////
			pBar,
			ID_MYEXTBTN_SCROLLER,
			0,
			/////////////////
			// CExtBarScrollerButton specific parms
			/////////////////
			//
			// scroll total/pos/page
			nScrollTotal, nScrollPos, nScrollPage,
			// button extent horz(left/right)/vert(up/down) in pixels
			// (if zeros - use slider-like layout instead of scrollbar-like)
			10, 10,
			// total slider control extent horz/vert in pixels
			300, 300
			);
		ASSERT_VALID( pScrollerTBB );
		if( pNodeI != NULL )
		{
			pScrollerTBB->SetBasicCmdNode( pNodeI );
			pScrollerTBB->OnCustomizeUpdateProps( pNodeI );
		} // if( pNodeI != NULL )
		else
			pScrollerTBB->OnCustomizeUpdateProps( pNodeC );
		pScrollerTBB->SetCustomizedCmdNode( pNodeC );
		return pScrollerTBB;
	} // if( pNodeC->GetCmdID(false) == ID_MYEXTBTN_SCROLLER )
	return CExtCustomizeSite::OnCreateToolbarButton( pBar, pNodeI, pNodeC );
}
#endif // (!defined __EXT_MFC_NO_CUSTOMIZE)

//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnSlider() 
{
	int nCount = CMainFrame::CZoomBarSliderButton::g_arrButtons.GetSize();
	if( nCount > 0 )
	{
		CZoomBarSliderButton * pZoomSliderTBB =
			CMainFrame::CZoomBarSliderButton::g_arrButtons[0];
		ASSERT_VALID(pZoomSliderTBB);
		DWORD nScrollPos = pZoomSliderTBB->ScrollPosGet();
		int nZoomPercent = 0;
		switch(nScrollPos) {
		case 0:
			nZoomPercent = 10;
			break;
		case 1:
			nZoomPercent = 25;
			break;
		case 2:
			nZoomPercent = 50;
			break;
		case 3:
			nZoomPercent = 75;
			break;
		case 4:
			nZoomPercent = 100;
			break;
		case 5:
			nZoomPercent = 150;
			break;
		case 6:
			nZoomPercent = 200;
			break;
		case 7:
			nZoomPercent = 250;
			break;
		case 8:
			nZoomPercent = 300;
			break;
		case 9:
			nZoomPercent = 350;
			break;
		case 10:
			nZoomPercent = 400;
			break;
		case 11:
			nZoomPercent = 450;
			break;
		}
		
		CString s;
		s.Format(_T("Current zoom:  %d %%"), nZoomPercent);
		AfxMessageBox(s);
	} // if( nCount > 0 )
}
void CMainFrame::OnScroller() 
{
int nCount = CMainFrame::CSeekBarSliderButton::g_arrButtons.GetSize();
	if( nCount > 0 )
	{
		CSeekBarSliderButton *pSeekScrollerTBB = CMainFrame::CSeekBarSliderButton::g_arrButtons[0];
		ASSERT_VALID(pSeekScrollerTBB);
		DWORD nScrollPos = pSeekScrollerTBB->ScrollPosGet();
		CString s;
		s.Format(_T("Current seek position:  %d"), nScrollPos);
		AfxMessageBox(s);
	} // if( nCount > 0 )
}
	
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pAviPlayer != NULL && m_pAviPlayer->IsOpen() && !m_pAviPlayer->IsPlaying()) ;
}
//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pAviPlayer != NULL && m_pAviPlayer->IsOpen() );
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnPause() 
{
	if( m_pAviPlayer ){
		m_pAviPlayer->Pause();
	}
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdatePause(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pAviPlayer != NULL && m_pAviPlayer->IsPlaying() ) ;
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnPlay() 
{
	if( m_pAviPlayer ){
		m_pAviPlayer->Play();
	}
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnStop() 
{
	if( m_pAviPlayer ){
		m_pAviPlayer->Stop();
		m_wndStatusBar.SetPaneText(3, _T(""));	
		m_wndStatusBar.SetPaneText(4, _T(""));	
	}

}

//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnFileOpen() 
{

	if( m_pWndView->GetSafeHwnd() == NULL )
		return;

	CFileDialog dlg( 
		TRUE, 
		_T("avi"),
		_T(""),
		OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_EXPLORER,
		_T("Avi Files (*.avi)|*.avi|All Files (*.*)|*.*||"), 
		this 
		);
	if( dlg.DoModal() == IDOK )
	{
		OnStop();
		m_wndStatusBar.SetPaneText(2, _T(""));	
		m_wndStatusBar.SetPaneText(3, _T(""));	
		m_wndStatusBar.SetPaneText(4, _T(""));	
		
		if(m_pAviPlayer){
			delete m_pAviPlayer;
			m_pAviPlayer = NULL;
		}

		int i = 0;

		for(i=0; i< CMainFrame::CZoomBarSliderButton::g_arrButtons.GetSize(); i++){
			CZoomBarSliderButton *pZoomSliderTBB = CMainFrame::CZoomBarSliderButton::g_arrButtons[i];
			ASSERT_VALID(pZoomSliderTBB);
  			pZoomSliderTBB->ScrollPosSet(4);
			pZoomSliderTBB->RedrawButton();
		}

		for(i=0; i< CMainFrame::CSeekBarSliderButton::g_arrButtons.GetSize(); i++){
			CSeekBarSliderButton *pSeekScrollerTBB = CMainFrame::CSeekBarSliderButton::g_arrButtons[i];
			ASSERT_VALID(pSeekScrollerTBB);
			pSeekScrollerTBB->ScrollPosSet(0);
			pSeekScrollerTBB->RedrawButton();
		}
		
		ASSERT( m_pWndView->GetSafeHwnd() != NULL );
		m_pAviPlayer = new CAviPlayer( m_pWndView );
		if( m_pAviPlayer->OpenFromFile( dlg.GetPathName() ) )
		{
			m_pWndView->OnSwUpdateScrollBars();
			
			CString sPaneText;
			sPaneText.Format(_T("Frames total:  %d"), m_pAviPlayer->GetFrameCount());
			m_wndStatusBar.SetPaneText(2, sPaneText);	
			
			DWORD nFrameCount = m_pAviPlayer->GetFrameCount()-1;
			int nPageSize = MulDiv(nFrameCount,1,20);
			if( nPageSize == 0 ) nPageSize = 2;
			
			for(i=0; i< CMainFrame::CSeekBarSliderButton::g_arrButtons.GetSize(); i++){
				CSeekBarSliderButton *pSeekScrollerTBB = CMainFrame::CSeekBarSliderButton::g_arrButtons[i];
				ASSERT_VALID(pSeekScrollerTBB);
				pSeekScrollerTBB->ScrollTotalRangeSet( nFrameCount + nPageSize );
				pSeekScrollerTBB->ScrollPageSizeSet( nPageSize );
				pSeekScrollerTBB->RedrawButton();
			}
			m_wndStatusBar.SetPaneText(1,_T("100 %"));
			OnPlay();
		}
	}

}

//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnTimer(UINT nIDEvent) 
{

	if( nIDEvent == 1 )
	{
		if(m_pAviPlayer)
		{
			
			for(int i=0; i< CMainFrame::CSeekBarSliderButton::g_arrButtons.GetSize(); i++){
				CSeekBarSliderButton *pSeekScrollerTBB = CMainFrame::CSeekBarSliderButton::g_arrButtons[i];
				ASSERT_VALID(pSeekScrollerTBB);
				
				pSeekScrollerTBB->ScrollPosSet( 
					m_pAviPlayer->GetCurrentFrameNumber()
					);
				pSeekScrollerTBB->RedrawButton();
			}
			
			if( m_pAviPlayer->IsOpen() ){
				CString sPaneText;
				sPaneText.Format(_T("Current frame :  %d"), m_pAviPlayer->GetCurrentFrameNumber());
				m_wndStatusBar.SetPaneText(3, sPaneText);	
				sPaneText.Format(_T("Frames skipped:  %d"), m_pAviPlayer->GetFrameSkipped());
				m_wndStatusBar.SetPaneText(4, sPaneText);	
			}
		}
		return;
	}

	CFrameWnd::OnTimer(nIDEvent);
}
