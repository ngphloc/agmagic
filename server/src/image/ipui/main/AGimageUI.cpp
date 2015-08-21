#include "AGimageUI.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

#if AGMAGIC_SUPPORT_MFC

/**************************CAGimageDlg dialog************************************************/

CAGimageDlg::CAGimageDlg(aguint32 nIDTemplate, CAGimage* pAGimage, const agtchar* szTitle, agbool bDeleteAGimage, agbool bCopyAGimage, CWnd* pParent)
	: CDialog()
{
	//{{AFX_DATA_INIT(CAGimageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pAGimage=NULL;
	SelectAGimage(pAGimage,bDeleteAGimage,bCopyAGimage);
	Create(nIDTemplate,pParent);
	if(szTitle!=NULL)
		SetWindowText(szTitle);
}
CAGimage*	CAGimageDlg::SelectAGimage(CAGimage* pAGimage, agbool bDeleteAGimage, agbool bCopyAGimage)
{
	CAGimage* pAGimageOld=NULL;
	if(m_bDeleteAGimage)
		delete m_pAGimage;
	else
		pAGimageOld=m_pAGimage;

	if(bCopyAGimage)
		AGMAGICIP_NEW_AND_COPY(m_pAGimage,pAGimage)
	else
		m_pAGimage=pAGimage;

	m_bDeleteAGimage=bDeleteAGimage;
	return pAGimageOld;
}
CAGimageDlg* CAGimageDlg::ShowAGimageDlg(aguint32 nIDTemplate, CAGimage* pAGimage, const agtchar* szTitle)
{
	CAGimageDlg*	pDlg=new CAGimageDlg(nIDTemplate,pAGimage,szTitle);
	pDlg->ShowWindow(SW_SHOWNORMAL);
	return pDlg;
}
void CAGimageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGimageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
void CAGimageDlg::OnOK()
{
	if(!UpdateData(TRUE))
		return;
	DestroyWindow();
}
void CAGimageDlg::OnCancel()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(CAGimageDlg, CDialog)
	//{{AFX_MSG_MAP(CAGimageDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageDlg message handlers

void CAGimageDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	if(m_pAGimage!=NULL && m_bDeleteAGimage)
	{
		delete m_pAGimage;
		m_pAGimage=NULL;
	}
	delete this;
}

void CAGimageDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(m_pAGimage!=NULL)
		m_pAGimage->Draw(dc.GetSafeHdc());
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CAGimageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAGimage!=NULL)
	{
		CRect rc;
		rc.left=rc.top=0;
		rc.right=m_pAGimage->GetWidth();
		rc.bottom=m_pAGimage->GetHeight();
		CalcWindowRect(&rc,CWnd::adjustOutside);
		SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


int CAGimageDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT(FALSE);
	return 0;//return CDialog::DoModal();
}


/**************************CAGimageModalDlg dialog************************************************/

CAGimageModalDlg::CAGimageModalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, const agtchar* szTitle, agbool bDeleteAGimage, agbool bCopyAGimage, CWnd* pParent)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CAGimageModalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pAGimage=NULL;
	SelectAGimage(pAGimage,bDeleteAGimage,bCopyAGimage);

	m_bkBrush.CreateSolidBrush(AGMAGIC_DIALOG_BKCOLOR);

	//if(szTitle!=NULL)	SetWindowText(szTitle);
}
CAGimage*	CAGimageModalDlg::SelectAGimage(CAGimage* pAGimage, agbool bDeleteAGimage, agbool bCopyAGimage)
{
	CAGimage* pAGimageOld=NULL;
	if(m_bDeleteAGimage)
		delete m_pAGimage;
	else
		pAGimageOld=m_pAGimage;

	if(bCopyAGimage)
		AGMAGICIP_NEW_AND_COPY(m_pAGimage,pAGimage)
	else
		m_pAGimage=pAGimage;

	m_bDeleteAGimage=bDeleteAGimage;
	return pAGimageOld;
}
agint32 CAGimageModalDlg::ShowAGimageDlg(aguint32 nIDTemplate, CAGimage* pAGimage, const agtchar* szTitle)
{
	CAGimageModalDlg	dlg(nIDTemplate,pAGimage,szTitle);
	return dlg.DoModal();
}
void CAGimageModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGimageModalDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAGimageModalDlg, CDialog)
	//{{AFX_MSG_MAP(CAGimageModalDlg)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageModalDlg message handlers

void CAGimageModalDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(m_pAGimage!=NULL)	m_pAGimage->Draw(dc.GetSafeHdc());
	// Do not call CDialog::OnPaint() for painting messages
}
HBRUSH CAGimageModalDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if(nCtlColor==CTLCOLOR_DLG)
		return (HBRUSH)m_bkBrush.GetSafeHandle();

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}
BOOL CAGimageModalDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAGimage!=NULL)
	{
		CRect rc;
		rc.left=rc.top=0;
		rc.right=m_pAGimage->GetWidth();
		rc.bottom=m_pAGimage->GetHeight();
		CalcWindowRect(&rc,CWnd::adjustOutside);
		SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return False
}



int CAGimageModalDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	int code=CDialog::DoModal();
	if(m_pAGimage!=NULL && m_bDeleteAGimage)
	{
		delete m_pAGimage;
		m_pAGimage=NULL;
	}
	return code;
}

/**************************CAGimageADlg dialog************************************************/

#include "../../ip/main/AGimageUtil.h"

CAGimageADlg::CAGimageADlg(aguint32 nIDTemplate, CAGptrArray *pAGimageA, aguint32 nCols, agbool bDeleteAGimageA, agbool bCopyAGimageA, CWnd* pParent)
{
	
	//{{AFX_DATA_INIT(CAGimageADlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if(bCopyAGimageA)
	{
		aguint32 n=pAGimageA->GetSize();
		m_pAGimageA=new CAGptrArray();
		for(aguint32 i=0; i<n; i++)
		{
			CAGimage* pAGimage=NULL;
			AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)pAGimageA->GetAt(i)))
			m_pAGimageA->Add(pAGimage);
		}
	}
	else	
		m_pAGimageA=pAGimageA;
	m_bDeleteAGimageA=bDeleteAGimageA;
	m_nCols=nCols;
	m_pos=CPoint(0,0);
	Create(nIDTemplate,pParent);
	SetWindowText(_T("Image Array"));
}
CAGimageADlg* CAGimageADlg::ShowAGimageADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageA, aguint32 nCols)
{
	CAGimageADlg* pDlg=new CAGimageADlg(nIDTemplate,pAGimageA,nCols);
	pDlg->ShowWindow(SW_SHOWNORMAL);
	return pDlg;
}

void CAGimageADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGimageADlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CAGimageADlg::OnOK()
{
	if(!UpdateData(TRUE))
		return;
	DestroyWindow();
}
void CAGimageADlg::OnCancel()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(CAGimageADlg, CDialog)
	//{{AFX_MSG_MAP(CAGimageADlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageADlg message handlers

BOOL CAGimageADlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAGimageA!=NULL)
	{
		CRect rc(0,0,0,0);
		CSize size;
		CAGimageMicUtil::DrawA(m_pos,m_nCols,m_pAGimageA,NULL,&size,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));

		rc.right=size.cx;
		rc.bottom=size.cy;
		CalcWindowRect(&rc,CWnd::adjustOutside);
		SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAGimageADlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(m_pAGimageA!=NULL)
		CAGimageMicUtil::DrawA(m_pos,m_nCols,m_pAGimageA,dc.GetSafeHdc(),NULL,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));

	// Do not call CDialog::OnPaint() for painting messages
}

void CAGimageADlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	if(m_bDeleteAGimageA)
	{
		DELETE_AGMAGICIP_ARRAYPTR(m_pAGimageA,agtrue)
		m_pAGimageA=NULL;
	}
	delete this;
}

int CAGimageADlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT(agfalse);
	return 0;
	//return CDialog::DoModal();
}


/**************************CAGimageAModalDlg dialog************************************************/

#include "../../ip/main/AGimageUtil.h"

CAGimageAModalDlg::CAGimageAModalDlg(aguint32 nIDTemplate, CAGptrArray* pAGimageA, aguint32 nCols, agbool bDeleteAGimageA, agbool bCopyAGimageA, CWnd* pParent)
	:CDialog(nIDTemplate,pParent)
{
	//{{AFX_DATA_INIT(CAGimageAModalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if(bCopyAGimageA)
	{
		aguint32 n=pAGimageA->GetSize();
		m_pAGimageA=new CAGptrArray();
		for(aguint32 i=0; i<n; i++)
		{
			CAGimage* pAGimage=NULL;
			AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)pAGimageA->GetAt(i)))

			m_pAGimageA->Add(pAGimage);
		}
	}
	else	
		m_pAGimageA=pAGimageA;
	m_bDeleteAGimageA=bDeleteAGimageA;
	m_nCols=nCols;
	m_pos=CPoint(0,0);

	m_bkBrush.CreateSolidBrush(AGMAGIC_DIALOG_BKCOLOR);

	//SetWindowText(_T("Image Array"));
}
agint32 CAGimageAModalDlg::ShowAGimageADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageA, aguint32 nCols)
{
	CAGimageAModalDlg dlg(nIDTemplate,pAGimageA,nCols);
	return dlg.DoModal();
}

void CAGimageAModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGimageAModalDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAGimageAModalDlg, CDialog)
	//{{AFX_MSG_MAP(CAGimageAModalDlg)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageAModalDlg message handlers

BOOL CAGimageAModalDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAGimageA!=NULL)
	{
		CSize size;
		CAGimageMicUtil::DrawA(m_pos,m_nCols,m_pAGimageA,NULL,&size,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));

		CRect rc(0,0,0,0);
		rc.right=size.cx;
		rc.bottom=size.cy;
		CalcWindowRect(&rc,CWnd::adjustOutside);
		SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAGimageAModalDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(m_pAGimageA!=NULL)
		CAGimageMicUtil::DrawA(m_pos,m_nCols,m_pAGimageA,dc.GetSafeHdc(),NULL,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));
	// Do not call CDialog::OnPaint() for painting messages
}
HBRUSH CAGimageAModalDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if(nCtlColor==CTLCOLOR_DLG)
		return (HBRUSH)m_bkBrush.GetSafeHandle();

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}
int CAGimageAModalDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	int code=CDialog::DoModal();
	if(m_bDeleteAGimageA)
	{
		DELETE_AGMAGICIP_ARRAYPTR(m_pAGimageA,agtrue)
		m_pAGimageA=NULL;
	}
	return code;
}

/**************************CAGimageAAbuDlg dialog************************************************/

#include "../../ip/main/AGimageUtil.h"

CAGimageAAbuDlg::CAGimageAAbuDlg(aguint32 nIDTemplate, CAGptrArray* pAGimageAA, agbool bDeleteImageExAA, agbool bCopyAGimageAA, CWnd* pParent)
{
	
	//{{AFX_DATA_INIT(CAGimageAAbuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if(bCopyAGimageAA)
	{
		aguint32 n=pAGimageAA->GetSize();
		m_pAGimageAA=new CAGptrArray();
		for(aguint32 i=0; i<n; i++)
		{
			CAGptrArray*	pAGimageA=new CAGptrArray();
			CAGptrArray*	pAGimageTempA=(CAGptrArray*)pAGimageAA->GetAt(i);
			aguint32		m=pAGimageTempA->GetSize();
			for(aguint32 j=0; j<m; j++)
			{
				CAGimage* pAGimage=NULL;
				AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)pAGimageTempA->GetAt(j)))
				pAGimageA->Add(pAGimage);
			}
			m_pAGimageAA->Add(pAGimageA);
		}
	}
	else	
		m_pAGimageAA=pAGimageAA;
	m_pos=CPoint(0,0);
	m_bDeleteAGimageAA=bDeleteImageExAA;
	Create(nIDTemplate,pParent);
	SetWindowText(_T("Image Array"));
}
CAGimageAAbuDlg* CAGimageAAbuDlg::ShowAGimageAADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageAA)
{
	CAGimageAAbuDlg* pDlg=new CAGimageAAbuDlg(nIDTemplate,pAGimageAA);
	pDlg->ShowWindow(SW_SHOWNORMAL);
	return pDlg;
}

void CAGimageAAbuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGimageAAbuDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
void CAGimageAAbuDlg::OnOK()
{
	if(!UpdateData(TRUE))
		return;
	DestroyWindow();
}
void CAGimageAAbuDlg::OnCancel()
{
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CAGimageAAbuDlg, CDialog)
	//{{AFX_MSG_MAP(CAGimageAAbuDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageAAbuDlg message handlers

void CAGimageAAbuDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();

	if(m_bDeleteAGimageAA)
	{
		DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR(m_pAGimageAA,agtrue)
		m_pAGimageAA=NULL;
	}
	delete this;

}

int CAGimageAAbuDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT(agfalse);
	return 0;
	//return CDialog::DoModal();
}

BOOL CAGimageAAbuDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAGimageAA!=NULL)
	{
		CSize size;
		CAGimageMicUtil::DrawAA(m_pos,m_pAGimageAA,NULL,&size,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));

		CRect rc(0,0,0,0);
		rc.right=size.cx;
		rc.bottom=size.cy;
		CalcWindowRect(&rc,CWnd::adjustOutside);
		SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAGimageAAbuDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	if(m_pAGimageAA!=NULL)
		CAGimageMicUtil::DrawAA(m_pos,m_pAGimageAA,dc.GetSafeHdc(),NULL,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));
}


/**************************CAGimageAAbuModalDlg dialog************************************************/

#include "../../ip/main/AGimageUtil.h"
CAGimageAAbuModalDlg::CAGimageAAbuModalDlg(aguint32 nIDTemplate, CAGptrArray* pAGimageAA, agbool bDeleteAGimageAA, agbool bCopyAGimageAA, CWnd* pParent)
	:CDialog(nIDTemplate,pParent)
{
	//{{AFX_DATA_INIT(CAGimageAAbuModalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if(bCopyAGimageAA)
	{
		aguint32 n=pAGimageAA->GetSize();
		m_pAGimageAA=new CAGptrArray();
		for(aguint32 i=0; i<n; i++)
		{
			CAGptrArray*	pAGimageA=new CAGptrArray();
			CAGptrArray*	pAGimageTempA=(CAGptrArray*)pAGimageAA->GetAt(i);
			aguint32		m=pAGimageTempA->GetSize();
			for(aguint32 j=0; j<m; j++)
			{
				CAGimage* pAGimage=NULL;
				AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)pAGimageTempA->GetAt(j)))
				pAGimageA->Add(pAGimage);
			}
			m_pAGimageAA->Add(pAGimageA);
		}
	}
	else	
		m_pAGimageAA=pAGimageAA;
	m_bDeleteAGimageAA=bDeleteAGimageAA;
	m_pos=CPoint(0,0);
}
agint32 CAGimageAAbuModalDlg::ShowAGimageAADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageAA)
{
	CAGimageAAbuModalDlg dlg(nIDTemplate,pAGimageAA);
	return dlg.DoModal();
}


void CAGimageAAbuModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGimageAAbuModalDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAGimageAAbuModalDlg, CDialog)
	//{{AFX_MSG_MAP(CAGimageAAbuModalDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageAAbuModalDlg message handlers

int CAGimageAAbuModalDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	int code=CDialog::DoModal();
	if(m_bDeleteAGimageAA)
	{
		DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR(m_pAGimageAA,agtrue)
		m_pAGimageAA=NULL;
	}
	return code;
}

BOOL CAGimageAAbuModalDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAGimageAA!=NULL)
	{
		CRect rc(0,0,0,0);
		CSize size;
		CAGimageMicUtil::DrawAA(m_pos,m_pAGimageAA,NULL,&size,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));

		rc.right=size.cx;
		rc.bottom=size.cy;
		CalcWindowRect(&rc,CWnd::adjustOutside);
		SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAGimageAAbuModalDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	if(m_pAGimageAA!=NULL)
		CAGimageMicUtil::DrawAA(m_pos,m_pAGimageAA,dc.GetSafeHdc(),NULL,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));
}

/***************************class CAGimageFrame*********************************/

IMPLEMENT_DYNCREATE(CAGimageFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CAGimageFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CAGimageFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
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
// CAGimageFrame construction/destruction

CAGimageFrame::CAGimageFrame()
{
	// TODO: add member initialization code here
	
}

CAGimageFrame::~CAGimageFrame()
{
}
CFrameWnd*	CAGimageFrame::CreateFrameWnd(CDocTemplate* pDocTemplate, agtchar* szTitle)
{
	CDocument*	pDoc=pDocTemplate->CreateNewDocument();
	CFrameWnd*	pFrame=(CFrameWnd*)pDocTemplate->CreateNewFrame(pDoc,NULL);
	pDocTemplate->InitialUpdateFrame(pFrame,pDoc);

	if(szTitle!=NULL)	pFrame->SetWindowText(szTitle);
	return pFrame;
}
int CAGimageFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
#ifdef 	IDR_MAINFRAME
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
#else
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) )
#endif
	{
		TRACE0(_T("Failed to create toolbar\n"));
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0(_T("Failed to create status bar\n"));
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CAGimageFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAGimageFrame diagnostics

#ifdef _DEBUG
void CAGimageFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CAGimageFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGimageFrame message handlers

/***************************class CAGimageSplitFrame*********************************/

IMPLEMENT_DYNCREATE(CAGimageSplitFrame, CFrameWnd)

CAGimageSplitFrame::CAGimageSplitFrame()
{
}

CAGimageSplitFrame::~CAGimageSplitFrame()
{
}


BEGIN_MESSAGE_MAP(CAGimageSplitFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CAGimageSplitFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageSplitFrame message handlers
BOOL CAGimageSplitFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	/*
	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CAGimageListView),CSize(0,0),pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CAGimageView),CSize(0,0),pContext);
	
	CRect rc;
	m_wndSplitter.GetClientRect(&rc);
	m_wndSplitter.SetColumnInfo(0,150,0);
	return TRUE;
	*/
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

/***************************class CAGimageMDIFrame*********************************/

IMPLEMENT_DYNAMIC(CAGimageMDIFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CAGimageMDIFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CAGimageMDIFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageMDIFrame construction/destruction

CAGimageMDIFrame::CAGimageMDIFrame()
{
	// TODO: add member initialization code here
	
}

CAGimageMDIFrame::~CAGimageMDIFrame()
{
}

int CAGimageMDIFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
#ifdef 	IDR_MAINFRAME
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
#else
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) )
#endif
	{
		TRACE0(_T("Failed to create toolbar\n"));
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0(_T("Failed to create status bar\n"));
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CAGimageMDIFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAGimageMDIFrame diagnostics

#ifdef _DEBUG
void CAGimageMDIFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CAGimageMDIFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGimageMDIFrame message handlers


/***************************class CAGimageMDIChildFrame*********************************/

IMPLEMENT_DYNCREATE(CAGimageMDIChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CAGimageMDIChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CAGimageMDIChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageMDIChildFrame construction/destruction

CAGimageMDIChildFrame::CAGimageMDIChildFrame()
{
	// TODO: add member initialization code here
	
}

CAGimageMDIChildFrame::~CAGimageMDIChildFrame()
{
}

BOOL CAGimageMDIChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAGimageMDIChildFrame diagnostics

#ifdef _DEBUG
void CAGimageMDIChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CAGimageMDIChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGimageMDIChildFrame message handlers

/***************************class CAGimageSplitMDIChildFrame*******************************/

IMPLEMENT_DYNCREATE(CAGimageSplitMDIChildFrame, CMDIChildWnd)

CAGimageSplitMDIChildFrame::CAGimageSplitMDIChildFrame()
{
}

CAGimageSplitMDIChildFrame::~CAGimageSplitMDIChildFrame()
{
}


BEGIN_MESSAGE_MAP(CAGimageSplitMDIChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CAGimageSplitMDIChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageSplitMDIChildFrame message handlers

BOOL CAGimageSplitMDIChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	/*
	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CAGimageListView),CSize(0,0),pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CAGimageView),CSize(0,0),pContext);
	
	CRect rc;
	m_wndSplitter.GetClientRect(&rc);
	m_wndSplitter.SetColumnInfo(0,150,0);
	return TRUE;
	*/
	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

/***************************class CAGimageDoc*******************************/

IMPLEMENT_DYNCREATE(CAGimageDoc, CDocument)

CAGimageDoc::CAGimageDoc()
{
	m_pAGimage=(CAGimage*)CreateAGimage();
}

BOOL CAGimageDoc::OnNewDocument()
{
	ASSERT(FALSE);
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CAGimageDoc::~CAGimageDoc()
{
	if(m_pAGimage!=NULL)
		delete m_pAGimage;
}


BEGIN_MESSAGE_MAP(CAGimageDoc, CDocument)
	//{{AFX_MSG_MAP(CAGimageDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageDoc diagnostics

#ifdef _DEBUG
void CAGimageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAGimageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGimageDoc serialization

void CAGimageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	m_pAGimage->Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CAGimageDoc commands
BOOL CAGimageDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	if(!m_pAGimage->IsValid())
	{
		MessageBox(NULL,_T("Warning : Not Image File or Invalid"),_T("Warning"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	UpdateAllViews(NULL);
	return TRUE;
}

/***************************class CAGimageView*******************************/

IMPLEMENT_DYNCREATE(CAGimageView, CScrollView)

CAGimageView::CAGimageView()
{
	m_pAGimage=NULL;
	m_bDeleteAGimage=agfalse;;
	m_docSize=CSize(0,0);
	m_pageSize=CSize(0,0);
	m_lineSize=CSize(0,0);
	INIT_GRAB_FLAT_CUR

	m_bMouseDown=agfalse;
	m_bScroll=agfalse;
	m_ptCursorCurPos=CPoint(0,0);
	m_ptCursorOldPos=CPoint(0,0);

	m_pos=CPoint(0,0);
}

CAGimageView::~CAGimageView()
{
	if(m_bDeleteAGimage)
		delete m_pAGimage;
}


BEGIN_MESSAGE_MAP(CAGimageView, CScrollView)
	//{{AFX_MSG_MAP(CAGimageView)
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageView drawing

CAGimageDoc* CAGimageView::GetDocument() // non-debug version is inline
{
	if(!m_pDocument->IsKindOf(RUNTIME_CLASS(CAGimageDoc)))
		return NULL;
	return (CAGimageDoc*)m_pDocument;
}
void CAGimageView::UpdateScrollSize()
{
 	if(m_pAGimage!=NULL)
	{
		CRect	rc(0,0,0,0);
		GetClientRect(&rc);	
		CSize	size(m_pAGimage->GetWidth(), m_pAGimage->GetHeight());

		m_docSize=CSize(size.cx,size.cy);
		m_pageSize=CSize(rc.Width(),rc.Height());

		m_pageSize.cx=m_pageSize.cx>m_docSize.cx?0:m_pageSize.cx;
		m_pageSize.cy=m_pageSize.cy>m_docSize.cy?0:m_pageSize.cy;
		m_lineSize.cx=m_pageSize.cx/10;
		m_lineSize.cy=m_pageSize.cy/10;
	}
	else
	{
		m_docSize=CSize(0,0);
		m_pageSize=CSize(0,0);
		m_lineSize=CSize(0,0);
	}
}
CAGimage* CAGimageView::SelectAGimageProtect(CAGimage* pAGimage, agbool bDeleteAGimage, agbool bCopyAGimage)
{
	if(bDeleteAGimage && m_pAGimage!=NULL)
	{
		delete m_pAGimage;
		m_pAGimage=NULL;
	}
	CAGimage* pOldAGimage=m_pAGimage;
	if(bCopyAGimage)
	{
		AGMAGICIP_NEW_AND_COPY(m_pAGimage,pAGimage)
	}
	else
		m_pAGimage=pAGimage;

	m_bDeleteAGimage=bDeleteAGimage;
	return pOldAGimage;
}
CAGimage* CAGimageView::SelectAGimage(CAGimage *pAGimage, agbool bDeleteAGimage, agbool bCopyAGimage)
{
	CAGimage* pOldAGimage=SelectAGimageProtect(pAGimage,bDeleteAGimage,bCopyAGimage);
	if(m_pAGimage!=NULL)
	{
		UpdateScrollSize();
		SetScrollSizes(MM_TEXT,m_docSize,m_pageSize,m_lineSize);
		Invalidate();
	}
	
	return pOldAGimage;
}
HCURSOR	CAGimageView::SetGrabCur(HCURSOR hGrabCur)
{
	HCURSOR	hOldGrabCur=m_hGrabCur;
	m_hGrabCur=hGrabCur;
	return hOldGrabCur;
}
HCURSOR	CAGimageView::SetFlatCur(HCURSOR hFlatCur)
{
	HCURSOR	hOldFlatCur=m_hFlatCur;
	m_hFlatCur=hFlatCur;
	return hOldFlatCur;
}
void CAGimageView::OnInitialUpdate()
{
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;

	CScrollView::OnInitialUpdate();
	CAGimageDoc*	pAGimageDoc=(CAGimageDoc*)GetDocument();
	if(pAGimageDoc==NULL)
	{
		SetScrollSizes(MM_TEXT, sizeTotal);
		return;
	}

	if(pAGimageDoc->GetAGimage()==NULL)
		SetScrollSizes(MM_TEXT, sizeTotal);
	else if(!pAGimageDoc->GetAGimage()->IsValid())
		SetScrollSizes(MM_TEXT, sizeTotal);
	else
	{
		SelectAGimageProtect(pAGimageDoc->GetAGimage(),agfalse,agfalse);
		UpdateScrollSize();
		SetScrollSizes(MM_TEXT,m_docSize,m_pageSize,m_lineSize);
	}
}
void CAGimageView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	UpdateScrollSize();
}
BOOL CAGimageView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush	*pBrush,*pOldBrush;
	CRect	rc;
	BOOL	ret;

	pBrush=new CBrush();
	pDC->GetClipBox(&rc);
	pBrush->CreateSolidBrush(RGB(128,128,128));
	pOldBrush=pDC->SelectObject(pBrush);
	ret=pDC->PatBlt(rc.left,rc.top,rc.Width(),rc.Height(),PATCOPY);
	pDC->SelectObject(pOldBrush);
	delete pBrush;

	return ret;
}
BOOL CAGimageView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	if(nHitTest!=HTCLIENT||!m_bScroll)
		return CScrollView::OnSetCursor(pWnd, nHitTest, message);
	if(m_bMouseDown)
	{
		if(m_hGrabCur==NULL)
			return CScrollView::OnSetCursor(pWnd, nHitTest, message);
		::SetCursor(m_hGrabCur);
	}
	else
	{
		if(m_hFlatCur==NULL)
			return CScrollView::OnSetCursor(pWnd, nHitTest, message);
		::SetCursor(m_hFlatCur);
	}
	return TRUE;
}
void CAGimageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bScroll)
	{
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	}
	WPARAM wParam;
	LPARAM lParam;

	m_bMouseDown=agtrue;
	wParam=(WPARAM)GetSafeHwnd();
	lParam=WM_LBUTTONDOWN;
	lParam=(lParam<<16)|HTCLIENT;
	SendMessage(WM_SETCURSOR,wParam,lParam);
	
	GetCursorPos(&m_ptCursorCurPos);
	m_ptCursorOldPos=m_ptCursorCurPos;
	SetCapture();
	CScrollView::OnLButtonDown(nFlags, point);
}
void CAGimageView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bMouseDown)
	{
		CScrollView::OnLButtonUp(nFlags, point);
		return;
	}
	CSize	d;
	CPoint	ptScrollPos;

	GetCursorPos(&m_ptCursorCurPos);
	d=m_ptCursorOldPos-m_ptCursorCurPos;
	d.cx=m_pageSize.cx==0?0:d.cx;
	d.cy=m_pageSize.cy==0?0:d.cy;

	ptScrollPos=GetScrollPosition();
	ptScrollPos.x +=d.cx;
	ptScrollPos.y +=d.cy;
	
	ScrollToPosition(ptScrollPos);

	m_ptCursorOldPos=m_ptCursorCurPos;

	CScrollView::OnMouseMove(nFlags, point);
}
void CAGimageView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bMouseDown)
	{
		CScrollView::OnLButtonUp(nFlags, point);
		return;
	}
	WPARAM wParam;
	LPARAM lParam;

	m_bMouseDown=agfalse;
	wParam=(WPARAM)GetSafeHwnd();
	lParam=WM_LBUTTONUP;
	lParam=(lParam<<16)|HTCLIENT;
	SendMessage(WM_SETCURSOR,wParam,lParam);
	
	::ReleaseCapture();
	CScrollView::OnLButtonUp(nFlags, point);
}
void CAGimageView::SwitchScroll() 
{
	// TODO: Add your command handler code here
	m_bScroll=!m_bScroll;
}

void CAGimageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	if(m_pAGimage==NULL)
		return;

	/*
	CRect	rc;
	GetClientRect(&rc);	
	m_pos.x=(rc.Width()-m_pAGimage->GetWidth())/2;
	m_pos.y=(rc.Height()-m_pAGimage->GetHeight())/2;
	if(m_pos.x<0)	m_pos.x=0;
	if(m_pos.y<0)	m_pos.y=0;
	*/
	m_pAGimage->Draw(pDC->GetSafeHdc(),m_pos.x,m_pos.y);
}

/////////////////////////////////////////////////////////////////////////////
// CAGimageView diagnostics

#ifdef _DEBUG
void CAGimageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAGimageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CAGimageView message handlers

/*******************************class CAGimageAView*******************************/

#include "../../ip/main/AGimageUtil.h"

IMPLEMENT_DYNCREATE(CAGimageAView, CScrollView)

CAGimageAView::CAGimageAView()
{
	m_pAGimageA=NULL;
	m_bDeleteAGimageA=agfalse;
	m_nCols=0;
	m_pos=CPoint(0,0);
}

CAGimageAView::~CAGimageAView()
{
}


BEGIN_MESSAGE_MAP(CAGimageAView, CScrollView)
	//{{AFX_MSG_MAP(CAGimageAView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageAView drawing

void CAGimageAView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CAGimageAView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	if(m_pAGimageA!=NULL && m_nCols>0)
		CAGimageMicUtil::DrawA(m_pos,m_nCols,m_pAGimageA,pDC->GetSafeHdc(),NULL,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));
}
/*
--Neu nhu bCopyAGimage=agtrue:dieu do co nghia la sao chep toan bo tung anh 
cua tham so pAGimageA vao bien mang thanh vien m_pAGimageA
*/
CAGptrArray* CAGimageAView::SelectAGimageA(CAGptrArray* pAGimageA, aguint32 nCols, agbool bDeleteAGimageA, agbool bCopyAGimageA)
{
	if(m_bDeleteAGimageA)
	{
		DELETE_AGMAGICIP_ARRAYPTR(m_pAGimageA,agtrue)
		m_pAGimageA=NULL;
	}

	CAGptrArray*	paOldAGimage=m_pAGimageA;
	if(bCopyAGimageA)
	{
		aguint32 n=pAGimageA->GetSize();
		m_pAGimageA=new CAGptrArray();
		for(aguint32 i=0; i<n; i++)
		{
			CAGimage* pAGimage=NULL;
			AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)pAGimageA->GetAt(i)))
			m_pAGimageA->Add(pAGimage);
		}
	}
	else
		m_pAGimageA=pAGimageA;
	m_bDeleteAGimageA=bDeleteAGimageA;

	
	m_nCols=AGMIN(nCols,(aguint32)m_pAGimageA->GetSize());
	if(m_pAGimageA!=NULL && m_nCols>0)
	{
		CSize	size;
		CAGimageMicUtil::DrawA(m_pos,m_nCols,m_pAGimageA,NULL,&size,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));
		CRect	rc(0,0,0,0);
		/*
		if(size.cx<300 && size.cy<240)
		{
			rc.right=size.cx;
			rc.bottom=size.cy;
			CFrameWnd* pFrameWnd=GetParentFrame();
			pFrameWnd->CalcWindowRect(&rc,CWnd::adjustOutside);
			pFrameWnd->SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);
		}
		else
		*/
		{
			GetClientRect(&rc);	
			CSize	docSize(size.cx,size.cy);
			CSize	pageSize(rc.Width(),rc.Height());
			CSize	lineSize;
			pageSize.cx=pageSize.cx>docSize.cx?0:pageSize.cx;
			pageSize.cy=pageSize.cy>docSize.cy?0:pageSize.cy;
			lineSize.cx=pageSize.cx/10;
			lineSize.cy=pageSize.cy/10;
			SetScrollSizes(MM_TEXT,docSize,pageSize,lineSize);
		}
		Invalidate();
	}
	return paOldAGimage;
}

/////////////////////////////////////////////////////////////////////////////
// CAGimageAView diagnostics

#ifdef _DEBUG
void CAGimageAView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAGimageAView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGimageAView message handlers

void CAGimageAView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_bDeleteAGimageA)
	{
		DELETE_AGMAGICIP_ARRAYPTR(m_pAGimageA,agtrue)
		m_pAGimageA=NULL;
	}
}

/*******************************class CAGimageAAbuView*******************************/

#include "../../ip/main/AGimageUtil.h"
IMPLEMENT_DYNCREATE(CAGimageAAbuView, CScrollView)

CAGimageAAbuView::CAGimageAAbuView()
{
	m_pAGimageAA=NULL;
	m_bDeleteAGimageAA=agfalse;
	m_pos=CPoint(0,0);
}

CAGimageAAbuView::~CAGimageAAbuView()
{
}


BEGIN_MESSAGE_MAP(CAGimageAAbuView, CScrollView)
	//{{AFX_MSG_MAP(CAGimageAAbuView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageAAbuView drawing

void CAGimageAAbuView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CAGimageAAbuView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CAGimageAAbuView diagnostics

#ifdef _DEBUG
void CAGimageAAbuView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAGimageAAbuView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGimageAAbuView message handlers
CAGptrArray* CAGimageAAbuView::SelectAGimageAA(CAGptrArray* pAGimageAA, agbool bDeleteAGimageAA, agbool bCopyAGimageAA)
{
	if(m_bDeleteAGimageAA)
	{
		DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR(m_pAGimageAA,agtrue)
		m_pAGimageAA=NULL;
	}

	CAGptrArray*	pOldAGimageAA=m_pAGimageAA;
	if(bCopyAGimageAA)
	{
		aguint32 n=pAGimageAA->GetSize();
		m_pAGimageAA=new CAGptrArray();
		for(aguint32 i=0; i<n; i++)
		{
			CAGptrArray*	pAGimageA=new CAGptrArray();
			CAGptrArray*	pAGimageATemp=(CAGptrArray*)pAGimageAA->GetAt(i);
			aguint32		m=pAGimageATemp->GetSize();
			for(aguint32 j=0; j<m; j++)
			{
				CAGimage* pAGimage=NULL;
				AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)(pAGimageATemp->GetAt(j))))
				pAGimageA->Add(pAGimage);
			}
			m_pAGimageAA->Add(pAGimageA);
		}
	}
	else
		m_pAGimageAA=pAGimageAA;
	m_bDeleteAGimageAA=bDeleteAGimageAA;

	if(m_pAGimageAA!=NULL)
	{
		CSize	size;
		CAGimageMicUtil::DrawAA(m_pos,m_pAGimageAA,NULL,&size,CSize(AGMAGICIP_MFC_UI_DEFAULT_HINGEW,AGMAGICIP_MFC_UI_DEFAULT_HINGEH));
		CRect	rc(0,0,0,0);
		/*
		if(size.cx<300 && size.cy<240)
		{
			rc.right=size.cx;
			rc.bottom=size.cy;
			CFrameWnd* pFrameWnd=GetParentFrame();
			pFrameWnd->CalcWindowRect(&rc,CWnd::adjustOutside);
			pFrameWnd->SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);
		}
		else
		*/
		{
			GetClientRect(&rc);	
			CSize	docSize(size.cx,size.cy);
			CSize	pageSize(rc.Width(),rc.Height());
			CSize	lineSize;
			pageSize.cx=pageSize.cx>docSize.cx?0:pageSize.cx;
			pageSize.cy=pageSize.cy>docSize.cy?0:pageSize.cy;
			lineSize.cx=pageSize.cx/10;
			lineSize.cy=pageSize.cy/10;
			SetScrollSizes(MM_TEXT,docSize,pageSize,lineSize);
		}
		Invalidate();
	}
	return pOldAGimageAA;
}

void CAGimageAAbuView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_bDeleteAGimageAA)
	{
		DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR(m_pAGimageAA,agtrue)
		m_pAGimageAA=NULL;
	}
	
}

/*******************************class CAGimageListCtrl*******************************/

#include "../../ip/main/AGimageUtil.h"
CAGimageListCtrl::CAGimageListCtrl()
{
	m_nIDTemplate=-1;
	m_bShowAll=agfalse;
}

CAGimageListCtrl::~CAGimageListCtrl()
{
}


BEGIN_MESSAGE_MAP(CAGimageListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CAGimageListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_WM_KEYUP()
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageListCtrl message handlers
void CAGimageListCtrl::DeleteAllAGimageData()
{
	aguint32 n=GetItemCount();
	for(aguint32 i=0; i<n; i++)
	{
		CAGimage *pAGimage=(CAGimage*)GetItemData(i);
		if(pAGimage!=NULL)
		{
			delete pAGimage;
			SetItemData(i,NULL);
		}
	}
}
void CAGimageListCtrl::ShowAllAGimageData()
{
	aguint32 n=GetItemCount();
	for(aguint32 i=0; i<n; i++)
	{
		CAGimage *pAGimage=(CAGimage*)GetItemData(i);
		if(pAGimage!=NULL)
		{
			if(m_nIDTemplate!=-1)
				CAGimageDlg::ShowAGimageDlg(m_nIDTemplate,pAGimage,GetItemText(i,0));
			else
			{
			}
		}
	}
}
/*
--pListInfo.sColumn la ten cac cot cach nhau bang dau ^, sColumn co the rong
--pListInfo.aTextItem la mang chuoi cac muc, moi muc(anh) ung voi moi chuoi, trong moi chuoi 
	co dau ^ ngan cach de ung voi tung tieu de, paTextItem co the NULL
--pListInfo.uType co 4 gia tri : LVS_ICON, LVS_LIST, LVS_REPORT, LVS_SMALLICON
--tham so bCopyAGimageA=agtrue co nghia la LV_ITEM	lvItem.lParam=con tro den anh
--tao roi khong can delete vi lop CAGimageListCtrl tu huy
*/
#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"
CAGimageListCtrl* CAGimageListCtrl::CreateAGimageListCtrl(AGMAGICIP_LISTINFO* pListInfo, CSize* psizeListLarge, CSize* psizeListSmall, COLORREF* pcrMask)
{
	if(pListInfo==NULL)
		return NULL;
	//Tao CListCtrl
	CAGimageListCtrl*	pListCtrl=new CAGimageListCtrl();
	RECT				rc;
	if(pListInfo->prc==NULL)
	{
		pListInfo->pParentWnd->GetClientRect(&rc);
		pListInfo->prc=&rc;
	}
	pListInfo->nID=(pListInfo->nID==-1)?((aguint32)time(NULL)):pListInfo->nID;
	CWnd*	pTopLevelWnd=pListInfo->pParentWnd;//->GetTopLevelParent();
	if(pTopLevelWnd==NULL)	pTopLevelWnd=pListInfo->pParentWnd;
	pListCtrl->Create(pListInfo->uType|AGMAGICIP_LVS_DEFAULTTYPE,*(pListInfo->prc),pTopLevelWnd,pListInfo->nID);

	//Khoi gan cac thong so
	CImageList* pImageListLarge=CAGimageMicUtil::CreateImageList(pListInfo->pAGimageA,psizeListLarge,pTopLevelWnd->GetDC(),pcrMask);
	CImageList* pImageListSmall=CAGimageMicUtil::CreateImageList(pListInfo->pAGimageA,psizeListSmall,pTopLevelWnd->GetDC(),pcrMask);
	pListCtrl->SetImageList(pImageListLarge,LVSIL_NORMAL);
	pListCtrl->SetImageList(pImageListSmall,LVSIL_SMALL);
	pListCtrl->m_nIDTemplate=pListInfo->nIDTemplate;

	//Datcac cot
	LV_COLUMN lvColumn;
	lvColumn.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
	lvColumn.fmt=LVCFMT_CENTER;
	lvColumn.cx=80;

	CStringArray aS;
	CAGmagicStrUtil::SplitString(pListInfo->sColumn,_T("^"),aS);//phan cach nhau bang dau ^
	aguint32	n=aS.GetSize();
	if(n==0)
	{
		lvColumn.iSubItem=0;
		lvColumn.pszText=NULL;
		pListCtrl->InsertColumn(0,&lvColumn);
	}
	else
	{
		TCHAR	szText[1024];
		for(aguint32 j=0; j<n; j++)
		{
			lvColumn.iSubItem=j;
			strcpy(szText,aS[j]);
			lvColumn.pszText=szText;
			pListCtrl->InsertColumn(j,&lvColumn);
		}
	}
	//Dat cac muc
	LV_ITEM	lvItem;
	lvItem.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	lvItem.state=0;
	lvItem.stateMask=0;

	aguint32	m=pListInfo->pAGimageA->GetSize();
	CAGimage*	pAGimage=NULL;
	if(m==0)
	{
		lvItem.iImage=0;
		lvItem.iItem=0;
		lvItem.iSubItem=0;
		lvItem.pszText=NULL;
		if(pListInfo->bCopyAGimageA)
		{
			pAGimage=NULL;
			AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)(pListInfo->pAGimageA->GetAt(0))))
			lvItem.lParam=(LPARAM)pAGimage;
		}
		else
			lvItem.lParam=NULL;

		pListCtrl->InsertItem(&lvItem);
	}
	else
	{
		for(aguint32 i=0; i<m; i++)
		{
			lvItem.iImage=i;
			lvItem.iItem=i;
			lvItem.iSubItem=0;
			lvItem.pszText=NULL;
			if(pListInfo->bCopyAGimageA)
			{
				pAGimage=NULL;
				AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)(pListInfo->pAGimageA->GetAt(0))))
				lvItem.lParam=(LPARAM)pAGimage;
			}
			else
				lvItem.lParam=NULL;

			pListCtrl->InsertItem(&lvItem);

			CString			src=pListInfo->paTextItem->GetAt(i);
			CStringArray	aS;
			CAGmagicStrUtil::SplitString(src,_T("^"),aS);//phan cach nhau bang dau ^
			aguint32 n=aS.GetSize();
			for(aguint32 j=0; j<n; j++)
				pListCtrl->SetItemText(i,j,aS[j]);	

		}
	}
	return pListCtrl;
}

void CAGimageListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	agint32 iItem=pNMListView->iItem;

	CAGimage	*pAGimage=(CAGimage*)GetItemData(iItem);
	if(m_nIDTemplate!=-1)
		CAGimageDlg::ShowAGimageDlg(m_nIDTemplate,pAGimage,GetItemText(iItem,0));
	else
	{
		//dung cua so de hien thi anh
	}
	*pResult = 0;
}

void CAGimageListCtrl::OnDestroy() 
{
	DeleteAllAGimageData();
	CImageList* pImageList=NULL;
	pImageList=GetImageList(LVSIL_NORMAL);
	if(pImageList!=NULL)	delete pImageList;
	pImageList=GetImageList(LVSIL_SMALL);
	if(pImageList!=NULL)	delete pImageList;
	pImageList=GetImageList(LVSIL_STATE);
	if(pImageList!=NULL)	delete pImageList;

	CListCtrl::OnDestroy();
	// TODO: Add your message handler code here
}
void CAGimageListCtrl::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListCtrl::PostNcDestroy();
	delete this;
}
void CAGimageListCtrl::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	agint32 iStart=-1;
	agint32 nIndex=-1;
	while((nIndex=GetNextItem(iStart,LVNI_SELECTED))!=-1)
	{
		CAGimage*	pAGimage=(CAGimage*)GetItemData(nIndex);
		if(m_nIDTemplate!=-1)
		{
			//dung dialog de hien thi
			CAGimageDlg::ShowAGimageDlg(m_nIDTemplate,pAGimage,GetItemText(nIndex,0));
		}
		else
		{
			//dung cua so de hien thi anh
		}

		iStart=nIndex;
	}
	*pResult = 0;
}

void CAGimageListCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if(pLVKeyDow->wVKey==VK_SHIFT && GetKeyState(VK_CONTROL))
	{
		if(!m_bShowAll)
			m_bShowAll=agtrue;
	}
	*pResult = 0;
}

void CAGimageListCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_SHIFT && GetKeyState(VK_CONTROL))
	{
		if(m_bShowAll)
		{
			ShowAllAGimageData();
			m_bShowAll=agfalse;
		}
	}
	CListCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}
/*******************************class CAGlvItemArray, CAGimageListCtrlEx*******************************/
#include "AGimageUI2.h"

CAGlvItemArray::CAGlvItemArray()
{
	m_bIsDeleteImages=agfalse;
}

CAGlvItemArray::~CAGlvItemArray()
{
	RemoveAll();
}
void CAGlvItemArray::RemoveAll()
{
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageLVItemExt* pAGimageLVItemExt=GetAt(i);
		if(pAGimageLVItemExt)
		{
			if(m_bIsDeleteImages)
				delete pAGimageLVItemExt->m_pAGimage;
			pAGimageLVItemExt->m_pAGimage=NULL;
		}
	}
	CAGobjPtrArray<CAGimageLVItemExt>::RemoveAll();
}

CAGimageListCtrlEx::CAGimageListCtrlEx()
{
	m_bIsCreateAGimage=agfalse;
	m_AGlvItems.m_bIsDeleteImages=m_bIsCreateAGimage;
	m_pOutsideContextMenu=NULL;
}

CAGimageListCtrlEx::~CAGimageListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CAGimageListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CAGimageListCtrlEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_WM_KEYUP()
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)

	ON_MESSAGE(AGMAGICIP_WM_RECEIVED_NEW_IMAGES, OnReceivedNewImages)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageListCtrlEx message handlers

int CAGimageListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_ImageList.Create(AGIMAGE_LISTCTRLEX_ITEM_WIDTH, AGIMAGE_LISTCTRLEX_ITEM_HEIGHT, ILC_COLOR24, 0, 1);
	SetImageList(&m_ImageList, LVSIL_NORMAL);
	
	return 0;
}
void CAGimageListCtrlEx::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_ImageList.GetSafeHandle()==NULL)
	{
		m_ImageList.Create(AGIMAGE_LISTCTRLEX_ITEM_WIDTH, AGIMAGE_LISTCTRLEX_ITEM_HEIGHT, ILC_COLOR24, 0, 1);
		SetImageList(&m_ImageList, LVSIL_NORMAL);
	}	
	CListCtrl::PreSubclassWindow();
}

void CAGimageListCtrlEx::OnDestroy()
{
	DeleteAllItems();
	if(m_pOutsideContextMenu)	delete m_pOutsideContextMenu; m_pOutsideContextMenu=NULL;
	CListCtrl::OnDestroy();
	
	// TODO: Add your message handler code here
}
void CAGimageListCtrlEx::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);
	//int n=GetItemCount();
	//if(n>0)
	//{
	//	RedrawItems(0,n-1);
	//	Invalidate();
	//}
	// TODO: Add your message handler code here
}
void CAGimageListCtrlEx::OnContextMenu(CWnd* pWnd, CPoint pos) 
{
	if(m_pOutsideContextMenu)
	{
		CPoint point=pos;
		ScreenToClient(&point);

		CAGint32Array	idxs;
		GetAllSelectedIdxs(&idxs);
		agint32			n=idxs.GetSize();
		agint32			i=0;
		for(i=0; i<n; i++)
		{
			CRect rItem;
			GetItemRect(idxs.GetAt(i), &rItem, LVIR_BOUNDS);
			if(rItem.PtInRect(point))	break;
		}
		if(i==n)	return;

		CMenu *pContextMenu=m_pOutsideContextMenu->GetSubMenu(0);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pos.x,pos.y,AfxGetMainWnd());

		return;
	}	
	CListCtrl::OnContextMenu(pWnd,pos);
}
BOOL CAGimageListCtrlEx::DeleteAllItems()
{
	BOOL bResult=CListCtrl::DeleteAllItems();
	m_AGlvItems.RemoveAll();

	//while(m_ImageList.GetImageCount()>0)
	//	m_ImageList.Remove(0);
	if(m_ImageList.GetImageCount()>0)
	{
		m_ImageList.DeleteImageList();
		if(m_ImageList.GetSafeHandle()==NULL)
			m_ImageList.Create(AGIMAGE_LISTCTRLEX_ITEM_WIDTH, AGIMAGE_LISTCTRLEX_ITEM_HEIGHT, ILC_COLOR24, 0, 1);
	}
	return bResult;
}
void CAGimageListCtrlEx::GetAllSelectedIdxs(CAGint32Array* idxs)
{
	if(idxs==NULL)	throw _T("Invalidate Parameter");
	idxs->RemoveAll();

	agint32 idx=-1;
	while(  (idx=GetNextItem(idx,LVNI_SELECTED))!=-1   )
	{
		idxs->Add(idx);
	}
}
void CAGimageListCtrlEx::GetAllSelectedIDs(CAGidArray* IDs)
{
	if(IDs==NULL)	throw _T("Invalidate Parameter");
	IDs->RemoveAll();

	CAGint32Array idxs;
	GetAllSelectedIdxs(&idxs);
	agint32		n=idxs.GetSize();
	if(n==0)	return;
	for(agint32 i=0; i<n; i++)
	{
		CAGimageLVItemExt* pAGimageLVItemExt=(CAGimageLVItemExt*)GetItemData(idxs.GetAt(i));
		IDs->Add(pAGimageLVItemExt->m_ID);
	}
}
void CAGimageListCtrlEx::SetOutsideContextMenu(aguint_id OutsideContextMenuID, aguint_id ToolbarIDforOutsideContextMenu)
{
	if(OutsideContextMenuID!=0)
	{
		if(m_pOutsideContextMenu) delete m_pOutsideContextMenu; m_pOutsideContextMenu=NULL;
		m_pOutsideContextMenu=new BCMenu();
		m_pOutsideContextMenu->LoadMenu((UINT)OutsideContextMenuID);
		if(ToolbarIDforOutsideContextMenu!=0)
			m_pOutsideContextMenu->LoadToolbar((UINT)ToolbarIDforOutsideContextMenu);
	}
}

typedef struct tagTHREADPROC_PARAM
{
	CAGinteractImagesMsg*	pAGinteractImagesMsg;
	CAGimageListCtrlEx*		pAGimageListCtrlEx;
	CMutex*					pMutex;
} THREADPROC_PARAM;

UINT ReceiveNewImages_ThreadProc(LPVOID param)
{
	THREADPROC_PARAM*	pThreadProcParam=(THREADPROC_PARAM*)param;
	CSingleLock			singleLock(pThreadProcParam->pMutex);
	singleLock.Lock();

	CAGinteractImagesMsg*	pAGinteractImagesMsg=pThreadProcParam->pAGinteractImagesMsg;
	ASSERT(pAGinteractImagesMsg!=NULL);
	CAGimageListCtrlEx*		pAGimageListCtrlEx=pThreadProcParam->pAGimageListCtrlEx;
	delete pThreadProcParam;

	int nFirstIndex=pAGimageListCtrlEx->m_ImageList.GetImageCount();

	//pAGimageListCtrlEx->SetRedraw(FALSE);

	// Create Brushes for Border and BackGround
	HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 192, 192));
	HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));

	// Border Size
	RECT rcBorder;
	rcBorder.left=rcBorder.top=0;
	rcBorder.right=AGIMAGE_LISTCTRLEX_ITEM_WIDTH;
	rcBorder.bottom=AGIMAGE_LISTCTRLEX_ITEM_HEIGHT;

	const float fRatio=(float)AGIMAGE_LISTCTRLEX_ITEM_HEIGHT/AGIMAGE_LISTCTRLEX_ITEM_WIDTH;
	int XDest, YDest, nDestWidth, nDestHeight;

	int n=pAGinteractImagesMsg->GetSize();
	ASSERT(n>0);
	for(int i=0; i<n; i++)
	{
		CAGimage* pAGimage=NULL;
		if(pAGinteractImagesMsg->IsPassID())
		{
			aguint_id ImageID=pAGinteractImagesMsg->GetIDAt(i);
			if(ImageID != 0)
			{
				pAGimage=pAGimageListCtrlEx->CreateAGimage();
				if(!CAGimageDBUtil::Load(ImageID, pAGinteractImagesMsg->DBCnnGet(),pAGimage))
				{
					delete pAGimage;
					continue;
				}
			}
			else if(pAGinteractImagesMsg->GetImageAt(i)!=NULL)
			{
				pAGimage=pAGimageListCtrlEx->CreateAGimage();
				pAGimage->Copy(pAGinteractImagesMsg->GetImageAt(i));
			}
			if(pAGimage==NULL)			continue;
			if(!pAGimage->IsValid())	{delete pAGimage;	continue;}
		}
		else
		{
			pAGimage=pAGinteractImagesMsg->GetImageAt(i);
			if(pAGimage==NULL || !pAGimage->IsValid())	continue;
		}

		const float fImgRatio=(float)pAGimage->GetHeight()/pAGimage->GetWidth();
		if(fImgRatio > fRatio)
		{
			nDestWidth=(int)((float)AGIMAGE_LISTCTRLEX_ITEM_HEIGHT/fImgRatio);
			XDest=(AGIMAGE_LISTCTRLEX_ITEM_WIDTH-nDestWidth)/2;
			YDest=0;
			nDestHeight=AGIMAGE_LISTCTRLEX_ITEM_HEIGHT;
		}
		else
		{
			XDest=0;
			nDestWidth=AGIMAGE_LISTCTRLEX_ITEM_WIDTH;
			nDestHeight=(int)((float)AGIMAGE_LISTCTRLEX_ITEM_WIDTH*fImgRatio);
			YDest=(AGIMAGE_LISTCTRLEX_ITEM_HEIGHT-nDestHeight)/2;
		}

		CClientDC dc(pAGimageListCtrlEx->GetParent());
		HDC		hDC=::CreateCompatibleDC(dc.m_hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(dc.m_hDC, AGIMAGE_LISTCTRLEX_ITEM_WIDTH, AGIMAGE_LISTCTRLEX_ITEM_HEIGHT);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC,hBitmap);
		// Draw Background
		::FillRect(hDC, &rcBorder, hBrushBk);

		// Draw Image
		pAGimage->Stretch(hDC, XDest, YDest, nDestWidth, nDestHeight);

		// Draw Border
		::FrameRect(hDC, &rcBorder, hBrushBorder);

		SelectObject(hDC, hOldBitmap);

		// Attach to Bitmap and Replace image in CImageList
		CBitmap bitmap;
		bitmap.Attach(hBitmap);
		pAGimageListCtrlEx->m_ImageList.Add(&bitmap, (CBitmap*)NULL);

		// Release used DC and Object
		DeleteDC(hDC);
		DeleteObject(hBitmap);

		
		//them vao m_AGlvItems
		CAGimageLVItemExt* pAGimageLVItemExt=new CAGimageLVItemExt();
		if(pAGinteractImagesMsg->IsPassID())
		{
			if(pAGimageListCtrlEx->m_bIsCreateAGimage)
				pAGimageLVItemExt->m_pAGimage=pAGimage;
			else
			{
				pAGimageLVItemExt->m_pAGimage=NULL;
				delete pAGimage;
			}
			pAGimageLVItemExt->m_ID=pAGinteractImagesMsg->GetIDAt(i);
		}
		else
		{
			if(pAGimageListCtrlEx->m_bIsCreateAGimage)
			{
				CAGimage*	pMyAGimage=pAGimageListCtrlEx->CreateAGimage();
				pMyAGimage->Copy(pAGimage);

				pAGimageLVItemExt->m_pAGimage=pMyAGimage;
			}
			else
				pAGimageLVItemExt->m_pAGimage=pAGimage;
			pAGimageLVItemExt->m_ID=pAGimage->m_ID;
		}
		if(pAGinteractImagesMsg->GetAt(i)->m_pReservedAGmagicElement)
		{
			pAGimageLVItemExt->m_pAGmagicElement=pAGinteractImagesMsg->GetAt(i)->m_pReservedAGmagicElement->CreateMe();
			pAGimageLVItemExt->m_pAGmagicElement->CopyFrom(pAGinteractImagesMsg->GetAt(i)->m_pReservedAGmagicElement);
			ASSERT(pAGimageLVItemExt->m_pAGmagicElement->GetID()==pAGimageLVItemExt->m_ID);
		}
		pAGimageLVItemExt->m_idx=nFirstIndex+i;

		pAGimageListCtrlEx->m_AGlvItems.Add(pAGimageLVItemExt);

		//Bat dau them vaio LisCtrl
		LV_ITEM	lvItem;
		memset(&lvItem,0,sizeof(LV_ITEM));
		lvItem.mask    =LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		lvItem.iItem   =nFirstIndex+i;
		lvItem.iImage  =lvItem.iItem;
		lvItem.pszText =(LPTSTR)(LPCTSTR)pAGinteractImagesMsg->GetTextAt(i);
		lvItem.lParam  =(LPARAM)pAGimageLVItemExt;
		pAGimageListCtrlEx->InsertItem(&lvItem);
	}

	//pAGimageListCtrlEx->SetRedraw(TRUE);
	//if(pAGimageListCtrlEx->m_ImageList.GetImageCount()>nFirstIndex)
	//{
	//	int nLastIndex=pAGimageListCtrlEx->m_ImageList.GetImageCount()-1;
	//	pAGimageListCtrlEx->RedrawItems(nFirstIndex,nLastIndex);
	//}
	//pAGimageListCtrlEx->Invalidate();


	CObject* pParam=(CObject*)pAGinteractImagesMsg->m_pNoFreeReserved;
	if(pParam)
	{
		if(pParam->IsKindOf(RUNTIME_CLASS(CEvent)))
			((CEvent*)pParam)->SetEvent();
	}
	if(pAGinteractImagesMsg->IsDeleteMeInProc())
		delete pAGinteractImagesMsg;
	else
	{
		pAGinteractImagesMsg->SetNULLAll();
		delete pAGinteractImagesMsg;
	}

	CWnd* pParentWnd=pAGimageListCtrlEx->GetParent();
	if(pParentWnd) pParentWnd->PostMessage(AGMAGICIP_WM_LISTCTRL_UPDATE_DOCUMENT_ALREADY,0,0);
	AfxEndThread(0,TRUE);
	return 0;
}
LRESULT CAGimageListCtrlEx::OnReceivedNewImages(WPARAM wParam, LPARAM lParam)
{
	CAGinteractImagesMsg* pAGinteractImagesMsg=(CAGinteractImagesMsg*)lParam;
	ASSERT(pAGinteractImagesMsg!=NULL);
	if(pAGinteractImagesMsg->GetSize()==0)	return 0;

	THREADPROC_PARAM* pThreadProcParam=new THREADPROC_PARAM;
	pThreadProcParam->pAGimageListCtrlEx=this;
	pThreadProcParam->pAGinteractImagesMsg=pAGinteractImagesMsg;
	pThreadProcParam->pMutex=&m_Mutex;

	AfxBeginThread((AFX_THREADPROC)ReceiveNewImages_ThreadProc,pThreadProcParam);
	//ReceiveNewImages_ThreadProc(pThreadProcParam);
	return 0;
}

void CAGimageListCtrlEx::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListCtrl::PostNcDestroy();
}

void CAGimageListCtrlEx::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CAGimageListCtrlEx::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW*	pNMListView=(NM_LISTVIEW *)pNMHDR;
	agint32			iItem=pNMListView->iItem;

	CAGimage*	pAGimage=m_AGlvItems.GetAt(iItem)->m_pAGimage;
	if(pAGimage==NULL)
	{
		pAGimage=CreateAGimage();
		if(pAGimage->Load(GetItemText(iItem,0)))
			CAGimageModalDlg::ShowAGimageDlg(IDD_AGMAGICIP_DEFAULT,pAGimage,GetItemText(iItem,0));
		delete pAGimage;
	}
	else
		CAGimageModalDlg::ShowAGimageDlg(IDD_AGMAGICIP_DEFAULT,pAGimage,GetItemText(iItem,0));
	
	*pResult = 0;
}

void CAGimageListCtrlEx::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CAGimageListCtrlEx::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CAGimageListCtrlEx::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CAGimageListCtrlEx::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

/*******************************class CAGimageListCtrlExBar*******************************/

CAGimageListCtrlExBar::CAGimageListCtrlExBar() : baseAGimageListCtrlExBar()
{
}
CAGimageListCtrlExBar::CAGimageListCtrlExBar(CFrameWnd* pFrameWnd, UINT ID) : baseAGimageListCtrlExBar()
{
	ASSERT(pFrameWnd!=NULL);
	if (!Create(_T("Search Result"), pFrameWnd, ID))
	{
		TRACE0("Failed to create mybar\n");
		return ;		// fail to create
	}
	SetBarStyle(GetBarStyle() |
				CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	EnableDocking(CBRS_ALIGN_RIGHT);
	pFrameWnd->FloatControlBar(this,CPoint(0,0));
	//pFrameWnd->DockControlBar(this, AFX_IDW_DOCKBAR_LEFT);
}

CAGimageListCtrlExBar::~CAGimageListCtrlExBar()
{
}


BEGIN_MESSAGE_MAP(CAGimageListCtrlExBar, baseAGimageListCtrlExBar)
	//{{AFX_MSG_MAP(CAGimageListCtrlExBar)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAGimageListCtrlExBar message handlers

int CAGimageListCtrlExBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (baseAGimageListCtrlExBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

	if (!m_ListCtrlEx.Create(AGIMAGE_LISTCTRLEX_DEFAULTTYPE,CRect(0,0,0,0), this, IDC_LISCTRLEX))
		return -1;
	
	LoadState(AfxGetApp()->m_pszProfileName);
	return 0;
}
void CAGimageListCtrlExBar::OnDestroy()
{
	baseAGimageListCtrlExBar::OnDestroy();
	
	// TODO: Add your message handler code here
	SaveState(AfxGetApp()->m_pszProfileName);
}
/*******************************class CAGimageListView*******************************/

#include "../../ip/main/AGimageUtil.h"
IMPLEMENT_DYNCREATE(CAGimageListView, CListView)

CAGimageListView::CAGimageListView()
{
	INIT_AGMAGICIP_LISTINFO(m_ListInfo);
	m_bShowAll=agfalse;
}

CAGimageListView::~CAGimageListView()
{
}


BEGIN_MESSAGE_MAP(CAGimageListView, CListView)
	//{{AFX_MSG_MAP(CAGimageListView)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimageListView drawing

void CAGimageListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CAGimageListView diagnostics

#ifdef _DEBUG
void CAGimageListView::AssertValid() const
{
	CListView::AssertValid();
}

void CAGimageListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAGimageListView message handlers
#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"
AGMAGICIP_LISTINFO CAGimageListView::SelectListInfo(AGMAGICIP_LISTINFO* pListInfo, CSize* psizeListLarge, CSize* psizeListSmall, COLORREF* pcrMask)
{
	AGMAGICIP_LISTINFO OldListInfo=m_ListInfo;
	if(pListInfo==NULL)
		return OldListInfo;
	m_ListInfo=*pListInfo;
	CListCtrl&	ListCtrl=GetListCtrl();

	//Thay doi style cua List control
	aguint32 dwNewStyle=pListInfo->uType;
	aguint32 dwOldStyle=::GetWindowLong(ListCtrl.m_hWnd,GWL_STYLE);
	dwNewStyle |=(dwOldStyle &= ~LVS_TYPEMASK);
	::SetWindowLong(ListCtrl.m_hWnd,GWL_STYLE,dwNewStyle);

	//Khoi gan cac thong so
	CImageList* pImageListLarge=CAGimageMicUtil::CreateImageList(pListInfo->pAGimageA,psizeListLarge,this->GetDC(),pcrMask);
	CImageList* pImageListSmall=CAGimageMicUtil::CreateImageList(pListInfo->pAGimageA,psizeListSmall,this->GetDC(),pcrMask);
	ListCtrl.SetImageList(pImageListLarge,LVSIL_NORMAL);
	ListCtrl.SetImageList(pImageListSmall,LVSIL_SMALL);

	//Datcac cot
	LV_COLUMN lvColumn;
	lvColumn.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
	lvColumn.fmt=LVCFMT_CENTER;
	lvColumn.cx=80;

	CStringArray aS;
	CAGmagicStrUtil::SplitString(pListInfo->sColumn,_T("^"),aS);//phan cach nhau bang dau ^
	aguint32	n=aS.GetSize();
	if(n==0)
	{
		lvColumn.iSubItem=0;
		lvColumn.pszText=NULL;
		ListCtrl.InsertColumn(0,&lvColumn);
	}
	else
	{
		TCHAR	szText[1024];
		for(aguint32 j=0; j<n; j++)
		{
			lvColumn.iSubItem=j;
			strcpy(szText,aS[j]);
			lvColumn.pszText=szText;
			ListCtrl.InsertColumn(j,&lvColumn);
		}
	}
	//Dat cac muc
	LV_ITEM	lvItem;
	lvItem.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	lvItem.state=0;
	lvItem.stateMask=0;

	aguint32		m=pListInfo->pAGimageA->GetSize();
	CAGimage*	pAGimage=NULL;
	if(m==0)
	{
		lvItem.iImage=0;
		lvItem.iItem=0;
		lvItem.iSubItem=0;
		lvItem.pszText=NULL;
		if(pListInfo->bCopyAGimageA)
		{
			pAGimage=NULL;
			AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)(pListInfo->pAGimageA->GetAt(0))))

			lvItem.lParam=(LPARAM)pAGimage;
		}
		else
			lvItem.lParam=NULL;

		ListCtrl.InsertItem(&lvItem);
	}
	else
	{
		for(aguint32 i=0; i<m; i++)
		{
			lvItem.iImage=i;
			lvItem.iItem=i;
			lvItem.iSubItem=0;
			lvItem.pszText=NULL;
			if(pListInfo->bCopyAGimageA)
			{
				pAGimage=NULL;
				AGMAGICIP_NEW_AND_COPY(pAGimage,((CAGimage*)(pListInfo->pAGimageA->GetAt(0))))
				lvItem.lParam=(LPARAM)pAGimage;
			}
			else
				lvItem.lParam=NULL;
			ListCtrl.InsertItem(&lvItem);

			if(pListInfo->paTextItem==NULL)
				continue;
			CString			src=pListInfo->paTextItem->GetAt(i);
			CStringArray	aS;
			CAGmagicStrUtil::SplitString(src,_T("^"),aS);//phan cach nhau bang dau ^
			aguint32 n=aS.GetSize();
			for(aguint32 j=0; j<n; j++)
				ListCtrl.SetItemText(i,j,aS[j]);	

		}
	}

	CDocument* pDoc = GetDocument();
	pDoc->UpdateAllViews(NULL);	
	return OldListInfo;
}
void CAGimageListView::DeleteAllAGimageData()
{
	CListCtrl&	ListCtrl=GetListCtrl();
	aguint32		n=ListCtrl.GetItemCount();
	for(aguint32 i=0; i<n; i++)
	{
		CAGimage*	pAGimage=(CAGimage*)ListCtrl.GetItemData(i);
		if(pAGimage!=NULL)
		{
			delete pAGimage;
			ListCtrl.SetItemData(i,NULL);
		}
	}
}
void CAGimageListView::ShowAllAGimageData()
{
	CListCtrl&	ListCtrl=GetListCtrl();
	aguint32		n=ListCtrl.GetItemCount();
	for(aguint32 i=0; i<n; i++)
	{
		CAGimage *pAGimage=(CAGimage*)ListCtrl.GetItemData(i);
		if(pAGimage!=NULL)
		{
			if(m_ListInfo.nIDTemplate!=-1)
				CAGimageDlg::ShowAGimageDlg(m_ListInfo.nIDTemplate,pAGimage,ListCtrl.GetItemText(i,0));
			else
			{
			}
		}
	}
}
void CAGimageListView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW*	pNMListView=(NM_LISTVIEW *)pNMHDR;
	CListCtrl&		ListCtrl=GetListCtrl();
	agint32 iItem=pNMListView->iItem;
	if(iItem==-1)
		return;

	CAGimage*	pAGimage=(CAGimage*)ListCtrl.GetItemData(iItem);
	CDocument*	pDoc = GetDocument();
	if(pDoc==NULL)
		return;
	POSITION pos=pDoc->GetFirstViewPosition();
	while(pos!=NULL)
	{
		CView*	pView=pDoc->GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CAGimageView)))
		{
			CAGimageView*	pAGimageView=(CAGimageView*)pView;
			pAGimageView->SelectAGimage(pAGimage,agfalse);
		}
	}
	*pResult = 0;
}

void CAGimageListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW*	pNMListView=(NM_LISTVIEW *)pNMHDR;
	agint32 iItem=pNMListView->iItem;
	if(iItem==-1)
		return;

	CListCtrl&	ListCtrl=GetListCtrl();
	CAGimage*	pAGimage=(CAGimage*)ListCtrl.GetItemData(iItem);
	if(m_ListInfo.nIDTemplate!=-1)
		CAGimageDlg::ShowAGimageDlg(m_ListInfo.nIDTemplate,pAGimage,ListCtrl.GetItemText(iItem,0));
	else
	{
		//dung cua so de hien thi anh
	}
	
	*pResult = 0;
}

void CAGimageListView::OnDestroy() 
{
	DeleteAllAGimageData();
	CImageList* pImageList=NULL;
	CListCtrl	&ListCtrl=GetListCtrl();

	pImageList=ListCtrl.GetImageList(LVSIL_NORMAL);
	if(pImageList!=NULL)	delete pImageList;
	pImageList=ListCtrl.GetImageList(LVSIL_SMALL);
	if(pImageList!=NULL)	delete pImageList;
	pImageList=ListCtrl.GetImageList(LVSIL_STATE);
	if(pImageList!=NULL)	delete pImageList;

	CListView::OnDestroy();
	// TODO: Add your message handler code here
}
void CAGimageListView::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListView::PostNcDestroy();
}
void CAGimageListView::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	agint32		iStart=-1;
	agint32		nIndex=-1;
	CListCtrl&	ListCtrl=GetListCtrl();
	while((nIndex=ListCtrl.GetNextItem(iStart,LVNI_SELECTED))!=-1)
	{
		CAGimage*	pAGimage=(CAGimage*)(ListCtrl.GetItemData(nIndex));
		if(m_ListInfo.nIDTemplate!=-1)
		{
			//dung dialog de hien thi
			CAGimageDlg::ShowAGimageDlg(m_ListInfo.nIDTemplate,pAGimage,ListCtrl.GetItemText(nIndex,0));
		}
		else
		{
			//dung cua so de hien thi anh
		}

		iStart=nIndex;
	}
	
	*pResult = 0;
}

//Key down nay cua view
void CAGimageListView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_SHIFT && GetKeyState(VK_CONTROL))
	{
		if(!m_bShowAll)
			m_bShowAll=agtrue;
	}
	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//Key up nay cua view
void CAGimageListView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_SHIFT && GetKeyState(VK_CONTROL))
	{
		if(m_bShowAll)
		{
			ShowAllAGimageData();
			m_bShowAll=agfalse;
		}
	}
	CListView::OnKeyUp(nChar, nRepCnt, nFlags);
}

/*******************************class CAGimagePalDlg*******************************/

#include "../../ip/main/AGimageUtil.h"

CAGimagePalDlg::CAGimagePalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, agbool bDeleteAGimage, CWnd* pParent)
{
	//{{AFX_DATA_INIT(CAGimagePalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pAGimage=pAGimage;
	m_bDeleteAGimage=bDeleteAGimage;
	m_bRainbow=agfalse;	//khong ve bang mau thanh vet dai

	//kich thuoc moi o mau
	m_squareXY=CSize(AGMAGICIP_MFC_UI_PAL_SQUARE_X,AGMAGICIP_MFC_UI_PAL_SQUARE_Y);
	//khoang cach giua cac o
	m_sizeHinge=CSize(AGMAGICIP_MFC_UI_PAL_SQUARE_HINGEX,AGMAGICIP_MFC_UI_PAL_SQUARE_HINGEY);

	m_nCols=AGMAGICIP_MFC_UI_PAL_NUM_COLS;

	Create(nIDTemplate,pParent);
}	
CAGimagePalDlg* CAGimagePalDlg::ShowPalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, agbool bDeleteAGimage)
{
	CAGimagePalDlg* pDlg=new CAGimagePalDlg(nIDTemplate,pAGimage,bDeleteAGimage);
	pDlg->ShowWindow(SW_SHOWNORMAL);
	return pDlg;
}


void CAGimagePalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGimagePalDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAGimagePalDlg, CDialog)
	//{{AFX_MSG_MAP(CAGimagePalDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimagePalDlg message handlers

int CAGimagePalDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT(FALSE);
	return 0;
	//return CDialog::DoModal();
}
void CAGimagePalDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();

	if(m_bDeleteAGimage)
		delete m_pAGimage;
	delete this;
}
void CAGimagePalDlg::OnOK()
{
	if(!UpdateData(TRUE))
		return;
	DestroyWindow();
}
void CAGimagePalDlg::OnCancel()
{
	DestroyWindow();
}

BOOL CAGimagePalDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAGimage==NULL)
		return FALSE;

	CSize	size;
	if(!CAGimageMicUtil::DrawPal(CPoint(0,0),m_pAGimage,m_squareXY,m_nCols,m_bRainbow,NULL,&size,m_sizeHinge))
		return FALSE;

	CRect rc(0,0,0,0);
	rc.right=size.cx;
	rc.bottom=size.cy;
	CalcWindowRect(&rc,CWnd::adjustOutside);
	SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAGimagePalDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	if(m_pAGimage==NULL)
		return;

	CAGimageMicUtil::DrawPal(CPoint(0,0),m_pAGimage,m_squareXY,m_nCols,m_bRainbow,&dc,NULL,m_sizeHinge);
}

/*******************************class CAGimagePalModalDlg*******************************/

#include "../../ip/main/AGimageUtil.h"

CAGimagePalModalDlg::CAGimagePalModalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, agbool bDeleteAGimage, CWnd* pParent)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CAGimagePalModalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pAGimage=pAGimage;
	m_bDeleteAGimage=bDeleteAGimage;
	m_bRainbow=agfalse;	//khong ve bang mau thanh vet dai

	//kich thuoc moi o mau
	m_squareXY=CSize(AGMAGICIP_MFC_UI_PAL_SQUARE_X,AGMAGICIP_MFC_UI_PAL_SQUARE_Y);
	//khoang cach giua cac o
	m_sizeHinge=CSize(AGMAGICIP_MFC_UI_PAL_SQUARE_HINGEX,AGMAGICIP_MFC_UI_PAL_SQUARE_HINGEY);

	m_nCols=AGMAGICIP_MFC_UI_PAL_NUM_COLS;
}	
agint32 CAGimagePalModalDlg::ShowPalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, agbool bDeleteAGimage)
{
	CAGimagePalModalDlg dlg(nIDTemplate,pAGimage,bDeleteAGimage);
	return dlg.DoModal();
}


void CAGimagePalModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGimagePalModalDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAGimagePalModalDlg, CDialog)
	//{{AFX_MSG_MAP(CAGimagePalModalDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGimagePalModalDlg message handlers

int CAGimagePalModalDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	int code=CDialog::DoModal();
	if(m_bDeleteAGimage)
		delete m_pAGimage;
	return code;
}

BOOL CAGimagePalModalDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAGimage==NULL)
		return FALSE;

	CSize	size;
	if(!CAGimageMicUtil::DrawPal(CPoint(0,0),m_pAGimage,m_squareXY,m_nCols,m_bRainbow,NULL,&size,m_sizeHinge))
		return FALSE;

	CRect rc(0,0,0,0);
	rc.right=size.cx;
	rc.bottom=size.cy;
	CalcWindowRect(&rc,CWnd::adjustOutside);
	SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),SWP_NOMOVE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAGimagePalModalDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	if(m_pAGimage==NULL)
		return;

	CAGimageMicUtil::DrawPal(CPoint(0,0),m_pAGimage,m_squareXY,m_nCols,m_bRainbow,&dc,NULL,m_sizeHinge);
}

/***********************class CAGsemanticOptionsTree****************************/
CAGsemanticOptionsTreeItem::CAGsemanticOptionsTreeItem() : COptionTreeItemEdit(), CAGmagicDBOrg()
{
	m_pSemantic=NULL;
}
CAGsemanticOptionsTreeItem::~CAGsemanticOptionsTreeItem()
{
	if(m_pSemantic) delete m_pSemantic; m_pSemantic=NULL;
}
void CAGsemanticOptionsTreeItem::Import(CAGimageSemantic* pSemantic)
{
	if(pSemantic==NULL)		throw _T("Invalid parameter");
	if(GetSafeHwnd()!=NULL)	throw _T("Can't import");

	CAGimageSemanticInfo* pSemanticInfo=pSemantic->m_pInfo;

	SetLabelText(pSemantic->m_Name);
	CreateEditItem(NULL, NULL);
	ReadOnly(TRUE);
	if(pSemanticInfo)
	{
		SetInfoText(pSemanticInfo->m_Descs);
		SetWindowText(pSemanticInfo->m_Descs);
	}
	else
	{
		SetInfoText(pSemantic->m_Name);
		SetWindowText(pSemantic->m_Name);
	}

	if(m_pSemantic==NULL) m_pSemantic=new CAGimageSemantic();
	m_pSemantic->CopyFrom(pSemantic);

	DBCnnAttach(pSemantic->DBCnnGet());
}
void CAGsemanticOptionsTreeItem::Export(CAGimageSemantic* pSemantic)
{
	if(pSemantic==NULL) throw _T("Invalid parameter");
	pSemantic->Destroy();
	if(m_pSemantic)	pSemantic->CopyFrom(m_pSemantic);
}

void* CAGsemanticOptionsTreeItem::DBCnnAttach(void* pDBCnnI)//khong AddRef, tra ve Connection cu doi ADO
{
	if(m_pSemantic) m_pSemantic->DBCnnAttach(pDBCnnI);
	return CAGmagicDBOrg::DBCnnAttach(pDBCnnI);
}
void* CAGsemanticOptionsTreeItem::DBCnnDetach()//khong Release
{
	if(m_pSemantic) m_pSemantic->DBCnnDetach();
	return CAGmagicDBOrg::DBCnnDetach();
}

CAGsemanticOptionsTree::CAGsemanticOptionsTree() : COptionTree(), CAGmagicDBOrg()
{
}
CAGsemanticOptionsTree::~CAGsemanticOptionsTree()
{
}
void CAGsemanticOptionsTree::InsertFromNode(CAGimageSemanticNode* pNode, CAGsemanticOptionsTreeItem* pParentItem)//pParentItem=NULL: Root item 
{
	if(pNode==NULL || pNode->GetSemantic()==NULL) return;

	CAGsemanticOptionsTreeItem* item = (CAGsemanticOptionsTreeItem*)InsertItem(new CAGsemanticOptionsTreeItem(), pParentItem);
	item->Import(pNode->GetSemantic());

	if(pNode->m_pChilds)
	{
		agint32 n=pNode->m_pChilds->GetSize();
		for(agint32 i=0; i<n; i++)
			InsertFromNode(pNode->m_pChilds->GetAt(i),item);
	}
}
void CAGsemanticOptionsTree::InsertToNode(CAGsemanticOptionsTreeItem* pItem, CAGimageSemanticNode*& pParentNode)
{
	//pParentNode=NULL: Root Node
	if(pItem==NULL) return;
	CAGsemanticOptionsTreeItem* pParentItem=(CAGsemanticOptionsTreeItem*) ( ((COptionTreeItem*)pItem)->GetParent() );
	

	if(pParentNode==NULL)
	{
		CAGimageSemantic* pSemantic=new CAGimageSemantic();
		pItem->Export(pSemantic);
		pParentNode=CAGimageSemanticTree::newNode(pSemantic);

		CAGsemanticOptionsTreeItem* pChildItem=(CAGsemanticOptionsTreeItem*)pItem->GetChild();
		InsertToNode(pChildItem,pParentNode);
	}
	else
	{
		while(pItem!=NULL)
		{
			CAGimageSemantic*		pSemantic=new CAGimageSemantic();
			pItem->Export(pSemantic);
			CAGimageSemanticNode*	pNode=CAGimageSemanticTree::newNode(pSemantic);
			CAGimageSemanticTree::InsertNode(pParentNode,pNode);

			CAGsemanticOptionsTreeItem* pChildItem=(CAGsemanticOptionsTreeItem*)pItem->GetChild();
			if(pChildItem) InsertToNode(pChildItem,pNode);

			pItem=(CAGsemanticOptionsTreeItem*)pItem->GetSibling();

		}
	}

}
void CAGsemanticOptionsTree::Import(CAGimageSemanticTree* pImageTree)
{
	if(pImageTree==NULL) throw _T("Invalid Parameter");
	DeleteAllItems();
	InsertFromNode(pImageTree->m_pRoot,NULL);
}
void CAGsemanticOptionsTree::Export(CAGimageSemanticTree* pImageTree)
{
	if(pImageTree==NULL) throw _T("Invalid Parameter");
	pImageTree->Destroy();

	CAGsemanticOptionsTreeItem* pFirstItem=(CAGsemanticOptionsTreeItem*)(GetRootItem()->GetChild());
	InsertToNode(pFirstItem,pImageTree->m_pRoot); 
}
CAGsemanticOptionsTreeItem* CAGsemanticOptionsTree::InsertItemEx(agtchar Name[], agtchar Descs[], CAGsemanticOptionsTreeItem* pParentItem, agbool bIsDBInsert)
{
	CAGsemanticOptionsTreeItem* item = (CAGsemanticOptionsTreeItem*)InsertItem(new CAGsemanticOptionsTreeItem(), pParentItem);

	aguint_id ParentID=0, ImageType=0;
	if(pParentItem)
	{
		ParentID=pParentItem->m_pSemantic->m_ID;
		ImageType=pParentItem->m_pSemantic->m_ImageType;
	}
	CAGimageSemantic semantic;
	semantic.Create(0,Name,ParentID,ImageType,Descs);

	item->Import(&semantic);
	item->DBCnnAttach(DBCnnGet());

	if(bIsDBInsert)
	{
		item->m_pSemantic->DBInsert(agtrue);
	}
	return item;
}

/***********************class CAGsemanticCheckedTree****************************/
CAGsemanticCheckedTree::CAGsemanticCheckedTree() : CAGcheckedTree()
{
}

CAGsemanticCheckedTree::~CAGsemanticCheckedTree()
{
}


BEGIN_MESSAGE_MAP(CAGsemanticCheckedTree, CAGcheckedTree)
	//{{AFX_MSG_MAP(CAGsemanticCheckedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGsemanticCheckedTree message handlers
CAGimageSemanticNode* CAGsemanticCheckedTree::GetSemanticNode(HTREEITEM hItem)
{
	if(hItem==NULL) return NULL;
	return (CAGimageSemanticNode*)GetItemData(hItem);
}

void CAGsemanticCheckedTree::InsertFromNode(CAGimageSemanticNode* pNode, HTREEITEM hParentItem)//hParentItem=NULL: Root item 
{
	if(pNode==NULL ) return;

	LPTSTR szItemText=NULL;
	CAGimageSemantic* pSemantic=pNode->GetSemantic();
	if(pSemantic)
	{
		if(pSemantic->m_pInfo)
			szItemText=pSemantic->m_pInfo->m_Descs;
		if(szItemText==NULL)
			szItemText=pSemantic->m_Name;
	}
	LPARAM lParam=(LPARAM)pNode;

	HTREEITEM item = InsertItem(hParentItem,szItemText,lParam,FALSE);

	if(pNode->m_pChilds)
	{
		agint32 n=pNode->m_pChilds->GetSize();
		for(agint32 i=0; i<n; i++)
			InsertFromNode(pNode->m_pChilds->GetAt(i),item);
	}
}
void CAGsemanticCheckedTree::Import(CAGimageSemanticTree* pImageTree)
{
	if(pImageTree==NULL) throw _T("Invalid Parameter");
	DeleteAllItems();
	InsertFromNode(pImageTree->m_pRoot,NULL);
}
void CAGsemanticCheckedTree::UpdateSemanticWeight()
{
	HTREEITEM hRoot=GetRootItem();
	UpdateSemanticWeight(hRoot, 0);
}
void CAGsemanticCheckedTree::UpdateSemanticWeight(HTREEITEM hItem, agreal64 level)
{
	if(hItem==NULL) return;

	level ++;
	HTREEITEM hSiblingItem=hItem;
	while(hSiblingItem!=NULL)
	{
		if(GetCheck(hSiblingItem))
		{
			CAGimageSemanticNode* pNode=(CAGimageSemanticNode*)GetSemanticNode(hSiblingItem);
			if(pNode)
				pNode->SetWeight(pNode->GetWeight() + 1*level);
			CTreeCtrl::SetCheck(hSiblingItem,FALSE);

			HTREEITEM hChildItem=GetChildItem(hSiblingItem);
			UpdateSemanticWeight(hChildItem, level);
		}
		hSiblingItem=GetNextSiblingItem(hSiblingItem);
	}
}

#endif	//#if AGMAGIC_SUPPORT_MFC

/*******************************class CAGimageUIUtil*******************************/
void CAGimageUIUtil::Show(CAGimageObjPtrbuMatrix* me, agbool bIsModal)
{
	agint32 n=me->GetSize();
#if AGMAGIC_SUPPORT_MFC
	if(n==0)	::MessageBox(NULL,_T("No Image to show"),_T("Error"),MB_OK|MB_ICONSTOP);
	else
	{
		CAGimageObjPtrbuMatrix tempMatrix;
		tempMatrix.CopyFrom(me,agfalse);
		tempMatrix.Flip();
		CAGptrArray tdAGimageAA;
		tempMatrix.Export(&tdAGimageAA,agfalse);
		tempMatrix.SetNULLAll();
		if(bIsModal)
			CAGimageAAbuModalDlg::ShowAGimageAADlg(IDD_AGMAGICIP_DEFAULT,&tdAGimageAA);
		else
			CAGimageAAbuModalDlg::ShowAGimageAADlg(IDD_AGMAGICIP_DEFAULT,&tdAGimageAA);
		DELETE_AGMAGICIP_ARRAYPTR_ARRAY_ONLY_ROW(tdAGimageAA)
	}
#else
	throw _T("Implement not yet");
#endif
}
void CAGimageUIUtil::Show(CAGimageObjPtrtdMatrix* me, agbool bIsModal)
{
	agint32 n=me->GetSize();
#if AGMAGIC_SUPPORT_MFC
	if(n==0)	::MessageBox(NULL,_T("No Image to show"),_T("Error"),MB_OK|MB_ICONSTOP);
	else
	{
		CAGptrArray tdAGimageAA;
		me->Export(&tdAGimageAA,agfalse);
		if(bIsModal)
			CAGimageAAbuModalDlg::ShowAGimageAADlg(IDD_AGMAGICIP_DEFAULT,&tdAGimageAA);
		else
			CAGimageAAbuModalDlg::ShowAGimageAADlg(IDD_AGMAGICIP_DEFAULT,&tdAGimageAA);
		DELETE_AGMAGICIP_ARRAYPTR_ARRAY_ONLY_ROW(tdAGimageAA)
	}
#else
	throw _T("Implement not yet");
#endif
}
void CAGimageUIUtil::Show(CAGimageObjPtrVec* me, agbool bIsModal)
{
	agint32 n=me->GetSize();
#if AGMAGIC_SUPPORT_MFC
	if(n==0)	::MessageBox(NULL,_T("No Image to show"),_T("Error"),MB_OK|MB_ICONSTOP);
	else
	{
		CAGptrArray AGimageA;
		me->Export(&AGimageA,agfalse);
		//if(bIsModal)
		//	CAGimageAModalDlg::ShowAGimageADlg(IDD_AGMAGICIP_DEFAULT,&AGimageA);
		//else
		//	CAGimageADlg::ShowAGimageADlg(IDD_AGMAGICIP_DEFAULT,&AGimageA);
	}
#else
	throw _T("Implement not yet");
#endif
}
void CAGimageUIUtil::Show(CAGimageSeg* me, agbool bIsModal)
{
#if AGMAGIC_SUPPORT_MFC
	if(me->m_pAGimage==NULL)	::MessageBox(NULL,_T("No Image to show"),_T("Error"),MB_OK|MB_ICONSTOP);
	else
	{
		if(bIsModal)
			CAGimageModalDlg::ShowAGimageDlg(IDD_AGMAGICIP_DEFAULT, me->m_pAGimage, _T("Image of segment"));
		else
			CAGimageDlg::ShowAGimageDlg(IDD_AGMAGICIP_DEFAULT, me->m_pAGimage, _T("Image of segment"));
	}
#else
	throw _T("Implement not yet");
#endif
}
void CAGimageUIUtil::Show(CAGimageSegs* me, agbool bIsModal)
{
	agint32 n=me->GetSize();
#if AGMAGIC_SUPPORT_MFC
	if(n==0)	::MessageBox(NULL,_T("No Image to show"),_T("Error"),MB_OK|MB_ICONSTOP);
	else
	{
		agint32 i;
		for(i=0; i<n; i++) 
		{
			if(me->GetAt(i)->m_pAGimage->GetWidth()>320 || 
			   me->GetAt(i)->m_pAGimage->GetHeight()>240)
			   break;
		}
		if(i<n)
		{
			for(i=0; i<n; i++)
				CAGimageUIUtil::Show(me->GetAt(i));
		}
		else
		{
			CAGptrArray AGimageA;
			for(i=0; i<n; i++) AGimageA.Add(me->GetAt(i)->m_pAGimage);
			if(bIsModal)
				CAGimageAModalDlg::ShowAGimageADlg(IDD_AGMAGICIP_DEFAULT,&AGimageA);
			else
				CAGimageADlg::ShowAGimageADlg(IDD_AGMAGICIP_DEFAULT,&AGimageA);
		}
	}
#else
	throw _T("Implement not yet");
#endif
}

