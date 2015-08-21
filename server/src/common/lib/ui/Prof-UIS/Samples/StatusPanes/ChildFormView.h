#if !defined(AFX_CHILDFORMVIEW_H__5A1BD4EF_2576_4480_BC1A_54B9357C8DC8__INCLUDED_)
#define AFX_CHILDFORMVIEW_H__5A1BD4EF_2576_4480_BC1A_54B9357C8DC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildFormView.h : header file
//

#include "ExtLabel.h"

class CMainFrame;

/////////////////////////////////////////////////////////////////////////////
// CChildFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CChildFormView
	: public CExtWS < CExtAFV < CFormView >  >
{
protected:
	CChildFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChildFormView)

	friend class CMainFrame;
	
	CMainFrame *m_pMainFrame;

// Form Data
public:
	//{{AFX_DATA(CChildFormView)
	enum { IDD = IDD_DIALOG_CHILD_VIEW };
	CExtRadioButton m_wndRadioText;
	CExtRadioButton	m_wndRadioStatic;
	CExtRadioButton	m_wndRadioSlider;
	CExtRadioButton	m_wndRadioProgress;
	CExtRadioButton	m_wndRadioEdit;
	CExtRadioButton	m_wndRadioButton;
	CExtRadioButton	m_wndRadioAnimCtrl;
	CExtLabel		m_wndStatic3;
	CExtLabel		m_wndStatic2;
	CExtLabel		m_wndStatic1;
	CExtButton		m_btnDisablePane;
	CSpinButtonCtrl	m_SpinPosition;
	CExtButton		m_btnRemovePane;
	CExtButton		m_btnAddPane;
	CExtCheckBox	m_chkHideTextOnDisabledPanes;
	CExtCheckBox	m_chkOuterRectInFirstBand;
	CExtCheckBox	m_chkDrawPaneSeparators;
	int		m_nPosition;
	//}}AFX_DATA

// Attributes
public:

	class CExtStatusBarAnimateCtrl : public CAnimateCtrl{
		virtual LRESULT WindowProc(    
			UINT uMsg,
			WPARAM wParam,
			LPARAM lParam
			)
		{
	if( uMsg == WM_ERASEBKGND )
				return (!0);
			if( uMsg == WM_PAINT )
			{
				CRect rcClient;
				GetClientRect( &rcClient );
				CPaintDC dcPaint( this );
				CExtMemoryDC dc( &dcPaint, &rcClient );
				if( g_PaintManager->GetCb2DbTransparentMode(this) )
				{
					CExtPaintManager::stat_ExcludeChildAreas(
						dc,
						GetSafeHwnd(),
						CExtPaintManager::stat_DefExcludeChildAreaCallback
						);
					g_PaintManager->PaintDockerBkgnd( dc, this );
				} // if( g_PaintManager->GetCb2DbTransparentMode(this) )
				else
					dc.FillSolidRect( &rcClient, g_PaintManager->GetColor(CExtPaintManager::CLR_3DFACE_OUT) );
				DefWindowProc( WM_PAINT, WPARAM(dc.GetSafeHdc()), 0L );
				g_PaintManager->OnPaintSessionComplete( this );
				return 0;
			}
			LRESULT lResult = CAnimateCtrl::WindowProc(uMsg, wParam, lParam);
			return lResult;
		}
		
		virtual void PostNcDestroy(){
			delete this;
		}
	};
	 
	class CExtStatusBarEdit : public CEdit{
		virtual void PostNcDestroy(){
			delete this;
		}
	};

	class CExtStatusBarSliderCtrl : public CSliderCtrl{
		virtual void PostNcDestroy(){
			delete this;
		}
	};

	class CExtStatusBarButton : public CExtButton{
		virtual void PostNcDestroy(){
			delete this;
		}
	};

	class CExtStatusBarLabel : public CExtLabel
	{
		virtual void OnDrawLabelText(
			CDC & dc,
			const RECT & rcText,
			__EXT_MFC_SAFE_LPCTSTR strText,
			DWORD dwDrawTextFlags,
			bool bEnabled
			)
		{
			bEnabled;
			INT nOldBkMode = dc.SetBkMode( TRANSPARENT );
			LOGFONT lf;
			memset( &lf, 0, sizeof(LOGFONT) );
			lf.lfQuality = PROOF_QUALITY;
			lf.lfHeight = 16;
			lf.lfWeight = 600;
			lstrcpy( lf.lfFaceName, _T("Arial") );
			CFont f;
			f.CreateFontIndirect( &lf );
			CFont * pOldFont = dc.SelectObject( &f );

			CRect rc( rcText );
			COLORREF clrOldText =
				dc.SetTextColor( g_PaintManager->GetColor( COLOR_3DHILIGHT) );
			rc.top -= 3;
			dc.DrawText( strText, rc, dwDrawTextFlags );
			
			rc = rcText;
			rc.top -= 1;
			rc.left += 2;
			dc.SetTextColor( GetSysColor( COLOR_3DSHADOW ) );
			dc.DrawText( strText, rc, dwDrawTextFlags );
			
			rc = rcText;
			rc.left += 1;
			rc.top -= 2;
			dc.SetTextColor( RGB(0,0,255) );
			dc.DrawText( strText, rc, dwDrawTextFlags );
			
			dc.SelectObject( pOldFont );
			f.DeleteObject();
			dc.SetBkMode( nOldBkMode );
			dc.SetTextColor( clrOldText );
		}
		virtual void PostNcDestroy()
		{
			delete this;
		}
	};

	class CExtStatusBarProgressCtrl : public CProgressCtrl
	{
		virtual LRESULT WindowProc(    
			UINT uMsg,
			WPARAM wParam,
			LPARAM lParam
			)
		{
			if( uMsg == WM_ERASEBKGND )
				return (!0);
			if( uMsg == WM_PAINT )
			{
				CRect rcClient;
				GetClientRect( &rcClient );
				CPaintDC dcPaint( this );
				CExtMemoryDC dc( &dcPaint, &rcClient );
				if( g_PaintManager->GetCb2DbTransparentMode(this) )
				{
					CExtPaintManager::stat_ExcludeChildAreas(
						dc,
						GetSafeHwnd(),
						CExtPaintManager::stat_DefExcludeChildAreaCallback
						);
					g_PaintManager->PaintDockerBkgnd( dc, this );
				} // if( g_PaintManager->GetCb2DbTransparentMode(this) )
				else
					dc.FillSolidRect( &rcClient, g_PaintManager->GetColor( CExtPaintManager::CLR_3DFACE_OUT) );
				DefWindowProc( WM_PAINT, WPARAM(dc.GetSafeHdc()), 0L );
				g_PaintManager->OnPaintSessionComplete( this );
				return 0;
			}
			if( uMsg == WM_TIMER ){
				StepIt();
			}
			if( uMsg == WM_DESTROY ){
				KillTimer(0);
			}
			LRESULT lResult = CProgressCtrl::WindowProc(uMsg, wParam, lParam);
			return lResult;
		}
		
		virtual void PostNcDestroy(){
			delete this;
		}
	};

	CExtStatusBarEdit *m_pWndEdit;
	CExtStatusBarSliderCtrl *m_pWndSliderCtrl;
	CExtStatusBarButton *m_pWndButton;
	CExtStatusBarProgressCtrl *m_pWndProgressCtrl;
	CExtStatusBarAnimateCtrl *m_pWndAnimateCtrl;
	CExtStatusBarLabel *m_pWndLabel;

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFormView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChildFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChildFormView)
	afx_msg void OnDrawPaneSeparators();
	afx_msg void OnOuterRectInFirstBand();
	afx_msg void OnHideTextOnDisabledPanes();
	afx_msg void OnAddPane();
	afx_msg void OnRemovePane();
	afx_msg void OnDisablePane();
	afx_msg void OnStatusBarButton();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CheckControls();
	bool m_bInitComplete;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFORMVIEW_H__5A1BD4EF_2576_4480_BC1A_54B9357C8DC8__INCLUDED_)
