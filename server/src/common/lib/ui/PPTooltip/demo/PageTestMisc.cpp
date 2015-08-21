// PageTestMisc.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageTestMisc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTestMisc property page

IMPLEMENT_DYNCREATE(CPageTestMisc, CPropertyPage)

CPageTestMisc::CPageTestMisc() : CPropertyPage(CPageTestMisc::IDD)
{
	//{{AFX_DATA_INIT(CPageTestMisc)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bResizedButton = FALSE;
}

CPageTestMisc::~CPageTestMisc()
{
}

void CPageTestMisc::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTestMisc)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTestMisc, CPropertyPage)
	//{{AFX_MSG_MAP(CPageTestMisc)
	ON_BN_CLICKED(IDC_BUTTON1, OnRuntimeResize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTestMisc message handlers

BOOL CPageTestMisc::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	//Dynamically created
	CRect rect;
	GetDlgItem(IDC_STATIC1)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_pButton = new CButton;
	m_pButton->Create("Dynamic button", WS_CHILD | WS_VISIBLE, rect, this, IDC_BUTTON2);
	
	m_tooltip.Create(this);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), _T("<center><h2>Runtime resize</h2><br><hr color=blue></center><br>Click this button to resize it"));
	m_tooltip.AddTool(GetDlgItem(IDC_COMBO1), _T("<center><h2>Child Window</h2><br><hr color=blue></center><br>A tooltip for a child window"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON2), _T("<center><h2>Dynamic control</h2><br><hr color=blue></center><br>This control was dynamic created"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageTestMisc::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CPageTestMisc::OnRuntimeResize() 
{
	CButton * pButton = (CButton*)GetDlgItem(IDC_BUTTON1);
	CRect rect;
	pButton->GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (m_bResizedButton)
	{
		rect.DeflateRect(0, 0, 50, 10);
		m_bResizedButton = FALSE;
	}
	else
	{
		rect.InflateRect(0, 0, 50, 10);
		m_bResizedButton = TRUE;
	}
	pButton->MoveWindow(rect);
}
