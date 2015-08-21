// AGmagicISClientUI2.cpp: implementation of the AGmagicISClientUI class.
//
//////////////////////////////////////////////////////////////////////

#include "AGmagicISClientUI2.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif	//#if AGMAGIC_SUPPORT_MFC

/*******************class CAGmagicISClientMainFrame*********************/

#if AGMAGIC_SUPPORT_MFC_UI

IMPLEMENT_DYNCREATE(CAGmagicISClientMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CAGmagicISClientMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CAGmagicISClientMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientMainFrame construction/destruction

CAGmagicISClientMainFrame::CAGmagicISClientMainFrame()
{
	::memset( &m_dataFrameWP, 0, sizeof(WINDOWPLACEMENT) );
	m_dataFrameWP.length = sizeof(WINDOWPLACEMENT);
	m_dataFrameWP.showCmd = SW_HIDE;

	// TODO: add member initialization code here
	
}

CAGmagicISClientMainFrame::~CAGmagicISClientMainFrame()
{
}

int CAGmagicISClientMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CWinApp * pApp = ::AfxGetApp();

	ASSERT( pApp != NULL );
	ASSERT( pApp->m_pszRegistryKey != NULL );
	ASSERT( pApp->m_pszRegistryKey[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );
	ASSERT( pApp->m_pszProfileName[0] != _T('\0') );

	if( CFrameWnd::OnCreate(lpCreateStruct) == -1 )
	{
		ASSERT( FALSE );
		return -1;
	}

	VERIFY(
		g_CmdManager->ProfileWndAdd(
			pApp->m_pszProfileName,
			GetSafeHwnd()
			)
		);
	VERIFY(
		g_CmdManager->UpdateFromMenu(
			pApp->m_pszProfileName,
			IDR_MAINFRAME
			)
		);

	if(	!m_wndMenuBar.Create(
			NULL,
			this,
			ID_VIEW_MENUBAR
			)
		)
    {
        TRACE0("Failed to create menubar\n");
        return -1;      // failed to create
    }
	
	if(	!m_wndToolBar.Create(
			NULL,
			this,
			AFX_IDW_TOOLBAR
			)
		||
		!m_wndToolBar.LoadToolBar( IDR_MAINFRAME )
		)
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if(	!m_wndStatusBar.Create(this)
		||
		!m_wndStatusBar.SetIndicators(
			indicators,
			sizeof(indicators) / sizeof(UINT)
			)
		)
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndMenuBar.EnableDocking( CBRS_ALIGN_ANY );
	m_wndToolBar.EnableDocking( CBRS_ALIGN_ANY );

//////////////////////////////////////////////////////////////////////////////////////

	if(	!m_wndSearchControlBar.Create(
			_T("Search Control"),
			this,
			ID_SEARCH_CONTROL_BAR
			)
		)
	{
		TRACE0("Failed to create m_wndSearchControlBar\n");
		return -1;		// fail to create
	}
	if( !m_wndSearchControlDlg.Create(
			IDD_SEARCH_CONTROL_DLG,
			&m_wndSearchControlBar
			)
		)
	{
		TRACE0("Failed to create m_wndSearchControlBar\n");
		return -1;		// fail to create
	}
	m_wndSearchControlDlg.ShowSizeGrip( FALSE );
	VERIFY(
			m_wndEditInDockedDlg.SubclassDlgItem(
				IDC_EDIT_SEARCH_CONTROL_ITEM,
				&m_wndSearchControlDlg
				)
		);

	m_wndSearchControlDlg.AddAnchor(
		IDC_EDIT_SEARCH_CONTROL_ITEM,
		__RDA_KEEP,
		__RDA_BOTH
		);

	m_wndSearchControlBar.EnableDocking( CBRS_ALIGN_ANY );

//////////////////////////////////////////////////////////////////////////////////////
	if(	!m_ResizableSampleBar.Create(
			_T("Search Control"),
			this,
			ID_RESIZABLE_SAMPLE_BAR
			)
		)
	{
		TRACE0("Failed to create m_wndResizableBar0\n");
		return -1;		// fail to create
	}
	if( !m_ResizableSampleDlg.Create(
			IDD_RESIZABLE_SAMPLE_DLG,
			&m_ResizableSampleBar
			)
		)
	{
		TRACE0("Failed to create m_wndResizableBar0\n");
		return -1;		// fail to create
	}
	m_ResizableSampleDlg.ShowSizeGrip( FALSE );
	m_ResizableSampleBar.EnableDocking( CBRS_ALIGN_ANY );
//////////////////////////////////////////////////////////////////////////////////////

	//
	// Prof-UIS advanced docking windows feature:
	// Show content of control bars when docking / resizing
	//
	if( !CExtControlBar::FrameEnableDocking(this) )
	{
		ASSERT( FALSE );
		return -1;
	}
	
#if (!defined __EXT_MFC_NO_TAB_CONTROLBARS)
	if( !CExtControlBar::FrameInjectAutoHideAreas(this) )
	{
		ASSERT( FALSE );
		return -1;
	}
#endif // (!defined __EXT_MFC_NO_TAB_CONTROLBARS)


	static UINT statBasicCommands[] =
	{
		ID_FILE_NEW, 
		ID_FILE_OPEN, 
		ID_FILE_SAVE,
		ID_APP_EXIT,
		ID_APP_ABOUT,
		ID_FILE_PRINT,
		ID_FILE_PRINT_SETUP, 
		ID_EDIT_COPY, 
		ID_EDIT_CUT, 
		ID_EDIT_PASTE, 
		ID_EDIT_UNDO, 
		ID_VIEW_TOOLBAR, 
		0 // end of commands list
	}; // statBasicCommands array

	VERIFY(
		g_CmdManager->SetBasicCommands(
			pApp->m_pszProfileName,
			statBasicCommands
			)
		);
	g_CmdManager->SerializeState(
		pApp->m_pszProfileName,
		pApp->m_pszRegistryKey,
		pApp->m_pszProfileName,
		false
		);

	if( !CExtControlBar::ProfileBarStateLoad(
			this,
			pApp->m_pszRegistryKey,
			pApp->m_pszProfileName,
			pApp->m_pszProfileName,
			&m_dataFrameWP
			)
		)
	{
		DockControlBar( &m_wndMenuBar );
		DockControlBar( &m_wndToolBar );

		m_wndSearchControlBar.DockControlBar(AFX_IDW_DOCKBAR_LEFT,1);
		m_ResizableSampleBar.DockControlBar(AFX_IDW_DOCKBAR_RIGHT,1);
	}

	return 0;
}

BOOL CAGmagicISClientMainFrame::DestroyWindow() 
{
CWinApp * pApp = ::AfxGetApp();
	ASSERT( pApp != NULL );
	ASSERT( pApp->m_pszRegistryKey != NULL );
	ASSERT( pApp->m_pszRegistryKey[0] != _T('\0') );
	ASSERT( pApp->m_pszProfileName != NULL );
	ASSERT( pApp->m_pszProfileName[0] != _T('\0') );
	pApp;

	VERIFY(
		CExtControlBar::ProfileBarStateSave(
			this,
			pApp->m_pszRegistryKey,
			pApp->m_pszProfileName,
			pApp->m_pszProfileName,
			&m_dataFrameWP
			)
		);

	VERIFY(
		g_CmdManager->SerializeState(
			pApp->m_pszProfileName,
			pApp->m_pszRegistryKey,
			pApp->m_pszProfileName,
			true
			)
		);

	g_CmdManager->ProfileWndRemove( GetSafeHwnd() );
	
	return CFrameWnd::DestroyWindow();
}

void CAGmagicISClientMainFrame::ActivateFrame(int nCmdShow) 
{
	if( m_dataFrameWP.showCmd != SW_HIDE )
	{
		SetWindowPlacement( &m_dataFrameWP );
		CFrameWnd::ActivateFrame( m_dataFrameWP.showCmd );
		m_dataFrameWP.showCmd = SW_HIDE;
		return;
	}
	CFrameWnd::ActivateFrame(nCmdShow);
}

BOOL CAGmagicISClientMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientMainFrame diagnostics

#ifdef _DEBUG
void CAGmagicISClientMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CAGmagicISClientMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientMainFrame message handlers


BOOL CAGmagicISClientMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if( m_wndMenuBar.TranslateMainFrameMessage(pMsg) )
		return TRUE;
	return CFrameWnd::PreTranslateMessage(pMsg);
}

#endif	//#if AGMAGIC_SUPPORT_MFC_UI

/*******************class CAGmagicISClientDoc***************************/

#if AGMAGIC_SUPPORT_MFC_UI

IMPLEMENT_DYNCREATE(CAGmagicISClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CAGmagicISClientDoc, CDocument)
	//{{AFX_MSG_MAP(CAGmagicISClientDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientDoc construction/destruction

CAGmagicISClientDoc::CAGmagicISClientDoc()
{
	// TODO: add one-time construction code here

}
CAGmagicISClientDoc::~CAGmagicISClientDoc()
{
}

BOOL CAGmagicISClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientDoc serialization

void CAGmagicISClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientDoc diagnostics

#ifdef _DEBUG
void CAGmagicISClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAGmagicISClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientDoc commands

#endif	//#if AGMAGIC_SUPPORT_MFC_UI

/*******************class CAGmagicISClientView***************************/

#if AGMAGIC_SUPPORT_MFC_UI

IMPLEMENT_DYNCREATE(CAGmagicISClientView, CView)

BEGIN_MESSAGE_MAP(CAGmagicISClientView, CView)
	//{{AFX_MSG_MAP(CAGmagicISClientView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientView construction/destruction

CAGmagicISClientView::CAGmagicISClientView()
{
	// TODO: add construction code here

}

CAGmagicISClientView::~CAGmagicISClientView()
{
}

BOOL CAGmagicISClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CView::PreCreateWindow(cs) )
		return FALSE;
	cs.style |= WS_CLIPSIBLINGS;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientView drawing

void CAGmagicISClientView::OnDraw(CDC* pDC)
{
	pDC;
	CAGmagicISClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientView printing

BOOL CAGmagicISClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAGmagicISClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAGmagicISClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientView diagnostics

#ifdef _DEBUG
void CAGmagicISClientView::AssertValid() const
{
	CView::AssertValid();
}

void CAGmagicISClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAGmagicISClientDoc* CAGmagicISClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAGmagicISClientDoc)));
	return (CAGmagicISClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientView message handlers

#endif	//#if AGMAGIC_SUPPORT_MFC_UI

/*******************class CAGmagicISClientApp***************************/

#if AGMAGIC_SUPPORT_MFC_UI

BEGIN_MESSAGE_MAP(CAGmagicISClientApp, CWinApp)
	//{{AFX_MSG_MAP(CAGmagicISClientApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientApp construction

CAGmagicISClientApp::CAGmagicISClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAGmagicISClientApp object

/////////////////////////////////////////////////////////////////////////////
// Prof-UIS advanced options

void CAGmagicISClientApp::SetupUiAdvancedOptions()
{
	ASSERT( m_pszRegistryKey != NULL );
	ASSERT( m_pszRegistryKey[0] != _T('\0') );
	ASSERT( m_pszProfileName != NULL );
	ASSERT( m_pszProfileName[0] != _T('\0') );

	//
	// Prof-UIS command manager profile
	//
	VERIFY(
		g_CmdManager->ProfileSetup( m_pszProfileName )
		);

	//
	// General UI look
    //
// UNCOMMENT THESE LINES FOR OFFICE 2000 UI STYLE
//	g_PaintManager.InstallPaintManager(
//		new CExtPaintManager
//	);

	//
	// Popup menu option: Display menu shadows
    //
	CExtPopupMenuWnd::g_bMenuWithShadows = true;

	//
	// Popup menu option: Display menu cool tips
    //
	CExtPopupMenuWnd::g_bMenuShowCoolTips = true;

	//
	// Popup menu option: Initially hide rarely used items (RUI)
    //
	CExtPopupMenuWnd::g_bMenuExpanding = true;

	//
	// Popup menu option: Display RUI in different style
    //
	CExtPopupMenuWnd::g_bMenuHighlightRarely = true;

	//
	// Popup menu option: Animate when expanding RUI (like Office XP)
    //
	CExtPopupMenuWnd::g_bMenuExpandAnimation = true;

	//
	// Popup menu option: Align to desktop work area (false - to screen area)
    //
	CExtPopupMenuWnd::g_bUseDesktopWorkArea = true;

	//
	// Popup menu option: Popup menu animation effect (when displaying)
    //
	CExtPopupMenuWnd::g_DefAnimationType =
		CExtPopupMenuWnd::__AT_FADE;

}

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientApp initialization

BOOL CAGmagicISClientApp::InitInstance()
{
	InitCommonControls();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MFC_VER < 0x700
	#ifdef _AFXDLL
		Enable3dControls();			// Call this when using MFC in a shared DLL
	#else
		Enable3dControlsStatic();	// Call this when linking to MFC statically
	#endif
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey( _T("AGmagic") );
	ASSERT( m_pszRegistryKey != NULL );

    // Change the application profile name (usually product name).
	// NOTE: The CWinApp class destructor will free the memory automatically.
	if( m_pszProfileName != NULL )
		free( (void*)m_pszProfileName );
	m_pszProfileName =
		_tcsdup( _T("AGmagicISClient") );
	ASSERT( m_pszProfileName != NULL );

	//
	// Prof-UIS advanced options
    //
	SetupUiAdvancedOptions();

	LoadStdProfileSettings(16);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAGmagicISClientDoc),
		RUNTIME_CLASS(CAGmagicISClientMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAGmagicISClientView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// Dispatch commands specified on the command line
	if( !ProcessShellCommand(cmdInfo) )
		return FALSE;

	ASSERT_VALID( m_pMainWnd );
	ASSERT_KINDOF( CFrameWnd, m_pMainWnd );
	// The one and only window has been initialized, so show and update it.
	((CFrameWnd *)m_pMainWnd)->ActivateFrame( SW_SHOW );

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

// App command to run the dialog
void CAGmagicISClientApp::OnAppAbout()
{
	VERIFY( ProfUISAbout() );
}

/////////////////////////////////////////////////////////////////////////////
// CAGmagicISClientApp message handlers

#endif	//#if AGMAGIC_SUPPORT_MFC_UI

/********************************class CResizableSampleDlg***************************/

#if AGMAGIC_SUPPORT_MFC_UI
	
CResizableSampleDlg::CResizableSampleDlg(CWnd* pParent /*=NULL*/)
	: CExtResizableDialog (CResizableSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResizableSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CResizableSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CExtResizableDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResizableSampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResizableSampleDlg, CExtResizableDialog)
	//{{AFX_MSG_MAP(CResizableSampleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizableSampleDlg message handlers

BOOL CResizableSampleDlg::OnInitDialog() 
{
	CExtResizableDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	AddAnchor(IDC_EDIT1, __RDA_KEEP, __RDA_X);
	AddAnchor(IDC_STATIC1, __RDA_KEEP, __RDA_X);
	AddAnchor(IDC_STATIC2, __RDA_KEEP, __RDA_BOTH);
	AddAnchor(IDC_TREE1, __RDA_KEEP, __RDA_BOTH);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
#endif	//#if AGMAGIC_SUPPORT_MFC_UI
