#include "stdafx.h"
#include "GenericMFC.h"
#include "GenericMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDS_MAILADDR	_T("mailto:davide_calabro@yahoo.com")
#define IDS_WEBADDR		_T("http://www.softechsoftware.it")

CGenericMFCDlg::CGenericMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGenericMFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenericMFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGenericMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenericMFCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CLOCKFRAME, m_Clock);

	DDX_Control(pDX, IDCANCEL, m_btnExit);

	DDX_Control(pDX, IDC_EMAILLINK, m_EMailLink);
	DDX_Control(pDX, IDC_HOMEPAGELINK, m_HomePageLink);
}

BEGIN_MESSAGE_MAP(CGenericMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CGenericMFCDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGenericMFCDlg::OnInitDialog()
{
	COLORREF	crBtnColor;

	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	// Calculate a color effect for hilighting the button
	crBtnColor = ::GetSysColor(COLOR_BTNFACE) + RGB(30, 30, 30);

	// Button exit
	m_btnExit.SetThemeHelper(&m_Theme);
	m_btnExit.SetIcon(IDI_NO3, IDI_NO4);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_IN, crBtnColor);
	m_btnExit.SetTooltipText(_T("Close the application"));

	// Set HyperLink for E-Mail
	m_EMailLink.SetURL(IDS_MAILADDR);
	m_EMailLink.SetUnderline(CHyperLink::ulAlways);

	// Set HyperLink for Home Page
	m_HomePageLink.SetURL(IDS_WEBADDR);
	m_HomePageLink.SetUnderline(CHyperLink::ulAlways);

	// Start clock
	m_Clock.Start(IDB_CLOCKST_PANE, IDB_CLOCKST_BIG, IDB_CLOCKST_SMALL);
	
	return TRUE;
} // End of OnInitDialog
