// StatusPanes.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "StatusPanes.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusPanesApp

BEGIN_MESSAGE_MAP(CStatusPanesApp, CWinApp)
	//{{AFX_MSG_MAP(CStatusPanesApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusPanesApp construction

CStatusPanesApp::CStatusPanesApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStatusPanesApp object

CStatusPanesApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStatusPanesApp initialization

BOOL CStatusPanesApp::InitInstance()
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
	SetRegistryKey( _T("Foss") );


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

//	// The one and only window has been initialized, so show and update it.
//	pFrame->ShowWindow(SW_SHOW);
//	pFrame->UpdateWindow();

	// window placement persistence
	pFrame->ActivateFrame( SW_SHOW );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStatusPanesApp message handlers


// App command to run the dialog
void CStatusPanesApp::OnAppAbout()
{
	VERIFY( ProfUISAbout() );
}

/////////////////////////////////////////////////////////////////////////////
// CStatusPanesApp message handlers

