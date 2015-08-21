// PagePopupMenus.cpp : implementation file
//

#include "stdafx.h"
#include "profuis_controls.h"
#include "PagePopupMenus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPagePopupMenus dialog


CPagePopupMenus::CPagePopupMenus(CWnd* pParent /*=NULL*/)
	: CPageBase(CPagePopupMenus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPagePopupMenus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPagePopupMenus::DoDataExchange(CDataExchange* pDX)
{
	CPageBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPagePopupMenus)
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_CHECK_MENU_WITH_SHADOWS, m_chkMenuWithShadows);
	DDX_Control(pDX, IDC_CHECK_MENU_ANIMATION, m_chkMenuAnimation);
	DDX_Control(pDX, IDC_STATIC_MENU_ANIMATION, m_StaticMenuAnimation);
	DDX_Control(pDX, IDC_MENU_ANIMATION, m_MenuAnimation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPagePopupMenus, CPageBase)
	//{{AFX_MSG_MAP(CPagePopupMenus)
	ON_CBN_SELENDOK(IDC_MENU_ANIMATION, OnSelendokMenuAnimation)
	ON_BN_CLICKED(IDC_CHECK_MENU_ANIMATION, OnCheckMenuAnimation)
	ON_BN_CLICKED(IDC_CHECK_MENU_WITH_SHADOWS, OnCheckMenuWithShadows)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(CExtPopupMenuWnd::g_nMsgPopupDrawItem,OnDrawPopupMenuItem)
	ON_REGISTERED_MESSAGE(CExtPopupMenuWnd::g_nMsgPopupDrawLeftArea,OnDrawPopupLeftArea)
#if (!defined __EXT_MFC_NO_DATE_PICKER)
	ON_REGISTERED_MESSAGE(CExtDatePickerWnd::g_nMsgSelectionNotification, OnMsgSelectionNotification)
#endif // #if (!defined __EXT_MFC_NO_DATE_PICKER)	
	
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
// CPagePopupMenus message handlers

BOOL CPagePopupMenus::OnInitDialog() 
{
	CPageBase::OnInitDialog();
	
	AddAnchor( IDC_STATIC1, CSize(50,50), CSize(50,50) );

	m_StaticMenuAnimation.SetStyle( CExtGroupBox::STYLE_FLAT );
	
	m_chkMenuWithShadows.SetCheck( BST_CHECKED );
	OnCheckMenuWithShadows();
	m_chkMenuAnimation.SetCheck( BST_CHECKED );
	OnCheckMenuAnimation();

	int nIndex = -1, nInitSel = -1;
	nIndex = m_MenuAnimation.AddString( _T("(none)") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_NONE );

	nIndex = m_MenuAnimation.AddString( _T("Random select") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_RANDOM);

	nIndex = m_MenuAnimation.AddString( _T("Roll") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_ROLL);

	nIndex = m_MenuAnimation.AddString( _T("Slide") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_SLIDE);

	nInitSel = nIndex = m_MenuAnimation.AddString( _T("Fade") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_FADE);

	nIndex = m_MenuAnimation.AddString( _T("Roll and stretch") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_ROLL_AND_STRETCH);

	nIndex = m_MenuAnimation.AddString( _T("Slide and stretch") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_SLIDE_AND_STRETCH);

	nIndex = m_MenuAnimation.AddString( _T("Noise") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_NOISE);

	nIndex = m_MenuAnimation.AddString( _T("Boxes") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_BOXES);

	nIndex = m_MenuAnimation.AddString( _T("Circles") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_CIRCLES);

	nIndex = m_MenuAnimation.AddString( _T("Holes") );
	m_MenuAnimation.SetItemData( nIndex, CExtPopupMenuWnd::__AT_HOLES);

	m_MenuAnimation.SetCurSel( nInitSel );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPagePopupMenus::OnSelendokMenuAnimation() 
{
	int nCurSel = m_MenuAnimation.GetCurSel();
	CExtPopupMenuWnd::g_DefAnimationType =
		(CExtPopupMenuWnd::e_animation_type_t)m_MenuAnimation.GetItemData( nCurSel );
}

void CPagePopupMenus::OnCheckMenuAnimation() 
{
	CExtPopupMenuWnd::g_bMenuExpandAnimation =
		m_chkMenuAnimation.GetCheck() ?
		true : false;
}

void CPagePopupMenus::OnCheckMenuWithShadows() 
{
	CExtPopupMenuWnd::g_bMenuWithShadows =
		m_chkMenuWithShadows.GetCheck() ?
		true : false;
}

void CPagePopupMenus::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	pWnd;
	
	CMenu _menu;
	if( _menu.GetSafeHmenu() == NULL ){
		if( !_menu.LoadMenu(IDR_POPUP_MENU) ){
			ASSERT( FALSE );
			return;
		}
	}
	CExtPopupMenuWnd * pPopup = new CExtPopupMenuWnd;
	pPopup->SetLeftAreaWidth( 30 );
	pPopup->UpdateFromMenu(
		GetSafeHwnd(),
		&_menu
		);
	
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
		CExtPopupDatePickerMenuWnd * pDatePickerPopup = 
			new CExtPopupDatePickerMenuWnd(
			0L,
			CSize(1,1),
			WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,
			__EDPWS_DEFAULT|__EDPWS_MULTIPLY_SELECTION
			);

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
	
	if( !pPopup->TrackPopupMenu(
		TPMX_OWNERDRAW_FIXED,
		point.x,
		point.y
		)
		)
		delete pPopup;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPagePopupMenus::OnDrawPopupLeftArea(WPARAM wParam, LPARAM lParam)
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

LRESULT CPagePopupMenus::OnDrawPopupMenuItem(WPARAM wParam, LPARAM lParam)
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
		DT_VCENTER | DT_END_ELLIPSIS | DT_SINGLELINE | DT_CENTER 
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

LRESULT CPagePopupMenus::OnMsgSelectionNotification( WPARAM wParam, LPARAM lParam )
{
	wParam;
	lParam;
#if (!defined __EXT_MFC_NO_DATE_PICKER)
	const CExtDatePickerWnd::SELECTION_NOTIFICATION * pSN =
		CExtDatePickerWnd::SELECTION_NOTIFICATION::FromWPARAM( wParam );

	if( !pSN->m_bFinalSelectionChanging )
		return 0L;
	
	CString	strMsg, strMsgAll,
		strDtBegin( pSN->m_dtBegin.Format() ),
		strDtEnd( pSN->m_dtEnd.Format() );
	strMsg.Format(
		_T("The date selected: %s"),
		strDtBegin
		);
	if( pSN->m_dtBegin != pSN->m_dtEnd ){
		strMsg += _T(" - ");
		strMsg += strDtEnd;
	}

	strMsg += _T("\r\n");
	TRACE( strMsg );
#endif // #if (!defined __EXT_MFC_NO_DATE_PICKER)	
	
	return 0L;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CPagePopupMenus::OnColorChangedFinally(WPARAM wParam, LPARAM lParam)
{
	switch( lParam )
	{
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

LRESULT CPagePopupMenus::OnColorSelectCustom(WPARAM wParam, LPARAM lParam)
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