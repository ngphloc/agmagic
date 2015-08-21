// CxSkinButtonDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CxSkinButtonDemo.h"
#include "CxSkinButtonDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCxSkinButtonDemoDlg dialog

CCxSkinButtonDemoDlg::CCxSkinButtonDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCxSkinButtonDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCxSkinButtonDemoDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CCxSkinButtonDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCxSkinButtonDemoDlg)
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_RADIO3, m_radio3);
	DDX_Control(pDX, IDC_RADIO2, m_radio2);
	DDX_Control(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_BUTTON1, m_btn5);
	DDX_Control(pDX, IDC_STX1, m_stx1);
	DDX_Control(pDX, IDC_BUTTON7, m_btn4);
	DDX_Control(pDX, IDC_BUTTON5, m_btn2);
	DDX_Control(pDX, IDC_BUTTON4, m_btn1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCxSkinButtonDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCxSkinButtonDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCxSkinButtonDemoDlg message handlers

BOOL CCxSkinButtonDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_btn1.SetSkin(IDB_LNORM,IDB_LDOWN,IDB_LOVER,IDB_LGRAY,0,IDB_LMASK,0,0,0);
	m_btn1.SetToolTipText("Ying");
	m_btn2.SetSkin(IDB_RNORM,IDB_RDOWN,IDB_ROVER,IDB_RGRAY,0,IDB_RMASK,0,0,0);
	m_btn2.SetToolTipText("Yang");

	m_btn4.SetTextColor(RGB(255,0,0));
	m_btn4.SetToolTipText("Button1");
	m_btn4.SetSkin(IDB_B1NORM,IDB_B1DOWN,IDB_B1OVER,IDB_B1GRAY,0,IDB_B1MASK,0,0,0);

	m_stx1.SetTextColor(RGB(128,255,128));
//	m_stx1.SetTextStyle(SST_SUNKEN);

	m_btn5.SetToolTipText("Test Button");
	m_btn5.SetSkin(IDB_B3NORM,IDB_B3OVER,IDB_B3OVER,0,0,0,0,1,0);


	m_radio1.SetSkin(IDB_EYECL,IDB_EYERED,IDB_EYEGRAY,IDB_EYECL,IDB_EYEF,IDB_EYEMASK,0,0,0);
	m_radio2.SetSkin(IDB_EYECL,IDB_EYEBLU,IDB_EYEGRAY,IDB_EYECL,IDB_EYEF,IDB_EYEMASK,0,0,0);
	m_radio3.SetSkin(IDB_EYECL,IDB_EYEGREEN,IDB_EYEGRAY,IDB_EYECL,IDB_EYEF,IDB_EYEMASK,0,0,0);
	m_radio1.SetToolTipText("Radio1");
	m_radio2.SetToolTipText("Radio2");
	m_radio3.SetToolTipText("Radio3");
	
	m_radio2.SetCheck(1);

	m_check1.SetSkin(IDB_EYECL,IDB_EYERED,IDB_EYEGRAY,IDB_EYECL,IDB_EYEF,IDB_EYEMASK,0,0,0);
	m_check2.SetSkin(IDB_EYECL,IDB_EYEBLU,IDB_EYEGRAY,IDB_EYECL,IDB_EYEF,IDB_EYEMASK,0,0,0);
	m_check3.SetSkin(IDB_EYECL,IDB_EYEGREEN,IDB_EYEGRAY,IDB_EYECL,IDB_EYEF,IDB_EYEMASK,0,0,0);
	m_check1.SetToolTipText("Check1");
	m_check2.SetToolTipText("Check2");
	m_check3.SetToolTipText("Check3");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCxSkinButtonDemoDlg::OnPaint() 
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

HCURSOR CCxSkinButtonDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCxSkinButtonDemoDlg::OnButton7() 
{
	m_stx1.SetTextColor(RGB(128,255,128));
	m_stx1.SetWindowText(" Button1 clicked");
}

void CCxSkinButtonDemoDlg::OnButton5() 
{
	m_stx1.SetTextColor(RGB(0,255,255));
	m_stx1.SetWindowText(" YANG clicked");
}

void CCxSkinButtonDemoDlg::OnButton4() 
{
	m_stx1.SetTextColor(RGB(255,0,128));
	m_stx1.SetWindowText(" YING clicked");
	m_btn4.EnableWindow(!m_btn4.IsWindowEnabled());
}

void CCxSkinButtonDemoDlg::OnButton1() 
{
	m_stx1.SetTextColor(RGB(255,255,255));
	m_stx1.SetWindowText(" Test clicked");
}
