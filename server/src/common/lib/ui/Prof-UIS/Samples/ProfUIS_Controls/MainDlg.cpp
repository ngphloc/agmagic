// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProfUIS_Controls.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CExtResizableDialog(CMainDlg::IDD, pParent)
	, m_pPageNotAvailable(NULL)
#if (!defined __EXT_MFC_NO_TAB_CTRL)
	, m_pPageTabWindows(NULL)
#endif // (!defined __EXT_MFC_NO_TAB_CTRL)
	, m_pPageButtons(NULL)
#if (!defined __EXT_MFC_NO_TAB_PAGECONTAINER_CTRL && !defined __EXT_MFC_NO_TAB_PAGECONTAINER_FLAT_CTRL )
	, m_pPageTabContainers(NULL)
#endif // #if (!defined __EXT_MFC_NO_TAB_PAGECONTAINER_CTRL && !defined __EXT_MFC_NO_TAB_PAGECONTAINER_FLAT_CTRL )
	, m_pPagePopupMenus(NULL)
	, m_pPageStatusBar(NULL)
	, m_pPageToolbars(NULL)
#if (!defined __EXT_MFC_NO_DATE_PICKER)
	, m_pPageCalendar(NULL)
#endif // #if (!defined __EXT_MFC_NO_DATE_PICKER)	
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bDialogInitComplete = false;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CExtResizableDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_STATIC_COMBO_UI_LOOK, m_labelUILook);
	DDX_Control(pDX, IDC_BACK, m_btnBack);
	DDX_Control(pDX, IDC_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_COMBO_UI_LOOK, m_UILook);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MAIN_MENUBAR, m_wndMenuBar);
	DDX_Control(pDX, IDC_MAIN_TOOLBAR, m_wndToolBar);
}

BEGIN_MESSAGE_MAP(CMainDlg, CExtResizableDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDC_THEME_2003, OnLook2003)
	ON_UPDATE_COMMAND_UI(IDC_THEME_2003, OnUpdateLook2003)
	ON_COMMAND(IDC_THEME_2000, OnLook2k)
	ON_UPDATE_COMMAND_UI(IDC_THEME_2000, OnUpdateLook2k)
	ON_COMMAND(IDC_THEME_XP, OnLookXp)
	ON_UPDATE_COMMAND_UI(IDC_THEME_XP, OnUpdateLookXp)
	ON_WM_SIZE()
	ON_CBN_SELENDOK(IDC_COMBO_UI_LOOK, OnSelendokComboUiLook)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL CMainDlg::OnInitDialog()
{
	if( !CExtResizableDialog::OnInitDialog() ){
		ASSERT( FALSE );
		return FALSE;
	}
CWinApp * pApp = ::AfxGetApp();
	ASSERT( pApp != NULL );
	ASSERT( pApp->m_pszRegistryKey != NULL );
	ASSERT( pApp->m_pszRegistryKey[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );
	ASSERT( pApp->m_pszProfileName[0] != _T('\0') );
	
	VERIFY(
		g_CmdManager->ProfileWndAdd(
			pApp->m_pszProfileName,
			GetSafeHwnd()
			)
		);

	VERIFY(
		g_CmdManager->UpdateFromMenu(
		pApp->m_pszProfileName,
		IDR_MAIN_MENU
		)
		);
	VERIFY(
		g_CmdManager->UpdateFromMenu(
		pApp->m_pszProfileName,
		IDR_POPUP_MENU
		)
		);
	
	VERIFY(
		g_CmdManager->UpdateFromToolBar(
		pApp->m_pszProfileName,
		IDR_MAIN_TOOLBAR
		)
		);

	VERIFY(
		g_CmdManager->UpdateFromToolBar(
		pApp->m_pszProfileName,
		IDR_EDIT
		)
		);
	
	ASSERT( m_wndMenuBar.GetSafeHwnd() != NULL );
	if(	!m_wndMenuBar.LoadMenuBar( IDR_MAIN_MENU ) ){
		ASSERT( FALSE );
		return FALSE;
	}
	m_wndMenuBar.SetBarStyle( 
		m_wndMenuBar.GetBarStyle() & ~CBRS_GRIPPER 
		);
	
	ASSERT( m_wndToolBar.GetSafeHwnd() != NULL );
	if(	!m_wndToolBar.LoadToolBar( IDR_MAIN_TOOLBAR ) ){
		ASSERT( FALSE );
		return FALSE;
	}
	m_wndToolBar.SetBarStyle( 
		m_wndToolBar.GetBarStyle() & ~CBRS_GRIPPER 
		);
	
	static UINT g_statBasicCommands[] =
	{
		ID_APP_ABOUT,
			ID_APP_EXIT,
			IDC_THEME_2003,
			IDC_THEME_XP,
			IDC_THEME_2000,
			ID_OWNERDRAW_ITEM,
			ID_COLOR_CTRL,
			ID_DATE_PICKER_CTRL,
			0, // end of list
	};
 
	VERIFY(
		g_CmdManager->SetBasicCommands(
		pApp->m_pszProfileName,
		g_statBasicCommands
		)
		);

	VERIFY( g_PaintManager.InstallPaintManager( RUNTIME_CLASS(CExtPaintManagerXP) ) );
	m_UILook.SetCurSel(1);
	
	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, ID_APP_ABOUT /*IDM_ABOUTBOX*/, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	AddAnchor( IDC_LIST, __RDA_LT, __RDA_LB );
	AddAnchor( IDOK, __RDA_RB );
	AddAnchor( IDC_COMBO_UI_LOOK, __RDA_LB );
	AddAnchor( IDC_STATIC_COMBO_UI_LOOK, __RDA_LB );
	AddAnchor( IDC_NEXT, __RDA_RB );
	AddAnchor( IDC_BACK, __RDA_RB );
	AddAnchor( IDC_STATIC_DELIVER_FRAME, __RDA_LB, __RDA_RB );
	AddAnchor( IDC_STATIC_PAGES_RECT, __RDA_LT, __RDA_RB );
	
	m_UILook.SetCurSel( 1 );
	
	//////////////////////////////////////////////////////////////////////////
	
	CRect rcPages;
	::GetWindowRect( (this->GetDlgItem(IDC_STATIC_PAGES_RECT))->GetSafeHwnd(), &rcPages );
	ScreenToClient( &rcPages );

	HINSTANCE hInstResource =
		::AfxFindResourceHandle(
		MAKEINTRESOURCE( IDR_MAINFRAME ),
		RT_ICON
		);
	ASSERT( hInstResource != NULL );

	//////////////////////////////////////////////////////////////////////////
	
	m_pPageNotAvailable = new CPageNotAvailable;
	ASSERT( m_pPageNotAvailable != NULL );
	m_pPageNotAvailable->Create(
		CPageNotAvailable::IDD,
		this
		);
	
	//////////////////////////////////////////////////////////////////////////
	
	m_pPageButtons = new CPageButtons;
	ASSERT( m_pPageButtons != NULL );
	m_pPageButtons->Create(
		CPageButtons::IDD,
		this
		);
	
	//////////////////////////////////////////////////////////////////////////

#if (!defined __EXT_MFC_NO_TAB_CTRL)
	m_pPageTabWindows = new CPageTabWindow;
	ASSERT( m_pPageTabWindows != NULL );
	m_pPageTabWindows->Create(
		CPageTabWindow::IDD,
		this
		);
#endif // (!defined __EXT_MFC_NO_TAB_CTRL)
	
	//////////////////////////////////////////////////////////////////////////
	
#if (!defined __EXT_MFC_NO_TAB_PAGECONTAINER_CTRL && !defined __EXT_MFC_NO_TAB_PAGECONTAINER_FLAT_CTRL )
	m_pPageTabContainers = new CPageTabContainers;
	ASSERT( m_pPageTabContainers != NULL );
	m_pPageTabContainers->Create(
		CPageTabContainers::IDD,
		this
		);
#endif // #if (!defined __EXT_MFC_NO_TAB_PAGECONTAINER_CTRL && !defined __EXT_MFC_NO_TAB_PAGECONTAINER_FLAT_CTRL )
	
	//////////////////////////////////////////////////////////////////////////
	
	m_pPagePopupMenus = new CPagePopupMenus;
	ASSERT( m_pPagePopupMenus != NULL );
	m_pPagePopupMenus->Create(
		CPagePopupMenus::IDD,
		this
		);
	
	//////////////////////////////////////////////////////////////////////////
	
	m_pPageStatusBar = new CPageStatusBar;
	ASSERT( m_pPageStatusBar != NULL );
	m_pPageStatusBar->Create(
		CPageStatusBar::IDD,
		this
		);
	
	//////////////////////////////////////////////////////////////////////////
	
	m_pPageToolbars = new CPageToolbars;
	ASSERT( m_pPageToolbars != NULL );
	m_pPageToolbars->Create(
		CPageToolbars::IDD,
		this
		);
	
	//////////////////////////////////////////////////////////////////////////
	
#if (!defined __EXT_MFC_NO_DATE_PICKER)
	m_pPageCalendar = new CPageCalendar;
	ASSERT( m_pPageCalendar != NULL );
	m_pPageCalendar->Create(
		CPageCalendar::IDD,
		this
		);
#endif // #if (!defined __EXT_MFC_NO_DATE_PICKER)	
	
	//////////////////////////////////////////////////////////////////////////
	
	// TODO:

	// Color controls
	// Toolbox
	// Shortcut List	
	// Grid Control	
	// Misc Control	(Font combobox, Browse Edit)

	//////////////////////////////////////////////////////////////////////////
	
	struct {
		LPCTSTR m_strResource;
		INT m_nWidth, m_nHeight;
		UINT m_nLoadImageFlags;
		CPageBase *m_pWndPage;
		LPCTSTR m_strText;
	} _iconInit[] =
	{
		{	MAKEINTRESOURCE( IDI_BUTTONS ),
			32, 32,
			0,
			m_pPageButtons,
			_T("Buttons")
		},
		{	MAKEINTRESOURCE( IDI_TAB_WINDOW ),
			32, 32,
			0,
#if (!defined __EXT_MFC_NO_TAB_CTRL)
			m_pPageTabWindows,
#else
			m_pPageNotAvailable,
#endif // (!defined __EXT_MFC_NO_TAB_CTRL)
			_T("Tab Window")
		},
		{	MAKEINTRESOURCE( IDI_TAB_CONTAINER ),
			32, 32,
			0,
#if (!defined __EXT_MFC_NO_TAB_PAGECONTAINER_CTRL && !defined __EXT_MFC_NO_TAB_PAGECONTAINER_FLAT_CTRL )
			m_pPageTabContainers,
#else
			m_pPageNotAvailable,
#endif // #if (!defined __EXT_MFC_NO_TAB_PAGECONTAINER_CTRL && !defined __EXT_MFC_NO_TAB_PAGECONTAINER_FLAT_CTRL )
			_T("Tab Containers")
		},
		{	MAKEINTRESOURCE( IDI_MENU ),
			32, 32,
			0,
			m_pPagePopupMenus,
			_T("Popup Menus")
		},
		{	MAKEINTRESOURCE( IDI_STATUS_BAR ),
			32, 32,
			0,
			m_pPageStatusBar,
			_T("Status Bar")
		},
		{	MAKEINTRESOURCE( IDI_MENU_TOOLBAR ),
			32, 32,
			0,
			m_pPageToolbars,
			_T("Menubar && Toolbars")
		},
		{	MAKEINTRESOURCE( IDI_CALENDAR ),
			32, 32,
			0,
#if (!defined __EXT_MFC_NO_DATE_PICKER)
			m_pPageCalendar,
#else
			m_pPageNotAvailable,
#endif // #if (!defined __EXT_MFC_NO_DATE_PICKER)	
			_T("Calendar")
		},
	};
	for( int nInit = 0; nInit < (sizeof(_iconInit)/sizeof(_iconInit[0])) ; nInit++ )
	{
		_iconInit[nInit].m_pWndPage->MoveWindow( &rcPages );
		AddAnchor( _iconInit[nInit].m_pWndPage->GetSafeHwnd(), __RDA_LT, __RDA_RB );

		HICON hIcon = (HICON)
			::LoadImage(
			hInstResource,
			_iconInit[nInit].m_strResource,
			IMAGE_ICON,
			_iconInit[nInit].m_nWidth,
			_iconInit[nInit].m_nHeight,
			_iconInit[nInit].m_nLoadImageFlags
			);
		ASSERT( hIcon != NULL );
		CExtCmdIcon icon( hIcon, false );
		ASSERT( !icon.IsEmpty() );
		m_wndList.AddIcon(
			icon,
			_iconInit[nInit].m_strText,
			_iconInit[nInit].m_pWndPage->GetSafeHwnd()
			);
	} // for( nInit = 0; nInit < (sizeof(_iconInit)/sizeof(_iconInit[0])) ; nInit++ )
	
	_iconInit[0].m_pWndPage->ShowWindow(SW_SHOW);
	m_wndList.SetCurSel( 0 );
	
	//////////////////////////////////////////////////////////////////////////
	
	EnableSaveRestore( _T("Dialog Positions"), _T("MainDlg") );
	
	CWnd::RepositionBars(0,0xFFFF,0);
	
	m_bDialogInitComplete = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//////////////////////////////////////////////////////////////////////////
	
void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		VERIFY( ProfUISAbout() );
	}
	else
	{
		CExtResizableDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CExtResizableDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnAppAbout() 
{
	VERIFY( ProfUISAbout() );
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnLook2003() 
{
	m_UILook.SetCurSel(2);
	OnSelendokComboUiLook();
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnUpdateLook2003(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerOffice2003) )
		? TRUE
		: FALSE
		);
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnLook2k() 
{
	m_UILook.SetCurSel(0);
	OnSelendokComboUiLook();
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnUpdateLook2k(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetRadio(
		g_PaintManager->IsKindOf( RUNTIME_CLASS(CExtPaintManagerXP) )
		? FALSE
		: TRUE
		);
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnLookXp() 
{
	m_UILook.SetCurSel(1);
	OnSelendokComboUiLook();
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnUpdateLookXp(CCmdUI* pCmdUI) 
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

void CMainDlg::OnSize(UINT nType, int cx, int cy) 
{
	CExtResizableDialog::OnSize(nType, cx, cy);

	if( nType != SIZE_MINIMIZED )
		CWnd::RepositionBars(0,0xFFFF,0);
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnSelendokComboUiLook() 
{
	if( !m_bDialogInitComplete )
		return;
	int nCurStyle = 
		g_PaintManager->IsKindOf(
		RUNTIME_CLASS( CExtPaintManagerOffice2003 )
		)
		? 2 : 0;
	if(		nCurStyle == 0
		&&	g_PaintManager->IsKindOf(
		RUNTIME_CLASS( CExtPaintManagerXP )
		)
		)
		nCurStyle = 1;
	int nCurSel = m_UILook.GetCurSel();
	if( nCurSel == nCurStyle )
		return;
	if(nCurSel == 0)
	{
		VERIFY( g_PaintManager.InstallPaintManager( RUNTIME_CLASS(CExtPaintManager) ) );
	}
	else if(nCurSel == 1)
	{
		VERIFY( g_PaintManager.InstallPaintManager( RUNTIME_CLASS(CExtPaintManagerXP) ) );
	}
	else
	{
		VERIFY( g_PaintManager.InstallPaintManager( RUNTIME_CLASS(CExtPaintManagerOffice2003) ) );
	}
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
	CWnd::RepositionBars(0,0xFFFF,0);
	RedrawWindow( NULL, NULL,
		RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW
		|RDW_ALLCHILDREN
		);
	UpdateDialogControls( this, FALSE );

	if( m_pPageToolbars ){
		m_pPageToolbars->_Update();
	}
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnSelchangeList() 
{
	int nIndex = m_wndList.GetCurSel();
	CIconListBox::ITEM_DATA *pItemData = m_wndList.m_arrItems[nIndex];
	
	for( int i=0; i < m_wndList.m_arrItems.GetSize(); i++ ){
		if( nIndex != i ){
			::ShowWindow(m_wndList.m_arrItems[i]->m_hWndPage,SW_HIDE);
		}
	}
	{
		::ShowWindow(pItemData->m_hWndPage,SW_SHOW);
		//::SetFocus(pItemData->m_hWndPage);
	}
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnBack() 
{
	int nIndex = m_wndList.GetCurSel();
	nIndex > 0
		? nIndex--
		: nIndex = m_wndList.GetCount()-1;
	m_wndList.SetCurSel( nIndex );
	OnSelchangeList();
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnNext() 
{
	int nIndex = m_wndList.GetCurSel();
	nIndex < m_wndList.GetCount()-1
		? nIndex++
		: nIndex = 0;
	m_wndList.SetCurSel( nIndex );
	OnSelchangeList();
} 

//////////////////////////////////////////////////////////////////////////

LRESULT CMainDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lResult = CExtResizableDialog::WindowProc(message, wParam, lParam);
	if( message == WM_SETMESSAGESTRING )
	{
		if( m_pPageStatusBar ){
			m_pPageStatusBar->SendMessage( message,wParam,lParam );
		}
		return 0L;
	}
	return lResult;
}
