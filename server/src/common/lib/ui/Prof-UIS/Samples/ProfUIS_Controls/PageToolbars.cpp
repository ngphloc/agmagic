// PageToolbars.cpp : implementation file
//

#include "stdafx.h"
#include "profuis_controls.h"
#include "PageToolbars.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageToolbars dialog


CPageToolbars::CPageToolbars(CWnd* pParent /*=NULL*/)
	: CPageBase(CPageToolbars::IDD, pParent)
	, m_bInitComplete( false )
	, m_clrColorCtrl( RGB(255,0,0) )
{
	//{{AFX_DATA_INIT(CPageToolbars)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nThinColorBtnHeight = 8;
}


void CPageToolbars::DoDataExchange(CDataExchange* pDX)
{
	CPageBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageToolbars)
	DDX_Control(pDX, IDC_CHECK_SHOW_GRIPPER, m_chkShowGripper);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MAIN_MENUBAR, m_wndMenuBar);
	DDX_Control(pDX, IDC_MAIN_TOOLBAR, m_wndToolBar);
	DDX_Control(pDX, IDC_COLOR_TOOLBAR, m_wndToolBarColor);
	DDX_Control(pDX, IDC_CONTROLS_TOOLBAR1, m_wndToolBarControls1);
	DDX_Control(pDX, IDC_CONTROLS_TOOLBAR2, m_wndToolBarControls2);
	DDX_Control(pDX, IDC_PALETTE_TOOLBAR, m_wndToolBarPalette);
}


BEGIN_MESSAGE_MAP(CPageToolbars, CPageBase)
	//{{AFX_MSG_MAP(CPageToolbars)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP

	ON_REGISTERED_MESSAGE(
		CExtPopupMenuWnd::g_nMsgPrepareMenu,
		OnExtMenuPrepare
		)
	// color popup menu
	ON_REGISTERED_MESSAGE(
		CExtPopupColorMenuWnd::g_nMsgNotifyColorChangedFinally,
		OnColorChangedFinally
		)
	ON_REGISTERED_MESSAGE(
		CExtPopupColorMenuWnd::g_nMsgNotifyCustColor,
		OnColorSelectCustom
		)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageToolbars message handlers

BOOL CPageToolbars::OnInitDialog() 
{
	CPageBase::OnInitDialog();
	
	CWinApp * pApp = ::AfxGetApp();
	ASSERT( pApp != NULL );
	
	VERIFY(
		g_CmdManager->ProfileSetup(
		_T("PageToolbars"),
		GetSafeHwnd()
		)
		);
	VERIFY(
		g_CmdManager->UpdateFromMenu(
		_T("PageToolbars"),
		IDR_MENU_PAGE_TOOLBARS
		)
		);
	VERIFY(
		g_CmdManager->UpdateFromMenu(
		_T("PageToolbars"),
		IDR_COLOR_MENU
		)
		);
	VERIFY(
		g_CmdManager->UpdateFromToolBar(
		_T("PageToolbars"),
		IDR_PALETTE_TOOLBAR
		)
		);
	VERIFY(
		g_CmdManager->UpdateFromToolBar(
		_T("PageToolbars"),
		IDR_EDIT
		)
		);

	//////////////////////////////////////////////////////////////////////////

	ASSERT( m_wndMenuBar.GetSafeHwnd() != NULL );
	if(	!m_wndMenuBar.LoadMenuBar( IDR_MENU_PAGE_TOOLBARS ) ){
		ASSERT( FALSE );
		return FALSE;
	}
	
	// init combobox in the menubar
	if(	!m_wndComboBoxInMenubar.Create(
		WS_CHILD|WS_VISIBLE|WS_TABSTOP
		|CBS_DROPDOWN|CBS_HASSTRINGS,
		CRect( 0, 0, 150, 100 ),
		&m_wndMenuBar,
		ID_COMBOBOX_IN_MENUBAR
		)
		)
	{
		ASSERT( FALSE );
		return FALSE;
	}
	
	m_wndMenuBar.InsertButton(
		-1,
		ID_COMBOBOX_IN_MENUBAR
		);
	VERIFY(
		m_wndMenuBar.SetButtonCtrl( 
		m_wndMenuBar.CommandToIndex(ID_COMBOBOX_IN_MENUBAR), 
		&m_wndComboBoxInMenubar )
		);
	
	m_wndComboBoxInMenubar.SetFont(
		CFont::FromHandle(
		(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
		)
		);
	m_wndComboBoxInMenubar.AddString( _T("ComboBox in menubar") );
	m_wndComboBoxInMenubar.SetCurSel( 0 );
	
	m_wndMenuBar.InsertButton(
		-1,
		ID_SEPARATOR
		);

	// init editbox in the menubar
	if(	!m_wndEditInMenubar.Create(
		WS_CHILD|WS_VISIBLE|WS_TABSTOP
		|ES_AUTOHSCROLL|ES_LEFT,
		CRect( 0, 0, 100, 18 ),
		&m_wndMenuBar,
		ID_EDIT_IN_MENUBAR
		)
		)
	{
		ASSERT( FALSE );
		return FALSE;
	}
	
	m_wndMenuBar.InsertButton(
		-1,
		ID_EDIT_IN_MENUBAR
		);
	VERIFY(
		m_wndMenuBar.SetButtonCtrl( 
		m_wndMenuBar.CommandToIndex(ID_EDIT_IN_MENUBAR), 
		&m_wndEditInMenubar )
		);
	
	m_wndEditInMenubar.SetFont(
		CFont::FromHandle(
		(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
		)
		);
	m_wndEditInMenubar.SetWindowText( _T("Edit in menubar") );
	
	//////////////////////////////////////////////////////////////////////////

	ASSERT( m_wndToolBar.GetSafeHwnd() != NULL );
	if(	!m_wndToolBar.LoadToolBar( IDR_MAIN_TOOLBAR ) ){
		ASSERT( FALSE );
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	
	ASSERT( m_wndToolBarControls1.GetSafeHwnd() != NULL );

	CExtCmdItem * pCmdItemSlider =
		g_CmdManager->CmdAllocPtr(
		_T("PageToolbars"),
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
		_T("PageToolbars"),
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
		&m_wndToolBarControls1,
		ID_MYEXTBTN_SLIDER,
		0,
		/////////////////
		// CExtBarSliderButton specific parms
		/////////////////
		//
		// scroll total/pos/page
		50, 25, 0,
		// button extent horz(left/right)/vert(up/down) in pixels
		// (if zeros - use slider-like layout instead of scrollbar-like)
		0, 0,
		// total slider control extent horz/vert in pixels
		100, 100
		);
	VERIFY(
		m_wndToolBarControls1.InsertSpecButton(
		-1,
		pZoomSliderTBB,
		FALSE
		)
		);
	
	CSeekBarSliderButton *pSeekScrollerTBB = new CSeekBarSliderButton(
		/////////////////
		// standard CExtBarButton parms
		/////////////////
		&m_wndToolBarControls1,
		ID_MYEXTBTN_SCROLLER,
		0,
		/////////////////
		// CExtBarScrollerButton specific parms
		/////////////////
		//
		// scroll total/pos/page
		100, 50, 0,
		// button extent horz(left/right)/vert(up/down) in pixels
		// (if zeros - use slider-like layout instead of scrollbar-like)
		10, 10,
		// total slider control extent horz/vert in pixels
		210, 210
		);
	VERIFY(
		m_wndToolBarControls1.InsertSpecButton(
		-1,
		pSeekScrollerTBB,
		FALSE
		)
		);

	VERIFY(
		m_wndToolBarControls1.InitContentExpandButton()
		);
	
	
	//////////////////////////////////////////////////////////////////////////
	
	ASSERT( m_wndToolBarControls2.GetSafeHwnd() != NULL );

	// init combobox in the toolbar
	if(	!m_wndComboBoxInToolbar.Create(
		WS_CHILD|WS_VISIBLE|WS_TABSTOP
		|CBS_DROPDOWN|CBS_HASSTRINGS,
		CRect( 0, 0, 150, 100 ),
		&m_wndToolBarControls2,
		ID_COMBOBOX_IN_TOOLBAR
		)
		)
	{
		ASSERT( FALSE );
		return FALSE;
	}

	m_wndToolBarControls2.InsertButton(
		-1,
		ID_COMBOBOX_IN_TOOLBAR
		);
	VERIFY(
		m_wndToolBarControls2.SetButtonCtrl( 
		m_wndToolBarControls2.CommandToIndex(ID_COMBOBOX_IN_TOOLBAR), 
		&m_wndComboBoxInToolbar )
		);
		
	m_wndComboBoxInToolbar.SetFont(
		CFont::FromHandle(
		(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
		)
		);
	m_wndComboBoxInToolbar.AddString( _T("ComboBox in toolbar") );
	m_wndComboBoxInToolbar.SetCurSel( 0 );

	m_wndToolBarControls2.InsertButton(
		-1,
		ID_SEPARATOR
		);

	// init editbox in the toolbar
	if(	!m_wndEditInToolbar.Create(
		WS_CHILD|WS_VISIBLE|WS_TABSTOP
		|ES_AUTOHSCROLL|ES_LEFT,
		CRect( 0, 0, 100, 19 ),
		&m_wndToolBarControls2,
		ID_EDIT_IN_TOOLBAR
		)
		)
	{
		ASSERT( FALSE );
		return FALSE;
	}
	
	m_wndToolBarControls2.InsertButton(
		-1,
		ID_EDIT_IN_TOOLBAR
		);
	VERIFY(
		m_wndToolBarControls2.SetButtonCtrl( 
		m_wndToolBarControls2.CommandToIndex(ID_EDIT_IN_TOOLBAR), 
		&m_wndEditInToolbar )
		);
	
	m_wndEditInToolbar.SetFont(
		CFont::FromHandle(
		(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
		)
		);
	m_wndEditInToolbar.SetWindowText( _T("Edit in toolbar") );

	VERIFY(
		m_wndToolBarControls2.InitContentExpandButton()
		);
	
	//////////////////////////////////////////////////////////////////////////

	ASSERT( m_wndToolBarColor.GetSafeHwnd() != NULL );
	VERIFY(
		m_wndToolBarColor.InsertButton(
		-1,
		ID_COLOR_BTN_HEIGHT,
		FALSE
		)
		);

	CMenu menuWidthCommands;
	VERIFY( menuWidthCommands.LoadMenu(IDR_COLOR_MENU) );
	VERIFY(
		m_wndToolBarColor.SetButtonMenu(
		m_wndToolBarColor.CommandToIndex(ID_COLOR_BTN_HEIGHT),
		menuWidthCommands.Detach(),
		TRUE,
		TRUE,
		FALSE
		)
		);
	VERIFY(
		m_wndToolBarColor.InsertButton( -1, ID_SEPARATOR, FALSE )
		);
	
	const int nLeftToolbarGrayscaleButtonsCount = 8;
	const int nLeftToolbarColorButtonsCount = 18;
	
	for( int nGrayscaleBtn = 0; nGrayscaleBtn < nLeftToolbarGrayscaleButtonsCount; nGrayscaleBtn++ )
	{
		VERIFY(
			m_wndToolBarColor.InsertSpecButton(
			-1,
			new CThinColorButtonInToolBar(
			CExtPaintManager::stat_HLStoRGB(
			0.0,
			double(nLeftToolbarGrayscaleButtonsCount - nGrayscaleBtn - 1)
			/ double(nLeftToolbarGrayscaleButtonsCount-1),
			0.0
			),
			&m_wndToolBarColor
			),
			FALSE
			)
			);
	}
	VERIFY(
		m_wndToolBarColor.InsertButton( -1, ID_SEPARATOR, FALSE )
		);

	for( int nColorBtn = 0; nColorBtn < nLeftToolbarColorButtonsCount; nColorBtn++ )
	{
		VERIFY(
			m_wndToolBarColor.InsertSpecButton(
			-1,
			new	CThinColorButtonInToolBar(
			CExtPaintManager::stat_HLStoRGB(
			double(nColorBtn) / double(nLeftToolbarColorButtonsCount),
			0.5,
			1.0
			),
			&m_wndToolBarColor
			),
			FALSE
			)
			);
	}
	
	VERIFY(
		m_wndToolBarColor.InitContentExpandButton()
		);

	
	//////////////////////////////////////////////////////////////////////////
	
	ASSERT( m_wndToolBarPalette.GetSafeHwnd() != NULL );

	if(	!m_wndToolBarPalette.LoadToolBar( IDR_PALETTE_TOOLBAR ) ){
		ASSERT( FALSE );
		return FALSE;
	}
	m_wndToolBarPalette.m_bPaletteMode = true;
	
	m_wndToolBarPalette.GetButton(3)->SetWrap( CExtBarButton::__EVT_FLOAT );
	m_wndToolBarPalette.GetButton(6)->SetWrap( CExtBarButton::__EVT_FLOAT );
	m_wndToolBarPalette.GetButton(9)->SetWrap( CExtBarButton::__EVT_FLOAT );
	m_wndToolBarPalette.GetButton(12)->SetWrap( CExtBarButton::__EVT_FLOAT );
	
	//////////////////////////////////////////////////////////////////////////
	
	static UINT g_statBasicCommands[] =
	{
			ID_HEIGHT_8PX,
			ID_HEIGHT_10PX,
			ID_HEIGHT_12PX,
			ID_HEIGHT_14PX,
			ID_HEIGHT_16PX,
			ID_HEIGHT_18PX,
			ID_HEIGHT_20PX,
			ID_HEIGHT_22PX,
			ID_HEIGHT_24PX,
			ID_HEIGHT_26PX,
			ID_HEIGHT_28PX,
			ID_HEIGHT_30PX,
			ID_COLOR_BTN_HEIGHT,
			0, // end of list
	};
	
	CExtCmdItem * pCmdItem =
		g_CmdManager->CmdAllocPtr(
		_T("PageToolbars"),
		ID_COLOR_BTN_HEIGHT
		);
	ASSERT( pCmdItem != NULL );
	pCmdItem->m_sToolbarText = pCmdItem->m_sMenuText
		= pCmdItem->m_sTipStatus = pCmdItem->m_sTipTool
		= _T( "Color cell height" );
	
	VERIFY(
		g_CmdManager->SetBasicCommands(
		_T("PageToolbars"),
		g_statBasicCommands
		)
		);

	//////////////////////////////////////////////////////////////////////////
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_SHOW_GRIPPER, 
		BST_CHECKED
		);
	
	CWnd::RepositionBars(0,0xFFFF,0);
	
	m_bInitComplete = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void CPageToolbars::OnSize(UINT nType, int cx, int cy) 
{
	CPageBase::OnSize(nType, cx, cy);
	if( nType != SIZE_MINIMIZED )
		CWnd::RepositionBars(0,0xFFFF,0);
}

//////////////////////////////////////////////////////////////////////////

BOOL CPageToolbars::OnCmdMsg(UINT nID, INT nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if( !m_bInitComplete ){
		return CPageBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}
	
	if(		nCode == CN_UPDATE_COMMAND_UI
		||	nCode == CN_COMMAND
		)
	{
		if( nID == ID_MYEXTBTN_SLIDER || nID == ID_MYEXTBTN_SCROLLER ) {
			if( nCode == CN_UPDATE_COMMAND_UI ){
				CCmdUI * pCmdUI = (CCmdUI *)pExtra;
				ASSERT( pCmdUI != NULL );
				pCmdUI->Enable();
			}
			return TRUE;
		}
		
		if(		nID == ID_COMBOBOX_IN_TOOLBAR 
			||	nID == ID_COMBOBOX_IN_MENUBAR 
			||	nID == ID_EDIT_IN_TOOLBAR 
			||	nID == ID_EDIT_IN_MENUBAR 
			||	nID == ID_CHECKBOX_IN_TOOLBAR 
			||	nID == ID_CHECKBOX_IN_MENUBAR 
			||	nID == ID_LINE_WIDTH_0
			||	nID == ID_LINE_WIDTH_1
			||	nID == ID_LINE_WIDTH_2
			||	nID == ID_LINE_WIDTH_3
			||	nID == ID_LINE_WIDTH_4
			||	nID == ID_LINE_WIDTH_5
			||	nID == ID_LINE_WIDTH_6
			||	nID == ID_LINE_WIDTH_7
			||	nID == ID_LINE_WIDTH_8
			||	nID == ID_LINE_WIDTH_9
			||	nID == ID_LINE_WIDTH_10
			||	nID == ID_LINE_WIDTH_OTHER
			)
		{
			if( nCode == CN_UPDATE_COMMAND_UI ){
				CCmdUI * pCmdUI = (CCmdUI *)pExtra;
				ASSERT( pCmdUI != NULL );
				pCmdUI->Enable();
			}
			return TRUE;
		}

		if( nID == IDC_CHECK_SHOW_GRIPPER ) {
			if( nCode == CN_COMMAND ){
				bool bDlgButtonChecked = ( IsDlgButtonChecked( nID ) == BST_CHECKED );
				m_wndToolBarColor.SetBarStyle( 
					bDlgButtonChecked
					? m_wndToolBarColor.GetBarStyle() |  CBRS_GRIPPER 
					: m_wndToolBarColor.GetBarStyle() & ~CBRS_GRIPPER 
					);
				m_wndToolBarPalette.SetBarStyle( 
					bDlgButtonChecked
					? m_wndToolBarPalette.GetBarStyle() |  CBRS_GRIPPER 
					: m_wndToolBarPalette.GetBarStyle() & ~CBRS_GRIPPER 
					);
				m_wndToolBar.SetBarStyle( 
					bDlgButtonChecked
					? m_wndToolBar.GetBarStyle() |  CBRS_GRIPPER 
					: m_wndToolBar.GetBarStyle() & ~CBRS_GRIPPER 
					);
				m_wndMenuBar.SetBarStyle( 
					bDlgButtonChecked
					? m_wndMenuBar.GetBarStyle() |  CBRS_GRIPPER 
					: m_wndMenuBar.GetBarStyle() & ~CBRS_GRIPPER 
					);
				m_wndToolBarControls1.SetBarStyle( 
					bDlgButtonChecked
					? m_wndToolBarControls1.GetBarStyle() |  CBRS_GRIPPER 
					: m_wndToolBarControls1.GetBarStyle() & ~CBRS_GRIPPER 
					);
				m_wndToolBarControls2.SetBarStyle( 
					bDlgButtonChecked
					? m_wndToolBarControls2.GetBarStyle() |  CBRS_GRIPPER 
					: m_wndToolBarControls2.GetBarStyle() & ~CBRS_GRIPPER 
					);
				_Update();
			}
		}

		if( m_wndToolBarColor.GetSafeHwnd() != NULL )
		{
			INT nBtnHeight = 0;
			switch( nID )
			{
			case ID_HEIGHT_8PX: nBtnHeight = 8; break;
			case ID_HEIGHT_10PX: nBtnHeight = 10; break;
			case ID_HEIGHT_12PX: nBtnHeight = 12; break;
			case ID_HEIGHT_14PX: nBtnHeight = 14; break;
			case ID_HEIGHT_16PX: nBtnHeight = 16; break;
			case ID_HEIGHT_18PX: nBtnHeight = 18; break;
			case ID_HEIGHT_20PX: nBtnHeight = 20; break;
			case ID_HEIGHT_22PX: nBtnHeight = 22; break;
			case ID_HEIGHT_24PX: nBtnHeight = 24; break;
			case ID_HEIGHT_26PX: nBtnHeight = 26; break;
			case ID_HEIGHT_28PX: nBtnHeight = 28; break;
			case ID_HEIGHT_30PX: nBtnHeight = 30; break;
			} // switch( nID )

			if( nBtnHeight != 0 )
			{
				if( nCode == CN_UPDATE_COMMAND_UI )
				{
					CCmdUI * pCmdUI = (CCmdUI *)pExtra;
					ASSERT( pCmdUI != NULL );
					pCmdUI->Enable();
					pCmdUI->SetRadio(
						(m_nThinColorBtnHeight == nBtnHeight) ? TRUE : FALSE
						);
				}
				else
				{
					if( m_nThinColorBtnHeight != nBtnHeight  )
					{
						m_nThinColorBtnHeight = nBtnHeight;
						CWnd::RepositionBars(0,0xFFFF,0);
						m_wndToolBarColor.RedrawWindow();
					}
				}
				return TRUE;
			}

			INT nColorCmdIndex =
				m_wndToolBarColor.CommandToIndex( nID );
			if( nColorCmdIndex >= 0 )
			{
				if( nCode == CN_UPDATE_COMMAND_UI )
				{
					CCmdUI * pCmdUI = (CCmdUI *)pExtra;
					ASSERT( pCmdUI != NULL );
					pCmdUI->Enable();
				}
				else
				{
					CWinApp * pApp = ::AfxGetApp();
					ASSERT( pApp != NULL );
					CExtCmdItem * pCmdItem =
						g_CmdManager->CmdGetPtr(
							_T("PageToolbars"),
							nID
							);
					ASSERT( pCmdItem != NULL );
					CString sMsg;
					sMsg.Format(
						_T("Command from the color toolbar:\n\n%s"),
						pCmdItem->m_sMenuText
						);
					::AfxMessageBox( LPCTSTR(sMsg) );
				}
				return TRUE;
			}
		}
	}
	return CPageBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//////////////////////////////////////////////////////////////////////////

void CPageToolbars::_Update()
{
	m_wndMenuBar.SetWindowPos(
		NULL, 0, 0, 0, 0,
		SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOOWNERZORDER
		|SWP_FRAMECHANGED
		);
	m_wndToolBar.SetWindowPos(
		NULL, 0, 0, 0, 0,
		SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOOWNERZORDER
		|SWP_FRAMECHANGED
		);
	m_wndToolBarColor.SetWindowPos(
		NULL, 0, 0, 0, 0,
		SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOOWNERZORDER
		|SWP_FRAMECHANGED
		);
	m_wndToolBarControls1.SetWindowPos(
		NULL, 0, 0, 0, 0,
		SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOOWNERZORDER
		|SWP_FRAMECHANGED
		);
	m_wndToolBarControls2.SetWindowPos(
		NULL, 0, 0, 0, 0,
		SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOOWNERZORDER
		|SWP_FRAMECHANGED
		);
	m_wndToolBarPalette.SetWindowPos(
		NULL, 0, 0, 0, 0,
		SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOOWNERZORDER
		|SWP_FRAMECHANGED
		);

	CWnd::RepositionBars(0,0xFFFF,0);
	RedrawWindow( NULL, NULL,
		RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW
		|RDW_ALLCHILDREN
		);
	UpdateDialogControls( this, FALSE );
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPageToolbars::OnExtMenuPrepare(WPARAM wParam, LPARAM lParam)
{
	lParam;
	CExtPopupMenuWnd::MsgPrepareMenuData_t * pData =
		reinterpret_cast
			< CExtPopupMenuWnd::MsgPrepareMenuData_t * >
			( wParam );
	ASSERT( pData != NULL );
	CExtPopupMenuWnd * pPopup = pData->m_pPopup;
	ASSERT( pPopup != NULL );

	INT nReplacePos =
		pPopup->ItemFindPosForCmdID(ID_COLOR_CTRL);
	
	if( nReplacePos >= 0 )
	{
		CExtPopupColorMenuWnd * pColorPopup = new CExtPopupColorMenuWnd;
		pColorPopup->m_lParamCookie = LPARAM(ID_COLOR_CTRL);
		pColorPopup->m_hWndNotifyColorChanged = GetSafeHwnd();
		pColorPopup->m_clrDefault = COLORREF(-1);
		pColorPopup->m_clrInitial =	m_clrColorCtrl;
		VERIFY(
			pPopup->ItemInsertSpecPopup(
			pColorPopup,
			nReplacePos + 1,
			pPopup->ItemGetText(nReplacePos),
			pPopup->ItemGetIcon(nReplacePos)
			)
			);
		pPopup->ItemSetDisplayed( nReplacePos + 1, true );
		VERIFY( pPopup->ItemRemove(nReplacePos) );
	} // if( nReplacePos >= 0 )

#if (!defined __EXT_MFC_NO_DATE_PICKER)
	nReplacePos =
		pPopup->ItemFindPosForCmdID(ID_DATE_PICKER_CTRL);
	
	if( nReplacePos >= 0 )
	{
		CExtPopupControlMenuWnd::g_bControlMenuWithShadows = true;
		CExtPopupDatePickerMenuWnd * pDatePickerPopup = new CExtPopupDatePickerMenuWnd;
		VERIFY(
			pPopup->ItemInsertSpecPopup(
			pDatePickerPopup,
			nReplacePos + 1,
			pPopup->ItemGetText(nReplacePos),
			pPopup->ItemGetIcon(nReplacePos)
			)
			);
		pPopup->ItemSetDisplayed( nReplacePos + 1, true );
		VERIFY( pPopup->ItemRemove(nReplacePos) );
	} // if( nReplacePos >= 0 )
#endif // #if (!defined __EXT_MFC_NO_DATE_PICKER)	
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPageToolbars::OnColorChangedFinally(WPARAM wParam, LPARAM lParam)
{
	switch( lParam )
	{
	case ID_COLOR_CTRL:
		m_clrColorCtrl = COLORREF(wParam);
		if( m_clrColorCtrl == COLORREF(-1) )
			AfxMessageBox(_T("Default Color"));
		else
		{
			CString sColor;
			sColor.Format(
				_T( "Command from the color control in the menubar\nRGB color is 0x%02X%02X%02X" ),
				INT( GetRValue(m_clrColorCtrl) ),
				INT( GetGValue(m_clrColorCtrl) ),
				INT( GetBValue(m_clrColorCtrl) )
				);
			AfxMessageBox( sColor );
		}
		break;
	default:
		break;
	} // switch( lParam )
	return 0;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPageToolbars::OnColorSelectCustom(WPARAM wParam, LPARAM lParam)
{
	wParam;
	if( lParam == ID_COLOR_CTRL )
	{
#if (defined _AFXDLL && !defined __STATPROFUIS_WITH_DLLMFC__)
		CExtColorDlg dlg;
		dlg.m_clrInit
			= dlg.m_clrNew
			= m_clrColorCtrl;
		if( dlg.DoModal() != IDOK )
			return -1;
		OnColorChangedFinally( 
			(WPARAM)dlg.m_clrNew,
			(LPARAM)ID_COLOR_CTRL
			);
#else
		CColorDialog dlg;
		if (dlg.DoModal() != IDOK)
			return -1;
		OnColorChangedFinally( 
			(WPARAM)dlg.GetColor(),
			(LPARAM)ID_COLOR_CTRL
			);
#endif
	} 
	return 0;
}
