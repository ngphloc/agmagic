/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.
   Author: Barretto VN 7/2002
**************************************************************************/

// DlgToolStatusBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DlgToolStatusBar.h"
#include "DlgToolStatusBarDlg.h"

#include "AboutBox.h"
#include <afxctl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//typedef struct _TBBUTTON {
//	int iBitmap;// zero-based index of button image
//	int idCommand;  // command to be sent when button pressed
//	BYTE fsState;   // button state--see below
//	BYTE fsStyle;   // button style--see below
//	DWORD dwData;   // application-defined value
//	int iString;// zero-based index of button label string
//} TBBUTTON;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgToolStatusBarDlg dialog

CDlgToolStatusBarDlg::CDlgToolStatusBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgToolStatusBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgToolStatusBarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgToolStatusBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgToolStatusBarDlg)
//	DDX_Control(pDX, IDC_EXPLORER1, m_Browser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgToolStatusBarDlg, CDialog)
	//{{AFX_MSG_MAP(CDlgToolStatusBarDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_BOLD, OnBold)
	ON_COMMAND(ID_DRAWING, OnDrawing)
	ON_COMMAND(ID_STRIKEOUT, OnStrikeOut)
	ON_WM_DESTROY()
	ON_COMMAND(IDD_ABOUTBOX, OnAboutbox)
	
	ON_COMMAND_RANGE(ID_FLAT_TOOLBAR1 , ID_VIEWSORT_TOOLBAR1, OnSelectToolbar)

	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgToolStatusBarDlg message handlers

BOOL CDlgToolStatusBarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	SetTimer(0, 1000, NULL); 
	m_Browser.Create(NULL,NULL,WS_BORDER|WS_VISIBLE,CRect(4,35,478,300),this,NULL);
	m_Browser.Navigate("E:/Internet/DlgToolStatusBar/TSBonDlg.html",NULL,NULL,NULL,NULL);
	CreateFlatToolBar();
	CreateStatusBar();

	return TRUE;

}

void CDlgToolStatusBarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgToolStatusBarDlg::OnPaint() 
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
HCURSOR CDlgToolStatusBarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDlgToolStatusBarDlg::OnFileExit() 
{
	// TODO: Add your command handler code here

	this->EndDialog(IDOK);
}

void CDlgToolStatusBarDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	KillTimer(1);
}

void CDlgToolStatusBarDlg::OnHelpAbout()
{
	AfxMessageBox(IDS_HELP_BUTTON);
}

void CDlgToolStatusBarDlg::OnBold()
{
	AfxMessageBox(IDS_BOLD_BUTTON);
}

void CDlgToolStatusBarDlg::OnStrikeOut()
{
	AfxMessageBox(IDS_STRIKEOUT_BUTTON);
}

void CDlgToolStatusBarDlg::OnDrawing()
{
	AfxMessageBox(IDS_DRAWING_BUTTON);
}

BOOL CDlgToolStatusBarDlg::SetupImages(CImageList* mImageList)
{
	CWinApp* pApp = AfxGetApp();
	mImageList->Create(24, 24, ILC_COLOR8 | ILC_MASK,  9, 9);
	mImageList->Add(pApp->LoadIcon(IDI_HELP));
	mImageList->Add(pApp->LoadIcon(IDI_BOLD));
	mImageList->Add(pApp->LoadIcon(IDI_DRAWING));
	mImageList->Add(pApp->LoadIcon(IDI_STRIKEOUT));
	mImageList->Add(pApp->LoadIcon(IDI_COMP));
	return TRUE;
}

void CDlgToolStatusBarDlg::CreateFlatToolBar()
{

	SetupImages(&m_pImageList);

	TBBUTTON tb;

	m_ToolBar.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|TBSTYLE_FLAT, CRect(0,0,0,0), this, 0);

	m_ToolBar.SetImageList(&m_pImageList);
	tb.iBitmap = 0;
	tb.iString = NULL;
	tb.fsState = TBSTATE_ENABLED;
	tb.fsStyle = TBSTYLE_BUTTON;
	tb.idCommand = ID_HELP_ABOUT;
	m_ToolBar.AddButtons(1, &tb);

	tb.iBitmap = 1;
	tb.idCommand = ID_BOLD;
	m_ToolBar.AddButtons(1, &tb);

	tb.iBitmap = 2;
	tb.idCommand = ID_DRAWING;
	m_ToolBar.AddButtons(1, &tb);

	TBBUTTON tb1;
	tb1.fsStyle = TBSTYLE_SEP;
	m_ToolBar.AddButtons(1, &tb1);

	tb.iBitmap = 3;
	tb.idCommand = ID_STRIKEOUT;
	tb.iString = NULL;
	m_ToolBar.AddButtons(1, &tb);
}

void CDlgToolStatusBarDlg::CreateStatusBar()
{
	CString string; 
	m_StatusBar.Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW, CRect(0,0,0,0), this, 0);

	int strPartDim[4]= {180, 300, 300, 450  -1};
	m_StatusBar.SetParts(4, strPartDim);

	string.LoadString(IDS_PANE0);
	m_StatusBar.SetText(string,0,0);
	string.LoadString(IDS_PANE1);
	m_StatusBar.SetText(string, 1, 0);
	
	string.LoadString(IDS_MYCOMPUTER);
	m_StatusBar.SetText(string, 3 ,SBT_NOBORDERS   );
	m_StatusBar.SetIcon(3, 
		SetIcon(AfxGetApp()->LoadIcon(IDI_COMP),
         FALSE));

}

void CDlgToolStatusBarDlg::OnAboutbox() 
{
	// TODO: Add your command handler code here

//	CAboutDlg dlgAbout;
//	dlgAbout.DoModal();
	CString string;
	string.LoadString(IDS_TITLE);
	ShowAboutBox(string, NULL);
	
}

HWND CDlgToolStatusBarDlg::CreateToolBar(HWND hWnd, int numButtons, BOOL bStandard)
{

	// Toolbar buttons
	TBBUTTON tbButtonsSTD [] = 
	{
		{STD_FILENEW,     IDM_NEW,         TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_FILEOPEN,    IDM_OPEN,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_FILESAVE,    IDM_SAVE,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{0,               0,               TBSTATE_ENABLED, TBSTYLE_SEP,    0L, 0},
		{STD_CUT,         IDM_CUT,         TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_COPY,        IDM_COPY,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_DELETE,      IDM_DELETE,      TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_PASTE,       IDM_PASTE,       TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_REPLACE,     IDM_REPLACE,     TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_REDOW,       IDM_REDOW,       TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_FIND,        IDM_FIND,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{0,               0,               TBSTATE_ENABLED, TBSTYLE_SEP,    0L, 0},
		{STD_PRINT,       IDM_PRINT,       TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{STD_PRINTPRE,    IDM_PRINTPRE,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{0,               0,               TBSTATE_ENABLED, TBSTYLE_SEP,    0L, 0},
		{STD_HELP,        IDM_HELP,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	}; 


	TBBUTTON tbButtonsViewSort [] = 
	{
		{VIEW_DETAILS,    IDM_DETAILS,     TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{VIEW_LARGEICONS, IDM_LARGEICONS,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{VIEW_LIST,       IDM_LIST,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{VIEW_SMALLICONS, IDM_SMALLICONS,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{0,               0,               TBSTATE_ENABLED, TBSTYLE_SEP,    0L, 0},
		{VIEW_SORTDATE,   IDM_SORTDATE,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{VIEW_SORTNAME,   IDM_SORTNAME,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{VIEW_SORTSIZE,   IDM_SORTSIZE,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{VIEW_SORTTYPE,   IDM_SORTTYPE,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
		{0,               0,               TBSTATE_ENABLED, TBSTYLE_SEP,    0L, 0},
		{STD_HELP,        IDM_VIEWHELP,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	}; 

	HWND hWndToolbar = CreateToolbarEx (hWnd, 
		WS_CHILD | 
		WS_BORDER | 
		WS_VISIBLE | 
		WS_CHILD | 
		TBSTYLE_TOOLTIPS, 
		ID_TOOLBAR, 
		11, 
		(HINSTANCE)HINST_COMMCTRL, 
		bStandard ? IDB_STD_SMALL_COLOR : IDB_VIEW_SMALL_COLOR, 
		bStandard ? (LPCTBBUTTON)&tbButtonsSTD : (LPCTBBUTTON)&tbButtonsViewSort, 
		bStandard ? numButtons : 11, 
		0, 
		0, 
		0, 
		0, 
		sizeof (TBBUTTON));

	return hWndToolbar;
}

void CDlgToolStatusBarDlg::OnToolbar(UINT nID)
{
	int id = IDM_NEW - nID;
	AfxMessageBox(IDS_NEW - id);
}

void CDlgToolStatusBarDlg::OnViewSortToolbar(UINT nID)
{
	int id = IDM_DETAILS - nID;
	AfxMessageBox(IDS_DETAILS - id);
}

void CDlgToolStatusBarDlg::OnSelectToolbar(UINT nID) 
{
	// TODO: Add your command handler code here
	DestroyToolBars();
	switch (nID)
	{
	case ID_FLAT_TOOLBAR1:
		CreateFlatToolBar();
		break;
	case ID_STANDARD_TOOLBAR1:
		CreateToolBar(this->m_hWnd, 16, TRUE);
		break;
	case ID_VIEWSORT_TOOLBAR1:
		CreateToolBar(this->m_hWnd, 16, FALSE);
		break;
	}
}

void CDlgToolStatusBarDlg::OnUpdateToolbarStyle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
//	pCmdUI->Enable();
//	BOOL bChecked = FALSE;
//	switch (pCmdUI->m_nID)
//	{
//		case ID_FLAT_TOOLBAR1:
//			bChecked = TRUE;
//			break;
//		case ID_STANDARD_TOOLBAR1:
//			bChecked = TRUE;
//			break;
//		case ID_VIEWSORT_TOOLBAR1:
//			bChecked = TRUE;
//			break;
//		default:
//			bChecked = FALSE;
//			break;
//	}
//	pCmdUI->SetCheck(bChecked ? 1 : 0);	
}

void CDlgToolStatusBarDlg::DestroyToolBars()
{
	if(hWndToolbar != NULL)
		hWndToolbar = NULL;

	if(m_ToolBar.m_hWnd != NULL)
	{
		m_pImageList.DeleteImageList();
		m_ToolBar.DestroyWindow();
	}
}

void CDlgToolStatusBarDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    time_t t;
    struct tm *ptm;
    time(&t);
    ptm = localtime(&t);
	char sDate[11];
	sprintf(sDate, "%.19s", asctime(ptm));
	m_StatusBar.SetText(sDate, 1, 0);
	CDialog::OnTimer(nIDEvent);
}
