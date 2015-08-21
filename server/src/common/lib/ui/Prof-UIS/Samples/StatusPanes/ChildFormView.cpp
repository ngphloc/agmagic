// ChildFormView.cpp : implementation file
//

#include "stdafx.h"
#include "StatusPanes.h"
#include "ChildFormView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFormView

IMPLEMENT_DYNCREATE(CChildFormView, CFormView)

CChildFormView::CChildFormView()
: CExtWS < CExtAFV < CFormView > > ( CChildFormView::IDD, ((CWnd *)NULL) )
,m_pWndEdit(NULL)
,m_pWndSliderCtrl(NULL)
,m_pWndButton(NULL)
,m_pWndProgressCtrl(NULL)
,m_pWndAnimateCtrl(NULL)
{
	//{{AFX_DATA_INIT(CChildFormView)
	m_nPosition = 1;
	//}}AFX_DATA_INIT
	m_bInitComplete = false;
	m_pMainFrame = DYNAMIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
}

CChildFormView::~CChildFormView()
{
}

void CChildFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChildFormView)
	DDX_Control(pDX, IDC_RADIO_TYPE_TEXT, m_wndRadioText);
	DDX_Control(pDX, IDC_RADIO_TYPE_STATIC, m_wndRadioStatic);
	DDX_Control(pDX, IDC_RADIO_TYPE_SLIDER, m_wndRadioSlider);
	DDX_Control(pDX, IDC_RADIO_TYPE_PROGRESS, m_wndRadioProgress);
	DDX_Control(pDX, IDC_RADIO_TYPE_EDIT, m_wndRadioEdit);
	DDX_Control(pDX, IDC_RADIO_TYPE_BUTTON, m_wndRadioButton);
	DDX_Control(pDX, IDC_RADIO_TYPE_ANIM_CTRL, m_wndRadioAnimCtrl);
	DDX_Control(pDX, IDC_STATIC3, m_wndStatic3);
	DDX_Control(pDX, IDC_STATIC2, m_wndStatic2);
	DDX_Control(pDX, IDC_STATIC1, m_wndStatic1);
	DDX_Control(pDX, IDC_DISABLE_PANE, m_btnDisablePane);
	DDX_Control(pDX, IDC_SPIN_POSITION, m_SpinPosition);
	DDX_Control(pDX, IDC_REMOVE_PANE, m_btnRemovePane);
	DDX_Control(pDX, IDC_ADD_PANE, m_btnAddPane);
	DDX_Control(pDX, IDC_HIDE_TEXT_ON_DISABLED_PANES, m_chkHideTextOnDisabledPanes);
	DDX_Control(pDX, IDC_OUTER_RECT_IN_FIRST_BAND, m_chkOuterRectInFirstBand);
	DDX_Control(pDX, IDC_DRAW_PANE_SEPARATORS, m_chkDrawPaneSeparators);
	DDX_Text(pDX, IDC_POSITION, m_nPosition);
	DDV_MinMaxInt(pDX, m_nPosition, 0, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChildFormView, CFormView)
	//{{AFX_MSG_MAP(CChildFormView)
	ON_BN_CLICKED(IDC_DRAW_PANE_SEPARATORS, OnDrawPaneSeparators)
	ON_BN_CLICKED(IDC_OUTER_RECT_IN_FIRST_BAND, OnOuterRectInFirstBand)
	ON_BN_CLICKED(IDC_HIDE_TEXT_ON_DISABLED_PANES, OnHideTextOnDisabledPanes)
	ON_BN_CLICKED(IDC_ADD_PANE, OnAddPane)
	ON_BN_CLICKED(IDC_REMOVE_PANE, OnRemovePane)
	ON_BN_CLICKED(IDC_DISABLE_PANE, OnDisablePane)
	ON_BN_CLICKED(IDC_STATUS_BAR_BUTTON, OnStatusBarButton)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFormView diagnostics

#ifdef _DEBUG
void CChildFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChildFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFormView message handlers

BOOL CChildFormView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CFormView::PreCreateWindow(cs))
		return FALSE;
	
	cs.dwExStyle &= ~(WS_EX_CLIENTEDGE|WS_EX_STATICEDGE);
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

void CChildFormView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	ShowSizeGrip(FALSE);
	m_SpinPosition.SetRange(0,20);
	m_chkHideTextOnDisabledPanes.SetCheck(0);
	OnHideTextOnDisabledPanes();
	m_bInitComplete = true;

	m_wndRadioText.SetCheck( TRUE );

	CheckControls();
}

//////////////////////////////////////////////////////////////////////////

void CChildFormView::OnDrawPaneSeparators() 
{
	if( m_chkDrawPaneSeparators.GetCheck() == 1 ){
		m_pMainFrame->m_wndStatusBar.DrawPaneSeparatorsSet(true);
		m_chkOuterRectInFirstBand.EnableWindow(0);
	}
	else{
		m_pMainFrame->m_wndStatusBar.DrawPaneSeparatorsSet(false);
		m_chkOuterRectInFirstBand.EnableWindow(1);
	}

	if( m_pWndButton && ::IsWindow(m_pWndButton->m_hWnd)){
		if(m_chkDrawPaneSeparators.GetCheck() == 1){
			m_pWndButton->SetDrawBorder(1);
		}
		else{
			m_pWndButton->SetDrawBorder(0);
		}
	}
	
}

void CChildFormView::OnOuterRectInFirstBand() 
{
	m_pMainFrame->m_wndStatusBar.OuterRectInFirstBandSet( 
		m_chkOuterRectInFirstBand.GetCheck() == 1 
		);
}

void CChildFormView::OnHideTextOnDisabledPanes() 
{
	m_pMainFrame->m_wndStatusBar.HideTextOnDisabledPanesSet( 
		m_chkHideTextOnDisabledPanes.GetCheck() == 1 
		);
}

//////////////////////////////////////////////////////////////////////////

void CChildFormView::OnAddPane() 
{
	UpdateData();
	
	if( m_nPosition < 0 || m_nPosition > 20 )
		return;
	
	if( m_wndRadioText.GetCheck() ) // text
	{
		bool bRet = m_pMainFrame->m_wndStatusBar.AddPane(IDS_PANE_TEXT,m_nPosition);
		if(!bRet){
			AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
			return;
		}
	}
	
	if( m_wndRadioEdit.GetCheck() ) // edit
	{
		m_pWndEdit = new CExtStatusBarEdit;
		if (!m_pWndEdit->Create(
			WS_CHILD|WS_VISIBLE|WS_TABSTOP, 
			CRect(0,0,0,0), 
			&m_pMainFrame->m_wndStatusBar, 
			0))
		{
			TRACE(_T("Failed to create edit control.\n"));
			return;
		}
		
		m_pWndEdit->SetFont(
			CFont::FromHandle(
			(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
			)
			);
		
		m_pWndEdit->SetWindowText(_T("Type text here..."));
		
		bool bRet = m_pMainFrame->m_wndStatusBar.AddPane(IDS_PANE_EDIT,m_nPosition);
		if(!bRet){
			AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
			return;
		}
		
		int nIndex = m_pMainFrame->m_wndStatusBar.CommandToIndex(IDS_PANE_EDIT);
		if (nIndex == -1)
			return;
		
		m_pMainFrame->m_wndStatusBar.SetPaneWidth(nIndex, 100);
		m_pMainFrame->m_wndStatusBar.SetPaneControl(m_pWndEdit, IDS_PANE_EDIT, true);
		return;
	}
	
	if( m_wndRadioProgress.GetCheck() ) // progress ctrl
	{
		m_pWndProgressCtrl = new CExtStatusBarProgressCtrl;
		if (!m_pWndProgressCtrl->Create(
			WS_CHILD|WS_VISIBLE|WS_TABSTOP, //|PBS_SMOOTH
			CRect(0,0,0,0), 
			&m_pMainFrame->m_wndStatusBar, 
			0))
		{
			TRACE(_T("Failed to create progress control.\n"));
			return;
		}
		
		m_pWndProgressCtrl->ModifyStyleEx(WS_EX_STATICEDGE,0,SWP_FRAMECHANGED);
		
		m_pWndProgressCtrl->SetRange(0,300);
		m_pWndProgressCtrl->SetPos(0);
		m_pWndProgressCtrl->SetStep(1);
		
		bool bRet = m_pMainFrame->m_wndStatusBar.AddPane(IDS_PANE_PROGRESS,m_nPosition);
		if(!bRet){
			AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
			return;
		}
		
		int nIndex = m_pMainFrame->m_wndStatusBar.CommandToIndex(IDS_PANE_PROGRESS);
		if (nIndex == -1)
			return;
		
		m_pMainFrame->m_wndStatusBar.SetPaneWidth(nIndex, 100);
		m_pMainFrame->m_wndStatusBar.SetPaneControl(m_pWndProgressCtrl, IDS_PANE_PROGRESS, true);
		
		m_pWndProgressCtrl->SetTimer(0,1,NULL);
		return;
	}
	
	if( m_wndRadioSlider.GetCheck() ) // slider ctrl
	{
		m_pWndSliderCtrl = new CExtStatusBarSliderCtrl;
		if (!m_pWndSliderCtrl->Create(
			WS_CHILD|WS_VISIBLE|WS_TABSTOP|TBS_HORZ, 
			CRect(0,0,0,0), 
			&m_pMainFrame->m_wndStatusBar, 
			0))
		{
			TRACE(_T("Failed to create slider control.\n"));
			return;
		}
		
		bool bRet = m_pMainFrame->m_wndStatusBar.AddPane(IDS_PANE_SLIDER_CTRL,m_nPosition);
		if(!bRet){
			AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
			return;
		}
		
		int nIndex = m_pMainFrame->m_wndStatusBar.CommandToIndex(IDS_PANE_SLIDER_CTRL);
		if (nIndex == -1)
			return;
		
		m_pMainFrame->m_wndStatusBar.SetPaneWidth(nIndex, 80);
		m_pMainFrame->m_wndStatusBar.SetPaneControl(m_pWndSliderCtrl, IDS_PANE_SLIDER_CTRL, true);
		return;
	}
	
	if( m_wndRadioButton.GetCheck() ) // button
	{
		m_pWndButton = new CExtStatusBarButton;
		if (!m_pWndButton->Create(
			_T("Button"),
			WS_CHILD|WS_VISIBLE|WS_TABSTOP,
			CRect(0,0,0,0), 
			&m_pMainFrame->m_wndStatusBar, 
			IDC_STATUS_BAR_BUTTON))
		{
			TRACE(_T("Failed to create button control.\n"));
			return;
		}
		m_pWndButton->SetFlat();
		m_pWndButton->SetDrawBorder( m_chkDrawPaneSeparators.GetCheck()==1 );
		
		bool bRet = m_pMainFrame->m_wndStatusBar.AddPane(IDS_PANE_BUTTON,m_nPosition);
		if(!bRet){
			AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
			return;
		}
		
		int nIndex = m_pMainFrame->m_wndStatusBar.CommandToIndex(IDS_PANE_BUTTON);
		if (nIndex == -1)
			return;
		
		m_pMainFrame->m_wndStatusBar.SetPaneWidth(nIndex, 50);
		m_pMainFrame->m_wndStatusBar.SetPaneControl(m_pWndButton, IDS_PANE_BUTTON, true);
		return;
	}
	
	if( m_wndRadioAnimCtrl.GetCheck() ) // animate ctrl
	{
		m_pWndAnimateCtrl = new CExtStatusBarAnimateCtrl;
		if (!m_pWndAnimateCtrl->Create(
			WS_CHILD|WS_VISIBLE|WS_TABSTOP|ACS_CENTER|ACS_AUTOPLAY|ACS_TRANSPARENT,
			CRect(0,0,0,0), 
			&m_pMainFrame->m_wndStatusBar, 
			0))
		{
			TRACE(_T("Failed to create animate control.\n"));
			return;
		}
		m_pWndAnimateCtrl->Open(IDR_DOWNLOAD);
		
		
		bool bRet = m_pMainFrame->m_wndStatusBar.AddPane(IDS_PANE_ANIMATE,m_nPosition);
		if(!bRet){
			AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
			return;
		}
		
		int nIndex = m_pMainFrame->m_wndStatusBar.CommandToIndex(IDS_PANE_ANIMATE);
		if (nIndex == -1)
			return;
		
		m_pMainFrame->m_wndStatusBar.SetPaneWidth(nIndex, 16);
		m_pMainFrame->m_wndStatusBar.SetPaneControl(m_pWndAnimateCtrl, IDS_PANE_ANIMATE, true);
		return;
	}
	
	if( m_wndRadioStatic.GetCheck() ) // label
	{
		m_pWndLabel = new CExtStatusBarLabel;
		if (!m_pWndLabel->Create(
			_T("Prof-UIS"),
			WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_CENTER,
			CRect(0,0,0,0), 
			&m_pMainFrame->m_wndStatusBar, 
			0))
		{
			TRACE(_T("Failed to create label control.\n"));
			return;
		}
		
		m_pWndLabel->SetFont(
			CFont::FromHandle(
			(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
			)
			);
		
		bool bRet = m_pMainFrame->m_wndStatusBar.AddPane(IDS_PANE_LABEL,m_nPosition);
		if(!bRet){
			AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
			return;
		}
		
		int nIndex = m_pMainFrame->m_wndStatusBar.CommandToIndex(IDS_PANE_LABEL);
		if (nIndex == -1)
			return;
		
		m_pMainFrame->m_wndStatusBar.SetPaneWidth(nIndex, 70);
		m_pMainFrame->m_wndStatusBar.SetPaneControl(m_pWndLabel, IDS_PANE_LABEL, true);
		return;
	}
}

//////////////////////////////////////////////////////////////////////////

void CChildFormView::OnRemovePane() 
{
	UpdateData();
	if( m_nPosition < 0 || m_nPosition > 20 )
		return;

	if(!m_pMainFrame->m_wndStatusBar.RemovePane(
		m_pMainFrame->m_wndStatusBar.GetItemID(m_nPosition))
		)
	{
		CString s;
		s.Format(_T("Pane %d was not found in the status bar \nor must be at least one of them."), m_nPosition);
		AfxMessageBox(s, MB_ICONERROR);
	}
}

//////////////////////////////////////////////////////////////////////////

void CChildFormView::OnStatusBarButton() 
{
	AfxMessageBox(_T("StatusBar Button Clicked."));
}

//////////////////////////////////////////////////////////////////////////

void CChildFormView::OnDisablePane() 
{
	UpdateData();
	if( m_nPosition < 0 || m_nPosition > 20 )
		return;
	
	UINT nID, nStyle;
	int cxWidth;
	
	m_pMainFrame->m_wndStatusBar.GetPaneInfo(m_nPosition, nID, nStyle, cxWidth);
	
	bool bDisabled = ((nStyle&SBPS_DISABLED) == 0);

	m_pMainFrame->m_wndStatusBar.SetPaneStyle(
		m_nPosition,
		//nID,
		bDisabled 
			? nStyle | SBPS_DISABLED 
			: nStyle & ~SBPS_DISABLED
		//`cxWidth
		);
}

//////////////////////////////////////////////////////////////////////////

void CChildFormView::CheckControls()
{
	if(!m_bInitComplete)
		return;
	
	UpdateData();
	if( m_nPosition < 0 ){
		m_nPosition = 0;
		UpdateData(0);
		return;
	}
	if( m_nPosition > 20 ){
		m_nPosition = 20;
		UpdateData(0);
		return;
	}
	
	int nCount = m_pMainFrame->m_wndStatusBar.GetPaneCount();

	if( m_nPosition >= nCount )
	{
		m_btnDisablePane.EnableWindow(FALSE);
		m_btnRemovePane.EnableWindow(FALSE);
		if( m_nPosition != nCount ){
			m_btnAddPane.EnableWindow(FALSE);
			return;
		}
	}
	else
	{
		m_btnDisablePane.EnableWindow(TRUE);
		m_btnRemovePane.EnableWindow(TRUE);
	}

	bool bFinded = false;
	int i=0;

	if( m_wndRadioText.GetCheck() ){
		for(i=0; i<m_pMainFrame->m_wndStatusBar.GetPaneCount(); i++)
			if( IDS_PANE_TEXT == m_pMainFrame->m_wndStatusBar.GetItemID(i) ){
				bFinded = true;
				break;
			}
	}
	if( m_wndRadioEdit.GetCheck() ){
		for(i=0; i<m_pMainFrame->m_wndStatusBar.GetPaneCount(); i++)
			if( IDS_PANE_EDIT == m_pMainFrame->m_wndStatusBar.GetItemID(i) ){
				bFinded = true;
				break;
			}
	}
	if( m_wndRadioProgress.GetCheck() ){
		for(i=0; i<m_pMainFrame->m_wndStatusBar.GetPaneCount(); i++)
			if( IDS_PANE_PROGRESS == m_pMainFrame->m_wndStatusBar.GetItemID(i) ){
				bFinded = true;
				break;
			}
	}
	if( m_wndRadioSlider.GetCheck() ){
		for(i=0; i<m_pMainFrame->m_wndStatusBar.GetPaneCount(); i++)
			if( IDS_PANE_SLIDER_CTRL == m_pMainFrame->m_wndStatusBar.GetItemID(i) ){
				bFinded = true;
				break;
			}
	}
	if( m_wndRadioButton.GetCheck() ){
		for(i=0; i<m_pMainFrame->m_wndStatusBar.GetPaneCount(); i++)
			if( IDS_PANE_BUTTON == m_pMainFrame->m_wndStatusBar.GetItemID(i) ){
				bFinded = true;
				break;
			}
	}
	if( m_wndRadioAnimCtrl.GetCheck() ){
		for(i=0; i<m_pMainFrame->m_wndStatusBar.GetPaneCount(); i++)
			if( IDS_PANE_ANIMATE == m_pMainFrame->m_wndStatusBar.GetItemID(i) ){
				bFinded = true;
				break;
			}
	}
	if( m_wndRadioStatic.GetCheck() ){
		for(i=0; i<m_pMainFrame->m_wndStatusBar.GetPaneCount(); i++)
			if( IDS_PANE_LABEL == m_pMainFrame->m_wndStatusBar.GetItemID(i) ){
				bFinded = true;
				break;
			}
	}

	m_btnAddPane.EnableWindow( !bFinded );
}


BOOL CChildFormView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
BOOL bRetVal = CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	if(		nCode == CN_COMMAND
		&&	(	nID == IDC_POSITION
			||	nID == IDC_SPIN_POSITION
			||	nID == IDC_ADD_PANE
			||	nID == IDC_REMOVE_PANE
			||	nID == IDC_DISABLE_PANE
			||	nID == IDC_RADIO_TYPE_TEXT
			||	nID == IDC_RADIO_TYPE_EDIT
			||	nID == IDC_RADIO_TYPE_PROGRESS
			||	nID == IDC_RADIO_TYPE_SLIDER
			||	nID == IDC_RADIO_TYPE_BUTTON
			||	nID == IDC_RADIO_TYPE_ANIM_CTRL
			||	nID == IDC_RADIO_TYPE_STATIC
			)
		)
		CheckControls();
	return bRetVal;
}

void CChildFormView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
}
