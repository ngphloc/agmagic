// ResizablePropertySheet.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ResizablePropertySheet.h"
#include "MyResizablePage1.h"
#include "MyResizablePage2.h"
#include "MyResizablePage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyResizablePropertySheet

class CMyResizablePropertySheet : public CExtResizablePropertySheet
{
public:
	CMyResizablePropertySheet(
		UINT nIDCaption,
		CWnd *pParentWnd = NULL,
		UINT iSelectPage = 0
		)
		: CExtResizablePropertySheet(
			nIDCaption,
			pParentWnd,
			iSelectPage
			)
	{
	}
	CMyResizablePropertySheet(
		LPCTSTR pszCaption,
		CWnd *pParentWnd = NULL,
		UINT iSelectPage = 0
		)
		: CExtResizablePropertySheet(
			pszCaption,
			pParentWnd,
			iSelectPage
			)
	{
	}
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
#if _MFC_VER >= 0x700
		if( (m_psh.dwFlags&PSH_WIZARD97) != 0 )
		{
			if( message == WM_PAINT || message == WM_ERASEBKGND )
			{
				LRESULT lResult = CPropertySheet::WindowProc(message,wParam,lParam);
				if(		message == WM_PAINT
					&&	m_bShowResizingGripper
					&&	(!IsZoomed())
					)
				{
					CClientDC dc( this );
					CFont * pOldFont =
						dc.SelectObject(
							&g_PaintManager->m_FontMarlett
							);
					ASSERT( pOldFont != NULL );
					COLORREF clrOld = dc.SetTextColor(
						g_PaintManager->GetColor(
							CExtPaintManager::CLR_TEXT_OUT
							)
						);
					INT nOldBkMode = dc.SetBkMode(TRANSPARENT);
					dc.DrawText(
						_T("o"),
						1,
						m_rcResizingGripper,
						DT_SINGLELINE|DT_RIGHT|DT_BOTTOM
						);
					dc.SetBkMode(nOldBkMode);
					dc.SetTextColor(clrOld);
					dc.SelectObject(pOldFont);
				}
				return lResult;
			}
		}
#endif // #if _MFC_VER >= 0x700

		return CExtResizablePropertySheet::WindowProc(message,wParam,lParam);
	}
}; // class CMyResizablePropertySheet

/////////////////////////////////////////////////////////////////////////////
// CMyApp

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	//{{AFX_MSG_MAP(CMyApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyApp construction

CMyApp::CMyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyApp object

CMyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyApp initialization

BOOL CMyApp::InitInstance()
{
	InitCommonControls();

	SetRegistryKey(
		_T("Foss") // your company name
		);

	// comment/uncomment one of these lines to set different style
	g_PaintManager.InstallPaintManager( new CExtPaintManagerOffice2003 );
	//g_PaintManager.InstallPaintManager( new CExtPaintManager );

CMyResizablePropertySheet
		_PropSheet(
			AFX_IDS_APP_TITLE // your software name
			);

	// add pages
CMyResizablePage1 _page1;
	_PropSheet.AddPage( &_page1 );
CMyResizablePage2 _page2;
	_PropSheet.AddPage( &_page2 );
CMyResizablePage3 _page3;
	_PropSheet.AddPage( &_page3 );

	// enable persistent window position
	_PropSheet.EnableSaveRestore(
		_T( "Dialog Settings" ),
		_T( "Main Property Sheet" )
		);

	// comment this line and next lines to set simple tabbed mode (non-wizard)
	_PropSheet.SetWizardMode();

/*
	// these lines are available with MFC7 only
	// uncomment them to set new wizard mode
#if _MFC_VER >= 0x700
	_PropSheet.m_psh.dwSize = sizeof(_PropSheet.m_psh);
	_PropSheet.m_psh.dwFlags |=
		PSH_WIZARD97|PSH_WATERMARK|PSH_WIZARDHASFINISH;
	_PropSheet.m_psh.pszbmWatermark = MAKEINTRESOURCE(IDB_BITMAP_WATERMARK);
	_PropSheet.m_psh.hInstance = ::AfxGetInstanceHandle();
	_page1.m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	_page1.m_psp.pszHeaderTitle = _T("Title of page 1");
	_page1.m_psp.pszHeaderSubTitle = _T("Subtitle of page 1");
	_page2.m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	_page2.m_psp.pszHeaderTitle = _T("Title of page 2");
	_page2.m_psp.pszHeaderSubTitle = _T("Subtitle of page 2");
	_page3.m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	_page3.m_psp.pszHeaderTitle = _T("Title of page 3");
	_page3.m_psp.pszHeaderSubTitle = _T("Subtitle of page 3");
#endif // #if _MFC_VER >= 0x700
*/

	// run it
	if( _PropSheet.DoModal() == IDOK )
	{
		//::AfxMessageBox( _T("<OK> pressed") );
	}
	else
	{
		//::AfxMessageBox( _T("<Cancel> pressed") );
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
