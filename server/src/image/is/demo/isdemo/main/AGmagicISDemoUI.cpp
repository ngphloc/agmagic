// AGmagicISDemoUI.cpp: implementation of the AGmagicISDemoUI class.
//
//////////////////////////////////////////////////////////////////////

#include "AGmagicISDemoUI.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoControlBar************************************/
#if AGMAGIC_SUPPORT_MFC
IMPLEMENT_DYNAMIC(CAGmagicISDemoControlBar, CDialogBar)

BEGIN_MESSAGE_MAP(CAGmagicISDemoControlBar, CDialogBar)
	//{{AFX_MSG_MAP(CAGmagicISDemoControlBar)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAGmagicISDemoControlBar::CAGmagicISDemoControlBar() : CDialogBar()
{
	m_hDefaultTipIcon=m_hInfoTipIcon=m_hQuestionTipIcon=NULL;
}
CAGmagicISDemoControlBar::CAGmagicISDemoControlBar(CFrameWnd* pFrameWnd) : CDialogBar()
{
	ASSERT(pFrameWnd!=NULL);
	if (!Create(pFrameWnd, IDD,	CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY, IDD))
	{
		TRACE0("Failed to create DlgBar\n");
		return;
	}
	//EnableDocking(CBRS_ALIGN_LEFT);
	//pFrameWnd->DockControlBar(this,AFX_IDW_DOCKBAR_LEFT);
	SetWindowText(_T("Serach Control"));
}
CAGmagicISDemoControlBar::~CAGmagicISDemoControlBar()
{
}

int CAGmagicISDemoControlBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDJ_SEARCH_CONTROL_BAR),_T("JPG"));
	m_pBgImage = new CAGimage();
	if (!m_pBgImage->LoadResource(FindResource(hInst,MAKEINTRESOURCE(IDJ_SEARCH_CONTROL_BAR),_T("JPG")),CXIMAGE_FORMAT_JPG,hInst)){
		delete m_pBgImage;
		m_pBgImage = NULL;
	}
	if (m_pBgImage) {
		//COLORREF rgb=GetSysColor(COLOR_APPWORKSPACE);
		//AGCLRQUAD hsl=m_pBgImage->RGBtoHSL(bgImage->RGBtoRGBQUAD(rgb));
		//m_pBgImage->Colorize(hsl.rgbRed,min(hsl.rgbGreen,100));
	}
	return 0;
}
void CAGmagicISDemoControlBar::OnInitDialog()
{
	m_hDefaultTipIcon=AfxGetApp()->LoadIcon(IDI_DEFAULT_TIP);
	m_hInfoTipIcon=AfxGetApp()->LoadIcon(IDI_INFO_TIP);
	m_hQuestionTipIcon=AfxGetApp()->LoadIcon(IDI_QUESTION_TIP);
	m_Tip.Create(this);
	m_Tip.SetEffectBk(CPPDrawManager::EFFECT_3HGRADIENT);
	m_Tip.SetBorder(RGB(0,255,0), 2, 2);
	m_Tip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 100);
	m_Tip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, m_Tip.GetDelayTime(PPTOOLTIP_TIME_AUTOPOP)*2);

	m_searchmodelLabel.SubclassDlgItem(IDC_SEARCH_MODEL_STATIC,this);
	m_searchmodelLabel.SetFont3D(TRUE,CLabel::Raised);
	m_searchmodelLabel.SetFontBold(TRUE);
	m_searchmodelLabel.SetText3DHiliteColor(CONTROL_BAR_TEXT_COLOR);
	m_searchmodelLabel.SetTransparent(TRUE);
	m_searchmodelLabel.SetText(_T("Search Model"));

	m_searchmodel.SubclassDlgItem(IDC_SEARCH_MODEL,this);
	m_searchmodel.AddString(_T("MMM System"));
	m_searchmodel.SetCurSel(0);
	m_Tip.AddTool(&m_searchmodel, _T("You select Searching Model.\nThat model must be support"), m_hDefaultTipIcon);

	m_confserver.SubclassDlgItem(IDC_CONFIG_SERVER,this);
	m_confserver.SetIcon(IDI_AGMAGICIP_G,BS_LEFT);
	m_confserver.SetTextColor(CONTROL_BAR_TEXT_COLOR);
	m_Tip.AddTool(&m_confserver, _T("You will configure SERVER.\n There are two server : Training System and Searching System running outline.\nYou must stop server before configure"), m_hDefaultTipIcon);

	m_createdb.SubclassDlgItem(IDC_CREATE_DB,this);
	m_createdb.SetIcon(IDI_AGMAGICIP_G,BS_LEFT);
	m_createdb.SetTextColor(CONTROL_BAR_TEXT_COLOR);
	m_Tip.AddTool(&m_createdb, _T("Create database. But first you must stop server.\nYou must nitialize System again"), m_hDefaultTipIcon);

	m_startserver.SubclassDlgItem(IDC_START_SERVER,this);
	m_startserver.SetSkin(IDB_RNORM,IDB_RDOWN,IDB_ROVER,IDB_RGRAY,0,IDB_RMASK,0,0,0);
	//m_startserver.SetToolTipText("Start Server");
	m_Tip.AddTool(&m_startserver, _T("Start/Stop SERVER : Training System and Searching System.\nYou can not configure in when SERVER running"), m_hDefaultTipIcon);
	
	m_stopserver.SubclassDlgItem(IDC_STOP_SERVER,this);
	m_stopserver.SetSkin(IDB_LNORM,IDB_LDOWN,IDB_LOVER,IDB_LGRAY,0,IDB_LMASK,0,0,0);
	m_Tip.AddTool(&m_stopserver, _T("Stop/Start SERVER : Training System and Searching System.\nYou can not search image in if SERVER stopped"), m_hDefaultTipIcon);
	//m_stopserver.SetToolTipText("Stop Server");

	m_browse.SubclassDlgItem(IDC_BROWSE,this);
	m_browse.SetSkin(IDB_BROWSE_NORM,IDB_BROWSE_DOWN,IDB_BROWSE_OVER,IDB_BROWSE_GRAY,0,IDB_BROWSE_MASK,0,0,0);
	//m_browse.SetToolTipText("Browse");
	m_Tip.AddTool(&m_browse, _T("Browse query image for searching.\n Choose image that you want to find \nother images which similar it"), m_hDefaultTipIcon);

	m_search.SubclassDlgItem(IDC_SEARCH,this);
	m_search.SetSkin(IDB_EYECLOSED, IDB_EYEBLUE,         IDB_EYEGRAY, 
					 IDB_EYECLOSED, IDB_EYECLOSED_FOCUS, IDB_EYEMASK,
					 0,             0,                   0 );
	//m_search.SetToolTipText("Search");
	m_Tip.AddTool(&m_search, _T("Press this button for SEARCHING \n. SERVER will send back preferring images into individual parts. \n Searching System will run outline, \n so you can do other thing"), m_hDefaultTipIcon);

	m_feedback.SubclassDlgItem(IDC_FEEDBACK,this);
	m_feedback.SetSkin(IDB_FEEDBACK_NORM,IDB_FEEDBACK_DOWN,IDB_FEEDBACK_OVER,IDB_FEEDBACK_GRAY,0,IDB_FEEDBACK_MASK,0,0,0);
	//m_feedback.SetToolTipText("Feedback");
	m_Tip.AddTool(&m_feedback, _T("You see in the searching result WINDOW.\nYou choose some images that you feel likest.\nFinally you press this button in order to \n send back Training System so that\n Training System refine Query Result for after Searching"), m_hDefaultTipIcon);
}
void CAGmagicISDemoControlBar::OnDestroy() 
{
	CDialogBar::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_hDefaultTipIcon)	::DestroyIcon(m_hDefaultTipIcon);
	if(m_hInfoTipIcon)		::DestroyIcon(m_hInfoTipIcon);
	if(m_hQuestionTipIcon)	::DestroyIcon(m_hQuestionTipIcon);
	
}
LRESULT CAGmagicISDemoControlBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch (message)
	{
		case WM_INITDIALOG:
			OnInitDialog();
			break;
	}		
	return CDialogBar::WindowProc(message, wParam, lParam);
}

BOOL CAGmagicISDemoControlBar::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_Tip.RelayEvent(pMsg);

	return CDialogBar::PreTranslateMessage(pMsg);
}

BOOL CAGmagicISDemoControlBar::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	if (m_pBgImage!=NULL)
	{
		RECT rect;
		GetClientRect(&rect);
		m_pBgImage->Tile(pDC->GetSafeHdc(),&rect);
		return TRUE;
	}
	return CDialogBar::OnEraseBkgnd(pDC);
}
BOOL CAGmagicISDemoControlBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
#if WINVER > 0x0400
	if(nHitTest!=HTCLIENT)	return CDialogBar::OnSetCursor(pWnd, nHitTest, message);
	HCURSOR			hCursor=AfxGetApp()->LoadCursor(IDCUR_HAND_P);
	HCURSOR			hOldCursor=::SetCursor(hCursor);
	//if(hOldCursor)	::DestroyCursor(hOldCursor);
	//if(hCursor)		::DestroyCursor(hCursor);
	return TRUE;
#else
	return CDialogBar::OnSetCursor(pWnd, nHitTest, message);
#endif
}
#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoServerDlg************************************/

#if AGMAGIC_SUPPORT_MFC
CAGmagicISDemoServerDlg::CAGmagicISDemoServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogSK()//CDialog(CAGmagicISDemoServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAGmagicISDemoServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Create(IDD,pParent);
}

void CAGmagicISDemoServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSK::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGmagicISDemoServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAGmagicISDemoServerDlg, CDialogSK)
	//{{AFX_MSG_MAP(CAGmagicISDemoServerDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoServerDlg message handlers

BOOL CAGmagicISDemoServerDlg::OnInitDialog() 
{
	CDialogSK::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ISDEMO_MAIN);
	HICON hOldBigIcon=SetIcon(hIcon, TRUE);			// Set big icon
	HICON hOldSmallIcon=SetIcon(hIcon, FALSE);		// Set small icon
	//if(hIcon)			::DestroyIcon(hIcon);
	if(hOldBigIcon)		::DestroyIcon(hOldBigIcon);
	if(hOldSmallIcon)	::DestroyIcon(hOldSmallIcon);
	SetWindowText(_T("AGmagicIS-Server"));

///////////////////////////////////////////////////////////////
	EnableEasyMove();                    // enable moving of the dialog by clicking anywhere in the dialog
    SetBitmap(IDB_ISDEMO_SERVER);		 // set background bitmap
    SetStyle(LO_STRETCH);                 // resize dialog to the size of the bitmap
    SetTransparentColor(RGB(0, 255, 0)); // set green as the transparent color

	//Clock
	m_Clock.SubclassDlgItem(IDC_CLOCKST, this);
	m_Clock.Start(IDB_CLOCKST_PANE, IDB_CLOCKST_BIG, IDB_CLOCKST_SMALL);

	//Notice
	CAGmagicISDemoMainFrame*	pAGmagicISDemoMainFrame=(CAGmagicISDemoMainFrame*)GetParentFrame();
	m_SearchingSystemNotice.SubclassDlgItem(IDC_SEARCHINGSYSTEM_NOTICE, this);
	m_SearchingSystemNotice.SetFont3D(TRUE,CLabel::Raised);
	m_SearchingSystemNotice.SetFontBold(TRUE);
	m_SearchingSystemNotice.SetTransparent(TRUE);

	m_TrainingSystemNotice.SubclassDlgItem(IDC_TRAININGSYSTEM_NOTICE, this);
	m_TrainingSystemNotice.SetFont3D(TRUE,CLabel::Raised);
	m_TrainingSystemNotice.SetFontBold(TRUE);
	m_TrainingSystemNotice.SetTransparent(TRUE);

	//Animate Notice
	m_AnimateNotice.SubclassDlgItem(IDC_AMINATE_NOTICE, this);
	m_AnimateNotice.Load(MAKEINTRESOURCE(IDG_ANIMATE_NOTICE),_T("GIF"));
	m_AnimateNotice.SetBkColor(RGB(0,255,0));

	//Dieu chinh
	if(pAGmagicISDemoMainFrame->m_pAGmmSearchingSystem!=NULL &&
	   pAGmagicISDemoMainFrame->m_pAGmmTrainingSystem!=NULL )
	{
		if(pAGmagicISDemoMainFrame->m_pAGmmSearchingSystem->IsRunning() &&
		   pAGmagicISDemoMainFrame->m_pAGmmTrainingSystem->IsRunning() )
		{
			m_SearchingSystemNotice.SetText3DHiliteColor(RUNNING_NOTICE_TEXT_COLOR);
			m_SearchingSystemNotice.SetText(SEARCHING_SYSTEM_RUNNING_NOTICE_TEXT);

			m_TrainingSystemNotice.SetText3DHiliteColor(RUNNING_NOTICE_TEXT_COLOR);
			m_TrainingSystemNotice.SetText(TRAINING_SYSTEM_RUNNING_NOTICE_TEXT);
			m_AnimateNotice.Draw();
		}
	}
	else
	{
		m_SearchingSystemNotice.SetText3DHiliteColor(STOPPED_NOTICE_TEXT_COLOR);
		m_SearchingSystemNotice.SetText(SEARCHING_SYSTEM_STOPPED_NOTICE_TEXT);
		m_TrainingSystemNotice.SetText3DHiliteColor(STOPPED_NOTICE_TEXT_COLOR);
		m_TrainingSystemNotice.SetText(TRAINING_SYSTEM_STOPPED_NOTICE_TEXT);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAGmagicISDemoServerDlg::OnDestroy()
{
	CDialogSK::OnDestroy();
	
	// TODO: Add your message handler code here
}
int CAGmagicISDemoServerDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class

	//modaless
	ASSERT(FALSE);//khong duoc goi ham DoModal
	return 0;

	//modal
	//return CDialog::DoModal();
}

void CAGmagicISDemoServerDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDialogSK::OnPaint();
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CAGmagicISDemoServerDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}
void CAGmagicISDemoServerDlg::OnTimer(UINT nIDEvent) 
{
	CDialogSK::OnTimer(nIDEvent);
}
void CAGmagicISDemoServerDlg::OnOK()
{
	// TODO: Add extra validation here

	//modaless
	//if(!UpdateData(TRUE))
	//{
	//	TRACE(_T("Update data failed during dialog termination"));
	//	return;
	//}
	//DestroyWindow();

	//modal
	//CDialog::OnOK();
}

void CAGmagicISDemoServerDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	//modaless
	//DestroyWindow();
	ShowWindow(SW_HIDE);

	//modal
	//CDialog::OnCancel();
}
#endif

/******************************class CAGmagicISDemoOutputBar, CAGmagicISDemoOutputEdit************************/
#if AGMAGIC_SUPPORT_MFC

CAGmagicISDemoOutputEdit::CAGmagicISDemoOutputEdit()
{
}

CAGmagicISDemoOutputEdit::~CAGmagicISDemoOutputEdit()
{
}


BEGIN_MESSAGE_MAP(CAGmagicISDemoOutputEdit, baseEdit)
	//{{AFX_MSG_MAP(CAGmagicISDemoOutputEdit)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoOutputEdit message handlers

HBRUSH CAGmagicISDemoOutputEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	HBRUSH bBkBrush=::CreateSolidBrush(RGB(255,255,255));
	//pDC->SetBkMode(TRANSPARENT);
	return bBkBrush;

	//return NULL;
}

CAGmagicISDemoOutputBar::CAGmagicISDemoOutputBar() : baseAGmagicISDemoOutputBar()
{
}
CAGmagicISDemoOutputBar::CAGmagicISDemoOutputBar(CFrameWnd* pFrameWnd) : baseAGmagicISDemoOutputBar()
{
	ASSERT(pFrameWnd!=NULL);
	if (!Create(_T("Out put"), pFrameWnd, ID_OUTPUT_BAR))
	{
		TRACE0("Failed to create mybar\n");
		return ;		// fail to create
	}
	SetBarStyle(GetBarStyle() |
				CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	EnableDocking(CBRS_ALIGN_BOTTOM);
	pFrameWnd->DockControlBar(this, AFX_IDW_DOCKBAR_BOTTOM);
}

CAGmagicISDemoOutputBar::~CAGmagicISDemoOutputBar()
{
}


BEGIN_MESSAGE_MAP(CAGmagicISDemoOutputBar, baseAGmagicISDemoOutputBar)
	//{{AFX_MSG_MAP(CAGmagicISDemoOutputBar)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoOutputBar message handlers

int CAGmagicISDemoOutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (baseAGmagicISDemoOutputBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

	if (!m_edit.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|
			ES_READONLY|ES_MULTILINE|ES_WANTRETURN|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
		CRect(0,0,0,0), this, IDC_OUTPUT_EDIT))
		return -1;
	m_edit.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	//m_edit.FmtLines(FALSE);//buoc phai ngat dong cung

	// older versions of Windows* (NT 3.51 for instance)
	// fail with DEFAULT_GUI_FONT
	//if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
	//	if (!m_font.CreatePointFont(80, "MS Sans Serif"))
	//		return -1;
	//m_edit.SetFont(&m_font);

	LoadState(AfxGetApp()->m_pszProfileName);
	return 0;
}
void CAGmagicISDemoOutputBar::OnDestroy()
{
	baseAGmagicISDemoOutputBar::OnDestroy();
	
	// TODO: Add your message handler code here
	SaveState(AfxGetApp()->m_pszProfileName);
}
#endif

/*******************************class CAGmagicISDemoSearchResultDlg*******************************/
#if AGMAGIC_SUPPORT_MFC

CAGmagicISDemoSearchResultDlg::CAGmagicISDemoSearchResultDlg(CWnd* pParent /*=NULL*/)
	: baseSearchResultDlg()//baseSearchResultDlg(CAGmagicISDemoSearchResultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAGmagicISDemoSearchResultDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Create(IDD,pParent);
}

void CAGmagicISDemoSearchResultDlg::DoDataExchange(CDataExchange* pDX)
{
	baseSearchResultDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGmagicISDemoSearchResultDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAGmagicISDemoSearchResultDlg, baseSearchResultDlg)
	//{{AFX_MSG_MAP(CAGmagicISDemoSearchResultDlg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_MESSAGE(AGMAGICIP_WM_LISTCTRL_UPDATE_DOCUMENT_ALREADY, OnListCtrlUpdateDocumentAlready)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SEARCH_RESULT_LISTCTRL, OnItemchangedSearchResultListCtrl)
	ON_NOTIFY(NM_RETURN, IDC_SEARCH_RESULT_LISTCTRL, OnReturnSearchResultListCtrl)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SEARCH_RESULT_LISTCTRL, OnOutofMemorySearchResultListCtrl)

	ON_COMMAND(ID_SEARCH_RESULT_MOVE_FIRST, OnMoveFirst)
	ON_COMMAND(ID_SEARCH_RESULT_MOVE_PREVIOUS, OnMovePrevious)
	ON_COMMAND(ID_SEARCH_RESULT_MOVE_NEXT, OnMoveNext)
	ON_COMMAND(ID_SEARCH_RESULT_MOVE_LAST, OnMoveLast)
	ON_COMMAND_RANGE(ID_SEARCH_RESULT_PAGE1, ID_SEARCH_RESULT_PAGE10, OnNumber)

	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_MOVE_FIRST, OnUpdateMoveFirst)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_MOVE_PREVIOUS, OnUpdateMovePrevious)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_MOVE_NEXT, OnUpdateMoveNext)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_MOVE_LAST, OnUpdateMoveLast)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SEARCH_RESULT_PAGE1, ID_SEARCH_RESULT_PAGE10, OnUpdateNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoSearchResultDlg message handlers

BOOL CAGmagicISDemoSearchResultDlg::OnInitDialog() 
{
	baseSearchResultDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_INFO_TIP);
	HICON hOldBigIcon=SetIcon(hIcon, TRUE);			// Set big icon
	HICON hOldSmallIcon=SetIcon(hIcon, FALSE);		// Set small icon
	//if(hIcon)			::DestroyIcon(hIcon);
	if(hOldBigIcon)		::DestroyIcon(hOldBigIcon);
	if(hOldSmallIcon)	::DestroyIcon(hOldSmallIcon);
	
///////Cac control//////////////////
	AddControl(IDC_SEARCH_RESULT_LISTCTRL, CST_RESIZE, CST_RESIZE, CST_RESIZE, CST_RESIZE, 1);
	AddControl(IDC_IMAGE_INFO, CST_NONE, CST_NONE, CST_REPOS, CST_REPOS, 1);
	AddControl(IDC_FIND_IMAGE, CST_NONE, CST_NONE, CST_REPOS, CST_REPOS, 1);

	m_SearchResultCtrl.SubclassDlgItem(IDC_SEARCH_RESULT_LISTCTRL,this);
	m_SearchResultCtrl.SetOutsideContextMenu(IDM_SEARCH_RESULT_CONTEXT);

	m_ListCtrlInfo.SubclassDlgItem(IDC_LISTCTRL_INFO,this);
	m_ListCtrlInfo.SetFont3D(TRUE,CLabel::Raised);
	m_ListCtrlInfo.SetFontBold(TRUE);
	m_ListCtrlInfo.SetTransparent(TRUE);
	m_ListCtrlInfo.SetText3DHiliteColor(RGB(0,0,255));
	m_ListCtrlInfo.SetText(_T(""));

	m_ImageInfo.SubclassDlgItem(IDC_IMAGE_INFO,this);
	m_ImageInfo.SetWindowText(_T(""));

	m_Find.SubclassDlgItem(IDC_FIND_IMAGE,this);
	m_Find.SetIcon(IDI_AGMAGICIP_G,BS_LEFT);
	m_Find.SetTextColor(CONTROL_BAR_TEXT_COLOR);
///////////////Cac bien/////////////////////////////
	m_pDoc=NULL;
	m_nPages=0;
	m_iPage=-1;
	m_NumberOfLoadImages=0;

	CreateToolBar();

/////////////////////////Transparency///////////////////////////////
//WinXP, Win2000 or later
//#if defined(_WIN32_WINNT) && defined(WINVER)
//##if _WIN32_WINNT>=0x0500 && WINVER>=0x0500
//#	const DWORD ANIMATION_MILLIS = 200;
//#	const BYTE TRANSLUCENCY = 150;
//#	const BYTE TRANSLUCENCY_STEP = 16;
//#	const DWORD TRANSLUCENCY_TIMEOUT = TRANSLUCENCY_STEP * ANIMATION_MILLIS / TRANSLUCENCY;
//
//#	// Make it a layered window.
//#	::SetWindowLong(m_hWnd, GWL_EXSTYLE,
//					::GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
//
//	// Completely transparent window - note the third parameter
//	SetLayeredWindowAttributes(0, 0, LWA_ALPHA);
//
//	// Show it _first_
//	ShowWindow(SW_SHOW);
//
//	// Redraw contents NOW - no flickering since the window's not visible
//	RedrawWindow(NULL, NULL, RDW_UPDATENOW); 

//	// Normally, you would use a timer here...
//	for (BYTE bTranslucency = 0; bTranslucency < TRANSLUCENCY; bTranslucency+=TRANSLUCENCY_STEP)
//	{
//		// Adjust the translucency
//		SetLayeredWindowAttributes(0, bTranslucency, LWA_ALPHA);
//
//		// Wait
//		::Sleep(TRANSLUCENCY_TIMEOUT);
//	}
//	// Set the final translucency
//	SetLayeredWindowAttributes(0, bTranslucency, LWA_ALPHA);
//#endif	//#if _WIN32_WINNT>=0x0500 && WINVER>=0x0500
//#endif	//#if defined(_WIN32_WINNT) && defined(WINVER)
//
/////////////////////////End Transparency///////////////////////////////

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAGmagicISDemoSearchResultDlg::OnDestroy()
{
	baseSearchResultDlg::OnDestroy();
	m_SearchResults.RemoveAll();
	m_pDoc=NULL;
	
	// TODO: Add your message handler code here
}
int CAGmagicISDemoSearchResultDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class

	//modaless
	ASSERT(FALSE);//khong duoc goi ham DoModal
	return 0;

	//modal
	//return baseSearchResultDlg::DoModal();
}

void CAGmagicISDemoSearchResultDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call baseSearchResultDlg::OnPaint() for painting messages
}
void CAGmagicISDemoSearchResultDlg::OnSize(UINT nType, int cx, int cy) 
{
	baseSearchResultDlg::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}

void CAGmagicISDemoSearchResultDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	baseSearchResultDlg::PostNcDestroy();
	delete this;
}
void CAGmagicISDemoSearchResultDlg::OnOK()
{
	// TODO: Add extra validation here

	//modaless
	//if(!UpdateData(TRUE))
	//{
	//	TRACE(_T("Update data failed during dialog termination"));
	//	return;
	//}
	//DestroyWindow();

	//modal
	//baseSearchResultDlg::OnOK();
}

void CAGmagicISDemoSearchResultDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	//modaless
	//DestroyWindow();
	ShowWindow(SW_HIDE);

	//modal
	//baseSearchResultDlg::OnCancel();
}
void CAGmagicISDemoSearchResultDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
	
	//baseSearchResultDlg::OnClose();
}
LRESULT CAGmagicISDemoSearchResultDlg::OnListCtrlUpdateDocumentAlready(WPARAM wParam, LPARAM lParam)
{
	CAGmagicISDemoMainFrame* pMainWnd=(CAGmagicISDemoMainFrame*)GetParent();
	pMainWnd->EndProgress();
	if(pMainWnd) pMainWnd->PostMessage(AGMAGICIP_WM_LISTCTRL_UPDATE_DOCUMENT_ALREADY,wParam,lParam);
	return 0;
}
void CAGmagicISDemoSearchResultDlg::OnItemchangedSearchResultListCtrl(NMHDR* pNMHDR, LRESULT* pResult)	
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	agint32			iItem=pNMListView->iItem;

	CAGint32Array idxs;
	m_SearchResultCtrl.GetAllSelectedIdxs(&idxs);
	if(idxs.GetSize()!=1)
		m_ImageInfo.SetWindowText(_T(""));
	else
	{
		CString	szFilePath=m_SearchResultCtrl.GetItemText(idxs.GetAt(0),0);
		CString  szFileName=szFilePath.Mid(szFilePath.ReverseFind(AGMAGIC_DIR_SPLASH)+1);

		aguint_id	ImageID=m_SearchResultCtrl.m_AGlvItems.GetAt(idxs.GetAt(0))->m_ID;
		agfreal sim=m_SearchResultCtrl.m_AGlvItems.GetAt(idxs.GetAt(0))->m_pAGmagicElement->GetValue();

		agtchar		szNotice[1024];
		_stprintf(szNotice,_T("Image %s has ID=%lu, Similtary Degree with Query Image is %.12f"),szFileName,(UINT)ImageID,sim);
		m_ImageInfo.SetWindowText(szNotice);
	}
	*pResult = 0;
}
void CAGmagicISDemoSearchResultDlg::OnReturnSearchResultListCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
void CAGmagicISDemoSearchResultDlg::OnOutofMemorySearchResultListCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	MessageBox(_T("List view in Search Result Dialog out of memory"),_T("Warning"),MB_OK|MB_ICONWARNING);
	*pResult = 0;
}
agbool CAGmagicISDemoSearchResultDlg::SetupImageList()
{
	m_ImageList.Create(18, 16, ILC_COLOR24 | ILC_MASK, 0, 1);
	CWinApp* pApp = AfxGetApp();

	HICON hMoveFirstIcon=pApp->LoadIcon(IDI_SEARCH_RESULT_MOVE_FIRST);
	HICON hMovePreviousIcon=pApp->LoadIcon(IDI_SEARCH_RESULT_MOVE_PREVIOUS);
	HICON hMoveNextIcon=pApp->LoadIcon(IDI_SEARCH_RESULT_MOVE_NEXT);
	HICON hMoveLastIcon=pApp->LoadIcon(IDI_SEARCH_RESULT_MOVE_LAST);

	HICON	hNumberIcon[MAX_PAGE_BUTTON];
	agint32 i=0;
	for(i=0; i<MAX_PAGE_BUTTON; i++)
		hNumberIcon[i]=pApp->LoadIcon(IDI_SEARCH_RESULT_PAGE1+i);

	m_ImageList.Add(hMoveFirstIcon);
	m_ImageList.Add(hMovePreviousIcon);
	m_ImageList.Add(hMoveNextIcon);
	m_ImageList.Add(hMoveLastIcon);
	for(i=0; i<MAX_PAGE_BUTTON; i++)
		m_ImageList.Add(hNumberIcon[i]);

	//////////////////////////////////////////////////////
	//Destroy icon
	if(hMoveFirstIcon)		::DestroyIcon(hMoveFirstIcon);
	if(hMovePreviousIcon)	::DestroyIcon(hMovePreviousIcon);
	if(hMoveNextIcon)		::DestroyIcon(hMoveNextIcon);
	if(hMoveLastIcon)		::DestroyIcon(hMoveLastIcon);
	for(i=0; i<MAX_PAGE_BUTTON; i++)
		if(hNumberIcon[i])		::DestroyIcon(hNumberIcon[i]);

	return agtrue;
}
aguint32 page_button_ids[MAX_PAGE_BUTTON]=
	{
		ID_SEARCH_RESULT_PAGE1,
		ID_SEARCH_RESULT_PAGE2,
		ID_SEARCH_RESULT_PAGE3,
		ID_SEARCH_RESULT_PAGE4,
		ID_SEARCH_RESULT_PAGE5,
		ID_SEARCH_RESULT_PAGE6,
		ID_SEARCH_RESULT_PAGE7,
		ID_SEARCH_RESULT_PAGE8,
		ID_SEARCH_RESULT_PAGE9,
		ID_SEARCH_RESULT_PAGE10
	};
void CAGmagicISDemoSearchResultDlg::CreateToolBar()
{
	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	//	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED) ||
	//	!m_wndToolBar.LoadToolBar(IDR_SEARCH_RESULT_TOOLBAR))
	//{
	//	TRACE0("Failed to create toolbar\n");
	//	return -1;      // fail to create
	//}

	SetupImageList();
	m_wndToolBar.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|TBSTYLE_FLAT, CRect(0,0,0,0), this, 137);
	m_wndToolBar.SetImageList(&m_ImageList);

	TBBUTTON tb;
	memset(&tb,0,sizeof(TBBUTTON));
	tb.iString = NULL;
	tb.fsState = TBSTATE_ENABLED;
	tb.fsStyle = TBSTYLE_BUTTON;

	TBBUTTON sep_tb;
	memset(&sep_tb,0,sizeof(TBBUTTON));
	sep_tb.fsStyle = TBSTYLE_SEP;
	
	tb.iBitmap = 0;
	tb.idCommand = ID_SEARCH_RESULT_MOVE_FIRST;
	m_wndToolBar.AddButtons(1, &tb);

	tb.iBitmap = 1;
	tb.idCommand = ID_SEARCH_RESULT_MOVE_PREVIOUS;
	m_wndToolBar.AddButtons(1, &tb);

	tb.iBitmap = 2;
	tb.idCommand = ID_SEARCH_RESULT_MOVE_NEXT;
	m_wndToolBar.AddButtons(1, &tb);

	tb.iBitmap = 3;
	tb.idCommand = ID_SEARCH_RESULT_MOVE_LAST;
	m_wndToolBar.AddButtons(1, &tb);

	m_wndToolBar.AddButtons(1, &sep_tb);

	for(agint32 i=0; i<MAX_PAGE_BUTTON; i++)
	{
		tb.iBitmap = 4+i;
		tb.idCommand = page_button_ids[i];
		m_wndToolBar.AddButtons(1, &tb);
	}
	DisableToolbar();
}
void CAGmagicISDemoSearchResultDlg::DisableToolbar()
{
	m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_FIRST,FALSE);
	m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_PREVIOUS,FALSE);
	m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_NEXT,FALSE);
	m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_LAST,FALSE);

	for(agint32 i=0; i<MAX_PAGE_BUTTON; i++)
		m_wndToolBar.EnableButton(page_button_ids[i],FALSE);
}
void CAGmagicISDemoSearchResultDlg::ShowPage(agint32 iPage)
{
	m_ListCtrlInfo.SetText(_T("There is no Image"));
	m_ImageInfo.SetWindowText(_T(""));
	CAGmagicISDemoMainFrame* pMainWnd=(CAGmagicISDemoMainFrame*)GetParent();
	if(m_pDoc==NULL || iPage<0 || iPage>=m_nPages || m_nPages==0 || m_NumberOfLoadImages==0)
	{
		if(!pMainWnd->m_bSearchingBusy)	ReleaseCapture();
		return;
	}
	agint32		n=m_SearchResults.GetSize();
	if(n==0)
	{
		if(!pMainWnd->m_bSearchingBusy)	ReleaseCapture();
		return;
	}

	agint32		i;
	agint32		FirstLoadImageIdx=iPage*m_NumberOfLoadImages;
	agint32		LastLoadImageIdx=(iPage==m_nPages-1)?(n-1):(FirstLoadImageIdx+m_NumberOfLoadImages-1);
	if(LastLoadImageIdx<FirstLoadImageIdx)
	{
		if(!pMainWnd->m_bSearchingBusy)	ReleaseCapture();
		return;
	}
	DisableToolbar();
	m_SearchResultCtrl.DeleteAllItems();
	m_iPage=iPage;

	if(m_nPages>1)
	{
		if(m_iPage==0)
		{
			m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_NEXT,TRUE);
			m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_LAST,TRUE);
		}
		else if(m_iPage==m_nPages-1)
		{
			m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_FIRST,TRUE);
			m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_PREVIOUS,TRUE);
		}
		else
		{
			m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_FIRST,TRUE);
			m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_PREVIOUS,TRUE);
			m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_NEXT,TRUE);
			m_wndToolBar.EnableButton(ID_SEARCH_RESULT_MOVE_LAST,TRUE);
		}
	}
	for(i=0; i<MAX_PAGE_BUTTON && i<m_nPages; i++)
	{
		m_wndToolBar.EnableButton(page_button_ids[i],TRUE);
		if(i==m_iPage)
			m_wndToolBar.CheckButton(page_button_ids[i], TRUE);
		else
			m_wndToolBar.CheckButton(page_button_ids[i], FALSE);
	}

	CAGinteractImagesMsg* pSendAGinteractImagesMsg=new CAGinteractImagesMsg();
	pSendAGinteractImagesMsg->CopyInfoFrom(m_pDoc->m_SearchResults2.GetAt(0));
	for(i=FirstLoadImageIdx; i<=LastLoadImageIdx; i++)
		pSendAGinteractImagesMsg->Add((CAGimageDBItem*)m_SearchResults.GetAt(i));
	pSendAGinteractImagesMsg->SetDeleteMeInProc(agfalse);

	ShowWindow(SW_NORMAL);
	agtchar szInfo[1024];
	_stprintf(szInfo,_T("There are %ld Image(s) In this Page of %ld Result Image(s)"), LastLoadImageIdx-FirstLoadImageIdx+1,n);
	m_ListCtrlInfo.SetText(szInfo);

	pMainWnd->m_bUpdatingSearchResults=agtrue;
	pMainWnd->SetCapture();
	pMainWnd->BeginProgress();
	m_SearchResultCtrl.PostMessage(AGMAGICIP_WM_RECEIVED_NEW_IMAGES,0,(LPARAM)(pSendAGinteractImagesMsg));
}
void CAGmagicISDemoSearchResultDlg::OnMoveFirst()
{
	if(m_pDoc==NULL || m_iPage<0 || m_iPage>=m_nPages || m_nPages==0 || m_NumberOfLoadImages==0)
		return;
	if(m_iPage==0)	return;
	ShowPage(m_iPage=0);
}
void CAGmagicISDemoSearchResultDlg::OnMovePrevious()
{
	if(m_pDoc==NULL || m_iPage<0 || m_iPage>=m_nPages || m_nPages==0 || m_NumberOfLoadImages==0)
		return;
	if(m_iPage==0)	return;
	ShowPage(--m_iPage);
}
void CAGmagicISDemoSearchResultDlg::OnMoveNext()
{
	if(m_pDoc==NULL || m_iPage<0 || m_iPage>=m_nPages || m_nPages==0 || m_NumberOfLoadImages==0)
		return;
	if(m_iPage==m_nPages-1)	return;
	ShowPage(++m_iPage);
}
void CAGmagicISDemoSearchResultDlg::OnMoveLast()
{
	if(m_pDoc==NULL || m_iPage<0 || m_iPage>=m_nPages || m_nPages==0 || m_NumberOfLoadImages==0)
		return;
	if(m_iPage==m_nPages-1)	return;
	ShowPage(m_iPage=m_nPages-1);
}
void CAGmagicISDemoSearchResultDlg::OnNumber(UINT nID)
{
	if(m_pDoc==NULL || m_iPage<0 || m_iPage>=m_nPages || m_nPages==0 || m_NumberOfLoadImages==0)
		return;
	for(agint32 i=0; i<MAX_PAGE_BUTTON; i++)
	{
		if(page_button_ids[i]==nID && i<m_nPages)
		{
			ShowPage(m_iPage=i);
			return;
		}
	}
}
void CAGmagicISDemoSearchResultDlg::OnUpdateMoveFirst(CCmdUI* pCmdUI)
{
}
void CAGmagicISDemoSearchResultDlg::OnUpdateMovePrevious(CCmdUI* pCmdUI)
{
}
void CAGmagicISDemoSearchResultDlg::OnUpdateMoveNext(CCmdUI* pCmdUI)
{
}
void CAGmagicISDemoSearchResultDlg::OnUpdateMoveLast(CCmdUI* pCmdUI)
{
}
void CAGmagicISDemoSearchResultDlg::OnUpdateNumber(CCmdUI* pCmdUI)
{
}

void CAGmagicISDemoSearchResultDlg::SetDocument(CAGmagicISDemoDoc*	pDoc)
{
	m_nPages=0;
	m_iPage=-1;
	m_NumberOfLoadImages=0;
	m_SearchResultCtrl.DeleteAllItems();
	DisableToolbar();
	m_SearchResults.RemoveAll();
	m_ListCtrlInfo.SetText(_T("There is no Image"));
	m_ImageInfo.SetWindowText(_T(""));

	m_pDoc=pDoc;
	if(m_pDoc==NULL)	return;

	agint32 m=m_pDoc->m_SearchResults2.GetSize();
	for(agint32 i=0; i<m; i++)
	{
		CAGinteractImagesMsg* pAGinteractImagesMsg=m_pDoc->m_SearchResults2.GetAt(i);
		agint32 n=pAGinteractImagesMsg->GetSize();
		for(agint32 j=0; j<n; j++)
			m_SearchResults.Add(pAGinteractImagesMsg->GetAt(j));
	}

	agint32		N=m_SearchResults.GetSize();
	if(N==0)	return;
	m_NumberOfLoadImages=AGMIN(N,MAX_NUMBER_OF_LOAD_IMAGES);
	m_nPages=N/m_NumberOfLoadImages;
	if(m_nPages>MAX_PAGE_BUTTON)
	{
		m_nPages=MAX_PAGE_BUTTON;
		m_NumberOfLoadImages=N/m_nPages;
	}
	m_iPage=0;

	ShowPage(m_iPage);
}
#endif

/******************************class CAGmagicISDemoProp*********************/

#if AGMAGIC_SUPPORT_MFC
/////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoProp dialog


CAGmagicISDemoProp::CAGmagicISDemoProp(CWnd* pParent /*=NULL*/)
	: CDialog(CAGmagicISDemoProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAGmagicISDemoProp)
	m_Features = _T("");
	m_FileName = _T("");
	m_FilePath = _T("");
	m_ID = 0;
	m_Similarity = 0.0;
	//}}AFX_DATA_INIT
}


void CAGmagicISDemoProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGmagicISDemoProp)
	DDX_Text(pDX, IDC_PROP_FEATURES, m_Features);
	DDX_Text(pDX, IDC_PROP_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_PROP_FILEPATH, m_FilePath);
	DDX_Text(pDX, IDC_PROP_ID, m_ID);
	DDX_Text(pDX, IDC_PROP_SIMILARITY, m_Similarity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAGmagicISDemoProp, CDialog)
	//{{AFX_MSG_MAP(CAGmagicISDemoProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoProp message handlers

BOOL CAGmagicISDemoProp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CAGmagicISDemoSearchResultDlg* pParentDlg=(CAGmagicISDemoSearchResultDlg*)GetParent();

	CAGint32Array idxs;
	pParentDlg->m_SearchResultCtrl.GetAllSelectedIdxs(&idxs);
	if(idxs.GetSize()==1)
	{
		m_FilePath=pParentDlg->m_SearchResultCtrl.GetItemText(idxs.GetAt(0),0);
		m_FileName=m_FilePath.Mid(m_FilePath.ReverseFind(AGMAGIC_DIR_SPLASH)+1);

		m_ID=(UINT)(pParentDlg->m_SearchResultCtrl.m_AGlvItems.GetAt(idxs.GetAt(0))->m_ID);
		m_Similarity=pParentDlg->m_SearchResultCtrl.m_AGlvItems.GetAt(idxs.GetAt(0))->m_pAGmagicElement->GetValue();

		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
#endif

/*******************************class CAGsemanticOptionsDlg*******************************/

#if AGMAGIC_SUPPORT_MFC

/////////////////////////////////////////////////////////////////////////////
// CAGinsertTreeItemDlg dialog


CAGinsertTreeItemDlg::CAGinsertTreeItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAGinsertTreeItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAGinsertTreeItemDlg)
	m_Name = _T("");
	m_Desc = _T("");
	//}}AFX_DATA_INIT
}


void CAGinsertTreeItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGinsertTreeItemDlg)
	DDX_Text(pDX, IDC_NAME_ITEM, m_Name);
	DDX_Text(pDX, IDC_DESC_ITEM, m_Desc);
	//}}AFX_DATA_MAP
}
agtchar* CAGinsertTreeItemDlg::GetName()
{
	if(m_Name.IsEmpty())	return NULL;
	return m_Name.GetBuffer(0);
}
agtchar* CAGinsertTreeItemDlg::GetDesc()
{
	if(m_Desc.IsEmpty())	return NULL;
	return m_Desc.GetBuffer(0);
}


BEGIN_MESSAGE_MAP(CAGinsertTreeItemDlg, CDialog)
	//{{AFX_MSG_MAP(CAGinsertTreeItemDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGinsertTreeItemDlg message handlers

void CAGinsertTreeItemDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(GetName()==NULL || GetDesc()==NULL)
	{
		MessageBox(_T("Name or Description empty"),_T("Error"),MB_OK|MB_ICONSTOP);
		return;
	}
	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CAGsemanticOptionsDlg dialog

CAGsemanticOptionsDlg::CAGsemanticOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAGsemanticOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAGsemanticOptionsDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_NumberOfCandidate = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_INFO_TIP);
	m_pSelectedItem=NULL;
	m_ImageType=0;
}
void CAGsemanticOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGsemanticOptionsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_IMAGETYPE, m_cmbImageType);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_OKNUS, m_btOKNUS);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Text(pDX, IDC_NUMBER_CANDIDATE, m_NumberOfCandidate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAGsemanticOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CAGsemanticOptionsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()

	ON_MESSAGE(OT_FS_NOTIFY_APPLY, WM_ApplyButton)
	ON_NOTIFY(OT_NOTIFY_DELETEITEM, IDC_SEMANTICS_OPTIONS_TREE, OnTreeDeleteItem)
	ON_NOTIFY(OT_NOTIFY_ITEMCHANGED, IDC_SEMANTICS_OPTIONS_TREE, OnTreeItemChanged)
	ON_NOTIFY(OT_NOTIFY_CONTEXTMENU, IDC_SEMANTICS_OPTIONS_TREE, OnTreeContextMenu)

	ON_COMMAND(ID_INSERT_OPTIONS_TREE_ITEM, OnInsertOptionsTreeItem)
	ON_COMMAND(ID_DELETE_OPTIONS_TREE_ITEM, OnDeleteOptionsTreeItem)
	ON_CBN_SELCHANGE(IDC_IMAGETYPE, OnSelchangeImageType)

	ON_BN_CLICKED(IDC_OKNUS, OnOkNUS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGsemanticOptionsDlg message handlers

BOOL CAGsemanticOptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

/////////////////////Khoi tao cac control//////////////////////
	//Cai dat cac control
	m_btOK.SetIcon(IDI_AGMAGICIP_G,BS_LEFT);
	m_btOKNUS.SetIcon(IDI_AGMAGICIP_G,BS_LEFT);
	m_btCancel.SetIcon(IDI_AGMAGICIP_G,BS_LEFT);
	
///////////////////////////////Tao cay///////////////////////
	// Declare variables
	CRect rcClient;
	DWORD dwStyle, dwOptions;

	// Get the clients rectangle
	GetClientRect(rcClient);
	rcClient.bottom -=80;	

	// Setup the window style
	dwStyle = WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// Setup the tree options 
	// OT_OPTIONS_SHOWINFOWINDOW
	dwOptions = OT_OPTIONS_SHADEEXPANDCOLUMN | OT_OPTIONS_SHADEROOTITEMS | OT_OPTIONS_SHOWINFOWINDOW;

	// Create tree options
	if (m_otTree.Create(dwStyle, rcClient, this, dwOptions, IDC_SEMANTICS_OPTIONS_TREE) == FALSE)
	{
		TRACE0("Failed to create options control.\r\n");
		return FALSE;
	}

	// Want to be notified
	m_otTree.SetNotify(TRUE, this);
	m_otTree.DBCnnAttach(pMainWnd->DBCnnGet());

	UpdateImageType();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CAGsemanticOptionsDlg::UpdateImageType()
{
	if(m_cmbImageType.GetSafeHwnd()==NULL) return;

	CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();
	
	CAGimageDBItemTypes item_types;
	item_types.DBCnnAttach(pMainWnd->DBCnnGet());
	item_types.DBReadAll();
	agint32				n=item_types.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		m_cmbImageType.AddString(item_types.GetAt(i)->m_Name);
	#if AGMAGIC_MFC_VER < 0x0700
		m_cmbImageType.SetItemData(i,item_types.GetAt(i)->m_ID);
	#else
		m_cmbImageType.SetItemData(i,(DWORD_PTR)item_types.GetAt(i)->m_ID);
	#endif
	}
	m_cmbImageType.SetCurSel(-1);
	m_otTree.DeleteAllItems();
}
void CAGsemanticOptionsDlg::OnSelchangeImageType()
{
	// TODO: Add your control notification handler code here
	agint32 idx=m_cmbImageType.GetCurSel();
	if(idx==CB_ERR || idx==-1) return;

	// Setup options tree
	CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();
	CAGimageSemanticTree		semantic_tree;

	semantic_tree.DBCnnAttach(pMainWnd->DBCnnGet());
	semantic_tree.DBBuild(m_cmbImageType.GetItemData(idx));
	m_otTree.Import(&semantic_tree);

	COptionTreeItem*	otiRoot=m_otTree.GetRootItem()->GetChild();
	if(otiRoot)			otiRoot->SetRootBackgroundColor(RGB(0, 150, 200));
	m_otTree.ExpandAllItems();
	//m_otTree.RefreshItems();

}
aguint_id CAGsemanticOptionsDlg::GetImageType()
{
	return m_ImageType;
}

void CAGsemanticOptionsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAGsemanticOptionsDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAGsemanticOptionsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CAGsemanticOptionsDlg::PreTranslateMessage(MSG* pMsg) 
{
	return CDialog::PreTranslateMessage(pMsg);
}

void CAGsemanticOptionsDlg::OnSize(UINT nType, int cx, int cy) 
{
	// Resize the control
	if ((cx > 0) && (cy > 0))
	{
		if (::IsWindow(m_otTree.GetSafeHwnd()))
		{
			m_otTree.MoveWindow(0, 0, cx, cy);
		}
	}
	
	CDialog::OnSize(nType, cx, cy);	
}

LRESULT CAGsemanticOptionsDlg::WM_ApplyButton(WPARAM wParam, LPARAM lParam)
{
	// Declare variables
	UINT uID;

	// Get incoming ID
	uID = (UINT) wParam;

	return 0;
}

void CAGsemanticOptionsDlg::OnTreeDeleteItem(NMHDR *pNotifyStruct, LRESULT *plResult)
{
	LPNMOPTIONTREE pNMPropTree = (LPNMOPTIONTREE)pNotifyStruct;
	*plResult=0;

	// Validate
	if (pNMPropTree == NULL)
	{
		*plResult=1;
		return ;
	}

	// pNMPropTree->otiItem is the item where CM was clicked or NULL
	return ;
}
void CAGsemanticOptionsDlg::OnTreeItemChanged(NMHDR* pNotifyStruct, LRESULT* plResult)
{
	// Declare variables
	LPNMOPTIONTREE pNMOptionTree = (LPNMOPTIONTREE)pNotifyStruct;
	*plResult=0;

	// Validate
	if (pNMOptionTree == NULL)
	{
		*plResult=1;
		return ;
	}

	// pNMPropTree->otiItem is the item where CM was clicked or NULL
	return;
}
void CAGsemanticOptionsDlg::OnTreeContextMenu(NMHDR *pNotifyStruct, LRESULT *plResult)
{
	LPNMOPTIONTREE pNMPropTree = (LPNMOPTIONTREE)pNotifyStruct;
	*plResult=0;

	// Validate
	if (pNMPropTree == NULL || pNMPropTree->otiItem==NULL)
	{
		*plResult=1;
		return;
	}

	CAGsemanticOptionsTreeItem*		item=(CAGsemanticOptionsTreeItem*)(pNMPropTree->otiItem);
	if(!item->IsSelected())
	{
		*plResult=1;
		return;
	}
	m_pSelectedItem=item;

	// pNMPropTree->otiItem is the item where CM was clicked or NULL
	BCMenu	OptionsTreeItemContextMenu;
	OptionsTreeItemContextMenu.LoadMenu(IDM_OPTIONS_TREE_ITEM_CONTEXT);
	//OptionsTreeItemContextMenu.LoadToolbar(IDM_OPTIONS_TREE_ITEM_CONTEXT_TOOLBAR);

	CMenu*	pContextMenu=OptionsTreeItemContextMenu.GetSubMenu(0);
	CPoint	pos(0,0);

	GetCursorPos(&pos);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pos.x,pos.y,this);

	return;
}
void CAGsemanticOptionsDlg::OnInsertOptionsTreeItem()
{
	if(m_pSelectedItem==NULL) return;

	CAGinsertTreeItemDlg InsertDlg;
	if(InsertDlg.DoModal()==IDOK)
	{
		CAGsemanticOptionsTreeItem* item=m_otTree.InsertItemEx(InsertDlg.GetName(), InsertDlg.GetDesc(), m_pSelectedItem, agtrue);
	}
	
	MessageBox(_T("InsertOptionsTreeItem"));
	m_pSelectedItem=NULL;
}
void CAGsemanticOptionsDlg::OnDeleteOptionsTreeItem()
{
	if(m_pSelectedItem==NULL) return;
	COptionTreeItem* pRoot=m_otTree.GetRootItem();
	COptionTreeItem* pParent=((COptionTreeItem*)m_pSelectedItem)->GetParent();
	if(pParent==pRoot)
		MessageBox(_T("Can not delete root"));
	else
	{
		m_otTree.DeleteItem(m_pSelectedItem);
	}
	m_pSelectedItem=NULL;
}
void CAGsemanticOptionsDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{		
	// Set minimum and maximum dimensions
	lpMMI->ptMinTrackSize.x = 425;
	lpMMI->ptMinTrackSize.y = 450;

	CDialog::OnGetMinMaxInfo(lpMMI);
}
void CAGsemanticOptionsDlg::OnOK()
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_SemanticTree.Destroy();
	m_SemanticTree.DBCnnAttach(m_otTree.DBCnnGet());

	agint32 idx=m_cmbImageType.GetCurSel();
	if(idx==CB_ERR || idx==-1)	m_ImageType=0;
	else						m_ImageType=m_cmbImageType.GetItemData(idx);

	if(m_ImageType!=0)
	{
		m_otTree.Export(&m_SemanticTree);

		agtchar* szTreeXMLPath=NULL;
		CAGmagicStrUtil::private_tcscat(szTreeXMLPath,CAGmagicConfUtil::AGmagic_GlobalCurDir,agtrue);
		CAGmagicStrUtil::private_tcscat(szTreeXMLPath,AGMAGIC_DIR_SPLASH_STR,agtrue);
		CAGmagicStrUtil::private_tcscat(szTreeXMLPath,_T(".."),agtrue);
		CAGmagicStrUtil::private_tcscat(szTreeXMLPath,AGMAGIC_DIR_SPLASH_STR,agtrue);
		CAGmagicStrUtil::private_tcscat(szTreeXMLPath,_T("temp"),agtrue);
		CAGmagicStrUtil::private_tcscat(szTreeXMLPath,AGMAGIC_DIR_SPLASH_STR,agtrue);
		CAGmagicStrUtil::private_tcscat(szTreeXMLPath,_T("tree.xml"),agtrue);
		
		m_SemanticTree.OutputXML(szTreeXMLPath);

		if(szTreeXMLPath) free(szTreeXMLPath); szTreeXMLPath=NULL;
	}
//////////////////////////////

	CDialog::OnOK();
}
void CAGsemanticOptionsDlg::OnOkNUS() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_SemanticTree.Destroy();
	m_SemanticTree.DBCnnAttach(m_otTree.DBCnnGet());

	agint32 idx=m_cmbImageType.GetCurSel();
	if(idx==CB_ERR || idx==-1)	m_ImageType=0;
	else						m_ImageType=m_cmbImageType.GetItemData(idx);
	
	CDialog::OnOK();
}
agint32 CAGsemanticOptionsDlg::GetNumberOfCandidate() 
{
	return m_NumberOfCandidate;
}

void CAGsemanticOptionsDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGsemanticCheckedTreeDlg************************************/
#if AGMAGIC_SUPPORT_MFC
/////////////////////////////////////////////////////////////////////////////
// CAGsemanticCheckedTreeDlg dialog


CAGsemanticCheckedTreeDlg::CAGsemanticCheckedTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAGsemanticCheckedTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAGsemanticCheckedTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pNoFreeSemanticTree=NULL;
}


void CAGsemanticCheckedTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGsemanticCheckedTreeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
void CAGsemanticCheckedTreeDlg::SetSemanticTree(CAGimageSemanticTree* pNoFreeSemanticTree)
{
	m_pNoFreeSemanticTree=pNoFreeSemanticTree;
}

BEGIN_MESSAGE_MAP(CAGsemanticCheckedTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CAGsemanticCheckedTreeDlg)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGsemanticCheckedTreeDlg message handlers

void CAGsemanticCheckedTreeDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_SemanticCheckedTree.UpdateSemanticWeight();
	CDialog::OnOK();
}

BOOL CAGsemanticCheckedTreeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.bottom -=45;	
	m_SemanticCheckedTree.CreateEx(rcClient, this, IDC_SEMANTIC_CHECKED_TREE);
	if(m_pNoFreeSemanticTree)
		m_SemanticCheckedTree.Import(m_pNoFreeSemanticTree);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAGsemanticCheckedTreeDlg::OnSize(UINT nType, int cx, int cy) 
{
	// Resize the control
	if ((cx > 0) && (cy > 0))
	{
		if (::IsWindow(m_SemanticCheckedTree.GetSafeHwnd()))
		{
			m_SemanticCheckedTree.MoveWindow(0, 0, cx, cy);
		}
	}
	
	CDialog::OnSize(nType, cx, cy);	
}
void CAGsemanticCheckedTreeDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{		
	// Set minimum and maximum dimensions
	lpMMI->ptMinTrackSize.x = 425;
	lpMMI->ptMinTrackSize.y = 450;

	CDialog::OnGetMinMaxInfo(lpMMI);
}
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CAGmagicISDemoMainFrame*********************/

#if AGMAGIC_SUPPORT_MFC
IMPLEMENT_DYNAMIC(CAGmagicISDemoMainFrame, CAGmmMainFrame)

BEGIN_MESSAGE_MAP(CAGmagicISDemoMainFrame, CAGmmMainFrame)
	//{{AFX_MSG_MAP(CAGmagicISDemoMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_ACTIVATE()
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	ON_MESSAGE(AGMAGICIP_WM_SEARCH_RESULT, OnReceivedSearchResult)
	ON_MESSAGE(AGMAGICIP_WM_LISTCTRL_UPDATE_DOCUMENT_ALREADY, OnListCtrlUpdateDocumentAlready)
	ON_MESSAGE(AGMAGICIP_WM_REQUIRE_SEND_ACCESS_FREQ_AGAIN, OnRequireSendAccessFreqAgain)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_CONFIG_SERVER, OnConfigServer)
	ON_COMMAND(IDC_CREATE_DB, OnCreateDB)
	ON_COMMAND(IDC_START_SERVER, OnStartServer)
	ON_COMMAND(IDC_STOP_SERVER, OnStopServer)

	ON_COMMAND(IDC_BROWSE, OnBrowse)
	ON_COMMAND(IDC_SEARCH, OnSearch)
	ON_COMMAND(IDC_FEEDBACK, OnFeedback)
	ON_COMMAND(ID_SEARCH_RESULT_USER_FEEDBACK, OnFeedback)
	ON_COMMAND(ID_SEARCH_RESULT_USER_FEEDBACK_ADVANCED, OnFeedbackAdvanced)
	ON_COMMAND(ID_SEARCH_RESULT_USER_OPEN, OnSearchResultUserOpen)
	ON_COMMAND(ID_SEARCH_RESULT_USER_OPEN_DIALOG, OnSearchResultUserOpenDialog)
	ON_COMMAND(ID_SEARCH_RESULT_USER_PROPERTIES, OnSearchResultUserProperties)

	ON_COMMAND(ID_MAINFRAME_SHOW_SERVER, OnMainframeShowServer)
	ON_COMMAND(ID_MAINFRAME_SHOW_OUTPUT, OnMainframeShowOutput)
	ON_COMMAND(ID_MAINFRAME_SHOW_RESULT, OnMainframeShowResult)

	ON_UPDATE_COMMAND_UI(IDC_CONFIG_SERVER, OnUpdateConfigServer)
	ON_UPDATE_COMMAND_UI(IDC_CREATE_DB, OnUpdateCreateDB)
	ON_UPDATE_COMMAND_UI(IDC_START_SERVER, OnUpdateStartServer)
	ON_UPDATE_COMMAND_UI(IDC_STOP_SERVER, OnUpdateStopServer)

	ON_UPDATE_COMMAND_UI(IDC_BROWSE, OnUpdateBrowse)
	ON_UPDATE_COMMAND_UI(IDC_SEARCH, OnUpdateSearch)
	ON_UPDATE_COMMAND_UI(IDC_FEEDBACK, OnUpdateFeedback)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_USER_FEEDBACK, OnUpdateFeedback)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_USER_FEEDBACK_ADVANCED, OnUpdateFeedbackAdvanced)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_USER_OPEN, OnUpdateSearchResultUserOpen)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_USER_OPEN_DIALOG, OnUpdateSearchResultUserOpenDialog)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_RESULT_USER_PROPERTIES, OnUpdateSearchResultUserProperties)

	ON_UPDATE_COMMAND_UI(ID_MAINFRAME_SHOW_SERVER, OnUpdateMainframeShowServer)
	ON_UPDATE_COMMAND_UI(ID_MAINFRAME_SHOW_OUTPUT, OnUpdateMainframeShowOutput)
	ON_UPDATE_COMMAND_UI(ID_MAINFRAME_SHOW_RESULT, OnUpdateMainframeShowResult)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoMainFrame construction/destruction
CAGmagicISDemoMainFrame::CAGmagicISDemoMainFrame() : CAGmmMainFrame()
{
	m_pProgressDoc=NULL;
	m_ProgressTimerID=0;
	m_nProgress=0;

	m_bSearchingBusy=agfalse;
	m_pSearchDoc=NULL;
	m_bUpdatingSearchResults=agfalse;
	
	m_bIsInsertDBIntel=agtrue;

	m_pAGmmTrainingSystem=NULL;
	m_pAGmmSearchingSystem=NULL;
	m_pISControlBar=NULL;
	m_pServerDlg=NULL;
	m_pOutputBar=NULL;
	m_pSearchResultDlg=NULL;

	m_szServerNotice=NULL;
	CAGmagicStrUtil::private_tcscat(m_szServerNotice,_T("If server is running, you can search but \n \
			you can not configure server. You can just configure when server stopped"),agtrue);
}
CAGmagicISDemoMainFrame::~CAGmagicISDemoMainFrame()
{
	m_pSearchDoc=NULL;
	if(m_pISControlBar)		delete m_pISControlBar;
	if(m_pOutputBar)		delete m_pOutputBar;

	if(m_szServerNotice)	free(m_szServerNotice);
}
void* CAGmagicISDemoMainFrame::DBCnnAttach(agtchar szDBCnnStr[])
{
	void* old=m_pDBCnnI;

	CAGmagicDBUtil::CnnCreate(m_pDBCnnI, szDBCnnStr, &CAGmagicConfUtil::AGmagic_GlobalDBCnnConfig, agtrue);
	ASSERT(m_pDBCnnI!=NULL);
	m_pAGmmTrainingSystem->DBCnnAttach(m_pDBCnnI);
	m_pAGmmSearchingSystem->DBCnnAttach(m_pDBCnnI);
	return old;
}
void* CAGmagicISDemoMainFrame::DBCnnDetach()//phai Release
{
	if(m_pDBCnnI==NULL)			return NULL;
	if(m_pAGmmTrainingSystem)	m_pAGmmTrainingSystem->DBCnnDetach();
	if(m_pAGmmSearchingSystem)	m_pAGmmSearchingSystem->DBCnnDetach();
	CAGmagicDBUtil::CnnDestroy(m_pDBCnnI, agtrue);
	ASSERT(m_pDBCnnI==NULL);
	return NULL;
}
CAGmagicISDemoDoc* CAGmagicISDemoMainFrame::GetDocument(aguint_id DocID)
{
	POSITION template_pos = AfxGetApp()->GetFirstDocTemplatePosition();
	while (template_pos != NULL)
	{
		CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate(template_pos);
		ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CDocTemplate)));

		POSITION doc_pos = pTemplate->GetFirstDocPosition();
		while (doc_pos != NULL)
		{
			CAGmagicISDemoDoc* pDoc = (CAGmagicISDemoDoc*) pTemplate->GetNextDoc(doc_pos);
			if(!pDoc->IsKindOf(RUNTIME_CLASS(CAGmagicISDemoDoc)))
				continue;
			if(pDoc->m_DocID==DocID) return pDoc;
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////
int CAGmagicISDemoMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CAGmmMainFrame::OnCreate(lpCreateStruct)==-1)
		return -1;
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ISDEMO_MAIN);
	HICON hOldBigIcon=SetIcon(hIcon, TRUE);			// Set big icon
	HICON hOldSmallIcon=SetIcon(hIcon, FALSE);		// Set small icon
	//if(hIcon)			::DestroyIcon(hIcon);
	if(hOldBigIcon)		::DestroyIcon(hOldBigIcon);
	if(hOldSmallIcon)	::DestroyIcon(hOldSmallIcon);
	SetWindowText(_T("AGmagicIS-Demo"));

/////////////////////////////////////////////////////////////////
	InitServer();

	EnableDocking(CBRS_ALIGN_ANY);
#ifdef _SCB_REPLACE_MINIFRAME
    m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
#endif //_SCB_REPLACE_MINIFRAME

	m_pISControlBar=new CAGmagicISDemoControlBar(this);
	//m_pServerDlg->ShowWindow(SW_HIDE);
	m_pOutputBar=new CAGmagicISDemoOutputBar(this);
	m_pSearchResultDlg=new CAGmagicISDemoSearchResultDlg(this);

	//m_pILeoMsgBox.CreateInstance(__uuidof(MsgBox));
	//if(m_pILeoMsgBox.GetInterfacePtr())	m_pILeoMsgBox->InitLeoMsgBox(255, -1, 0);	
	
	if(m_pServerDlg)
	{
		m_pServerDlg->m_SearchingSystemNotice.Invalidate();
		m_pServerDlg->m_TrainingSystemNotice.Invalidate();
	}
	//LoadBarState(AfxGetApp()->m_pszProfileName);
	return 0;
}
void CAGmagicISDemoMainFrame::OnDestroy()
{
	CAGmmMainFrame::OnDestroy();
	CleanupServer();
	
	// TODO: Add your message handler code here
	//SaveBarState(AfxGetApp()->m_pszProfileName);
}
void CAGmagicISDemoMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CAGmmMainFrame::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	AdjustChildWndLayout();
}
void CAGmagicISDemoMainFrame::OnMove(int x, int y) 
{
	CAGmmMainFrame::OnMove(x, y);
	
	// TODO: Add your message handler code here
	AdjustChildWndLayout();
}
void CAGmagicISDemoMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CAGmmMainFrame::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	if(m_bUpdatingSearchResults || m_bSearchingBusy)
		SetCapture();
	else
		ReleaseCapture();
		
}
void CAGmagicISDemoMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent=(UINT)m_ProgressTimerID)
	{
		if(m_pProgressDoc==NULL)	return;
		POSITION		pos=m_pProgressDoc->GetFirstViewPosition();
		CView*			pView=m_pProgressDoc->GetNextView(pos);
		if(pView==NULL)	return;

		m_nProgress=(m_nProgress==0)? 10: m_nProgress;
		pView->SendMessage(WM_USER_PROGRESS,m_nProgress,0);
		m_nProgress +=10;
		if(m_nProgress>=100)	m_nProgress=10;
	}
	CAGmmMainFrame::OnTimer(nIDEvent);
}
void CAGmagicISDemoMainFrame::OnContextMenu(CWnd* pWnd, CPoint pos) 
{
	// TODO: Add your message handler code here
	BCMenu	sw_context_menu;
	sw_context_menu.LoadMenu(IDM_MAINFRAME_SHOW_CONTROL_CONTEXT);
	//sw_context_menu.LoadToolbar(IDT_MAINFRAME_SHOW_CONTROL_CONTEXT);

	CPoint point=pos;
	ScreenToClient(&point);
	CMenu *pContextMenu=sw_context_menu.GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pos.x,pos.y,this);
}
void CAGmagicISDemoMainFrame::AdjustChildWndLayout() 
{
	CRect clientRC;
	GetClientRect(&clientRC);

	if(m_pSearchResultDlg)
	{
		CRect search_resultRC;
		m_pSearchResultDlg->GetWindowRect(&search_resultRC);
		CPoint search_resultPos(clientRC.right-search_resultRC.Width(), clientRC.top);
		ClientToScreen(&search_resultPos);
		m_pSearchResultDlg->SetWindowPos(NULL,search_resultPos.x,search_resultPos.y+30,0,0,SWP_NOSIZE);
	}
	if(m_pServerDlg)
	{
		CRect servRC;
		m_pServerDlg->GetWindowRect(&servRC);
		CPoint servPos(clientRC.right-servRC.Width(), clientRC.bottom-servRC.Height());
		ClientToScreen(&servPos);
		m_pServerDlg->SetWindowPos(NULL,servPos.x,servPos.y-20,0,0,SWP_NOSIZE);
	}
}
void CAGmagicISDemoMainFrame::BeginProgress()
{
	if(m_pProgressDoc!=NULL || m_ProgressTimerID!=0)	return;
	CAGmagicISDemoDoc*		pDoc=(CAGmagicISDemoDoc*)GetActiveFrame()->GetActiveDocument();
	if(pDoc)
	{
		if(pDoc->hThread)		return;

		m_ProgressTimerID=SetTimer(101,500,NULL);
		if(m_ProgressTimerID!=0)
		{
			m_nProgress=0;
			m_pProgressDoc=pDoc;
			m_pProgressDoc->Stopwatch(0);
		}
	}
}
void CAGmagicISDemoMainFrame::EndProgress()
{
	if(m_pProgressDoc==NULL || m_ProgressTimerID==0)	return;
	KillTimer((UINT_PTR)m_ProgressTimerID);
	m_ProgressTimerID=0;
	m_nProgress=0;

	POSITION	pos=m_pProgressDoc->GetFirstViewPosition();
	CView*		pView=m_pProgressDoc->GetNextView(pos);
	if(pView)
	{
		pView->SendMessage(WM_USER_PROGRESS,100,0);
		pView->SendMessage(WM_USER_PROGRESS,0,0);
	}

	m_pProgressDoc->Stopwatch(1);
	m_pProgressDoc->UpdateStatusBar();
	m_pProgressDoc=NULL;
}
void CAGmagicISDemoMainFrame::SetAllDocBusy(agbool bBusy)
{
	POSITION template_pos = AfxGetApp()->GetFirstDocTemplatePosition();
	while (template_pos != NULL)
	{
		CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate(template_pos);
		ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CDocTemplate)));

		POSITION doc_pos = pTemplate->GetFirstDocPosition();
		while (doc_pos != NULL)
		{
			CAGmagicISDemoDoc* pDoc = (CAGmagicISDemoDoc*) pTemplate->GetNextDoc(doc_pos);
			if(!pDoc->IsKindOf(RUNTIME_CLASS(CAGmagicISDemoDoc)))
				continue;
			pDoc->m_bBusy=bBusy;
		}
	}
	{
		POST_OUTPUT_NOTICE(this,_T("Notice Busy for All document"))
	}
}

LRESULT CAGmagicISDemoMainFrame::OnReceivedSearchResult(WPARAM wParam, LPARAM lParam)
{
	if(m_pSearchDoc==NULL)	throw _T("Fatal Error");

	//wParam: so thu tu cua ket qua tim kiem, =-1:ket qua tim kiem da het
	//lParam
	CAGinteractImagesMsg* pSearchResultAGinteractImagesMsg=(CAGinteractImagesMsg*)lParam;
	if(wParam==-1)//da het
	{
		EndProgress();

		if(pSearchResultAGinteractImagesMsg)
		{
			if(pSearchResultAGinteractImagesMsg->IsDeleteMeInProc())
				delete pSearchResultAGinteractImagesMsg;
		}

		agint32	nTotalFoundImages=0;
		agint32	n=m_pSearchDoc->m_SearchResults.GetSize();
		for(agint32 i=0; i<n; i++)
			nTotalFoundImages +=m_pSearchDoc->m_SearchResults.GetAt(i)->GetSize();

		agtchar szSearchFinish[1024];
		_stprintf(szSearchFinish,_T("User's searching require Finished. There are %lu Image(s) found"),nTotalFoundImages);
		MessageBox(szSearchFinish,_T("Finish"),MB_OK|MB_ICONINFORMATION);
		{
			POST_OUTPUT_NOTICE(this,szSearchFinish)
		}

		if(nTotalFoundImages > 0)
		{
			if(m_pSearchDoc->m_QueryImageID==0)
			{
				if(
					MessageBox(_T("Do you want to store this Image to Database for after searching ?"),
					_T("Notice"),
					MB_OKCANCEL|MB_DEFBUTTON2|MB_ICONQUESTION)==IDOK
				  )
				{
					//Add m_QueryImageID vao CSDL
					POST_OUTPUT_NOTICE(this,_T("Inserting Image to Database..."))
					m_pSearchDoc->OnDatabaseInsert();
				}
			}
			if(m_pSearchDoc->m_QueryImageID!=0)
			{
				CAGuserAccessMsgs*	pAGuserAccessMsgs=new CAGuserAccessMsgs();
				pAGuserAccessMsgs->m_bDeleteMeInProc=agtrue;

				CAGuserAccessMsg*	pAGuserAccessMsg=new CAGuserAccessMsg();
				pAGuserAccessMsg->m_accessk=new AGUSER_ACCESS_FREQUENCY_ITEM();
				pAGuserAccessMsg->m_accessk->kID=m_pSearchDoc->m_QueryImageID;
				pAGuserAccessMsg->m_accessk->nAccessed=1;
				pAGuserAccessMsg->m_accessk->tAccessed=time(NULL);
				pAGuserAccessMsgs->Add(pAGuserAccessMsg);

				{
					agtchar szNotice[1024];
					_stprintf(szNotice,_T("Feedback User Access Frequency ACCESS%lu=%lu (form ACCESSk)"),
							(UINT)(pAGuserAccessMsg->m_accessk->kID),
							(UINT)(pAGuserAccessMsg->m_accessk->nAccessed)
							);
					POST_OUTPUT_NOTICE(this,szNotice)
					POST_OUTPUT_NOTICE(this,_T("Loading Found Image(s)..."))

				}
				m_pAGmmTrainingSystem->PostThreadMessage(AGMAGICIP_WM_RECEIVED_USER_ACCESS, 0, (LPARAM)pAGuserAccessMsgs);
			}
		}

		m_bSearchingBusy=agfalse;
		SetAllDocBusy(agfalse);
		if(!m_bUpdatingSearchResults) ReleaseCapture();
		m_pSearchResultDlg->SetDocument(m_pSearchDoc);

		return 0;
	}
	ASSERT(pSearchResultAGinteractImagesMsg!=NULL);
	if(wParam==0)//ket qua tim kiem dau tien
	{
		m_pSearchDoc->m_SearchResults.RemoveAll();
		m_pSearchDoc->m_SearchResults2.RemoveAll();
	}
	ASSERT(pSearchResultAGinteractImagesMsg->GetSize()>0);

	CAGoutSimPtrArray*	pAGoutSimPtrArray=new CAGoutSimPtrArray();
	pSearchResultAGinteractImagesMsg->CopyAGmagicElementsTo(pAGoutSimPtrArray);
	ASSERT(pAGoutSimPtrArray->GetSize()>0);
	ASSERT(pAGoutSimPtrArray->GetSize()==pSearchResultAGinteractImagesMsg->GetSize());
	m_pSearchDoc->m_SearchResults.Add(pAGoutSimPtrArray);
	m_pSearchDoc->m_SearchResults2.Add(pSearchResultAGinteractImagesMsg);
	{
		agtchar szOutput[1024];
		_stprintf(szOutput,_T("Have just recive %lu Image(s) found From searching System"),pSearchResultAGinteractImagesMsg->GetSize());
		POST_OUTPUT_NOTICE(this,szOutput)
	}
	return 0;
}
LRESULT CAGmagicISDemoMainFrame::OnListCtrlUpdateDocumentAlready(WPARAM wParam, LPARAM lParam)
{
	{
		POST_OUTPUT_NOTICE(this,_T("Load Found Image(s) Already"))
	}

	m_bUpdatingSearchResults=agfalse;
	if(!m_bSearchingBusy)	ReleaseCapture();
	return 0;
}
LRESULT CAGmagicISDemoMainFrame::OnRequireSendAccessFreqAgain(WPARAM wParam, LPARAM lParam)
{
	{
		POST_OUTPUT_NOTICE(this,_T("Receive Require Send Access Frequency again"))
	}

	CAGuserAccessFrequencyVec*	access=(CAGuserAccessFrequencyVec*)lParam;
	if(access==NULL || access->GetSize()==0)	return 0;

	POSITION template_pos = AfxGetApp()->GetFirstDocTemplatePosition();
	while (template_pos != NULL)
	{
		CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate(template_pos);
		ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CDocTemplate)));

		POSITION doc_pos = pTemplate->GetFirstDocPosition();
		while (doc_pos != NULL)
		{
			CAGmagicISDemoDoc* pDoc = (CAGmagicISDemoDoc*) pTemplate->GetNextDoc(doc_pos);
			if(!pDoc->IsKindOf(RUNTIME_CLASS(CAGmagicISDemoDoc)))
				continue;
			if(pDoc->m_DocID==0 || access->m_aRelatedImageID.LSearch(pDoc->m_DocID)==-1)
				continue;

			CAGuserAccessMsgs*	pAGuserAccessMsgs=new CAGuserAccessMsgs();
			pAGuserAccessMsgs->m_bDeleteMeInProc=agtrue;

			CAGuserAccessMsg*	pAGuserAccessMsg=new CAGuserAccessMsg();
			pAGuserAccessMsg->m_accessk=new AGUSER_ACCESS_FREQUENCY_ITEM();
			pAGuserAccessMsg->m_accessk->kID=pDoc->m_DocID;
			pAGuserAccessMsg->m_accessk->nAccessed=1;
			pAGuserAccessMsg->m_accessk->tAccessed=time(NULL);
			pAGuserAccessMsgs->Add(pAGuserAccessMsg);
			m_pAGmmTrainingSystem->PostThreadMessage(AGMAGICIP_WM_RECEIVED_USER_ACCESS, 0, (LPARAM)pAGuserAccessMsgs);
		}
	}
	return 0;
}
LRESULT CAGmagicISDemoMainFrame::OnReceivedOutputNotice(WPARAM wParam, LPARAM lParam)
{
	agtchar*					szOutputNotice=(agtchar*)lParam;
	if(szOutputNotice==NULL)	return 0;

	CTime		CurTime=CTime::GetCurrentTime();
	CString		szCurTime=CurTime.Format("%I:%M:%S %p, %m-%d-%Y : ");
	agtchar*	szFullOutputNotice=NULL;
	CAGmagicStrUtil::private_tcscat(szFullOutputNotice,szCurTime.GetBuffer(0),agtrue);
	CAGmagicStrUtil::private_tcscat(szFullOutputNotice,szOutputNotice,agtrue);
	free(szOutputNotice);
	if(szFullOutputNotice==NULL)	return 0;

	
	CAGmagicISDemoOutputEdit*	pEdit=(CAGmagicISDemoOutputEdit*)(&(m_pOutputBar->m_edit));
	agint32						nLines=pEdit->GetLineCount();
	if(nLines==0 || nLines>=1000)	pEdit->SetWindowText(szFullOutputNotice);
	else
	{
		while(agtrue)
		{
			agint32		LineLength=pEdit->LineLength(nLines-1);
			if(LineLength==0)
			{
				nLines --;
				if(nLines==0)	pEdit->SetWindowText(szFullOutputNotice);
				break;
			}
			agint32		first_char_idx=pEdit->LineIndex(nLines-1);
			agint32		end_char_idx=first_char_idx + (LineLength/sizeof(agtchar)-1);
			agtchar		szLine[1024];
			memset(szLine,0,1024*sizeof(agtchar));
			pEdit->GetLine(nLines-1,szLine,1024);

			agtchar*	szInsert=NULL;
			CAGmagicStrUtil::private_tcscat(szInsert,szLine,agtrue);
			CAGmagicStrUtil::private_tcscat(szInsert,_T("\r\n"),agtrue);
			CAGmagicStrUtil::private_tcscat(szInsert,szFullOutputNotice,agtrue);

			pEdit->SetSel(first_char_idx, -1);
			pEdit->ReplaceSel(szInsert);
			free(szInsert);
			break;
		}
	}
	free(szFullOutputNotice);
	return 0;
}

void CAGmagicISDemoMainFrame::OnConfigServer()
{
	{
		POST_OUTPUT_NOTICE(this,_T("User congigure Server (Training and Searching System)"))
	}

	for(agint32 i=0; i<15; i++)
	{
		agtchar* sz=NULL;
		CAGmagicStrUtil::private_tcscat(sz,_T("AAChao cac ban "),agtrue);
		CAGmagicStrUtil::private_tcscat(sz,i,agtrue);
		if(i==11)
		{

			agint32 a=0;
			a=1;
		}
		//MessageBox(sz);
		//SendMessage(AGMAGICIP_WM_RECEIVED_OUTPUT_NOTICE,0,(LPARAM)sz);
		OnReceivedOutputNotice(0,(LPARAM)sz);
	}
}
#include "../../../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../../ip/main/AGsemantic.h"
#include "../../../../../common/include/AGEND_INCLUDE_LIBRARY.h"
void CAGmagicISDemoMainFrame::OnCreateDB()
{
	{
		POST_OUTPUT_NOTICE(this,_T("User re-create database"))
	}
	agtchar* base_url=CAGmagicConfUtil::AGmagicSampleImagesPathAbsolute();
	CAGimageDBUtil::CreateDBFromURL(base_url,DBCnnGet());

	if(base_url) free(base_url); base_url=NULL;
}
void CAGmagicISDemoMainFrame::OnStartServer()
{
	{
		POST_OUTPUT_NOTICE(this,_T("User starting Server (Training and Searching System)..."))
	}

	if(!m_pAGmmSearchingSystem->IsRunning())
	{
		m_Event.ResetEvent();
		m_pAGmmSearchingSystem->Start();
		//ngong doi thread ket thuc
		::WaitForSingleObject(m_Event.m_hObject,INFINITE);
		m_pServerDlg->m_SearchingSystemNotice.SetText3DHiliteColor(RUNNING_NOTICE_TEXT_COLOR);
		m_pServerDlg->m_SearchingSystemNotice.SetText(SEARCHING_SYSTEM_RUNNING_NOTICE_TEXT);
	}

	if(!m_pAGmmTrainingSystem->IsRunning())
	{
		m_Event.ResetEvent();
		m_pAGmmTrainingSystem->Start();
		//ngong doi thread ket thuc
		::WaitForSingleObject(m_Event.m_hObject,INFINITE);
		m_pServerDlg->m_TrainingSystemNotice.SetText3DHiliteColor(RUNNING_NOTICE_TEXT_COLOR);
		m_pServerDlg->m_TrainingSystemNotice.SetText(TRAINING_SYSTEM_RUNNING_NOTICE_TEXT);
	}

	if(!m_pAGmmTrainingSystem->IsRunning() || !m_pAGmmSearchingSystem->IsRunning())
	{
		MessageBox(_T("Cannot start server"), _T("Warning"), MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	
	//if(!IsWindowVisible())
		m_pServerDlg->ShowWindow(SW_NORMAL);
	if(!m_pServerDlg->m_AnimateNotice.IsPlaying())	m_pServerDlg->m_AnimateNotice.Draw();

	//if(m_pILeoMsgBox.GetInterfacePtr())
	//	m_pILeoMsgBox->DisplayLeoMsgBox(m_szServerNotice);
	//else
	//{
	//}
}
void CAGmagicISDemoMainFrame::OnStopServer()
{
	{
		POST_OUTPUT_NOTICE(this,_T("User stopping server (Training and Searching System)..."))
	}
	if(m_pAGmmSearchingSystem->IsRunning())
	{
		m_Event.ResetEvent();
		m_pAGmmSearchingSystem->Stop();
		//ngong doi thread ket thuc
		::WaitForSingleObject(m_Event.m_hObject,INFINITE);
		m_pServerDlg->m_SearchingSystemNotice.SetText3DHiliteColor(STOPPED_NOTICE_TEXT_COLOR);
		m_pServerDlg->m_SearchingSystemNotice.SetText(SEARCHING_SYSTEM_STOPPED_NOTICE_TEXT);
	}
	if(m_pAGmmTrainingSystem->IsRunning())
	{
		m_Event.ResetEvent();
		m_pAGmmTrainingSystem->Stop();
		//ngong doi thread ket thuc
		::WaitForSingleObject(m_Event.m_hObject,INFINITE);
		m_pServerDlg->m_TrainingSystemNotice.SetText3DHiliteColor(STOPPED_NOTICE_TEXT_COLOR);
		m_pServerDlg->m_TrainingSystemNotice.SetText(TRAINING_SYSTEM_STOPPED_NOTICE_TEXT);
	}


	if(m_pAGmmTrainingSystem->IsRunning() || m_pAGmmSearchingSystem->IsRunning())
	{
		MessageBox(_T("Cannot stop server"), _T("Warning"), MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	//if(!IsWindowVisible())
		m_pServerDlg->ShowWindow(SW_NORMAL);
	if(m_pServerDlg->m_AnimateNotice.IsPlaying())	m_pServerDlg->m_AnimateNotice.Stop();

	//if(m_pILeoMsgBox.GetInterfacePtr())
	//	m_pILeoMsgBox->DisplayLeoMsgBox(m_szServerNotice);
	//else
	//{
	//}
}

void CAGmagicISDemoMainFrame::OnBrowse()
{
	// TODO: Add your control notification handler code here
	{
		POST_OUTPUT_NOTICE(this,_T("User browse Images for searching"))
	}
	//SendMessage(WM_COMMAND,MAKEWPARAM(ID_FILE_OPEN,0));
	m_pAGmmTrainingSystem->Test();
}
void AnalyzeImagePath(CString szImagePath, CString& szBaseSampleDir, CString& szDirTypeName, CString& szImageName)
{
	szImageName.Empty();
	szBaseSampleDir.Empty();
	szDirTypeName.Empty();

	agint32		idx=szImagePath.ReverseFind(AGMAGIC_DIR_SPLASH);
	if(idx==-1)	return;

	CString		szDir=szImagePath.Mid(0,idx);
	szImageName=szImagePath.Mid(idx+1,szImagePath.GetLength()-idx-1);
	idx=szDir.ReverseFind(AGMAGIC_DIR_SPLASH);

	if(idx==-1)	szBaseSampleDir=szDir;
	else
	{
		szBaseSampleDir=szDir.Mid(0,idx);
		szDirTypeName=szDir.Mid(idx+1,szDir.GetLength()-idx-1);
	}
}
void CAGmagicISDemoMainFrame::OnSearch()
{

	{
		POST_OUTPUT_NOTICE(this,_T("User require search Image"))
	}
	
	CAGsemanticOptionsDlg		SemanticsOptionDlg;
	if(SemanticsOptionDlg.DoModal()==IDCANCEL) return;


////////////////////////////////////////////////
	CAGmagicISDemoDoc*	pDoc=(CAGmagicISDemoDoc*)GetActiveFrame()->GetActiveDocument();
	if(pDoc==NULL || pDoc->image==NULL)
	{
		MessageBox(_T("Don't load Image to search"),_T("Error"),MB_OK|MB_ICONSTOP);
		return;
	}
	CString		szImagePath=pDoc->GetPathName();
	CString		szFileName=szImagePath.Mid(szImagePath.ReverseFind(AGMAGIC_DIR_SPLASH)+1);

//Khoi tao m_QueryImageID
	if(pDoc->m_QueryImageID==0)
	{
		CAGidTypeArray ImageIDTypes;
		CAGimageDBUtil::FindImageIntel(m_pDBCnnI, szImagePath.GetBuffer(0), &ImageIDTypes);

		if(ImageIDTypes.GetSize()==1)
		{
			IMAGE_ID_TYPE	ImageIDType;
			ImageIDType=ImageIDTypes.GetAt(0);
			if(ImageIDType.ImageType==SemanticsOptionDlg.GetImageType())
			{
				pDoc->m_QueryImageID=ImageIDType.ImageID;
				pDoc->m_QueryImageType=ImageIDType.ImageType;
			}
			else
				pDoc->m_QueryImageType=SemanticsOptionDlg.GetImageType();
		}
		else
			pDoc->m_QueryImageType=SemanticsOptionDlg.GetImageType();

		pDoc->GetImage()->m_ID=pDoc->m_QueryImageID;
	}

	pDoc->SetQuerySemanticTree(NULL,agtrue);
	if(!SemanticsOptionDlg.m_SemanticTree.IsEmpty())
		pDoc->SetQuerySemanticTree(&SemanticsOptionDlg.m_SemanticTree,agtrue);

///////////////////////////////////
	CAGinteractImagesMsg* pSearchRequireAGinteractImagesMsg=new CAGinteractImagesMsg();
	CAGinteractImagesMsg::DefaultInit(pSearchRequireAGinteractImagesMsg);
	pSearchRequireAGinteractImagesMsg->DBCnnAttach(m_pDBCnnI);
	//dong nay rat quan trong
	if(!SemanticsOptionDlg.m_SemanticTree.IsEmpty())
	{
		pSearchRequireAGinteractImagesMsg->SetSemanticTree(&SemanticsOptionDlg.m_SemanticTree,agtrue);
		pSearchRequireAGinteractImagesMsg->m_CandidateCount=SemanticsOptionDlg.GetNumberOfCandidate();
	}

	if(pDoc->m_QueryImageID==0)
		pSearchRequireAGinteractImagesMsg->SetIsPassID(agfalse);
	else
		pSearchRequireAGinteractImagesMsg->SetIsPassID(agtrue);

	CAGimageDBItem* pMsgItem=new CAGimageDBItem();
	pMsgItem->SetIsStoreImage(pSearchRequireAGinteractImagesMsg->IsStoreImage());
	pMsgItem->DBCnnAttach(m_pDBCnnI);
	pMsgItem->m_ImageID=pDoc->m_QueryImageID;
	pMsgItem->m_ImageType=pDoc->m_QueryImageType;
	if(!pSearchRequireAGinteractImagesMsg->IsPassID())
	{
		if(!szFileName.IsEmpty())
			pMsgItem->AllocName(szFileName.GetBuffer(0));
		pMsgItem->AllocURL(szImagePath.GetBuffer(0));

		pMsgItem->m_pAGimageSrc=pDoc->GetImage()->CreateMe();
		pMsgItem->m_pAGimageSrc->Copy(pDoc->image);
		pMsgItem->m_pAGimageSrc->m_ID=pDoc->m_QueryImageID;
	}
	//dong nay rat quan trong
	if(!SemanticsOptionDlg.m_SemanticTree.IsEmpty())
		pMsgItem->SetSemanticTree(&SemanticsOptionDlg.m_SemanticTree,agtrue);

	pSearchRequireAGinteractImagesMsg->Add(pMsgItem);

	//gan cac thuoc tnh cho pSearchRequireAGinteractImagesMsg
	//...........
	m_bSearchingBusy=agtrue;
	m_pSearchDoc=pDoc;
	m_pSearchDoc->m_SearchResults.RemoveAll();
	m_pSearchDoc->m_SearchResults2.RemoveAll();
	SetAllDocBusy(agtrue);
	SetCapture();

	{
		POST_OUTPUT_NOTICE(this,_T("User's search require is sended to Searching System"))
	}
	BeginProgress();

///////////////goi di/////////////////////////
	m_pAGmmSearchingSystem->PostThreadMessage(AGMAGICIP_WM_SEARCH_REQUIRE, 0, (LPARAM)pSearchRequireAGinteractImagesMsg);
}
void CAGmagicISDemoMainFrame::OnFeedback()
{
	// TODO: Add your control notification handler code here
	CAGmagicISDemoDoc* pActiveDoc=(CAGmagicISDemoDoc*)(GetActiveFrame()->GetActiveDocument());
	CAGmagicISDemoDoc* pSearchResultCtrlDoc=(CAGmagicISDemoDoc*)(m_pSearchResultDlg->m_pDoc);

	if(m_pSearchDoc==NULL || pActiveDoc==NULL || pSearchResultCtrlDoc==NULL ||
	   m_pSearchDoc!=pActiveDoc || m_pSearchDoc!=pSearchResultCtrlDoc)
	{
		MessageBox(_T("Can not feedback Images"),_T("Notice"),MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	if(m_pSearchResultDlg->m_pDoc->m_QueryImageID==0)
	{
		MessageBox(_T("Can not feedback Images due not to store Query Image to Database"),_T("Notice"),MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	CAGidArray	IDs;
	m_pSearchResultDlg->m_SearchResultCtrl.GetAllSelectedIDs(&IDs);
	agint32 n=IDs.GetSize();
	if(n==0)
	{
		MessageBox(_T("You must choose one or more Images to feedback"),_T("Notice"),MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	CAGuserAccessMsgs*	pAGuserAccessMsgs=new CAGuserAccessMsgs();
	pAGuserAccessMsgs->m_bDeleteMeInProc=agtrue;

	for(agint32 i=0; i<n; i++)
	{
		aguint_id mID=IDs.GetAt(i);
		if(mID==0)	continue;

		CAGuserAccessMsg*	pAGuserAccessMsg=new CAGuserAccessMsg();
		pAGuserAccessMsg->m_usemk=new AGUSER_ACCESS_PATTERN_ITEM();
		pAGuserAccessMsg->m_usemk->mID=mID;
		pAGuserAccessMsg->m_usemk->kID=m_pSearchResultDlg->m_pDoc->m_QueryImageID;
		pAGuserAccessMsg->m_usemk->isAccess=1;
		pAGuserAccessMsg->m_usemk->tAccessed=time(NULL);
	
		//if(m_pSearchResultDlg->m_pDoc->m_pQuerySemanticTree)
		//{
		//	pAGuserAccessMsg->m_usemk->isAccess += m_pSearchResultDlg->m_pDoc->m_pQuerySemanticTree->GetNormWeight()*10;
		//}
		pAGuserAccessMsgs->Add(pAGuserAccessMsg);
		{
			agtchar szNotice[1024];
			_stprintf(szNotice,_T("User's Feeling(s) feedback Training System: USE%lu,%lu (form: USEm,k)"),
					(UINT)(pAGuserAccessMsg->m_usemk->mID),
					(UINT)(pAGuserAccessMsg->m_usemk->kID)
					);
			POST_OUTPUT_NOTICE(this,szNotice)
		}
	}

	m_pAGmmTrainingSystem->PostThreadMessage(AGMAGICIP_WM_RECEIVED_USER_ACCESS, 0, (LPARAM)pAGuserAccessMsgs);
}
void CAGmagicISDemoMainFrame::OnFeedbackAdvanced()
{
	// TODO: Add your control notification handler code here
	CAGmagicISDemoDoc* pActiveDoc=(CAGmagicISDemoDoc*)(GetActiveFrame()->GetActiveDocument());
	CAGmagicISDemoDoc* pSearchResultCtrlDoc=(CAGmagicISDemoDoc*)(m_pSearchResultDlg->m_pDoc);

	if(m_pSearchDoc==NULL || pActiveDoc==NULL || pSearchResultCtrlDoc==NULL ||
	   m_pSearchDoc!=pActiveDoc || m_pSearchDoc!=pSearchResultCtrlDoc)
	{
		MessageBox(_T("Can not feedback Images"),_T("Notice"),MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	if(m_pSearchResultDlg->m_pDoc->m_QueryImageID==0)
	{
		MessageBox(_T("Can not feedback Images due not to store Query Image to Database"),_T("Notice"),MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	CAGsemanticCheckedTreeDlg SemanticCheckedTreeDlg;
	SemanticCheckedTreeDlg.SetSemanticTree(m_pSearchDoc->m_pQuerySemanticTree);
	//SemanticCheckedTreeDlg.DoModal();
	if(SemanticCheckedTreeDlg.DoModal()==IDOK)
	{
		OnFeedback();

		CAGidArray	IDs;
		m_pSearchResultDlg->m_SearchResultCtrl.GetAllSelectedIDs(&IDs);
		agint32 n=IDs.GetSize();
		for(agint32 i=0; i<n; i++)
		{
			aguint_id mID=IDs.GetAt(i);
			m_pSearchDoc->m_pQuerySemanticTree->DBUpdateSemanticWeight(mID,agfalse);
		}

		m_pSearchDoc->m_pQuerySemanticTree->DBUpdateSemanticWeight(m_pSearchDoc->m_QueryImageID,agtrue);
	}
}
void CAGmagicISDemoMainFrame::OnSearchResultUserOpen()
{
	CAGint32Array idxs;
	m_pSearchResultDlg->m_SearchResultCtrl.GetAllSelectedIdxs(&idxs);
	agint32 n=idxs.GetSize();
	if(n>1||n==0)
	{
		MessageBox(_T("You must choose only one Image to Load"),_T("Error"),MB_OK|MB_ICONSTOP);
		return;
	}
	CString		szFilePath=m_pSearchResultDlg->m_SearchResultCtrl.GetItemText(idxs.GetAt(0),0);
	agtchar*	szFullFilePathMustFree=CAGmagicIOUtil::ConvertAndAllocFullURL(szFilePath.GetBuffer(0));
	if(szFullFilePathMustFree==NULL)	return;;
	AfxGetApp()->OpenDocumentFile(szFullFilePathMustFree);

	free(szFullFilePathMustFree);
}
void CAGmagicISDemoMainFrame::OnSearchResultUserOpenDialog()
{
	agint32 iStart=-1;
	agint32 iIndex=-1;
	while((iIndex=m_pSearchResultDlg->m_SearchResultCtrl.GetNextItem(iStart,LVNI_SELECTED))!=-1)
	{
		CAGimage*	pAGimage=m_pSearchResultDlg->m_SearchResultCtrl.m_AGlvItems.GetAt(iIndex)->m_pAGimage;
		if(pAGimage==NULL)
		{
			pAGimage=m_pSearchResultDlg->m_SearchResultCtrl.CreateAGimage();
			if(pAGimage->Load(m_pSearchResultDlg->m_SearchResultCtrl.GetItemText(iIndex,0)))
				CAGimageModalDlg::ShowAGimageDlg(IDD_AGMAGICIP_DEFAULT,pAGimage,m_pSearchResultDlg->m_SearchResultCtrl.GetItemText(iIndex,0));
			delete pAGimage;
		}
		else
			CAGimageModalDlg::ShowAGimageDlg(IDD_AGMAGICIP_DEFAULT,pAGimage,m_pSearchResultDlg->m_SearchResultCtrl.GetItemText(iIndex,0));

		iStart=iIndex;
	}
}
void CAGmagicISDemoMainFrame::OnSearchResultUserProperties()
{
	CAGmagicISDemoProp prop_dlg;
	prop_dlg.DoModal();
}
void CAGmagicISDemoMainFrame::OnMainframeShowServer()
{
	m_pServerDlg->ShowWindow(m_pServerDlg->IsWindowVisible()?SW_HIDE:SW_NORMAL);
}
void CAGmagicISDemoMainFrame::OnMainframeShowOutput()
{
	ShowControlBar(m_pOutputBar, !m_pOutputBar->IsVisible(), FALSE);
}
void CAGmagicISDemoMainFrame::OnMainframeShowResult()
{
	m_pSearchResultDlg->ShowWindow(m_pSearchResultDlg->IsWindowVisible()?SW_HIDE:SW_NORMAL);
}

void CAGmagicISDemoMainFrame::OnUpdateConfigServer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bSearchingBusy || m_bUpdatingSearchResults || m_pAGmmTrainingSystem==NULL || m_pAGmmTrainingSystem->IsRunning() || m_pAGmmSearchingSystem->IsRunning())	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoMainFrame::OnUpdateCreateDB(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bSearchingBusy || m_bUpdatingSearchResults || m_pAGmmTrainingSystem==NULL || m_pAGmmTrainingSystem->IsRunning() || m_pAGmmSearchingSystem->IsRunning())	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoMainFrame::OnUpdateStartServer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bSearchingBusy || m_bUpdatingSearchResults)	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoMainFrame::OnUpdateStopServer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bSearchingBusy || m_bUpdatingSearchResults)	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoMainFrame::OnUpdateBrowse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bSearchingBusy || m_bUpdatingSearchResults || m_pAGmmTrainingSystem==NULL || !m_pAGmmSearchingSystem->IsRunning())	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoMainFrame::OnUpdateSearch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CAGmagicISDemoDoc*	pDoc=(CAGmagicISDemoDoc*)GetActiveFrame()->GetActiveDocument();
	if(pDoc==NULL || m_bSearchingBusy || m_bUpdatingSearchResults || 
		m_pAGmmTrainingSystem==NULL || !m_pAGmmSearchingSystem->IsRunning())	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoMainFrame::OnUpdateFeedback(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CAGmagicISDemoDoc* m_pSearchDoc=m_pSearchResultDlg->m_pDoc;

	if(m_pSearchResultDlg->m_SearchResultCtrl.GetItemCount()==0 || 
		m_pSearchDoc==NULL || m_bSearchingBusy || m_bUpdatingSearchResults ||
		m_pAGmmTrainingSystem==NULL || !m_pAGmmSearchingSystem->IsRunning())
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoMainFrame::OnUpdateFeedbackAdvanced(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CAGmagicISDemoDoc* m_pSearchDoc=m_pSearchResultDlg->m_pDoc;

	if(m_pSearchResultDlg->m_SearchResultCtrl.GetItemCount()==0 || 
		m_pSearchDoc==NULL || m_bSearchingBusy || m_bUpdatingSearchResults ||
		m_pAGmmTrainingSystem==NULL || !m_pAGmmSearchingSystem->IsRunning()||
		m_pSearchDoc->m_pQuerySemanticTree==NULL)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoMainFrame::OnUpdateSearchResultUserOpen(CCmdUI* pCmdUI)
{
	CAGmagicISDemoDoc* m_pSearchDoc=m_pSearchResultDlg->m_pDoc;

	if(m_pSearchResultDlg->m_SearchResultCtrl.GetItemCount()==0 || m_pSearchDoc==NULL || 
		m_bSearchingBusy || m_bUpdatingSearchResults ||
		m_pAGmmTrainingSystem==NULL || !m_pAGmmSearchingSystem->IsRunning())
		pCmdUI->Enable(FALSE);
	else
	{
		CAGint32Array idxs;
		m_pSearchResultDlg->m_SearchResultCtrl.GetAllSelectedIdxs(&idxs);
		agint32 n=idxs.GetSize();
		if(n>1 || n==0)	pCmdUI->Enable(FALSE);
		else			pCmdUI->Enable(TRUE);
	}
}
void CAGmagicISDemoMainFrame::OnUpdateSearchResultUserOpenDialog(CCmdUI* pCmdUI)
{
	CAGmagicISDemoDoc* m_pSearchDoc=m_pSearchResultDlg->m_pDoc;

	if(m_pSearchResultDlg->m_SearchResultCtrl.GetItemCount()==0 || m_pSearchDoc==NULL || 
		m_bSearchingBusy || m_bUpdatingSearchResults ||
		m_pAGmmTrainingSystem==NULL || !m_pAGmmSearchingSystem->IsRunning())
		pCmdUI->Enable(FALSE);
	else
	{
		CAGint32Array idxs;
		m_pSearchResultDlg->m_SearchResultCtrl.GetAllSelectedIdxs(&idxs);
		agint32 n=idxs.GetSize();
		if(n==0)	pCmdUI->Enable(FALSE);
		else		pCmdUI->Enable(TRUE);
	}
}
void CAGmagicISDemoMainFrame::OnUpdateSearchResultUserProperties(CCmdUI* pCmdUI)
{
	CAGmagicISDemoDoc* m_pSearchDoc=m_pSearchResultDlg->m_pDoc;

	if(m_pSearchResultDlg->m_SearchResultCtrl.GetItemCount()==0 || m_pSearchDoc==NULL || 
		m_bSearchingBusy || m_bUpdatingSearchResults ||
		m_pAGmmTrainingSystem==NULL || !m_pAGmmSearchingSystem->IsRunning())
		pCmdUI->Enable(FALSE);
	else
	{
		CAGint32Array idxs;
		m_pSearchResultDlg->m_SearchResultCtrl.GetAllSelectedIdxs(&idxs);
		agint32 n=idxs.GetSize();
		if(n!=1)	pCmdUI->Enable(FALSE);
		else		pCmdUI->Enable(TRUE);
	}
}
void CAGmagicISDemoMainFrame::OnUpdateMainframeShowServer(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_pServerDlg->IsWindowVisible());
}
void CAGmagicISDemoMainFrame::OnUpdateMainframeShowOutput(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_pOutputBar->IsVisible());
}
void CAGmagicISDemoMainFrame::OnUpdateMainframeShowResult(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_pSearchResultDlg->IsWindowVisible());
}
void CAGmagicISDemoMainFrame::InitServer()
{
	CleanupServer();
	//CAGmagicSysUtil::ExecProgram(_T("RegSvr32 ..\\lib\\ui\\LeoMsgBox.dll"));
	//CAGmagicSysUtil::RegSvr(AGMAGICISDEMO_LEO_MSG_BOX_LIBPATH);

	m_pAGmmTrainingSystem=new CAGmmTrainingSystemUIWinThread(this,&m_Event);
	m_pAGmmSearchingSystem=new CAGmmSearchingSystemUIWinThread(this,&m_Event);

	DBCnnAttach(CAGmagicConfUtil::AGmagic_GlobalDBCnnStr);
	//CAGimageDBUtil::CreateDBFromURL(_T("d:\\temp\\hinh"),DBCnnGet());

	m_pAGmmTrainingSystem->Init();
	m_pAGmmSearchingSystem->Init();

	if(m_pServerDlg==NULL)
	{
		m_pServerDlg=new CAGmagicISDemoServerDlg(this);
	}

	{
		POST_OUTPUT_NOTICE(this,_T("Initialized Server (Training System and Searching System)"))
	}
}
void CAGmagicISDemoMainFrame::CleanupServer()
{
	DBCnnDetach();
	
	if(m_pAGmmTrainingSystem)
	{
		if(!m_pAGmmTrainingSystem->IsRunning())
		{
			m_Event.ResetEvent();
			m_pAGmmTrainingSystem->Start();
			//ngong doi thread ket thuc
			::WaitForSingleObject(m_Event.m_hObject,INFINITE);
		}
		if(m_pAGmmTrainingSystem->IsRunning())
		{
			m_pAGmmTrainingSystem->PostThreadMessage(WM_QUIT,0,0);
			::WaitForSingleObject(m_pAGmmTrainingSystem->m_hThread,INFINITE);
		}
		else delete m_pAGmmTrainingSystem;
		m_pAGmmTrainingSystem=NULL;
	}

	if(m_pAGmmSearchingSystem)
	{
		if(!m_pAGmmSearchingSystem->IsRunning())
		{
			m_Event.ResetEvent();
			m_pAGmmSearchingSystem->Start();
			//ngong doi thread ket thuc
			::WaitForSingleObject(m_Event.m_hObject,INFINITE);
		}
		if(m_pAGmmSearchingSystem->IsRunning())
		{
			m_pAGmmSearchingSystem->PostThreadMessage(WM_QUIT,0,0);
			::WaitForSingleObject(m_pAGmmSearchingSystem->m_hThread,INFINITE);
		}
		else delete m_pAGmmSearchingSystem;
		m_pAGmmSearchingSystem=NULL;
	}
	//CAGmagicSysUtil::ExecProgram(_T("RegSvr32 /u ..\\lib\\ui\\LeoMsgBox.dll"));
	//CAGmagicSysUtil::UnregSvr(AGMAGICISDEMO_LEO_MSG_BOX_LIBPATH);

	{
		POST_OUTPUT_NOTICE(this,_T("Stoped Server (Training and Searching System)"))
	}
}
BOOL CAGmagicISDemoMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CAGmmMainFrame::PreTranslateMessage(pMsg);
}
#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoChildFrame************************************/

#if AGMAGIC_SUPPORT_MFC
IMPLEMENT_DYNCREATE(CAGmagicISDemoChildFrame, CAGmagicIP_MDIChildFrame)

BEGIN_MESSAGE_MAP(CAGmagicISDemoChildFrame, CAGmagicIP_MDIChildFrame)
	//{{AFX_MSG_MAP(CAGmagicISDemoChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIP_MDIChildFrame construction/destruction
CAGmagicISDemoChildFrame::CAGmagicISDemoChildFrame() : CAGmagicIP_MDIChildFrame()
{
	// TODO: add member initialization code here
}

CAGmagicISDemoChildFrame::~CAGmagicISDemoChildFrame()
{
}
#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoDoc************************************/
#if AGMAGIC_SUPPORT_MFC

IMPLEMENT_DYNCREATE(CAGmagicISDemoDoc, CAGmagicIPDoc)

BEGIN_MESSAGE_MAP(CAGmagicISDemoDoc, CAGmagicIPDoc)
	//{{AFX_MSG_MAP(CAGmagicISDemoDoc)
	ON_COMMAND(ID_DATABASE_INSERT, OnDatabaseInsert)
	ON_COMMAND(ID_DATABASE_UPDATE, OnDatabaseUpdate)
	ON_COMMAND(ID_DATABASE_DELETE, OnDatabaseDelete)
	ON_COMMAND(ID_DATABASE_SELECT, OnDatabaseSelect)

	ON_UPDATE_COMMAND_UI(ID_DATABASE_INSERT, OnUpdateDatabaseInsert)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_UPDATE, OnUpdateDatabaseUpdate)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_DELETE, OnUpdateDatabaseDelete)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_SELECT, OnUpdateDatabaseSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAGmagicISDemoDoc::CAGmagicISDemoDoc() : CAGmagicIPDoc()
{
	m_QueryImageID=0;
	m_QueryImageType=0;
	m_pQuerySemanticTree=NULL;
}
CAGmagicISDemoDoc::~CAGmagicISDemoDoc()
{
	if(m_pQuerySemanticTree) delete m_pQuerySemanticTree; m_pQuerySemanticTree=NULL;
}
void CAGmagicISDemoDoc::SetQuerySemanticTree(CAGimageSemanticTree* pSemanticTree, agbool bIsCopy)
{
	if(m_pQuerySemanticTree) delete m_pQuerySemanticTree; m_pQuerySemanticTree=NULL;
	if(!bIsCopy) m_pQuerySemanticTree=pSemanticTree;
	else if(pSemanticTree!=NULL)
	{
		m_pQuerySemanticTree=new CAGimageSemanticTree();
		m_pQuerySemanticTree->CopyFrom(pSemanticTree);
	}

}
void CAGmagicISDemoDoc::OnDatabaseInsert()
{
	CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();

//Da insert roi
	if(m_QueryImageID!=0)
	{
		AfxMessageBox(_T("Image Inserted Already"),MB_OK|MB_ICONSTOP,0);
		POST_OUTPUT_NOTICE(pMainWnd,_T("Image Inserted Already"))
		return;
	}
//Khong xu ly voi pMainWnd->m_bIsInsertDBIntel==agfalse
	if(!pMainWnd->m_bIsInsertDBIntel)
	{
		AfxMessageBox(_T("Implement not yet"),MB_OK|MB_ICONSTOP,0);
		return;
	}
	if(m_SearchResults2.GetSize()==0)
	{
		AfxMessageBox(_T("Implement not yet"),MB_OK|MB_ICONSTOP,0);
		return;
	}

//Khai bao cac bien dung chung
	CString			szImagePath=GetPathName();
	aguint_id		ImageType=0;
	CAGimageDBItem	share_item;
	share_item.DBCnnAttach(pMainWnd->DBCnnGet());

//Tim ImageType cua anh giong nhat
	if(m_QueryImageType==0)
	{
		CAGinteractImagesMsg*	pMsg=m_SearchResults2.GetAt(0);
		aguint_id				ImageIntelID=0;
		if(pMsg->IsPassID())	ImageIntelID=pMsg->GetIDAt(0);
		else
		{
			CAGimage* pAGimage=pMsg->GetImageAt(0);
			if(pAGimage==NULL || !pAGimage->IsValid())
			{
				AfxMessageBox(_T("Can't insert into database"),MB_OK|MB_ICONSTOP,0);
				POST_OUTPUT_NOTICE(pMainWnd,_T("Insert Image to Database not success"))
				return;
			}
			ImageIntelID=pAGimage->m_ID;
		}
		if(!share_item.DBRead(ImageIntelID))
		{
			AfxMessageBox(_T("Can't insert into database"),MB_OK|MB_ICONSTOP,0);
			POST_OUTPUT_NOTICE(pMainWnd,_T("Insert Image to Database not success"))
			return;
		}
		ImageType=share_item.m_ImageType;//dong nay rat quan trong
	}
	else
		ImageType=m_QueryImageType;
	if(ImageType==0)
	{
		AfxMessageBox(_T("Can't insert into database"),MB_OK|MB_ICONSTOP,0);
		POST_OUTPUT_NOTICE(pMainWnd,_T("Insert Image to Database not success"))
		return;
	}

//TIm anh trong CSDL co szImagePath
	CAGidTypeArray ImageIDTypes;
	CAGimageDBUtil::FindImageIntel(pMainWnd->DBCnnGet(), szImagePath.GetBuffer(0), &ImageIDTypes);

	agbool		bInsert=agtrue;
	aguint_id	OldImageID=0;
	if(ImageIDTypes.GetSize()==1)
	{
		IMAGE_ID_TYPE	ImageIDType;
		ImageIDType=ImageIDTypes.GetAt(0);
		if(ImageIDType.ImageType!=ImageType)//co mot anh trong CSDL co Type cung duong dan nhung co Type, phai replace anh nay
		{
			share_item.m_ImageID=OldImageID=ImageIDType.ImageID;
			share_item.DBDelete();
			bInsert=agfalse;
		}
	}

//Insert anh vao CSDL
	share_item.SetIsStoreImage(agtrue);
	if(!share_item.LoadURL(szImagePath.GetBuffer(0)))
	{
		AfxMessageBox(_T("Can't insert into database"),MB_OK|MB_ICONSTOP,0);
		POST_OUTPUT_NOTICE(pMainWnd,_T("Insert Image to Database not success"))
		return;
	}
	share_item.m_ImageType=ImageType;//dong nay rat quan trong
	agtchar*	brief_url=CAGmagicIOUtil::ConvertAndAllocBriefURL(szImagePath.GetBuffer(0));
	share_item.AllocURL(brief_url);
	if(brief_url)	free(brief_url);

	agbool				bResult;
	AGMAGICIP_DEFAULT_SEGS_CLASS	segs;
	if(bInsert)
		bResult=share_item.DBInsert(agtrue, agtrue, agtrue,CAGmagicConfUtil::IsNegativeImageWhenSegment(share_item.m_ImageType)/*neu la loai flower-spec thi negative*/,
				&segs);
	else
	{
		bResult=share_item.DBInsert(agtrue, agtrue, agfalse,CAGmagicConfUtil::IsNegativeImageWhenSegment(share_item.m_ImageType)/*neu la loai flower-spec thi negative*/,
			&segs);
		if(bResult)
		{
			if(OldImageID==0)	throw _T("Fatal Error");
			if(!CAGimageAffMatrix::ReplaceImageID(pMainWnd->DBCnnGet(), 
				OldImageID, share_item.m_ImageID, agfalse))
				throw _T("Fatal Error");
			if(!CAGimageAffMatrix::ReplaceImageID(pMainWnd->DBCnnGet(), 
				OldImageID, share_item.m_ImageID, agtrue))
				throw _T("Fatal Error");

			if(!CAGimageAffMatrix::ReplaceRelatedImageID(pMainWnd->DBCnnGet(), 
				OldImageID, share_item.m_ImageID, agfalse))
				throw _T("Fatal Error");
			if(!CAGimageAffMatrix::ReplaceRelatedImageID(pMainWnd->DBCnnGet(), 
				OldImageID, share_item.m_ImageID, agtrue))
				throw _T("Fatal Error");
		}
	}
	if(!bResult)	throw _T("Fatal Error");
	m_QueryImageID=share_item.m_ImageID;
	m_QueryImageType=share_item.m_ImageType;
	GetImage()->m_ID=m_QueryImageID;
	POST_OUTPUT_NOTICE(pMainWnd,_T("Insert Image to Database success"))
}

void CAGmagicISDemoDoc::OnDatabaseUpdate()
{
	AfxMessageBox(_T("Implement not yet"),MB_OK|MB_ICONSTOP,0);
}
void CAGmagicISDemoDoc::OnDatabaseDelete()
{
	AfxMessageBox(_T("Implement not yet"),MB_OK|MB_ICONSTOP,0);
}
void CAGmagicISDemoDoc::OnDatabaseSelect()
{
	AfxMessageBox(_T("Implement not yet"),MB_OK|MB_ICONSTOP,0);
}

void CAGmagicISDemoDoc::OnUpdateDatabaseInsert(CCmdUI* pCmdUI)
{
	CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();
	if(m_QueryImageID!=0 || 
		pMainWnd->m_bSearchingBusy || pMainWnd->m_bUpdatingSearchResults || m_bBusy ||
		!pMainWnd->m_pAGmmSearchingSystem->IsRunning())	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoDoc::OnUpdateDatabaseUpdate(CCmdUI* pCmdUI)
{
	CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();
	if(pMainWnd->m_bSearchingBusy || pMainWnd->m_bUpdatingSearchResults || m_bBusy ||
		!pMainWnd->m_pAGmmSearchingSystem->IsRunning())	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoDoc::OnUpdateDatabaseDelete(CCmdUI* pCmdUI)
{
	CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();
	if(pMainWnd->m_bSearchingBusy || pMainWnd->m_bUpdatingSearchResults || m_bBusy ||
		!pMainWnd->m_pAGmmSearchingSystem->IsRunning())	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
void CAGmagicISDemoDoc::OnUpdateDatabaseSelect(CCmdUI* pCmdUI)
{
	CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();
	if(pMainWnd->m_bSearchingBusy || pMainWnd->m_bUpdatingSearchResults || m_bBusy ||
		!pMainWnd->m_pAGmmSearchingSystem->IsRunning())	
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
BOOL CAGmagicISDemoDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	BOOL bOpen=CAGmagicIPDoc::OnOpenDocument(lpszPathName);
	if(bOpen)
	{
		;
	}
	return bOpen;
}
BOOL CAGmagicISDemoDoc::DoSave(LPCTSTR pszPathName, BOOL bReplace /*=TRUE*/)
{
	BOOL bSave=CAGmagicIPDoc::DoSave(pszPathName, bReplace /*=TRUE*/);
	if(bSave)
	{
		CAGmagicISDemoMainFrame*	pMainWnd=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();
		if(m_QueryImageID==0 && pMainWnd->m_bIsInsertDBIntel &&
			m_SearchResults2.GetSize()!=0)
		{
			OnDatabaseInsert();
		}
	}
	return bSave;
}
#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoView************************************/

#if AGMAGIC_SUPPORT_MFC

IMPLEMENT_DYNCREATE(CAGmagicISDemoView, CAGmagicIPView)

BEGIN_MESSAGE_MAP(CAGmagicISDemoView, CAGmagicIPView)
	//{{AFX_MSG_MAP(CAGmagicISDemoView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoView construction/destruction
CAGmagicISDemoView::CAGmagicISDemoView() : CAGmagicIPView()
{
}
//////////////////////////////////////////////////////////////////////////////
CAGmagicISDemoView::~CAGmagicISDemoView()
{
}

void CAGmagicISDemoView::OnHelpTestAGmagicIP()
{
	CAGmagicISDemoMainFrame*	pMainFrame=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();
	/*
	CAGimageDBUtil::ResetAffInDB(pAGmagicISDemoMainFrame->DBCnnGet());
	*/
	/*
	CAGimageAffMatrix::CreateAffInDB(m_pDBCnnI);
	*/
	/*
	CAGimageAffMatrix::DeleteAllAffInDB(m_pDBCnnI);
	for(int i=0; i<CAGmagicConfUtil::nAGmagic_GlobalSampleImagesDirNames; i++)
	{
		CAGimageAffMatrix::CreateAffInDB(m_pDBCnnI,CAGmagicConfUtil::idAGmagic_GlobalSampleImagesDirNames[i]);
	}
	*/
	/*
	CAGimageSemanticTree tree;
	tree.DBCnnAttach(DBCnnGet());
	tree.DBBuild(1,agtrue);
	tree.OutputXML(_T("d:\\semantic_tree.xml"));
	*/
	/*
	CAGimageSemanticTree::DBResetAndInsertSampleTopLevelImageIDs(pAGmagicISDemoMainFrame->DBCnnGet());
	*/
	
	//CAGimageSemanticTree::DBResetAndInsertSampleTopLevelSemantics(pMainFrame->DBCnnGet());
	/*
	CAGmagicISDemoDoc* pDoc=GetDocument();
	CAGimageGrayScale SegAGimage;
	SegAGimage.Copy(pDoc->image);

	AGMAGICIP_DEFAULT_SEGS_CLASS segs;
	segs.SegCreate(pDoc->image,NULL,&SegAGimage);
	segs.DBCnnAttach(pMainFrame->DBCnnGet());
	segs.SetImageID(pDoc->m_QueryImageID);
	segs.DBDelete();
	segs.DBInsert();
	segs.Show();

	AGMAGICIP_DEFAULT_SEGS_CLASS segs2;
	segs2.DBCnnAttach(pMainFrame->DBCnnGet());
	segs2.DBRead(pDoc->m_QueryImageID);
	segs2.Show();
	*/
	/*
	CAGmagicISDemoDoc* pDoc=GetDocument();
	CAGimageColorUtil::RGB25PrimaryLut(pDoc->GetImage());
	Invalidate();
	*/
	/*
	CAGbaseArray<int> a;
	a.SetSize(10);
	int& i=a.ElementAt(0);
	i=10;
	i=a.ElementAt(0);
	a[0]=1;
	i=a[0];
	i=a.ElementAt(0);
	*/
	/*
	CAGmagicISDemoDoc* pDoc=GetDocument();
	CAGimageObjPtrMatrix* matrix=new CAGimageObjPtrtdMatrix();
	SIZE block_size={8,8};
	matrix->CreateByCut(pDoc->image,block_size);
	matrix->Show();

	AGCLRQUAD fill_color={0,0,0,0};
	CAGimage* pImage=matrix->NewImageByJoin(NULL,2,2);

	if(pImage && !pImage->IsTransparent())
	{
		CAGimageModalDlg::ShowAGimageDlg(IDD_AGMAGICIP_DEFAULT,pImage);
		//CAGimageDlg::ShowAGimageDlg(IDD_AGMAGICIP_DEFAULT,NULL);
		delete pImage;
	}
	delete matrix;
	*/
	CAGmagicISDemoDoc*	pDoc=GetDocument();
	CString				szImagePath=pDoc->GetPathName();
	CString				results;
	IAGmmSearchingSystem::SampleSearch(0, szImagePath, results);
	MessageBox(results);
}
void CAGmagicISDemoView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CAGmagicIPView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	CAGmagicISDemoMainFrame* pMainFrm=(CAGmagicISDemoMainFrame*)AfxGetMainWnd();

	if(pMainFrm->m_bSearchingBusy || pMainFrm->m_bUpdatingSearchResults)	return;
	if(bActivate)
	{
		CAGmagicISDemoDoc* pActiveDoc=(CAGmagicISDemoDoc*)(pMainFrm->GetActiveFrame()->GetActiveDocument());
		if(pMainFrm->m_pSearchDoc!=pActiveDoc)
		{
			pMainFrm->m_pSearchDoc=pActiveDoc;
			pMainFrm->m_pSearchResultDlg->SetDocument(pActiveDoc);
		}
	}
	else if(pMainFrm->m_pSearchResultDlg->m_SearchResultCtrl.GetItemCount()>0)
	{
		if(pMainFrm->GetActiveFrame()->GetActiveDocument()==NULL)
		{
			pMainFrm->m_pSearchDoc=NULL;
			pMainFrm->m_pSearchResultDlg->SetDocument(NULL);
		}
	}
}

#ifdef _DEBUG
CAGmagicISDemoDoc* CAGmagicISDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAGmagicISDemoDoc)));
	return (CAGmagicISDemoDoc*)m_pDocument;
}
#endif //_DEBUG

#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoApp************************************/

#if AGMAGIC_SUPPORT_MFC
BEGIN_MESSAGE_MAP(CAGmagicISDemoApp, CAGmagicIPApp)
	//{{AFX_MSG_MAP(CAGmagicISDemoApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoApp construction
CAGmagicISDemoApp::CAGmagicISDemoApp() : CAGmagicIPApp()
{
}
//////////////////////////////////////////////////////////////////////////////
// The one and only CAGmagicISDemoApp object

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIPApp initialization
BOOL CAGmagicISDemoApp::InitInstance()
{
	//CAGmagicConfUtil::Init();
	//CAGmagicIPConfUtil::Init();
	CAGmagicLoginDlg LoginDlg;
	if(LoginDlg.DoModal()==IDCANCEL)
	{
		return FALSE;
	}
#if AGMAGIC_SUPPORT_ADO
	CAGmagicConfUtil::AGmagic_GlobalADOProvider=LoginDlg.GetCnnProvider();
#endif
	_tcscpy(CAGmagicConfUtil::AGmagic_GlobalDBCnnStr,LoginDlg.GetCnnStr());

	// <dave> dump memory leaks
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	// Standard initialization
#if _MFC_VER < 0x0700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL //khong can thiet nua doi voi VC 7.0
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically //khong can thiet nua doi voi VC 7.0
#endif
#endif	//#if _MFC_VER < 0x0700
	LoadStdProfileSettings(9);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_AGMAGICIPTYPE,
		RUNTIME_CLASS(CAGmagicISDemoDoc),
		RUNTIME_CLASS(CAGmagicISDemoChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAGmagicISDemoView) );
	demoTemplate = pDocTemplate;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CAGmagicISDemoMainFrame* pMainFrame = new CAGmagicISDemoMainFrame();
	if (!pMainFrame->LoadFrame(IDR_AGMAGICIPMAINFRAME)) return FALSE;
	m_pMainWnd = pMainFrame;

	// This code replaces the MFC created menus with 
	// the Ownerdrawn versions 
	pDocTemplate->m_hMenuShared=pMainFrame->NewMenu();
	pMainFrame->m_hMenuDefault=pMainFrame->NewDefaultMenu();
	// This simulates a window being opened if you don't have
	// a default window displayed at startup
	pMainFrame->OnUpdateFrameMenu(pMainFrame->m_hMenuDefault);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
    // Alter behaviour to not open window immediately
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo)) return FALSE;

#ifdef VATI_EXTENSIONS
	// recall if main window was maximized on last exit
    if ( GetProfileInt ( _T("Screen"), _T("maximized"), 0 ))
        m_nCmdShow|=SW_MAXIMIZE;
#endif;

	// The main window has been initialized, so show and update it.
    pMainFrame -> ShowWindow ( m_nCmdShow | SW_MAXIMIZE) ;
	pMainFrame->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable open from command line
	if (*m_lpCmdLine != 0)
		OpenDocumentFile(m_lpCmdLine);

	return TRUE;
}
#endif	//#if AGMAGIC_SUPPORT_MFC




