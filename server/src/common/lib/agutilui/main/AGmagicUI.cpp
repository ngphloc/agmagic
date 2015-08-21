#include "AGmagicUI.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/******************************class BCMenu************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/bcmenu/BCMenu.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CxTargetButton************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CxTargetButton/xTargetButton.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CxSkinButton************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CxSkinButton/xSkinButton.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CDialogSK************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CDialogSK/CDialogSK.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CClockST************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CClockST/ClockST.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CLable************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CLabel/Label.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CPictureEx************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CPictureEx_CPictureExWnd/mfc/PictureEx.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/*************************class CSizingControlBar, CSizingControlBarG, CSizingControlBarCF*******************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/sizecbar/src/sizecbar.cpp"
#include "../../ui/sizecbar/src/scbarg.cpp"
#include "../../ui/sizecbar/src/scbarcf.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CPictureEx************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/ResizeDlg/ResizeDlg.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CXInfoTip************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/InfoTip/XInfoTip.cpp"

CAGxinfoTip::CAGxinfoTip() : CXInfoTip()
{
}
CAGxinfoTip::~CAGxinfoTip()
{
}
void CAGxinfoTip::RelayEvent(LPMSG lpMsg)
{
	switch(lpMsg->message)
	{
		case WM_MOUSEMOVE:
		{
			HRGN	hRegion;
			CSize	WindowSize;
			CDC		*pDC = GetDC();
			GetWindowRegion(pDC, &hRegion, &WindowSize);

			CPoint	curpos;
			GetCursorPos(&curpos);

			if(curpos.x - WindowSize.cx + CX_ROUNDED <0)		curpos.x=0;
			if(curpos.y - WindowSize.cy + CY_ROUNDED<0)		curpos.y=0;
			if(curpos.x==0 || curpos.y==0)
			{
				CPoint			point;
				CWnd			*pWindow;
				CString			szTooltipText;
				TipToolInfo		Info;
				GetCursorPos(&point);
				
				if (point != m_ptOrigin)
				{
					// Find the tool
					pWindow = WindowFromPoint(point);
					if (pWindow != NULL)
					{
						if (m_ToolMap.Lookup(pWindow->m_hWnd, Info))
						{
							m_ptOrigin = point;
							SetIcon(Info.hIcon);
							Show(Info.szText, &point);
						}
					}
				}

				// Hide the tooltip
				if (point != m_ptOrigin)	ShowWindow(SW_HIDE);
				return;
			}
		}		
		break;
	}
	CXInfoTip::RelayEvent(lpMsg);
}
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class COptionTree************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/OptionTree/src/COptionTree/OptionTree.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeCheckButton.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeColorPopUp.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeFileDlg.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeFontSel.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeFontSelColorButton.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeFontSelFontCombo.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeFontSelGlobals.cpp"

#include "../../ui/OptionTree/src/COptionTree/OptionTreeFontSelSizeCombo.cpp"

#include "../../ui/OptionTree/src/COptionTree/OptionTreeImagePopUp.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeInfo.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeIPAddressEdit.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItem.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemCheckBox.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemColor.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemComboBox.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemDate.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemEdit.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemFile.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemFont.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemHyperLink.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemImage.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemIPAddress.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemRadio.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemSpinner.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeItemStatic.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeList.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeRadioButton.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeSpinnerButton.cpp"
#include "../../ui/OptionTree/src/COptionTree/OptionTreeSpinnerEdit.cpp"

#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CAGcheckedTree************************************/
#if AGMAGIC_SUPPORT_MFC
/////////////////////////////////////////////////////////////////////////////
// CAGcheckedTree

CAGcheckedTree::CAGcheckedTree()
{
}

CAGcheckedTree::~CAGcheckedTree()
{
}


BEGIN_MESSAGE_MAP(CAGcheckedTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CAGcheckedTree)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGcheckedTree message handlers

BOOL CAGcheckedTree::CreateEx(const RECT &rect, CWnd *pParentWnd, UINT nID)
{
	return CTreeCtrl::Create(
		WS_CHILD | 
		WS_VISIBLE |
		WS_BORDER |
		WS_TABSTOP |
		TVS_HASBUTTONS |
		TVS_HASLINES |
		TVS_LINESATROOT |
		TVS_SHOWSELALWAYS |
		TVS_CHECKBOXES |		// These style constant is needed !
		TVS_TRACKSELECT, 
		rect, pParentWnd, nID
	);
	SetBitmaps(0,0,IDB_TREE_BITMAP_STATUS,16);
}
// Method to set the images for the tree-control
void CAGcheckedTree::SetBitmaps(UINT NormalId,	// Resource-Id of the item-images
								int  normal_cx,
								UINT StatusId,	// Resource-Id of the checkbox-images
								int  status_cx
							   )
{
	// create Imagelists
	// 16x16 Pixel, white colour is transparent
	m_NormalImageList.DeleteImageList();
	if(NormalId!=0)
		m_NormalImageList.Create(NormalId, normal_cx, 2, RGB (255,255,255));

	m_StatusImageList.DeleteImageList();
	if(StatusId!=0)
		m_StatusImageList.Create(StatusId, status_cx, 2, RGB (255,255,255));

	// and set the imagelists
	SetImageList(&m_NormalImageList, TVSIL_NORMAL );
	SetImageList(&m_StatusImageList, TVSIL_STATE );
}
HTREEITEM CAGcheckedTree::InsertItem(HTREEITEM hParentItem, LPCTSTR szItemText, LPARAM lParam, BOOL bIsChecked)
{
	TV_INSERTSTRUCT	InsertItem;
	memset (&InsertItem,0,sizeof(TV_INSERTSTRUCT));
	
	InsertItem.hParent = hParentItem;
	InsertItem.hInsertAfter = TVI_LAST;

	InsertItem.item.mask=TVIF_STATE | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	// !!! DO NOT USE Index 0 for Statusimage
	if(m_StatusImageList.m_hImageList)
	{
		if(bIsChecked)
			InsertItem.item.state = INDEXTOSTATEIMAGEMASK(1);
		else
			InsertItem.item.state = INDEXTOSTATEIMAGEMASK(2);
		InsertItem.item.stateMask = TVIS_STATEIMAGEMASK;
	}
	InsertItem.item.pszText=(LPSTR)szItemText;
	InsertItem.item.cchTextMax = 255;
	if(m_NormalImageList.m_hImageList)
	{
		InsertItem.item.iImage = 0;
		InsertItem.item.iSelectedImage = 1;
	}
	InsertItem.item.lParam=lParam;

	return CTreeCtrl::InsertItem(&InsertItem);
}
BOOL CAGcheckedTree::IsChecked(HTREEITEM hItem)
{
	UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
	if(nState==1) return TRUE;

	return FALSE;
}
BOOL CAGcheckedTree::SetCheck(HTREEITEM hItem, BOOL fCheck)
{
	if(!CTreeCtrl::SetCheck(hItem,fCheck)) return FALSE;

	SetCheckChildOf(hItem, fCheck);
	SetCheckParentOf(hItem, fCheck);
	return TRUE;
}
void CAGcheckedTree::SetCheckChildOf(HTREEITEM hItem, BOOL fCheck)
{
	if(hItem==NULL)			return;
	HTREEITEM				hChildItem=GetChildItem(hItem);

	while(hChildItem!=NULL)
	{
		if(CTreeCtrl::SetCheck(hChildItem,fCheck))
			SetCheckChildOf(hChildItem,fCheck);

		hChildItem=GetNextSiblingItem(hChildItem);
	}
}
void CAGcheckedTree::SetCheckParentOf(HTREEITEM hItem, BOOL fCheck)
{
	if(hItem==NULL)			return;
	HTREEITEM				hParentItem=GetParentItem(hItem);
	if(hParentItem==NULL)	return;

	if(!fCheck && IsHavedOneChildChecked(hParentItem))
		return;

	if(CTreeCtrl::SetCheck(hParentItem,fCheck))
	{
		SetCheckParentOf(hParentItem, fCheck);
	}	
}
BOOL CAGcheckedTree::IsHavedOneChildChecked(HTREEITEM hParentItem)
{
	if(hParentItem==NULL) return FALSE;
	HTREEITEM	hSiblingItem=GetChildItem(hParentItem);

	while(hSiblingItem!=NULL)
	{
		if(GetCheck(hSiblingItem)) return TRUE;
		hSiblingItem=GetNextSiblingItem(hSiblingItem);
	}
	return FALSE;
}


void CAGcheckedTree::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTreeCtrl::OnLButtonDown(nFlags, point);

	UINT uFlags=0;
	HTREEITEM hItem = HitTest(point,&uFlags);

	if( uFlags & TVHT_ONITEMSTATEICON )
		SetCheck(hItem, GetCheck(hItem));
}

#endif	//#if AGMAGIC_SUPPORT_MFC
/******************************class CAGmagicLoginDlg************************************/

#if AGMAGIC_SUPPORT_MFC
#include "../../../include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../agutil/main/AGutilCore.h"
#include "../../../include/AGEND_INCLUDE_LIBRARY.h"
CAGmagicLoginDlg::CONNECTION_TYPE CAGmagicLoginDlg::ConnectionType[NUMBER_OF_SUPPORTED_CONNECTION_TYPE]= 
	{
		{	_T("Microsoft SQL Server"), MICROSOFT_SQL_SERVER_CONECTION_TYPE},
		{	_T("Microsoft Access"),		MICROSOFT_ACCESS_CONECTION_TYPE},
		{	_T("Oracle"),				ORACLE_CONECTION_TYPE}
	};

/////////////////////////////////////////////////////////////////////////////
// CAGmagicLoginDlg dialog


CAGmagicLoginDlg::CAGmagicLoginDlg(aguint_id id, CWnd* pParent /*=NULL*/)
	: CDialog((UINT)id, pParent)
{
	//{{AFX_DATA_INIT(CAGmagicLoginDlg)
	m_ServerName = _T("(local)");
	m_Port = 3751;
	m_DBName = _T("AGmagic");
	m_User = _T("sa");
	m_Password = _T("");
	m_DBProvider = _T("");
	//}}AFX_DATA_INIT
	m_szCnn=NULL;
	m_Provider=0;
}
CAGmagicLoginDlg::CAGmagicLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAGmagicLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAGmagicLoginDlg)
	m_ServerName = _T("(local)");
	m_Port = 3751;
	m_DBName = _T("AGmagic");
	m_User = _T("sa");
	m_Password = _T("");
	m_DBProvider = _T("");
	//}}AFX_DATA_INIT
	m_szCnn=NULL;
	m_Provider=0;
}
CAGmagicLoginDlg::~CAGmagicLoginDlg()
{
	if(m_szCnn) free(m_szCnn); m_szCnn=NULL;
}


void CAGmagicLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAGmagicLoginDlg)
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_SERVER_MACHINE, m_ServerNameCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_PORT, m_PortCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_DB_CONNECTION_TYPE, m_DBConnectionTypeCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_DB_PROVIDER, m_DBProviderCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_DB_NAME, m_DBNameCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_DB_BROWSE, m_DBBrowseCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_DB_CREATE, m_DBCreateCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_USER, m_UserCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_USER_REGISTER, m_UserRegisterCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_PASSWORD, m_PasswordCtrl);
	DDX_Control(pDX, IDC_AGMAGIC_LOGIN_TEST_CONNECTION, m_TestConnectionCtrl);
	DDX_Text(pDX, IDC_AGMAGIC_LOGIN_SERVER_MACHINE, m_ServerName);
	DDX_Text(pDX, IDC_AGMAGIC_LOGIN_PORT, m_Port);
	DDX_Text(pDX, IDC_AGMAGIC_LOGIN_DB_PROVIDER, m_DBProvider);
	DDX_Text(pDX, IDC_AGMAGIC_LOGIN_DB_NAME, m_DBName);
	DDX_Text(pDX, IDC_AGMAGIC_LOGIN_USER, m_User);
	DDX_Text(pDX, IDC_AGMAGIC_LOGIN_PASSWORD, m_Password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAGmagicLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CAGmagicLoginDlg)
	ON_BN_CLICKED(IDC_AGMAGIC_LOGIN_DB_BROWSE, OnDBBrowse)
	ON_BN_CLICKED(IDC_AGMAGIC_LOGIN_DB_CREATE, OnDBCreate)
	ON_BN_CLICKED(IDC_AGMAGIC_LOGIN_USER_REGISTER, OnUserRegister)
	ON_BN_CLICKED(IDC_AGMAGIC_LOGIN_TEST_CONNECTION, OnTestConnection)
	ON_CBN_SELCHANGE(IDC_AGMAGIC_LOGIN_DB_CONNECTION_TYPE, OnSelchangeConnectionType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


agint32 CAGmagicLoginDlg::GetConnectionTypeIdxFromConnectionTypeID(aguint_id ConnectionTypeID)
{
	for(agint32 i=0; i<NUMBER_OF_SUPPORTED_CONNECTION_TYPE; i++)
		if(ConnectionType[i].id==ConnectionTypeID) return i;
	return -1;
}
void CAGmagicLoginDlg::EnableAllCtrl(BOOL bEnable)
{
	m_ServerNameCtrl.EnableWindow(bEnable);
	m_PortCtrl.EnableWindow(bEnable);
	m_DBConnectionTypeCtrl.EnableWindow(bEnable);
	m_DBProviderCtrl.EnableWindow(bEnable);
	m_DBNameCtrl.EnableWindow(bEnable);
	m_DBBrowseCtrl.EnableWindow(bEnable);
	m_DBCreateCtrl.EnableWindow(bEnable);
	m_UserCtrl.EnableWindow(bEnable);
	m_UserRegisterCtrl.EnableWindow(bEnable);
	m_PasswordCtrl.EnableWindow(bEnable);
	m_TestConnectionCtrl.EnableWindow(bEnable);
}
void CAGmagicLoginDlg::ResetAllCtrl()
{
	m_ServerName = _T("");
	m_Port = 0;
	m_DBProvider = _T("");
	m_DBName = _T("");
	m_User = _T("");
	m_Password = _T("");
	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAGmagicLoginDlg message handlers

BOOL CAGmagicLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for(agint32 i=0; i<NUMBER_OF_SUPPORTED_CONNECTION_TYPE; i++)
	{
		m_DBConnectionTypeCtrl.AddString(ConnectionType[i].szName);
	#if AGMAGIC_MFC_VER < 0x0700
		m_DBConnectionTypeCtrl.SetItemData(i,ConnectionType[i].id);
	#else
		m_DBConnectionTypeCtrl.SetItemData(i,(DWORD_PTR)(ConnectionType[i].id));
	#endif
	}
	m_DBConnectionTypeCtrl.SetCurSel(0);
	OnSelchangeConnectionType();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAGmagicLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(!OnTestConnectionEx()) return;
	GetConnectionString(m_szCnn,m_Provider);
	CDialog::OnOK();
}

void CAGmagicLoginDlg::OnDBBrowse() 
{
	// TODO: Add your control notification handler code here
	
}
void CAGmagicLoginDlg::OnDBCreate() 
{
	// TODO: Add your control notification handler code here
	
}

void CAGmagicLoginDlg::OnUserRegister() 
{
	// TODO: Add your control notification handler code here
	
}
agbool CAGmagicLoginDlg::TestConnection(agtchar szCnn[]) 
{
	agbool bTest=agfalse;
#if	AGMAGIC_SUPPORT_ADO
	::CoInitialize(NULL);
	try
	{

		_ConnectionPtr	pADODBCnn;
		pADODBCnn.CreateInstance(_T("ADODB.Connection"));
		pADODBCnn->Open((LPCTSTR)szCnn,_T(""),_T(""),adConnectUnspecified);
		pADODBCnn->Close();

		bTest=agtrue;
	}
	catch(_com_error &e)
	{
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
	}
	::CoUninitialize();
#else
	throw _T("Implement not yet");
#endif
	return bTest;
}
agbool CAGmagicLoginDlg::OnTestConnectionEx() 
{
	agtchar*	szCnn=NULL;
	agint32		Provider=0;
	GetConnectionString(szCnn, Provider);
	if(szCnn==NULL)
	{
		MessageBox(_T("Connection failed. You can not run program"),_T("Error"),MB_OK|MB_ICONSTOP);
		return agfalse;
	}

	CString szMsg=_T("Connection String is : \"");
	szMsg +=szCnn;
	szMsg +=_T("\".\n\nYou Press OK to continue.");
	agint32 idx1=szMsg.Find(_T("Password="));
	if(idx1!=-1)
	{
		agint32 idx2=szMsg.Find(_T(";"),idx1);
		if(idx2!=-1)
		{
			CString szMsg1=szMsg.Mid(0,idx1);
			CString szMsg2=szMsg.Mid(idx2+1);
			szMsg=szMsg1+szMsg2;
		}
	}

	MessageBox(szMsg,_T("Notice"),MB_OK|MB_ICONINFORMATION);
	if(!TestConnection(szCnn))
	{
		MessageBox(_T("Connection failed. You can not run program"),_T("Error"),MB_OK|MB_ICONSTOP);
		if(szCnn) free(szCnn); szCnn=NULL;
		return agfalse;
	}

	MessageBox(_T("Connection successfully. You press OK to continue."),_T("Success"),MB_OK);
	if(szCnn) free(szCnn); szCnn=NULL;
	return agtrue;
}
void CAGmagicLoginDlg::OnTestConnection() 
{
	// TODO: Add your control notification handler code here
	OnTestConnectionEx();
}
void CAGmagicLoginDlg::UpdateConnectionType(aguint_id ConnectionTypeID)
{
	switch(ConnectionTypeID)
	{
		case MICROSOFT_SQL_SERVER_CONECTION_TYPE :
			EnableAllCtrl(TRUE);
			m_DBBrowseCtrl.EnableWindow(FALSE);

			m_ServerName = _T("(local)");
			m_Port = 3751;
			m_DBProvider = _T("SQLOLEDB");
			m_DBName = _T("AGmagic");
			m_User = _T("sa");
			m_Password = _T("");

			break;
		case MICROSOFT_ACCESS_CONECTION_TYPE	:
			EnableAllCtrl(TRUE);
			m_ServerNameCtrl.EnableWindow(FALSE);
			m_PortCtrl.EnableWindow(FALSE);

			m_ServerName = _T("");
			m_Port = 0;
			m_DBProvider = _T("Microsoft.Jet.OLEDB.4.0");
			m_DBName = _T("AGmagic.mdb");
			m_User = _T("");
			m_Password = _T("");
			break;
		case ORACLE_CONECTION_TYPE :
			EnableAllCtrl(FALSE);
			ResetAllCtrl();
			m_DBConnectionTypeCtrl.EnableWindow(TRUE);
			MessageBox(_T("Connection Type not support"),_T("Error"),MB_OK|MB_ICONSTOP);
			break;
		default:
			EnableAllCtrl(FALSE);
			ResetAllCtrl();
			m_DBConnectionTypeCtrl.EnableWindow(TRUE);
			MessageBox(_T("Connection Type not support"),_T("Error"),MB_OK|MB_ICONSTOP);
			return;
	}
	UpdateData(FALSE);
}
void CAGmagicLoginDlg::OnSelchangeConnectionType()
{
	aguint_id				ConnectionTypeID=GetCurConnectionTypeID();
	if(ConnectionTypeID==0) return;
	UpdateConnectionType(ConnectionTypeID);
}
aguint_id CAGmagicLoginDlg::GetCurConnectionTypeID()
{
	agint32						idx=m_DBConnectionTypeCtrl.GetCurSel();
	if(idx==CB_ERR || idx==-1)	return 0;
	return m_DBConnectionTypeCtrl.GetItemData(idx);
}
agbool CAGmagicLoginDlg::GetConnectionString(agtchar*& szCnn, agint32& Provider)
{
#if AGMAGIC_SUPPORT_ADO
	if(szCnn) free(szCnn); szCnn=NULL;
	Provider=0;

	UpdateData(TRUE);
	aguint_id				ConnectionTypeID=GetCurConnectionTypeID();
	if(ConnectionTypeID==0) return agfalse;

	switch(ConnectionTypeID)
	{
		case MICROSOFT_SQL_SERVER_CONECTION_TYPE :
			if(m_ServerName.IsEmpty() || m_DBName.IsEmpty()) return agfalse;

			Provider=AGMAGIC_SQLSERVER_ADO_PROVIDER;
			CAGmagicStrUtil::private_tcscat(szCnn,_T("Provider="),agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,m_DBProvider,agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,_T(";Persist Security Info=False;User ID="),agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,m_User,agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,_T(";Password="),agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,m_Password,agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,_T(";Initial Catalog="),agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,m_DBName,agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,_T(";Data Source="),agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,m_ServerName,agtrue);
			break;
		case MICROSOFT_ACCESS_CONECTION_TYPE	:
			if(m_DBName.IsEmpty()) return agfalse;

			Provider=AGMAGIC_ACCESS_ADO_PROVIDER;
			CAGmagicStrUtil::private_tcscat(szCnn,_T("Provider="),agtrue);
			CAGmagicStrUtil::private_tcscat(szCnn,m_DBProvider,agtrue);

			if(m_DBName.CompareNoCase(_T("AGmagic.mdb"))!=0)
			{
				CAGmagicStrUtil::private_tcscat(szCnn,_T(";Persist Security Info=False;User ID="),agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,m_User,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,_T(";Password="),agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,m_Password,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,_T(";Data Source="),agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,m_DBName,agtrue);
			}
			else
			{
				CAGmagicStrUtil::private_tcscat(szCnn,_T(";Persist Security Info=False;User ID="),agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,m_User,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,_T(";Password="),agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,m_Password,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,_T(";Data Source="),agtrue);

				agtchar* basedir=CAGmagicConfUtil::AGmagicBaseDirAbsoluteFromBin();
				CAGmagicStrUtil::private_tcscat(szCnn,basedir,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,AGMAGIC_DIR_SPLASH_STR,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,_T("data"),agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,AGMAGIC_DIR_SPLASH_STR,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,_T("db"),agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,AGMAGIC_DIR_SPLASH_STR,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,_T("access-2000"),agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,AGMAGIC_DIR_SPLASH_STR,agtrue);
				CAGmagicStrUtil::private_tcscat(szCnn,_T("AGmagic.mdb"),agtrue);
				if(basedir) free(basedir);
			}

			break;
		case ORACLE_CONECTION_TYPE :
			return agfalse;
		default:
			return agfalse;
	}
	return agtrue;
#else //AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif //AGMAGIC_SUPPORT_ADO
}
agtchar* CAGmagicLoginDlg::GetCnnStr()
{
	return m_szCnn;
}
agint32	CAGmagicLoginDlg::GetCnnProvider()
{
	return m_Provider;
}

#endif	//#if AGMAGIC_SUPPORT_MFC



