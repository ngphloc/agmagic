// PageButtons.cpp : implementation file
//

#include "stdafx.h"
#include "profuis_controls.h"
#include "PageButtons.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_HAND MAKEINTRESOURCE(32649)

/////////////////////////////////////////////////////////////////////////////
// CPageButtons dialog


CPageButtons::CPageButtons(CWnd* pParent /*=NULL*/)
	: CPageBase(CPageButtons::IDD, pParent)
	, m_bInitComplete( false )
{
	//{{AFX_DATA_INIT(CPageButtons)
	//}}AFX_DATA_INIT
}


void CPageButtons::DoDataExchange(CDataExchange* pDX)
{
	CPageBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageButtons)
	DDX_Control(pDX, IDC_RADIO1, m_wndRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_wndRadio2);
	DDX_Control(pDX, IDC_CHECK_BOX2, m_chkCheckBox2);
	DDX_Control(pDX, IDC_CHECK_BOX1, m_chkCheckBox1);
	DDX_Control(pDX, IDC_BUTTON_WITH_MENU, m_btnWithMenu);
	DDX_Control(pDX, IDC_BUTTON_COLOR2, m_btnColor2);
	DDX_Control(pDX, IDC_BUTTON_COLOR1, m_btnColor1);
	DDX_Control(pDX, IDC_CHECK_BOX_SHOW_FOCUS_RECT, m_chkCheckBoxShowFocusRect);
	DDX_Control(pDX, IDC_TOOLTIP, m_Tooltip);
	DDX_Control(pDX, IDC_TEXT_ALIGN1, m_TextAlign1);
	DDX_Control(pDX, IDC_TEXT_ALIGN2, m_TextAlign2);
	DDX_Control(pDX, IDC_STATIC_TOOLTIP, m_StaticTooltip);
	DDX_Control(pDX, IDC_STATIC_TEXT_ALIGN1, m_StaticTextAlign1);
	DDX_Control(pDX, IDC_STATIC_TEXT_ALIGN2, m_StaticTextAlign2);
	DDX_Control(pDX, IDC_STATIC_SKIN, m_StaticSkin);
	DDX_Control(pDX, IDC_STATIC_PUSH_BUTTON, m_StaticPushButton);
	DDX_Control(pDX, IDC_STATIC_CHECK_BOX, m_StaticCheckBox);
	DDX_Control(pDX, IDC_STATIC_CURSOR, m_StaticCursor);
	DDX_Control(pDX, IDC_SKIN, m_CheckBoxSkin);
	DDX_Control(pDX, IDC_PUSH_LIKE_BUTTON, m_btnPushLikeButton);
	DDX_Control(pDX, IDC_PUSH_BUTTON, m_btnPushButton);
	DDX_Control(pDX, IDC_CURSOR, m_Cursor);
	DDX_Control(pDX, IDC_CHECK_TRISTATE, m_chkTriState);
	DDX_Control(pDX, IDC_CHECK_BUTTON_SHOW_FOCUS_RECT, m_chkButtonShowFocusRect);
	DDX_Control(pDX, IDC_CHECK_BUTTON_ENABLE, m_chkButtonEnable);
	DDX_Control(pDX, IDC_CHECK_BOX_ENABLE, m_chkCheckBoxEnable);
	DDX_Control(pDX, IDC_CHECK_LEFT_TEXT, m_chkLeftText);
	DDX_Control(pDX, IDC_CHECK_SEPARATED_BUTTONS, m_chkSeparatedButtons);
	DDX_Control(pDX, IDC_CHECK_FLAT, m_chkFlat);
	DDX_Control(pDX, IDC_CHECK_BORDER, m_chkBorders);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageButtons, CPageBase)
	//{{AFX_MSG_MAP(CPageButtons)
	ON_CBN_SELENDOK(IDC_SKIN, OnSelendokSkin)
	ON_CBN_SELENDOK(IDC_TEXT_ALIGN2, OnSelendokTextAlign2)
	ON_CBN_SELENDOK(IDC_CURSOR, OnSelendokCursor)
	//}}AFX_MSG_MAP
	// color popup menu
	ON_REGISTERED_MESSAGE(
		CExtPopupColorMenuWnd::g_nMsgNotifyColorChangedFinally,
		OnColorChangedFinally
		)
	ON_REGISTERED_MESSAGE(
		CExtPopupColorMenuWnd::g_nMsgNotifyCustColor,
		OnColorSelectCustom
		)
	ON_REGISTERED_MESSAGE(CExtPopupMenuWnd::g_nMsgPrepareMenu,OnExtMenuPrepare)
	ON_REGISTERED_MESSAGE(CExtPopupMenuWnd::g_nMsgPopupDrawItem,OnDrawPopupMenuItem)
	ON_REGISTERED_MESSAGE(CExtPopupMenuWnd::g_nMsgPopupDrawLeftArea,OnDrawPopupLeftArea)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageButtons message handlers

BOOL CPageButtons::OnInitDialog() 
{
	CPageBase::OnInitDialog();
	
	m_StaticPushButton.SetStyle( CExtGroupBox::STYLE_ROUNDED );
	m_StaticCheckBox.SetStyle( CExtGroupBox::STYLE_ROUNDED );
	
	CString sTooltip( _T("Tooltip") );
	m_Tooltip.SetWindowText( sTooltip );
	m_btnPushButton.SetTooltipText( sTooltip );
	
	m_btnPushButton.SetIcon(IDI_NOTEPAD);
	m_btnWithMenu.SetIcon(IDI_ICON_IN, IDI_ICON_OUT);
	m_btnPushLikeButton.SetIcon(IDI_LED_OFF);
	
	CheckDlgButton( IDC_CHECK_BUTTON_ENABLE, BST_CHECKED );
	CheckDlgButton( IDC_CHECK_BOX_ENABLE, BST_CHECKED );
	
	m_btnColor1.m_lParamCookie = LPARAM(IDC_BUTTON_COLOR1);
	m_btnColor1.m_nMenuLeftAreaWidth = 30;
	m_btnColor2.m_lParamCookie = LPARAM(IDC_BUTTON_COLOR2);
	
	m_btnWithMenu.m_dwMenuOpt |= TPMX_OWNERDRAW_FIXED;
	CMenu _menu;
	VERIFY(
		_menu.LoadMenu(IDR_POPUP_MENU)
		);
	m_btnWithMenu.m_menu.Attach(
		_menu.Detach()
		);
	
	m_bInitComplete = true;

	int nIndex = -1, nInitSel = -1;
	nInitSel = nIndex = m_CheckBoxSkin.AddString( _T("Standard") );
	m_CheckBoxSkin.SetItemData( nIndex, 0 );
	nIndex = m_CheckBoxSkin.AddString( _T("XP") );
	m_CheckBoxSkin.SetItemData( nIndex, IDB_BOX_IMAGES_XP );
	nIndex = m_CheckBoxSkin.AddString( _T("XP Blue") );
	m_CheckBoxSkin.SetItemData( nIndex, IDB_BOX_IMAGES_XP_BLUE );
	nIndex = m_CheckBoxSkin.AddString( _T("XP Cross") );
	m_CheckBoxSkin.SetItemData( nIndex, IDB_BOX_IMAGES_XP_CROSS );
	m_CheckBoxSkin.SetCurSel( nInitSel );
	
	nInitSel = nIndex = m_TextAlign2.AddString( _T("Default") );
	m_TextAlign2.SetItemData( nIndex, 0 );
	nIndex = m_TextAlign2.AddString( _T("Left") );
	m_TextAlign2.SetItemData( nIndex, BS_LEFT );
	nIndex = m_TextAlign2.AddString( _T("Right") );
	m_TextAlign2.SetItemData( nIndex, BS_RIGHT );
	nIndex = m_TextAlign2.AddString( _T("Center") );
	m_TextAlign2.SetItemData( nIndex, BS_CENTER );
	m_TextAlign2.SetCurSel( nInitSel );
	
	nInitSel = nIndex = m_Cursor.AddString( _T("Default") );
	m_Cursor.SetItemData( nIndex, 0 );
	nIndex = m_Cursor.AddString( _T("Hand") );
	m_Cursor.SetItemData( nIndex, (DWORD)IDC_HAND);
	nIndex = m_Cursor.AddString( _T("Cross") );
	m_Cursor.SetItemData( nIndex, (DWORD)IDC_CROSS);
	nIndex = m_Cursor.AddString( _T("UpArrow") );
	m_Cursor.SetItemData( nIndex, (DWORD)IDC_UPARROW);
	nIndex = m_Cursor.AddString( _T("Wait") );
	m_Cursor.SetItemData( nIndex, (DWORD)IDC_WAIT);
	nIndex = m_Cursor.AddString( _T("SizeAll") );
	m_Cursor.SetItemData( nIndex, (DWORD)IDC_SIZEALL);
	m_Cursor.SetCurSel( nInitSel );
	
	OnCmdMsg( IDC_CHECK_BUTTON_ENABLE, CN_COMMAND, NULL, NULL );
	OnCmdMsg( IDC_CHECK_FLAT, CN_COMMAND, NULL, NULL );
	OnCmdMsg( IDC_CHECK_BORDER, CN_COMMAND, NULL, NULL );
	OnCmdMsg( IDC_CHECK_BUTTON_SHOW_FOCUS_RECT, CN_COMMAND, NULL, NULL );
	OnCmdMsg( IDC_CHECK_SEPARATED_BUTTONS, CN_COMMAND, NULL, NULL );
	OnCmdMsg( IDC_CHECK_BOX_ENABLE, CN_COMMAND, NULL, NULL );
	OnCmdMsg( IDC_CHECK_TRISTATE, CN_COMMAND, NULL, NULL );
	OnCmdMsg( IDC_CHECK_LEFT_TEXT, CN_COMMAND, NULL, NULL );
	OnCmdMsg( IDC_CHECK_BOX_SHOW_FOCUS_RECT, CN_COMMAND, NULL, NULL );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

BOOL CPageButtons::OnCmdMsg(UINT nID, INT nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if( !m_bInitComplete ){
		return CPageBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}

	if( nCode == EN_CHANGE )
	{
		if( nID == IDC_TOOLTIP ){
			CString sTooltip;
			m_Tooltip.GetWindowText( sTooltip );
			m_btnPushButton.SetTooltipText( sTooltip );
		}else{
			return CPageBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
		}
		return TRUE;
	}

	if( nCode == CN_COMMAND )
	{
		BOOL bChecked = FALSE;
		
		switch( nID )
		{
		case IDC_CHECK_BUTTON_ENABLE:
			bChecked = IsDlgButtonChecked( nID );
			m_btnPushButton.EnableWindow( bChecked );
			m_btnPushLikeButton.EnableWindow( bChecked );
			m_btnWithMenu.EnableWindow( bChecked );
			m_btnColor1.EnableWindow( bChecked );
			m_btnColor2.EnableWindow( bChecked );
			break;

		case IDC_CHECK_FLAT:
			bChecked = IsDlgButtonChecked( nID );
			m_btnPushButton.SetFlat( bChecked );
			m_btnPushLikeButton.SetFlat( bChecked );
			m_btnWithMenu.SetFlat( bChecked );
			m_btnColor1.SetFlat( bChecked );
			m_btnColor2.SetFlat( bChecked );
			break;
			
		case IDC_CHECK_BORDER:
			bChecked = IsDlgButtonChecked( nID );
			m_btnPushButton.SetDrawBorder( bChecked );
			m_btnPushLikeButton.SetDrawBorder( bChecked );
			m_btnWithMenu.SetDrawBorder( bChecked );
			m_btnColor1.SetDrawBorder( bChecked );
			m_btnColor2.SetDrawBorder( bChecked );
			break;
			
		case IDC_PUSH_LIKE_BUTTON:
			IsDlgButtonChecked( nID )
				? m_btnPushLikeButton.SetIcon(IDI_LED_ON)
				: m_btnPushLikeButton.SetIcon(IDI_LED_OFF);
			break;
			
		case IDC_CHECK_BUTTON_SHOW_FOCUS_RECT:
			bChecked = IsDlgButtonChecked( nID );
			m_btnPushButton.SetDrawFocusRect( bChecked );
			m_btnPushLikeButton.SetDrawFocusRect( bChecked );
			m_btnWithMenu.SetDrawFocusRect( bChecked );
			m_btnColor1.SetDrawFocusRect( bChecked );
			m_btnColor2.SetDrawFocusRect( bChecked );
			break;
			
		case IDC_CHECK_SEPARATED_BUTTONS:
			bChecked = IsDlgButtonChecked( nID );
			m_btnWithMenu.SetSeparatedDropDown( bChecked );
			m_btnColor1.SetSeparatedDropDown( bChecked );
			m_btnColor2.SetSeparatedDropDown( bChecked );
			break;

		case IDC_CHECK_BOX_ENABLE:
			m_chkCheckBox1.EnableWindow( IsDlgButtonChecked( nID ) );
			m_chkCheckBox2.EnableWindow( IsDlgButtonChecked( nID ) );
			m_wndRadio1.EnableWindow( IsDlgButtonChecked( nID ) );
			m_wndRadio2.EnableWindow( IsDlgButtonChecked( nID ) );
			break;
			
		case IDC_CHECK_TRISTATE:
			if( IsDlgButtonChecked( nID ) ){
				m_chkCheckBox1.SetButtonStyle( BS_AUTO3STATE );
				m_chkCheckBox2.SetButtonStyle( BS_AUTO3STATE );
			}else{
				m_chkCheckBox1.SetButtonStyle( BS_AUTOCHECKBOX );
				m_chkCheckBox2.SetButtonStyle( BS_AUTOCHECKBOX );
			}
			m_chkCheckBox1.Invalidate();
			m_chkCheckBox2.Invalidate();
			break;
			
		case IDC_CHECK_LEFT_TEXT:
			if( IsDlgButtonChecked( nID ) ){
				m_chkCheckBox1.ModifyStyle( 0, BS_LEFTTEXT );
				m_chkCheckBox2.ModifyStyle( 0, BS_LEFTTEXT );
				m_wndRadio1.ModifyStyle( 0, BS_LEFTTEXT );
				m_wndRadio2.ModifyStyle( 0, BS_LEFTTEXT );
			}else{
				m_chkCheckBox1.ModifyStyle( BS_LEFTTEXT, 0 );
				m_chkCheckBox2.ModifyStyle( BS_LEFTTEXT, 0 );
				m_wndRadio1.ModifyStyle( BS_LEFTTEXT, 0 );
				m_wndRadio2.ModifyStyle( BS_LEFTTEXT, 0 );
			}
			m_chkCheckBox1.Invalidate();
			m_chkCheckBox2.Invalidate();
			m_wndRadio1.Invalidate();
			m_wndRadio2.Invalidate();
			break;
			
		case IDC_CHECK_BOX_SHOW_FOCUS_RECT:
			bChecked = IsDlgButtonChecked( nID );
			m_chkCheckBox1.SetDrawFocusRect( bChecked );
			m_chkCheckBox2.SetDrawFocusRect( bChecked );
			m_wndRadio1.SetDrawFocusRect( bChecked );
			m_wndRadio2.SetDrawFocusRect( bChecked );
			break;

		default:
			return CPageBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
		}
		return TRUE;
	}
	return CPageBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPageButtons::OnColorChangedFinally(WPARAM wParam, LPARAM lParam)
{
	switch( lParam )
	{
	case IDC_BUTTON_COLOR1:
	case IDC_BUTTON_COLOR2:
	case ID_COLOR_CTRL:
		{
		COLORREF clrColorCtrl = COLORREF(wParam);
		if( clrColorCtrl == COLORREF(-1) )
			AfxMessageBox(_T("Default Color"));
		else
		{
			CString sColor;
			sColor.Format(
				_T( "RGB color is 0x%02X%02X%02X" ),
				INT( GetRValue(clrColorCtrl) ),
				INT( GetGValue(clrColorCtrl) ),
				INT( GetBValue(clrColorCtrl) )
				);
			AfxMessageBox( sColor );
		}
		}
		break;
	default:
		break;
	} // switch( lParam )
	return 0;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPageButtons::OnColorSelectCustom(WPARAM wParam, LPARAM lParam)
{
	wParam;
	if( lParam == ID_COLOR_CTRL )
	{
		COLORREF clrNew;
#if (defined _AFXDLL && !defined __STATPROFUIS_WITH_DLLMFC__)
		CExtColorDlg dlg;
		if( dlg.DoModal() != IDOK )
			return 0;
		clrNew = dlg.m_clrNew;
#else
		CColorDialog dlg;
		if (dlg.DoModal() != IDOK)
			return 0;
		clrNew = dlg.GetColor();
#endif
		OnColorChangedFinally((WPARAM)clrNew, ID_COLOR_CTRL);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPageButtons::OnDrawPopupLeftArea(WPARAM wParam, LPARAM lParam)
{
	wParam;
	CExtPopupMenuWnd::DRAWLEFTAREADATA * pDrawLeftAreaData =
		reinterpret_cast < CExtPopupMenuWnd::DRAWLEFTAREADATA * > ( lParam );
	ASSERT( pDrawLeftAreaData != NULL );
	
	// get draw DC
	CDC & dc = *( (CDC *) *pDrawLeftAreaData );
	
	CRect rcItem = LPCRECT(*pDrawLeftAreaData);
	CExtPaintManager::stat_PaintGradientRect(
		dc,
		&rcItem,
		dc.GetNearestColor( RGB( 0, 0, 0 ) ),
		dc.GetNearestColor( RGB( 100, 100, 255 ) ),
		true
		);
	
	LOGFONT lf;
	::memset(&lf,0,sizeof(LOGFONT));
	g_PaintManager->m_FontNormalVertX.GetLogFont( &lf );
	lf.lfHeight = -18;
	lf.lfWidth = 0;
	lf.lfWeight = 900;
	_tcscpy( lf.lfFaceName, _T("Times New Roman") );
	CFont font;
	VERIFY(
		font.CreateFontIndirect(&lf)
		);
	CFont * pOldFont = dc.SelectObject( &font );
	INT nOldBkMode = dc.SetBkMode( TRANSPARENT );
	COLORREF clrOldText = dc.SetTextColor( RGB( 0, 0, 0 ) );
	
	static CString sTitle( _T("Prof-UIS") );
	CPoint ptText( rcItem.left+4, rcItem.bottom-5 );
	dc.DrawState(
		ptText, rcItem.Size(), (LPCTSTR)sTitle,
		DSS_NORMAL,  TRUE, 0, (CBrush*)NULL
		);
	dc.SetTextColor( RGB( 255, 255, 255 ) );
	ptText.Offset( -1, -2 );
	dc.DrawState(
		ptText, rcItem.Size(), (LPCTSTR)sTitle,
		DSS_NORMAL,  TRUE, 0, (CBrush*)NULL
		);
	
	const int nIconMetric = 24;
	HICON hIcon = (HICON)
		::LoadImage(
		::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_ICON_FOR_POPUP_MENU),
		IMAGE_ICON,
		nIconMetric,
		nIconMetric,
		0
		);
	if( hIcon != NULL )
	{
		int nOffset = (rcItem.Width() - nIconMetric) / 2;
		VERIFY(
			::DrawIconEx(
			dc.GetSafeHdc(),
			rcItem.left + nOffset,
			rcItem.top + nOffset,
			hIcon,
			nIconMetric,
			nIconMetric,
			0,
			(HBRUSH)NULL,
			DI_NORMAL
			)
			);
		VERIFY( DestroyIcon( hIcon ) );
	}
	
	dc.SetBkMode( nOldBkMode );
	dc.SetTextColor( clrOldText );
	dc.SelectObject( pOldFont );
	
	return !0;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPageButtons::OnDrawPopupMenuItem(WPARAM wParam, LPARAM lParam)
{
	wParam;
	CExtPopupMenuWnd::DRAWITEMDATA * pDrawItemData =
		reinterpret_cast < CExtPopupMenuWnd::DRAWITEMDATA * > ( lParam );
	ASSERT( pDrawItemData != NULL );
	UINT nCmdID = pDrawItemData->GetCmdID();
	if( nCmdID != ID_OWNERDRAW_ITEM )
		return 0; // default painting
	
	// paint default menu item background
	pDrawItemData->PaintDefaultBk();
	
	// paint some staff in a little bit rect
	CRect rcItem = LPCRECT(*pDrawItemData);
	rcItem.DeflateRect( 10, 1, 10, 4 );
	
	LPCTSTR sItemText = __EXT_MFC_SAFE_LPCTSTR( *pDrawItemData );
	INT nItemTextLen = _tcslen( sItemText );
	
	// get draw DC
	CDC & dc = *( (CDC *) *pDrawItemData );
	
	CExtWndShadow _shadow;
	_shadow.Paint(
		dc, rcItem, CRect(0,0,0,0), CRect(0,0,0,0),
		3,
		CExtWndShadow::DEF_BRIGHTNESS_MIN,
		CExtWndShadow::DEF_BRIGHTNESS_MAX,
		false
		);
	CExtPaintManager::stat_PaintGradientRect(
		dc,
		&rcItem,
		dc.GetNearestColor( RGB( 255, 0, 0 ) ),
		dc.GetNearestColor( RGB( 0, 0, 255 ) ),
		false
		);
	
	INT nOldBkMode = dc.SetBkMode( TRANSPARENT );
	COLORREF clrOldText = dc.SetTextColor( RGB( 0, 0, 0 ) );
	CFont * pOldFont = dc.SelectObject( &g_PaintManager->m_FontBold );
	
	rcItem.OffsetRect( 2, 1 );
	dc.DrawText(
		sItemText, nItemTextLen, &rcItem, 
		DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS
		);
	clrOldText = dc.SetTextColor( RGB( 255, 255, 255 ) );
	rcItem.OffsetRect( -2, -1 );
	dc.DrawText(
		sItemText, nItemTextLen, &rcItem, 
		DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS
		);
	
	dc.SelectObject( pOldFont );
	dc.SetBkMode( nOldBkMode );
	dc.SetTextColor( clrOldText );

	return !0;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPageButtons::OnExtMenuPrepare(WPARAM wParam, LPARAM lParam)
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
		//pColorPopup->m_clrInitial =	;
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

void CPageButtons::OnSelendokSkin() 
{
	int nCurSel = m_CheckBoxSkin.GetCurSel();
	int nBitmapResource = m_CheckBoxSkin.GetItemData( nCurSel );

	m_chkCheckBox2.m_nBitmapResource 
		= m_chkCheckBox1.m_nBitmapResource 
		= nBitmapResource;

	if( nBitmapResource == IDB_BOX_IMAGES_XP ){
		m_wndRadio1.m_nBitmapResource 
			= m_wndRadio2.m_nBitmapResource 
			= IDB_RADIO_BOX_IMAGES_XP;
	}else if( nBitmapResource == IDB_BOX_IMAGES_XP_CROSS ){
		m_wndRadio1.m_nBitmapResource 
			= m_wndRadio2.m_nBitmapResource 
			= IDB_RADIO_BOX_IMAGES_XP_CROSS;
	}else if( nBitmapResource == IDB_BOX_IMAGES_XP_BLUE ){
		m_wndRadio1.m_nBitmapResource 
			= m_wndRadio2.m_nBitmapResource 
			= IDB_RADIO_BOX_IMAGES_XP_BLUE;
	}else{
		m_wndRadio1.m_nBitmapResource 
			= m_wndRadio2.m_nBitmapResource 
			= 0;
	}
		
	m_chkCheckBox1.Invalidate();
	m_chkCheckBox2.Invalidate();
	m_wndRadio1.Invalidate();
	m_wndRadio2.Invalidate();
}

//////////////////////////////////////////////////////////////////////////

void CPageButtons::OnSelendokTextAlign2() 
{
	int nCurSel = m_TextAlign2.GetCurSel();
	int nStyle = m_TextAlign2.GetItemData( nCurSel );
	m_chkCheckBox1.ModifyStyle( BS_LEFT|BS_CENTER|BS_RIGHT, nStyle );
	m_chkCheckBox2.ModifyStyle( BS_LEFT|BS_CENTER|BS_RIGHT, nStyle );
	m_wndRadio1.ModifyStyle( BS_LEFT|BS_CENTER|BS_RIGHT, nStyle );
	m_wndRadio2.ModifyStyle( BS_LEFT|BS_CENTER|BS_RIGHT, nStyle );
	m_chkCheckBox1.Invalidate();
	m_chkCheckBox2.Invalidate();
	m_wndRadio1.Invalidate();
	m_wndRadio2.Invalidate();
}

//////////////////////////////////////////////////////////////////////////

void CPageButtons::OnSelendokCursor() 
{
	int nCurSel = m_Cursor.GetCurSel();
	int nCursorType = m_Cursor.GetItemData( nCurSel );
	if( nCursorType == 0 )
		nCursorType = -1;
	m_btnPushButton.SetBtnCursor( nCursorType );
}

