#if !defined(AGMAGICUI_H__AA20C4AD_AB82_4CCF_93FA_18ED02C5092D__INCLUDED_)
#define AGMAGICUI_H__AA20C4AD_AB82_4CCF_93FA_18ED02C5092D__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif
#include "../../../include/AGmagicDefs.h"
/*********************************class BCMenu***************************************/

#if AGMAGIC_SUPPORT_MFC
#include "../../ui/bcmenu/BCMenu.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CxTargetButton************************************/

#if AGMAGIC_SUPPORT_MFC
#include "../../../../image/ipui/main/AGimageRC.h"
#include "../../../include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../agutil/main/AGutilCore.h"
#include "../../../include/AGEND_INCLUDE_LIBRARY.h"
#include "../../ui/CxTargetButton/xTargetButton.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CxSkinButton************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CxSkinButton/xSkinButton.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CDialogSK************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CDialogSK/CDialogSK.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CClockST************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CClockST/ClockST.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CLabel************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CLabel/Label.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CPictureEx************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/CPictureEx_CPictureExWnd/mfc/PictureEx.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/*************************class CSizingControlBar, CSizingControlBarG, CSizingControlBarCF*******************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/sizecbar/src/sizecbar.h"
#include "../../ui/sizecbar/src/scbarg.h"
#include "../../ui/sizecbar/src/scbarcf.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CResizeDlg************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/ResizeDlg/ResizeDlg.h"
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CXInfoTip************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/InfoTip/XInfoTip.h"
class AGMAGIC_DECL CAGxinfoTip : public CXInfoTip
{
public:
	CAGxinfoTip();
	virtual ~CAGxinfoTip();
	void RelayEvent(LPMSG lpMsg);
};
#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class COptionTree************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/OptionTree/src/COptionTree/OptionTree.h"

#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CAGcheckedTree************************************/

#if AGMAGIC_SUPPORT_MFC

#include "AGmagicUtilRC.h"
class AGMAGIC_DECL CAGcheckedTree : public CTreeCtrl
{
// Construction
public:
	CAGcheckedTree();

	BOOL CreateEx(const RECT &rect, CWnd *pParentWnd, UINT nID);

	// Method to set the images for the tree-control
	void SetBitmaps(UINT NormalId,	// Resource-Id of the item-images
					int  normal_cx,
					UINT StatusId,	// Resource-Id of the checkbox-images
					int  status_cx
				   );
	
	HTREEITEM	InsertItem(HTREEITEM hParentItem, LPCTSTR szItem, LPARAM lParam, BOOL bIsChecked);
	BOOL		IsChecked(HTREEITEM hItem);
	BOOL		SetCheck(HTREEITEM hItem, BOOL fCheck = TRUE);

// Attributes
public:

protected:
	//imagelist for item-images
	CImageList	m_NormalImageList;

	//imagelist for checkbox-images fuer Statusbilder der Elemente
	// !!! KEEP CARE !!!
	// !!! LET IMAGE WITH INDEX 0 EMPTY AND DO NOT USE IT !!!
	CImageList	m_StatusImageList;

	void		SetCheckChildOf(HTREEITEM hItem, BOOL fCheck);
	void		SetCheckParentOf(HTREEITEM hItem, BOOL fCheck);
	BOOL		IsHavedOneChildChecked(HTREEITEM hParentItem);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGcheckedTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGcheckedTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGcheckedTree)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif	//#if AGMAGIC_SUPPORT_MFC

/******************************class CAGmagicLoginDlg************************************/

#if AGMAGIC_SUPPORT_MFC

#include "AGmagicUtilRC.h"

#define NUMBER_OF_SUPPORTED_CONNECTION_TYPE		3

#define MICROSOFT_SQL_SERVER_CONECTION_TYPE		1
#define MICROSOFT_ACCESS_CONECTION_TYPE			2
#define ORACLE_CONECTION_TYPE					3

class AGMAGIC_DECL CAGmagicLoginDlg : public CDialog
{
public:

	struct CONNECTION_TYPE
	{
		agtchar		szName[256];
		aguint_id	id;
	};
	static	CONNECTION_TYPE ConnectionType[NUMBER_OF_SUPPORTED_CONNECTION_TYPE];

protected:
	agint32		GetConnectionTypeIdxFromConnectionTypeID(aguint_id ID);
	void		EnableAllCtrl(BOOL bEnable);
	void		UpdateConnectionType(aguint_id ConnectionTypeID);
	void		ResetAllCtrl();
	aguint_id	GetCurConnectionTypeID();
	agbool		GetConnectionString(agtchar*& szCnn, agint32& Provider);
	agbool		OnTestConnectionEx();

	agtchar*	m_szCnn;
	agint32		m_Provider;

// Construction
public:
	CAGmagicLoginDlg(aguint_id id, CWnd* pParent =NULL);
	CAGmagicLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAGmagicLoginDlg();

	static agbool TestConnection(agtchar szCnn[]);
	agtchar*	GetCnnStr();
	agint32		GetCnnProvider();

// Dialog Data
	//{{AFX_DATA(CAGmagicLoginDlg)
	enum { IDD = IDD_AGMAGIC_LOGIN };
	CEdit	m_ServerNameCtrl;
	CEdit	m_PortCtrl;
	CComboBox	m_DBConnectionTypeCtrl;
	CEdit	m_DBProviderCtrl;
	CEdit	m_DBNameCtrl;
	CButton	m_DBBrowseCtrl;
	CButton	m_DBCreateCtrl;
	CEdit	m_UserCtrl;
	CButton	m_UserRegisterCtrl;
	CEdit	m_PasswordCtrl;
	CButton	m_TestConnectionCtrl;

	CString	m_ServerName;
	UINT	m_Port;
	CString	m_DBProvider;
	CString	m_DBName;
	CString	m_User;
	CString	m_Password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGmagicLoginDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDBBrowse();
	afx_msg void OnDBCreate();
	afx_msg void OnUserRegister();
	afx_msg void OnTestConnection();
	afx_msg void OnSelchangeConnectionType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC

#endif // !defined(AGMAGICUI_H__AA20C4AD_AB82_4CCF_93FA_18ED02C5092D__INCLUDED_)
