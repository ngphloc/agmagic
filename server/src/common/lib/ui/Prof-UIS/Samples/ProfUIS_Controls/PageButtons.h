#if !defined(AFX_PAGEBUTTONS_H__D5F47AD0_2BD7_4BFE_91DD_AD9337222252__INCLUDED_)
#define AFX_PAGEBUTTONS_H__D5F47AD0_2BD7_4BFE_91DD_AD9337222252__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageButtons.h : header file
//
#include "PageBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPageButtons dialog

/////////////////////////////////////////////////////////////////////////////
// CHighImageList
/////////////////////////////////////////////////////////////////////////////

class CHighImageList : public CImageList
{
public:
	
	CHighImageList()
	{
	}
	
	CHighImageList(
		UINT nResourceID,
		COLORREF clrTransparencyMask = RGB(255,0,255),
		int nButtonWidth = 16,
		HINSTANCE hInstResource = AfxGetInstanceHandle()
		)
	{
		VERIFY(
			LoadHighImgLst(
			nResourceID,
			clrTransparencyMask,
			nButtonWidth,
			hInstResource
			)
			);
	}
	
	BOOL LoadHighImgLst(
		UINT nResourceID,
		COLORREF clrTransparencyMask = RGB(255,0,255),
		int nButtonWidth = 16,
		HINSTANCE hInstResource = AfxGetInstanceHandle()
		)
	{
		if( hInstResource == NULL )
		{
			hInstResource = ::AfxGetInstanceHandle();
			if( hInstResource == NULL )
			{
				ASSERT( FALSE );
				return FALSE;
			}
		}
		CBitmap objBitmap;
		if( !objBitmap.Attach(
			LoadImage(
			hInstResource,
			MAKEINTRESOURCE( nResourceID ),
			IMAGE_BITMAP,
			0,
			0,
			LR_DEFAULTSIZE|LR_CREATEDIBSECTION
			)
			)
			)
		{
			ASSERT( FALSE );
			return FALSE;
		}
		BITMAP infoBitmap;
		if( !objBitmap.GetBitmap( &infoBitmap ) )
		{
			ASSERT( FALSE );
			return FALSE;
		}
		CSize sizeBitmap(
			infoBitmap.bmWidth,
			infoBitmap.bmHeight
			); 
		int nCountOfButtons = sizeBitmap.cx / nButtonWidth;
		if( !Create(
			nButtonWidth,
			sizeBitmap.cy,
			ILC_COLOR24|ILC_MASK,
			nCountOfButtons,
			0
			)
			)
		{
			ASSERT( FALSE );
			return FALSE;
		}
		if( Add( &objBitmap, clrTransparencyMask ) == -1 )
		{
			ASSERT( FALSE );
			return FALSE;
		}
		return TRUE;
	}
};// class CHighImageList

//////////////////////////////////////////////////////////////////////////
// class CPageButtons
//////////////////////////////////////////////////////////////////////////

class CPageButtons : public CPageBase
{
// Construction
public:
	CPageButtons(CWnd* pParent = NULL);   // standard constructor

	/////////////////////////////////////////////////////////////////////////////
	// CSkinCheckBox window
	/////////////////////////////////////////////////////////////////////////////
	
	class CSkinCheckBox : public CExtCheckBox
	{
	public:
		CSkinCheckBox()
			: CExtCheckBox()
			, m_nBitmapResource( 0 )
		{
		}
		int m_nBitmapResource;
		
	protected:
		virtual bool OnPaintBox(
			CDC & dc,
			CRect & rcBox,
			eCheckBoxState eState
			)
		{
			if( m_nBitmapResource == 0 )
				return CExtCheckBox::OnPaintBox(dc,rcBox,eState);
			
			CHighImageList il(m_nBitmapResource, RGB(255,0,255), __EXT_DEFAULT_CHECK_BOX_SIZE);
			bool bRet = il.Draw(
				&dc, 
				eState, 
				rcBox.TopLeft(), 
				ILD_NORMAL
				) == TRUE;
			return bRet;
		}
	};// class CSkinCheckBox
	
	/////////////////////////////////////////////////////////////////////////////
	// CSkinRadioButton window
	/////////////////////////////////////////////////////////////////////////////
	
	class CSkinRadioButton : public CExtRadioButton
	{
	public:
		CSkinRadioButton()
			: CExtRadioButton()
			, m_nBitmapResource( 0 )
		{
		}
		int m_nBitmapResource;
		
	protected:
		virtual bool OnPaintBox(
			CDC & dc,
			CRect & rcBox,
			eRadioBoxState eState
			)
		{
			if( m_nBitmapResource == 0 )
				return CExtRadioButton::OnPaintBox(dc,rcBox,eState);
			
			CHighImageList il(m_nBitmapResource, RGB(255,0,255), __EXT_DEFAULT_RADIO_BOX_SIZE);
			bool bRet = il.Draw(
				&dc, 
				eState, 
				rcBox.TopLeft(), 
				ILD_NORMAL
				) == TRUE;
			return bRet;
		}
	};// class CSkinRadioButton
	
// Dialog Data
	//{{AFX_DATA(CPageButtons)
	enum { IDD = IDD_PAGE_BUTTONS };
	CSkinRadioButton	m_wndRadio1;
	CSkinRadioButton m_wndRadio2;
	CSkinCheckBox	m_chkCheckBox2;
	CSkinCheckBox	m_chkCheckBox1;
	CExtButton		m_btnWithMenu;
	CExtColorButton	m_btnColor2;
	CExtColorButton	m_btnColor1;
	CExtCheckBox	m_chkCheckBoxShowFocusRect;
	CExtEdit		m_Tooltip;
	CExtComboBox	m_TextAlign1;
	CExtComboBox	m_TextAlign2;
	CExtLabel		m_StaticTooltip;
	CExtLabel		m_StaticTextAlign1;
	CExtLabel		m_StaticTextAlign2;
	CExtLabel		m_StaticSkin;
	CExtGroupBox	m_StaticPushButton;
	CExtGroupBox	m_StaticCheckBox; 
	CExtLabel		m_StaticCursor;
	CExtComboBox	m_CheckBoxSkin;
	CExtButton		m_btnPushLikeButton;
	CExtButton		m_btnPushButton;
	CExtComboBox	m_Cursor;
	CExtCheckBox	m_chkTriState;
	CExtCheckBox	m_chkButtonShowFocusRect;
	CExtCheckBox	m_chkButtonEnable;
	CExtCheckBox	m_chkCheckBoxEnable;
	CExtCheckBox	m_chkLeftText;
	CExtCheckBox	m_chkSeparatedButtons;
	CExtCheckBox	m_chkFlat;
	CExtCheckBox	m_chkBorders;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageButtons)
public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool m_bInitComplete:1;
	
	// Generated message map functions
	//{{AFX_MSG(CPageButtons)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokSkin();
	afx_msg void OnSelendokTextAlign2();
	afx_msg void OnSelendokCursor();
	//}}AFX_MSG
	afx_msg LRESULT OnExtMenuPrepare(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorSelectCustom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorChangedFinally(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawPopupMenuItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawPopupLeftArea(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEBUTTONS_H__D5F47AD0_2BD7_4BFE_91DD_AD9337222252__INCLUDED_)
