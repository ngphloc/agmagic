// ChildFormView.cpp : implementation file
//

#include "stdafx.h"
#include "AviFrames.h"
#include "ChildFormView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GetMainFrame() (DYNAMIC_DOWNCAST(CMainFrame,AfxGetMainWnd())) 

/////////////////////////////////////////////////////////////////////////////
// CAviView

IMPLEMENT_DYNAMIC(CAviView, CExtScrollWnd)

CAviView::CAviView()
{
	//{{AFX_DATA_INIT(CAviView)
	//}}AFX_DATA_INIT
	m_bInitComplete = false;
}

CAviView::~CAviView()
{
}

BEGIN_MESSAGE_MAP(CAviView, CExtScrollWnd)
	//{{AFX_MSG_MAP(CAviView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

void CAviView::PostNcDestroy() 
{
	CExtScrollWnd::PostNcDestroy();
	delete this;
}

/////////////////////////////////////////////////////////////////////////////
// CAviView diagnostics

#ifdef _DEBUG
void CAviView::AssertValid() const
{
	CExtScrollWnd::AssertValid();
}

void CAviView::Dump(CDumpContext& dc) const
{
	CExtScrollWnd::Dump(dc);
}
#endif //_DEBUG

bool CAviView::Create(
			CWnd * pWndParent,
			UINT nDlgCtrlID, // = AFX_IDW_PANE_FIRST
			CRect rc, // = CRect( 0,0,0,0 )
			DWORD dwStyle, // = WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_HSCROLL|WS_VSCROLL
			DWORD dwStyleEx // = 0L
			)
{
//	dwStyleEx |= WS_EX_CLIENTEDGE;

LPCTSTR strClass =
		::AfxRegisterWndClass(
			CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
			::LoadCursor(NULL, IDC_ARROW),
			NULL,
			NULL
			);
	if( strClass == NULL )
	{
		ASSERT( FALSE );
		return false;
	}
	if( ! CreateEx(
		dwStyleEx,
		strClass,
		_T(""),
		dwStyle,
		rc.left, rc.top, rc.Width(), rc.Height(),
		pWndParent->GetSafeHwnd(),
		NULL,
		NULL
		)
		)
	{
		ASSERT( FALSE );
		return false;
	}
	SetDlgCtrlID( nDlgCtrlID );
	return true;
}

//////////////////////////////////////////////////////////////////////////

int CAviView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if( CExtScrollWnd::OnCreate(lpCreateStruct) == -1 )
		return -1;
	
	m_bInitComplete = true;
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CAviView message handlers
//////////////////////////////////////////////////////////////////////////

CSize CAviView::OnSwGetTotalSize() const
{
	if( GetMainFrame()->m_pAviPlayer != NULL )
		return GetMainFrame()->m_pAviPlayer->GetAviRenderSize();
	return CSize(0,0);
}

//////////////////////////////////////////////////////////////////////////

bool CAviView::OnSwDoScrollBy(
					CSize sizeScroll,
					bool bDoScroll // = true
					)
{
	CExtScrollWnd::OnSwDoScrollBy(sizeScroll,bDoScroll);
	
	if(!GetMainFrame()->m_pAviPlayer)
		return true;
	
	LONG lPosHorz = ScrollPos32Get( SB_HORZ );
	LONG lPosVert = ScrollPos32Get( SB_VERT );
	
	CSize szAvi = GetMainFrame()->m_pAviPlayer->GetAviRenderSize();
	GetMainFrame()->m_pAviPlayer->SetPlayerWindowPos(
		-lPosHorz,
		-lPosVert,
		szAvi.cx,
		szAvi.cy
		);	

	return true;
}

//////////////////////////////////////////////////////////////////////////

CRect CAviView::OnSwRecalcLayout(
					   bool bDoLayout,
					   LPCRECT pRectClientSrc )
{
CRect rc = CExtScrollWnd::OnSwRecalcLayout( bDoLayout, pRectClientSrc ); 
	if(!bDoLayout)
		return rc;
	
	if(!GetMainFrame()->m_pAviPlayer)
		return rc;
	
	LONG lPosHorz = ScrollPos32Get( SB_HORZ );
	LONG lPosVert = ScrollPos32Get( SB_VERT );
	
	CSize szAvi = GetMainFrame()->m_pAviPlayer->GetAviRenderSize();
	GetMainFrame()->m_pAviPlayer->SetPlayerWindowPos(
		-lPosHorz,
		-lPosVert,
		szAvi.cx,
		szAvi.cy
		);	
	

	return rc;
}

