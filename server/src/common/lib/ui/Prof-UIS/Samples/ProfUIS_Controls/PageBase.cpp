// PageBase.cpp : implementation file
//

#include "stdafx.h"
#include "profuis_controls.h"
#include "PageBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageBase dialog

CPageBase::CPageBase(UINT _IDD, CWnd* pParent /*=NULL*/)
	: CExtResizableDialog(_IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageBase)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageBase::DoDataExchange(CDataExchange* pDX)
{
	CExtResizableDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageBase)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageBase, CExtResizableDialog)
	//{{AFX_MSG_MAP(CPageBase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageBase message handlers

BOOL CPageBase::OnInitDialog() 
{
	CExtResizableDialog::OnInitDialog();
	
	ShowSizeGrip( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void CPageBase::PostNcDestroy() 
{
	CExtResizableDialog::PostNcDestroy();
	delete this;	
}
