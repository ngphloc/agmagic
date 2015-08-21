// PageTabWindow.cpp : implementation file
//

#include "stdafx.h"

#if (!defined __EXT_MFC_NO_TAB_CTRL)

#include "profuis_controls.h"
#include "PageTabWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPageTabWindow::demo_items_data_t CPageTabWindow::g_ItemsData[] =
{
	{ _T("DevStudio"),				true  },
		
	{ _T("Help Index"),				true  },
	{ _T("Help Search"),			false },
	{ _T("Index Results"),			false },
	{ _T("Contents"),				false },
	
	{ _T("Reload"),					true  },
	{ _T("Home"),					false },
	{ _T("Browser"),				false },
	
	{ _T("Find Results 1"),			true  },
	{ _T("Find Symbol Results"),	false },
	{ _T("Find Results 2"),			false },
	{ _T("Find In Files"),			false },
	
	{ _T("Favorites"),				true  },
	{ _T("Add To Favorites"),		false },
	
	{ _T("Full Screen"),			true  },
	
	{ _T("Dynamic Help"),			true  },
	
	{ _T("Resource View"),			true  },
	{ _T("Solution Explorer"),		false },
	{ _T("Class View"),				false },
	
	{ _T("Toolbox"),				true  },
	{ _T("Task List"),				false },
	
	{ _T("Open"),					true  },
	{ _T("Save All"),				false },
};

/////////////////////////////////////////////////////////////////////////////
// CPageTabWindow dialog
/////////////////////////////////////////////////////////////////////////////

CPageTabWindow::CPageTabWindow(CWnd* pParent /*=NULL*/)
	: CPageBase(CPageTabWindow::IDD, pParent)
	, m_nDemoImageListSize( sizeof( g_ItemsData ) / sizeof( g_ItemsData[0] ) )
	, m_nDemoImageListAddIndexInner( 0 )
	, m_nDemoImageListAddIndexOuter( 0 )
{
	//{{AFX_DATA_INIT(CPageTabWindow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	VERIFY(
		m_ImageList.Create(
		IDR_TAB_IMAGES,
		16,
		1,
		RGB(255,0,255)
		)
		);
	ASSERT( m_ImageList.GetImageCount() >= m_nDemoImageListSize );
}


void CPageTabWindow::DoDataExchange(CDataExchange* pDX)
{
	CPageBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTabWindow)
	DDX_Control(pDX, IDC_CHECK_FOCUS_ON_HOVER, m_CheckFocusOnHover);
	DDX_Control(pDX, IDC_CHECK_FULL_WIDTHS, m_CheckFullRowWidth);
	DDX_Control(pDX, IDC_CHECK_CENTER_TEXT, m_CheckCenterText);
	DDX_Control(pDX, IDC_CHECK_AUTOHIDE_SCROLL, m_CheckAutoHideScroll);
	DDX_Control(pDX, IDC_CHECK_ENABLE_HELP, m_CheckEnableHelp);
	DDX_Control(pDX, IDC_CHECK_ENABLE_CLOSE, m_CheckEnableClose);
	DDX_Control(pDX, IDC_CHECK_SHOW_HELP, m_CheckShowHelp);
	DDX_Control(pDX, IDC_CHECK_BOLD_SELECTION, m_CheckBoldSelection);
	DDX_Control(pDX, IDC_CHECK_SHOW_CLOSE, m_CheckShowClose);
	DDX_Control(pDX, IDC_CHECK_INVERT_VERT_FONT, m_CheckInvertFont);
	DDX_Control(pDX, IDC_CHECK_EQUAL_WIDTHS, m_CheckEqualWidth);
	DDX_Control(pDX, IDC_CHECK_SHOW_BORDERS, m_CheckShowBorders);
	DDX_Control(pDX, IDC_BUTTON_ADD_TAB_10, m_BtnAdd10);
	DDX_Control(pDX, IDC_BUTTON_ADD_TAB_1, m_BtnAdd1);
	DDX_Control(pDX, IDC_BUTTON_CLEAR_TABS, m_BtnClear);
	//}}AFX_DATA_MAP
	
	DDX_Control( pDX, ID_TABCTRL_OUTER_TOP, m_wndTabOuterTop );
	DDX_Control( pDX, ID_TABCTRL_OUTER_BOTTOM, m_wndTabOuterBottom );
	DDX_Control( pDX, ID_TABCTRL_OUTER_LEFT, m_wndTabOuterLeft );
	DDX_Control( pDX, ID_TABCTRL_OUTER_RIGHT, m_wndTabOuterRight );
	
	DDX_Control( pDX, ID_TABCTRL_INNER_TOP, m_wndTabInnerTop );
	DDX_Control( pDX, ID_TABCTRL_INNER_BOTTOM, m_wndTabInnerBottom );
	DDX_Control( pDX, ID_TABCTRL_INNER_LEFT, m_wndTabInnerLeft );
	DDX_Control( pDX, ID_TABCTRL_INNER_RIGHT, m_wndTabInnerRight );
}


BEGIN_MESSAGE_MAP(CPageTabWindow, CPageBase)
	//{{AFX_MSG_MAP(CPageTabWindow)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_TABS, OnButtonClearTabs)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TAB_1, OnButtonAddTab1)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TAB_10, OnButtonAddTab10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTabWindow message handlers

BOOL CPageTabWindow::OnInitDialog() 
{
	if( !CPageBase::OnInitDialog() ){
		ASSERT( FALSE );
		return FALSE;
	}

	if( m_ImageList.GetSafeHandle() == NULL ){
		ASSERT( FALSE );
		return FALSE;
	}
	
	AddAnchor( IDC_CHECK_SHOW_BORDERS,		CSize( 0,  0) );
	AddAnchor( IDC_CHECK_EQUAL_WIDTHS,		CSize( 0,  11) );
	AddAnchor( IDC_CHECK_FULL_WIDTHS,		CSize( 0,  22) );
	AddAnchor( IDC_CHECK_CENTER_TEXT,		CSize( 0,  33) );
	AddAnchor( IDC_CHECK_INVERT_VERT_FONT,	CSize( 0,  44) );
	AddAnchor( IDC_CHECK_BOLD_SELECTION,	CSize( 0,  55) );
	AddAnchor( IDC_CHECK_SHOW_CLOSE,		CSize( 0,  66) );
	AddAnchor( IDC_CHECK_ENABLE_CLOSE,		CSize( 0,  66) );
	AddAnchor( IDC_CHECK_SHOW_HELP,			CSize( 0,  77) );
	AddAnchor( IDC_CHECK_ENABLE_HELP,		CSize( 0,  77) );
	AddAnchor( IDC_CHECK_AUTOHIDE_SCROLL,	CSize( 0,  88) );
	AddAnchor( IDC_CHECK_FOCUS_ON_HOVER,	CSize( 0,  100) );

	AddAnchor( IDC_BUTTON_CLEAR_TABS,		__RDA_RB );
	AddAnchor( IDC_BUTTON_ADD_TAB_1,		__RDA_LB );
	AddAnchor( IDC_BUTTON_ADD_TAB_10,		__RDA_LB );
	
	AddAnchor( ID_TABCTRL_OUTER_TOP,		__RDA_LT, __RDA_RT );
	AddAnchor( ID_TABCTRL_OUTER_BOTTOM,		__RDA_LB, __RDA_RB );
	AddAnchor( ID_TABCTRL_OUTER_LEFT,		__RDA_LT, __RDA_LB );
	AddAnchor( ID_TABCTRL_OUTER_RIGHT,		__RDA_RT, __RDA_RB );
	
	AddAnchor( ID_TABCTRL_INNER_TOP,		__RDA_LT, __RDA_RT );
	AddAnchor( ID_TABCTRL_INNER_BOTTOM,		__RDA_LB, __RDA_RB );
	AddAnchor( ID_TABCTRL_INNER_LEFT,		__RDA_LT, __RDA_LB );
	AddAnchor( ID_TABCTRL_INNER_RIGHT,		__RDA_RT, __RDA_RB );

	m_wndTabOuterTop.ModifyTabWndStyle(		0, __ETWS_ORIENT_TOP	| __ETWS_GROUPED , true );
	m_wndTabOuterBottom.ModifyTabWndStyle(	0, __ETWS_ORIENT_BOTTOM	| __ETWS_GROUPED , true );
	m_wndTabOuterLeft.ModifyTabWndStyle(	0, __ETWS_ORIENT_LEFT	| __ETWS_GROUPED , true );
	m_wndTabOuterRight.ModifyTabWndStyle(	0, __ETWS_ORIENT_RIGHT	| __ETWS_GROUPED , true );
	m_wndTabInnerTop.ModifyTabWndStyle(		0, __ETWS_ORIENT_TOP	, true );
	m_wndTabInnerBottom.ModifyTabWndStyle(	0, __ETWS_ORIENT_BOTTOM	, true );
	m_wndTabInnerLeft.ModifyTabWndStyle(	0, __ETWS_ORIENT_LEFT	, true );
	m_wndTabInnerRight.ModifyTabWndStyle(	0, __ETWS_ORIENT_RIGHT	, true );
	
	//////////////////////////////////////////////////////////////////////////
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_EQUAL_WIDTHS, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_EQUAL_WIDTHS
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_FULL_WIDTHS, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_FULL_WIDTH
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_CENTER_TEXT, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_CENTERED_TEXT
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_INVERT_VERT_FONT, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_INVERT_VERT_FONT
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_BOLD_SELECTION, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_BOLD_SELECTION
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_SHOW_CLOSE, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_SHOW_BTN_CLOSE
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	GetDlgItem( IDC_CHECK_ENABLE_CLOSE )->EnableWindow( 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_SHOW_BTN_CLOSE 
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_ENABLE_CLOSE, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_ENABLED_BTN_CLOSE
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_SHOW_HELP, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_SHOW_BTN_HELP
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	GetDlgItem( IDC_CHECK_ENABLE_HELP )->EnableWindow( 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_SHOW_BTN_HELP 
		);

	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_ENABLE_HELP, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_ENABLED_BTN_HELP
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_AUTOHIDE_SCROLL, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_AUTOHIDE_SCROLL
		? BST_CHECKED
		: BST_UNCHECKED		
		);
	
	::CheckDlgButton( 
		this->GetSafeHwnd(), 
		IDC_CHECK_FOCUS_ON_HOVER, 
		m_wndTabOuterTop.GetTabWndStyle() & __ETWS_HOVER_FOCUS
		? BST_CHECKED
		: BST_UNCHECKED		
		);

	OnButtonAddTab10();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

BOOL CPageTabWindow::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if( nCode == CN_COMMAND )
	{
		DWORD dwTabWndStyleRemove = 0;
		DWORD dwTabWndStyleAdd = 0;
		
		switch( nID )
		{
		case IDC_CHECK_SHOW_BORDERS:
			{
				DWORD dwAddExBorderStyles = WS_EX_STATICEDGE;
				DWORD dwRemoveExBorderStyles = WS_EX_STATICEDGE;
				if( m_CheckShowBorders.GetCheck() )
					dwRemoveExBorderStyles = 0;
				else
					dwAddExBorderStyles = 0;
				m_wndTabOuterTop.ModifyStyleEx( dwRemoveExBorderStyles, dwAddExBorderStyles );
				m_wndTabOuterBottom.ModifyStyleEx( dwRemoveExBorderStyles, dwAddExBorderStyles );
				m_wndTabOuterLeft.ModifyStyleEx( dwRemoveExBorderStyles, dwAddExBorderStyles );
				m_wndTabOuterRight.ModifyStyleEx( dwRemoveExBorderStyles, dwAddExBorderStyles );
				m_wndTabInnerTop.ModifyStyleEx( dwRemoveExBorderStyles, dwAddExBorderStyles );
				m_wndTabInnerBottom.ModifyStyleEx( dwRemoveExBorderStyles, dwAddExBorderStyles );
				m_wndTabInnerLeft.ModifyStyleEx( dwRemoveExBorderStyles, dwAddExBorderStyles );
				m_wndTabInnerRight.ModifyStyleEx( dwRemoveExBorderStyles, dwAddExBorderStyles );
				
				UINT nSetWindowPosFlags =
					SWP_NOMOVE|SWP_NOSIZE
					|SWP_NOZORDER|SWP_NOOWNERZORDER
					|SWP_NOACTIVATE
					|SWP_FRAMECHANGED
					;
				m_wndTabOuterTop.SetWindowPos(NULL,0,0,0,0,nSetWindowPosFlags);
				m_wndTabOuterBottom.SetWindowPos(NULL,0,0,0,0,nSetWindowPosFlags);
				m_wndTabOuterLeft.SetWindowPos(NULL,0,0,0,0,nSetWindowPosFlags);
				m_wndTabOuterRight.SetWindowPos(NULL,0,0,0,0,nSetWindowPosFlags);
				m_wndTabInnerTop.SetWindowPos(NULL,0,0,0,0,nSetWindowPosFlags);
				m_wndTabInnerBottom.SetWindowPos(NULL,0,0,0,0,nSetWindowPosFlags);
				m_wndTabInnerLeft.SetWindowPos(NULL,0,0,0,0,nSetWindowPosFlags);
				m_wndTabInnerRight.SetWindowPos(NULL,0,0,0,0,nSetWindowPosFlags);
			}
			break;
		case IDC_CHECK_EQUAL_WIDTHS:
			m_CheckEqualWidth.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_EQUAL_WIDTHS
				: dwTabWndStyleRemove = __ETWS_EQUAL_WIDTHS;
			break;
		case IDC_CHECK_FULL_WIDTHS:
			m_CheckFullRowWidth.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_FULL_WIDTH
				: dwTabWndStyleRemove = __ETWS_FULL_WIDTH;
			break;
		case IDC_CHECK_CENTER_TEXT:
			m_CheckCenterText.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_CENTERED_TEXT
				: dwTabWndStyleRemove = __ETWS_CENTERED_TEXT;
			break;
		case IDC_CHECK_INVERT_VERT_FONT:
			m_CheckInvertFont.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_INVERT_VERT_FONT
				: dwTabWndStyleRemove = __ETWS_INVERT_VERT_FONT;
			break;
		case IDC_CHECK_BOLD_SELECTION:
			m_CheckBoldSelection.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_BOLD_SELECTION
				: dwTabWndStyleRemove = __ETWS_BOLD_SELECTION;
			break;
		case IDC_CHECK_SHOW_CLOSE:
			m_CheckShowClose.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_SHOW_BTN_CLOSE
				: dwTabWndStyleRemove = __ETWS_SHOW_BTN_CLOSE;
			GetDlgItem( IDC_CHECK_ENABLE_CLOSE )->EnableWindow( IsDlgButtonChecked( nID ) );
			break;
		case IDC_CHECK_ENABLE_CLOSE:
			m_CheckEnableClose.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_ENABLED_BTN_CLOSE
				: dwTabWndStyleRemove = __ETWS_ENABLED_BTN_CLOSE;
			break;
		case IDC_CHECK_SHOW_HELP:
			m_CheckShowHelp.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_SHOW_BTN_HELP
				: dwTabWndStyleRemove = __ETWS_SHOW_BTN_HELP;
			GetDlgItem( IDC_CHECK_ENABLE_HELP )->EnableWindow( IsDlgButtonChecked( nID ) );
			break;
		case IDC_CHECK_ENABLE_HELP:
			m_CheckEnableHelp.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_ENABLED_BTN_HELP
				: dwTabWndStyleRemove = __ETWS_ENABLED_BTN_HELP;
			break;
		case IDC_CHECK_AUTOHIDE_SCROLL:
			m_CheckAutoHideScroll.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_AUTOHIDE_SCROLL
				: dwTabWndStyleRemove = __ETWS_AUTOHIDE_SCROLL;
			break;
		case IDC_CHECK_FOCUS_ON_HOVER:
			m_CheckFocusOnHover.GetCheck() != 0 
				? dwTabWndStyleAdd = __ETWS_HOVER_FOCUS
				: dwTabWndStyleRemove = __ETWS_HOVER_FOCUS;
			break;
		default:
			return CPageBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
		}
		m_wndTabOuterTop.ModifyTabWndStyle( dwTabWndStyleRemove, dwTabWndStyleAdd, true );
		m_wndTabOuterBottom.ModifyTabWndStyle( dwTabWndStyleRemove, dwTabWndStyleAdd, true );
		m_wndTabOuterLeft.ModifyTabWndStyle( dwTabWndStyleRemove, dwTabWndStyleAdd, true );
		m_wndTabOuterRight.ModifyTabWndStyle( dwTabWndStyleRemove, dwTabWndStyleAdd, true );
		m_wndTabInnerTop.ModifyTabWndStyle( dwTabWndStyleRemove, dwTabWndStyleAdd, true );
		m_wndTabInnerBottom.ModifyTabWndStyle( dwTabWndStyleRemove, dwTabWndStyleAdd, true );
		m_wndTabInnerLeft.ModifyTabWndStyle( dwTabWndStyleRemove, dwTabWndStyleAdd, true );
		m_wndTabInnerRight.ModifyTabWndStyle( dwTabWndStyleRemove, dwTabWndStyleAdd, true );
		return TRUE;
	}

	return CPageBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//////////////////////////////////////////////////////////////////////////

void CPageTabWindow::OnButtonClearTabs() 
{
	m_BtnClear.EnableWindow( FALSE );
	
	if( !m_BtnAdd1.IsWindowEnabled() ){
		m_BtnAdd1.EnableWindow( TRUE );
		m_BtnAdd10.EnableWindow( TRUE );
	}
	
	m_wndTabOuterTop.ItemRemoveAll(true);
	m_wndTabOuterBottom.ItemRemoveAll(true);
	m_wndTabOuterLeft.ItemRemoveAll(true);
	m_wndTabOuterRight.ItemRemoveAll(true);
	m_wndTabInnerTop.ItemRemoveAll(true);
	m_wndTabInnerBottom.ItemRemoveAll(true);
	m_wndTabInnerLeft.ItemRemoveAll(true);
	m_wndTabInnerRight.ItemRemoveAll(true);
}

//////////////////////////////////////////////////////////////////////////

void CPageTabWindow::OnButtonAddTab1() 
{
	_DoAdd1(true);
}

//////////////////////////////////////////////////////////////////////////

void CPageTabWindow::OnButtonAddTab10() 
{
	for( INT i=0; i < 10; i++ ){
		bool bUpdateTabWnd = ( i == 9 ) ? true : false;
		_DoAdd1(bUpdateTabWnd);
	}
}

//////////////////////////////////////////////////////////////////////////

void CPageTabWindow::_DoAdd1( bool bUpdateTabWnd )
{
	ASSERT( m_ImageList.GetSafeHandle()	!= NULL );
	ASSERT( m_nDemoImageListSize > 0 );

	if( !m_BtnClear.IsWindowEnabled() )
		m_BtnClear.EnableWindow( TRUE );
	
	// insert 1 item into inner (non-grouped) tab controls
	ASSERT( m_nDemoImageListAddIndexInner <= m_nDemoImageListSize );
	if( m_nDemoImageListAddIndexInner == (m_nDemoImageListSize-1) )
		m_nDemoImageListAddIndexInner = 0;

	ASSERT( g_ItemsData[m_nDemoImageListAddIndexInner].m_sItemText != NULL );

HICON hIconInner = m_ImageList.ExtractIcon( m_nDemoImageListAddIndexInner );
	ASSERT( hIconInner != NULL );
	m_wndTabInnerTop.ItemInsert(
		g_ItemsData[m_nDemoImageListAddIndexInner].m_sItemText,
		hIconInner
		);
	m_wndTabInnerBottom.ItemInsert(
		g_ItemsData[m_nDemoImageListAddIndexInner].m_sItemText,
		hIconInner
		);
	m_wndTabInnerLeft.ItemInsert(
		g_ItemsData[m_nDemoImageListAddIndexInner].m_sItemText,
		hIconInner
		);
	m_wndTabInnerRight.ItemInsert(
		g_ItemsData[m_nDemoImageListAddIndexInner].m_sItemText,
		hIconInner
		);
	::DestroyIcon( hIconInner );

	m_nDemoImageListAddIndexInner++;

	// insert 1 group into outer (grouped) tab controls
/*
	m_wndTabOuterTop.ItemInsert( );
	m_wndTabOuterBottom.ItemInsert( );
	m_wndTabOuterLeft.ItemInsert( );
	m_wndTabOuterRight.ItemInsert( );
*/

	ASSERT( m_nDemoImageListAddIndexOuter <= m_nDemoImageListSize );

	if( m_nDemoImageListAddIndexOuter == (m_nDemoImageListSize-1) )
		m_nDemoImageListAddIndexOuter = 0;

	for( INT nAddedToOuter = 0; true ; nAddedToOuter++ )
	{

		bool bGroupStart = 
			g_ItemsData[m_nDemoImageListAddIndexOuter].m_bGroupStart;
		if( nAddedToOuter != 0 && bGroupStart )
			break;

		DWORD dwItemStyle = 0;
		if( bGroupStart )
			dwItemStyle |= __ETWI_GROUP_START | __ETWI_IN_GROUP_ACTIVE;

		HICON hIconOuter = m_ImageList.ExtractIcon( m_nDemoImageListAddIndexOuter );
		ASSERT( hIconOuter != NULL );

		ASSERT( g_ItemsData[m_nDemoImageListAddIndexOuter].m_sItemText != NULL );
		
		m_wndTabOuterTop.ItemInsert(
			g_ItemsData[m_nDemoImageListAddIndexOuter].m_sItemText,
			hIconOuter,
			true,
			dwItemStyle
			);
		m_wndTabOuterBottom.ItemInsert(
			g_ItemsData[m_nDemoImageListAddIndexOuter].m_sItemText,
			hIconOuter,
			true,
			dwItemStyle
			);
		m_wndTabOuterLeft.ItemInsert(
			g_ItemsData[m_nDemoImageListAddIndexOuter].m_sItemText,
			hIconOuter,
			true,
			dwItemStyle
			);
		m_wndTabOuterRight.ItemInsert(
			g_ItemsData[m_nDemoImageListAddIndexOuter].m_sItemText,
			hIconOuter,
			true,
			dwItemStyle
			);
		::DestroyIcon( hIconOuter );
	
		if( m_nDemoImageListAddIndexOuter == (m_nDemoImageListSize-1) )
			m_nDemoImageListAddIndexOuter = 0;
		else
			m_nDemoImageListAddIndexOuter++;
	} // for( INT nAddedToOuter = 0; true ; nAddedToOuter++ )

	// update or delay-update all tab controls
	m_wndTabInnerTop.UpdateTabWnd( bUpdateTabWnd );
	m_wndTabInnerBottom.UpdateTabWnd( bUpdateTabWnd );
	m_wndTabInnerLeft.UpdateTabWnd( bUpdateTabWnd );
	m_wndTabInnerRight.UpdateTabWnd( bUpdateTabWnd );
	m_wndTabOuterTop.UpdateTabWnd( bUpdateTabWnd );
	m_wndTabOuterBottom.UpdateTabWnd( bUpdateTabWnd );
	m_wndTabOuterLeft.UpdateTabWnd( bUpdateTabWnd );
	m_wndTabOuterRight.UpdateTabWnd( bUpdateTabWnd );

	if( m_wndTabInnerTop.ItemGetCount() >= 100 )
	{
		if( m_BtnAdd1.IsWindowEnabled() )
		{
			m_BtnAdd1.EnableWindow( FALSE );
			m_BtnAdd10.EnableWindow( FALSE );
		}
	}
}

#endif // (!defined __EXT_MFC_NO_TAB_CTRL)

