// TestBed.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestBed.h"
#include "Label.h"
#include "Prop.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp

BEGIN_MESSAGE_MAP(CTestBedApp, CWinApp)
	//{{AFX_MSG_MAP(CTestBedApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp construction

CTestBedApp::CTestBedApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestBedApp object

CTestBedApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp initialization

BOOL CTestBedApp::InitInstance()
{

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CAboutDlg dlg;
	dlg.DoModal();

	CPropertySheet pdlg;
	
	CProp pg;

	pdlg.AddPage(&pg);
	pdlg.DoModal();


	return FALSE;
}


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_LINKMAIL, m_stcMail);
	DDX_Control(pDX, IDC_GRADIENT, m_lblGradient);
	DDX_Control(pDX, IDC_MONTY2, m_lblRotate);
	DDX_Control(pDX, IDC_3D, m_3D);
	DDX_Control(pDX, IDC_3D2, m_3D2);
	DDX_Control(pDX, IDC_TRANS, m_lblTrans);
	DDX_Control(pDX, IDC_LINK, m_link);
	DDX_Control(pDX, IDC_FLASH, m_flash);
	DDX_Control(pDX, IDC_MONTY, m_monty);
	DDX_Control(pDX, IDC_FSIZE, m_fsize);
	DDX_Control(pDX, IDC_SUNKEN, m_sunken);
	DDX_Control(pDX, IDC_BORDER, m_border);
	DDX_Control(pDX, IDC_BOLD, m_bold);
	DDX_Control(pDX, IDC_TULINE, m_uline);
	DDX_Control(pDX, IDC_TCOLOR, m_tcolor);
	DDX_Control(pDX, IDC_ITALICS, m_italics);
	DDX_Control(pDX, IDC_FNAME, m_fname);
	DDX_Control(pDX, IDC_BCOLOR, m_bcolor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp commands

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_fname.SetFontName("System");
	m_fsize.SetFontSize(14);
	m_uline.SetFontUnderline(TRUE);
	m_tcolor.SetTextColor(RGB(255,0,0));
	m_bcolor.SetBkColor(RGB(0,255,255));
	m_italics.SetFontItalic(TRUE);
	m_bold.SetFontBold(TRUE);
	m_border.SetBorder(TRUE);
	m_sunken.SetSunken(TRUE);

	m_lblGradient.SetBkColor(RGB(255,255,255),RGB(0,0,255), CLabel::Gradient);

	m_monty
		.SetFontName("Arial")
		.SetFontSize(12)
		.SetTextColor(RGB(255,255,0))
		.SetFontUnderline(TRUE)
		.SetBkColor(RGB(0,0,0))
		.SetFontItalic(TRUE)
		.SetFontBold(TRUE)
		.SetBorder(TRUE)
		.SetSunken(TRUE);

	
	m_flash.SetBkColor(RGB(0,0,0));
	m_flash.SetTextColor(RGB(255,0,0));
	m_flash.SetFontBold(TRUE);
	m_flash.SetTextColor(RGB(0,255,0));
	
	m_flash.SetWindowText(_T("Payload\r\nBay"));
	m_flash.FlashText(TRUE);

	m_stcMail.SetMailLink(TRUE,FALSE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(LoadCursor(NULL, IDC_HAND));

	m_link.SetLink(TRUE,FALSE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(LoadCursor(NULL, IDC_HAND));

	
	m_lblTrans.SetTextColor(RGB(255,255,255)).SetTransparent(TRUE);

	m_3D.SetFont3D(TRUE,CLabel::Sunken)
		.SetFontName("Arial")
		.SetFontSize(16)
		.SetFontBold(TRUE);

	m_3D2.SetFont3D(TRUE,CLabel::Raised)
		.SetText3DHiliteColor(RGB(0,0,255))
		.SetFontName("Times New Roman")
		.SetFontSize(16)
		.SetFontBold(TRUE);


	m_nAngle = 0;
	m_lblRotate
		.SetTextColor(RGB(192,0,0))
		.SetFontSize(14)
		.SetFontBold(TRUE)
		.SetFontName("Arial").SetRotationAngle(m_nAngle,true);

	SetTimer(ID_ROTATE_TIMER,100,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CAboutDlg::OnButton1() 
{

}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	if (m_nAngle == 360)
		m_nAngle = 0;

	m_nAngle+=10;

	m_lblRotate.SetRotationAngle(m_nAngle,true);
	
	CDialog::OnTimer(nIDEvent);
}
