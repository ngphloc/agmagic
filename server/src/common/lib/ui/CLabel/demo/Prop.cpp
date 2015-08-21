// Prop.cpp : implementation file
//

#include "stdafx.h"
#include "testbed.h"
#include "Prop.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProp property page

IMPLEMENT_DYNCREATE(CProp, CPropertyPage)

CProp::CProp() : CPropertyPage(CProp::IDD)
{
	//{{AFX_DATA_INIT(CProp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CProp::~CProp()
{
}

void CProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProp)
	DDX_Control(pDX, IDC_TEST, m_stc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProp, CPropertyPage)
	//{{AFX_MSG_MAP(CProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProp message handlers

BOOL CProp::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}

BOOL CProp::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_stc.SetTextColor(RGB(255,0,0));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
