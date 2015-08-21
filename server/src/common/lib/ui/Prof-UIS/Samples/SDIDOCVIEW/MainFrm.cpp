// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SDIDOCVIEW.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDC_THEME_2000, OnTheme2000)
	ON_UPDATE_COMMAND_UI(IDC_THEME_2000, OnUpdateTheme2000)
	ON_COMMAND(IDC_THEME_2003, OnTheme2003)
	ON_UPDATE_COMMAND_UI(IDC_THEME_2003, OnUpdateTheme2003)
	ON_COMMAND(IDC_THEME_XP, OnThemeXp)
	ON_UPDATE_COMMAND_UI(IDC_THEME_XP, OnUpdateThemeXp)
	//}}AFX_MSG_MAP
	ON_COMMAND_EX(ID_VIEW_MENUBAR, OnBarCheck )
	ON_UPDATE_COMMAND_UI(ID_VIEW_MENUBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_RESIZABLEBAR_EMPTY, OnBarCheck )
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESIZABLEBAR_EMPTY, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_RESIZABLEBAR_TREE, OnBarCheck )
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESIZABLEBAR_TREE, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_RESIZABLEBAR_EDIT, OnBarCheck )
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESIZABLEBAR_EDIT, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_RESIZABLEBAR_CP, OnBarCheck )
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESIZABLEBAR_CP, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_RESIZABLEBAR_DLG, OnBarCheck )
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESIZABLEBAR_DLG, OnUpdateControlBarMenu)
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
	::memset( &m_dataFrameWP, 0, sizeof(WINDOWPLACEMENT) );
	m_dataFrameWP.length = sizeof(WINDOWPLACEMENT);
	m_dataFrameWP.showCmd = SW_HIDE;

	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnUpdateControlBarMenu(CCmdUI* pCmdUI)
{
	CExtControlBar::DoFrameBarCheckUpdate( this, pCmdUI, false );
}

BOOL CMainFrame::OnBarCheck(UINT nID)
{
	return CExtControlBar::DoFrameBarCheckCmd( this, nID, false );
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
CWinApp * pApp = ::AfxGetApp();
	ASSERT( pApp != NULL );
	ASSERT( pApp->m_pszRegistryKey != NULL );
	ASSERT( pApp->m_pszRegistryKey[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );
	ASSERT( pApp->m_pszProfileName[0] != _T('\0') );

	if( CFrameWnd::OnCreate(lpCreateStruct) == -1 )
	{
		ASSERT( FALSE );
		return -1;
	}

	VERIFY(
		g_CmdManager->ProfileWndAdd(
			pApp->m_pszProfileName,
			GetSafeHwnd()
			)
		);
	VERIFY(
		g_CmdManager->UpdateFromMenu(
			pApp->m_pszProfileName,
			IDR_MAINFRAME
			)
		);

	if(	!m_wndMenuBar.Create(
			NULL,
			this,
			ID_VIEW_MENUBAR
			)
		)
    {
        TRACE0("Failed to create menubar\n");
        return -1;      // failed to create
    }
	
	if(	!m_wndToolBar.Create(
			NULL,
			this,
			AFX_IDW_TOOLBAR
			)
		||
		!m_wndToolBar.LoadToolBar( IDR_MAINFRAME )
		)
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if(	!m_wndStatusBar.Create(this)
		||
		!m_wndStatusBar.SetIndicators(
			indicators,
			sizeof(indicators) / sizeof(UINT)
			)
		)
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndResizableBarEmpty.SetInitDesiredSizeVertical(
		CSize( 200, 400 )
		);
	m_wndResizableBarEmpty.SetInitDesiredSizeHorizontal(
		CSize( 400, 200 )
		);
	if(	!m_wndResizableBarEmpty.Create(
			NULL, // _T("Optional control bar caption"),
			this,
			ID_VIEW_RESIZABLEBAR_EMPTY
			)
		)
	{
		TRACE0("Failed to create m_wndResizableBarEmpty\n");
		return -1;		// fail to create
	}

	m_wndResizableBarTree.SetInitDesiredSizeVertical(
		CSize( 200, 400 )
		);
	m_wndResizableBarTree.SetInitDesiredSizeHorizontal(
		CSize( 400, 200 )
		);
	if(	!m_wndResizableBarTree.Create(
			NULL, // _T("Optional control bar caption"),
			this,
			ID_VIEW_RESIZABLEBAR_TREE
			)
		)
	{
		TRACE0("Failed to create m_wndResizableBarTree\n");
		return -1;		// fail to create
	}
	if( !m_wndDockedCtrlTree.Create(
			WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL
			|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT
			|TVS_INFOTIP|TVS_DISABLEDRAGDROP
			|TVS_SINGLEEXPAND|TVS_SHOWSELALWAYS
			,
			CRect(0,0,0,0),
			&m_wndResizableBarTree,
			m_wndResizableBarTree.GetDlgCtrlID()
			)
		)
	{
		TRACE0("Failed to create m_wndDockedCtrlEdit\n");
		return -1;		// fail to create
	}
	m_wndDockedCtrlTree.SetFont(
		CFont::FromHandle(
			(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
			)
		);
	for( int nTreeIdx0=0; nTreeIdx0<10; nTreeIdx0++ )
	{
		CString sTreeItemText;
		sTreeItemText.Format( _T("Item 1-%d"), nTreeIdx0+1 );
		HTREEITEM htiAtLevel0 =
			m_wndDockedCtrlTree.InsertItem(
			LPCTSTR(sTreeItemText)
			);
		ASSERT( htiAtLevel0 != NULL );
		for( int nTreeIdx1=0; nTreeIdx1<5; nTreeIdx1++ )
		{
			sTreeItemText.Format( _T("Item 2-%d"), nTreeIdx1+1 );
			HTREEITEM htiAtLevel1 =
				m_wndDockedCtrlTree.InsertItem(
					LPCTSTR(sTreeItemText),
					htiAtLevel0
					);
			ASSERT( htiAtLevel1 != NULL );
			for( int nTreeIdx2=0; nTreeIdx2<3; nTreeIdx2++ )
			{
				sTreeItemText.Format( _T("Item 3-%d"), nTreeIdx2+1 );
				HTREEITEM htiAtLevel2 =
					m_wndDockedCtrlTree.InsertItem(
						LPCTSTR(sTreeItemText),
						htiAtLevel1
						);
				ASSERT( htiAtLevel2 != NULL );
				htiAtLevel2;
			} // for( int nTreeIdx2=0; nTreeIdx2<5; nTreeIdx2++ )
		} // for( int nTreeIdx1=0; nTreeIdx1<5; nTreeIdx1++ )
	} // for( int nTreeIdx0=0; nTreeIdx0<10; nTreeIdx0++ )

	m_wndResizableBarEdit.SetInitDesiredSizeVertical(
		CSize( 200, 400 )
		);
	m_wndResizableBarEdit.SetInitDesiredSizeHorizontal(
		CSize( 400, 200 )
		);
	if(	!m_wndResizableBarEdit.Create(
			NULL, // _T("Optional control bar caption"),
			this,
			ID_VIEW_RESIZABLEBAR_EDIT
			)
		)
	{
		TRACE0("Failed to create m_wndResizableBarEdit\n");
		return -1;		// fail to create
	}
	if( !m_wndDockedCtrlEdit.Create(
			WS_CHILD|WS_VISIBLE
				|ES_MULTILINE|ES_LEFT
				|ES_NOHIDESEL|ES_WANTRETURN
				,
			CRect(0,0,0,0),
			&m_wndResizableBarEdit,
			m_wndResizableBarEdit.GetDlgCtrlID()
			)
		)
	{
		TRACE0("Failed to create m_wndDockedCtrlEdit\n");
		return -1;		// fail to create
	}
	m_wndDockedCtrlEdit.SetFont(
		CFont::FromHandle(
			(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
			)
		);
	m_wndDockedCtrlEdit.SetWindowText(
		_T("    Edit control\r\n")
		_T("    inside resizable control bar")
		);

	m_wndResizableBarCP.SetInitDesiredSizeVertical(
		CSize( 200, 400 )
		);
	m_wndResizableBarCP.SetInitDesiredSizeHorizontal(
		CSize( 400, 200 )
		);
	if(	!m_wndResizableBarCP.Create(
			NULL, // _T("Optional control bar caption"),
			this,
			ID_VIEW_RESIZABLEBAR_CP
			)
		)
	{
		TRACE0("Failed to create m_wndResizableBarCP\n");
		return -1;		// fail to create
	}
	if( !m_wndDockedCtrlCP.Create(
			_T("BUTTON"),
			_T(""),
			WS_CHILD|WS_VISIBLE,
			CRect(0,0,0,0),
			&m_wndResizableBarCP,
			m_wndResizableBarCP.GetDlgCtrlID()
			)
		)
	{
		TRACE0("Failed to create m_wndDockedCtrlCP\n");
		return -1;		// fail to create
	}

	m_wndResizableBarDlg.SetInitDesiredSizeVertical(
		CSize( 200, 400 )
		);
	m_wndResizableBarDlg.SetInitDesiredSizeHorizontal(
		CSize( 400, 200 )
		);
	if(	!m_wndResizableBarDlg.Create(
			NULL, // _T("Optional control bar caption"),
			this,
			ID_VIEW_RESIZABLEBAR_DLG
			)
		)
	{
		TRACE0("Failed to create m_wndResizableBarDlg\n");
		return -1;		// fail to create
	}
	if( !m_wndDockedResizableDialog.Create(
			IDD_DIALOG_FOR_RESIZABLE_BAR,
			&m_wndResizableBarDlg
			)
		)
	{
		TRACE0("Failed to create m_wndResizableBarDlg\n");
		return -1;		// fail to create
	}
	m_wndDockedResizableDialog.ShowSizeGrip( FALSE );
	m_wndDockedResizableDialog.AddAnchor(
		IDC_EDIT_IN_RESIZABLE_FORM,
		__RDA_LT,
		__RDA_RT
		);
	VERIFY(
			m_wndEditInDockedDlg.SubclassDlgItem(
				IDC_EDIT_IN_RESIZABLE_FORM,
				&m_wndDockedResizableDialog
				)
		&&	m_wndLableInDockedDlg.SubclassDlgItem(
				IDC_STATIC1,
				&m_wndDockedResizableDialog
				)
		);

	m_wndMenuBar.EnableDocking( CBRS_ALIGN_ANY );
	m_wndToolBar.EnableDocking( CBRS_ALIGN_ANY );
	m_wndResizableBarEmpty.EnableDocking( CBRS_ALIGN_ANY );
	m_wndResizableBarTree.EnableDocking( CBRS_ALIGN_ANY );
	m_wndResizableBarEdit.EnableDocking( CBRS_ALIGN_ANY );
	m_wndResizableBarCP.EnableDocking( CBRS_ALIGN_ANY );
	m_wndResizableBarDlg.EnableDocking( CBRS_ALIGN_ANY );

	//
	// Prof-UIS advanced docking windows feature:
	// Show content of control bars when docking / resizing
	//
	if( !CExtControlBar::FrameEnableDocking(this) )
	{
		ASSERT( FALSE );
		return -1;
	}
	
#if (!defined __EXT_MFC_NO_TAB_CONTROLBARS)
	if( !CExtControlBar::FrameInjectAutoHideAreas(this) )
	{
		ASSERT( FALSE );
		return -1;
	}
#endif // (!defined __EXT_MFC_NO_TAB_CONTROLBARS)


static UINT statBasicCommands[] =
{
	ID_FILE_NEW, 
	ID_FILE_OPEN, 
	ID_FILE_SAVE,
	ID_APP_EXIT,
	ID_APP_ABOUT,
	ID_FILE_PRINT,
	ID_FILE_PRINT_SETUP, 
	ID_EDIT_COPY, 
	ID_EDIT_CUT, 
	ID_EDIT_PASTE, 
	ID_EDIT_UNDO, 
	ID_VIEW_TOOLBAR, 
	ID_VIEW_RESIZABLEBAR_EMPTY,
	ID_VIEW_RESIZABLEBAR_TREE,
	ID_VIEW_RESIZABLEBAR_EDIT,
	ID_VIEW_RESIZABLEBAR_CP,
	ID_VIEW_RESIZABLEBAR_DLG,
	IDC_THEME_2000,
	IDC_THEME_XP,
	IDC_THEME_2003,
	0 // end of commands list
}; // statBasicCommands array

	VERIFY(
		g_CmdManager->SetBasicCommands(
			pApp->m_pszProfileName,
			statBasicCommands
			)
		);
	g_CmdManager->SerializeState(
		pApp->m_pszProfileName,
		pApp->m_pszRegistryKey,
		pApp->m_pszProfileName,
		false
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

		m_wndResizableBarEmpty.FloatControlBar(
			CPoint( 40, 100 )
			);
		m_wndResizableBarTree.FloatControlBar(
			CPoint( 300, 100 )
			);
		m_wndResizableBarEmpty.DockControlBar(
			&m_wndResizableBarEdit,
			true,
			true,
			this,
			true
			);
		m_wndResizableBarCP.FloatControlBar(
			CPoint( 360, 170 )
			);
		m_wndResizableBarCP.DockControlBar(
			&m_wndResizableBarDlg,
			false,
			true,
			this,
			true
			);
	}

	return 0;
}

BOOL CMainFrame::DestroyWindow() 
{
CWinApp * pApp = ::AfxGetApp();
	ASSERT( pApp != NULL );
	ASSERT( pApp->m_pszRegistryKey != NULL );
	ASSERT( pApp->m_pszRegistryKey[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );
	ASSERT( pApp->m_pszProfileName[0] != _T('\0') );
	pApp;

	VERIFY(
		CExtControlBar::ProfileBarStateSave(
			this,
			pApp->m_pszRegistryKey,
			pApp->m_pszProfileName,
			pApp->m_pszProfileName,
			&m_dataFrameWP
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

void CMainFrame::ActivateFrame(int nCmdShow) 
{
	if( m_dataFrameWP.showCmd != SW_HIDE )
	{
		SetWindowPlacement( &m_dataFrameWP );
		CFrameWnd::ActivateFrame( m_dataFrameWP.showCmd );
		m_dataFrameWP.showCmd = SW_HIDE;
		return;
	}
	CFrameWnd::ActivateFrame(nCmdShow);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

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


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if( m_wndMenuBar.TranslateMainFrameMessage(pMsg) )
		return TRUE;
	return CFrameWnd::PreTranslateMessage(pMsg);
}



void CMainFrame::OnTheme2000() 
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

void CMainFrame::OnUpdateTheme2000(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerXP) )
		? FALSE
		: TRUE
		);
}

void CMainFrame::OnThemeXp() 
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

void CMainFrame::OnUpdateThemeXp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		(	g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerXP) )
		&&	(! g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerOffice2003) ) )
		)	? TRUE
		: FALSE
		);
}

void CMainFrame::OnTheme2003() 
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

void CMainFrame::OnUpdateTheme2003(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerOffice2003) )
		? TRUE
		: FALSE
		);
}