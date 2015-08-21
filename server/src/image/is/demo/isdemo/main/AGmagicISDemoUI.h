// AGmagicISDemoUI.h: interface for the AGmagicISDemoUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AGMAGICISDEMOUI_H__202FE12C_E86C_4D6B_BE71_2CD33244D1AF__INCLUDED_)
#define AGMAGICISDEMOUI_H__202FE12C_E86C_4D6B_BE71_2CD33244D1AF__INCLUDED_

#include "../../../../../common/include/AGmagicDefs.h"
#include "AGmagicISDemoUIRC.h"

#include "../../../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
//#include "../../../../../common/lib/agutilui/main/AGmagicUI.h"
#include "../../../../../common/lib/agutilui/main/AGmagicUI2.h"
#include "../../../../ipui/main/AGimageUI.h"
#include "../../../../ipui/main/AGimageUI2.h"
#include "../../../../ip/main/AGsemantic.h"
#include "../../../../is/main/AGmmm.h"
#include "../../../../is/main/AGsearchEngine.h"
#include "../../../../isui/main/AGmagicISUI.h"
#include "../../../../../common/include/AGEND_INCLUDE_LIBRARY.h"

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

/*********************************class CAGmagicISDemoControlBar************************************/
#if AGMAGIC_SUPPORT_MFC
#define		CONTROL_BAR_TEXT_COLOR	(RGB(57,0,127))

class CAGmagicISDemoControlBar : public CDialogBar
{
	DECLARE_DYNAMIC(CAGmagicISDemoControlBar)

	CAGimage* m_pBgImage;

//Attributes
public:
	enum { IDD = IDD_SEARCH_CONTROL_BAR };

	HICON			m_hDefaultTipIcon, m_hInfoTipIcon, m_hQuestionTipIcon;
	CPPToolTip		m_Tip;

	CLabel			m_searchmodelLabel;
	CComboBox		m_searchmodel;

	CxTargetButton	m_confserver;
	CxTargetButton	m_createdb;
	CxSkinButton	m_startserver;
	CxSkinButton	m_stopserver;

	CxSkinButton	m_browse;
	CxSkinButton	m_search;
	CxSkinButton	m_feedback;
public:
	CAGmagicISDemoControlBar();
	CAGmagicISDemoControlBar(CFrameWnd* pFrameWnd);

	virtual ~CAGmagicISDemoControlBar();
	virtual void OnInitDialog();

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAGmagicISDemoControlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};
#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoServerDlg************************************/

#if AGMAGIC_SUPPORT_MFC

#define	SEARCHING_SYSTEM_RUNNING_NOTICE_TEXT	_T("Searching System running ...")
#define	SEARCHING_SYSTEM_STOPPED_NOTICE_TEXT	_T("Searching System stoped !")
#define	TRAINING_SYSTEM_RUNNING_NOTICE_TEXT		_T("Training System running ...")
#define	TRAINING_SYSTEM_STOPPED_NOTICE_TEXT		_T("Training System stoped !")

#define	RUNNING_NOTICE_TEXT_COLOR				(RGB(255,255,0))
#define	STOPPED_NOTICE_TEXT_COLOR				(RGB(255,0,0))

class CAGmagicISDemoServerDlg : public CDialogSK
{
// Construction
public:
	CAGmagicISDemoServerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAGmagicISDemoServerDlg)
	enum { IDD = IDD_ISDEMO_SERVER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CClockST	m_Clock;
	CLabel		m_TrainingSystemNotice, m_SearchingSystemNotice;
	CPictureEx	m_AnimateNotice;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoServerDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGmagicISDemoServerDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif

/******************************class CAGmagicISDemoOutputBar, CAGmagicISDemoOutputEdit************************/
#if AGMAGIC_SUPPORT_MFC

#define	baseEdit	CEdit
class CAGmagicISDemoOutputEdit : public baseEdit
{
// Construction
public:
	CAGmagicISDemoOutputEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoOutputEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISDemoOutputEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISDemoOutputEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#ifndef baseAGmagicISDemoOutputBar
#define baseAGmagicISDemoOutputBar	CSizingControlBarCF
#endif

class CAGmagicISDemoMainFrame;
class CAGmagicISDemoOutputBar : public baseAGmagicISDemoOutputBar
{

// Construction
public:
	CAGmagicISDemoOutputBar();
	CAGmagicISDemoOutputBar(CFrameWnd* pFrameWnd);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoOutputBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISDemoOutputBar();

protected:
	CAGmagicISDemoOutputEdit	m_edit;
	CFont						m_font;

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISDemoOutputBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CAGmagicISDemoMainFrame;
};

#endif

/*******************************class CAGmagicISDemoSearchResultDlg*******************************/

#if AGMAGIC_SUPPORT_MFC
#ifndef baseSearchResultDlg
#define baseSearchResultDlg		CResizeDlg
#endif

#define	MAX_PAGE_BUTTON					10
#define	MAX_NUMBER_OF_LOAD_IMAGES		50

class CAGmagicISDemoDoc;
class AGMAGIC_DECL CAGmagicISDemoSearchResultDlg : public baseSearchResultDlg
{
//
protected:
	CImageList		m_ImageList;
	CToolBarCtrl	m_wndToolBar;
	agbool			SetupImageList();
	void			CreateToolBar();

	CAGptrArray		m_SearchResults;
	agint32			m_nPages;
	agint32			m_iPage;
	agint32			m_NumberOfLoadImages;

	void			DisableToolbar();
	void			ShowPage(agint32 iPage);

	CLabel			m_ListCtrlInfo;
	CStatic			m_ImageInfo;
	CxTargetButton	m_Find;

// Construction
public:
	CAGmagicISDemoSearchResultDlg(CWnd* pParent=NULL);\

	CAGimageListCtrlEx		m_SearchResultCtrl;
	CAGmagicISDemoDoc*	m_pDoc;

	void SetDocument(CAGmagicISDemoDoc* pDoc);

// Dialog Data
	//{{AFX_DATA(CAGmagicISDemoSearchResultDlg)
	enum { IDD = IDD_SEARCH_RESULT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoSearchResultDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGmagicISDemoSearchResultDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg LRESULT OnListCtrlUpdateDocumentAlready(WPARAM wParam, LPARAM lParam);
	afx_msg void OnItemchangedSearchResultListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturnSearchResultListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofMemorySearchResultListCtrl(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnMoveFirst();
	afx_msg void OnMovePrevious();
	afx_msg void OnMoveNext();
	afx_msg void OnMoveLast();
	afx_msg void OnNumber(UINT nID);

	afx_msg void OnUpdateMoveFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMovePrevious(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoveNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoveLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNumber(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC

/*******************************class CAGmagicISDemoProp*******************************/

#if AGMAGIC_SUPPORT_MFC
/////////////////////////////////////////////////////////////////////////////
// CAGmagicISDemoProp dialog

class CAGmagicISDemoProp : public CDialog
{
// Construction
public:
	CAGmagicISDemoProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAGmagicISDemoProp)
	enum { IDD = IDD_IMAGE_PROPERTY };
	CString	m_Features;
	CString	m_FileName;
	CString	m_FilePath;
	UINT	m_ID;
	double	m_Similarity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGmagicISDemoProp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC

/*******************************class CAGsemanticOptionsDlg*******************************/

#if AGMAGIC_SUPPORT_MFC

/////////////////////////////////////////////////////////////////////////////
// CAGinsertTreeItemDlg dialog

class CAGinsertTreeItemDlg : public CDialog
{
// Construction
public:
	CAGinsertTreeItemDlg(CWnd* pParent = NULL);   // standard constructor
	agtchar* GetName();
	agtchar* GetDesc();

// Dialog Data
	//{{AFX_DATA(CAGinsertTreeItemDlg)
	enum { IDD = IDD_INSERT_TREE_ITEM };
	CString	m_Name;
	CString	m_Desc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGinsertTreeItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGinsertTreeItemDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAGsemanticOptionsDlg dialog

class CAGmagicISDemoMainFrame;
class CAGsemanticOptionsDlg : public CDialog
{
// Construction
public:
	CAGsemanticOptionsDlg(CWnd* pParent = NULL);	// standard constructor

	aguint_id	GetImageType();
	agint32		GetNumberOfCandidate();

// Dialog Data
	//{{AFX_DATA(CAGsemanticOptionsDlg)
	enum { IDD = IDD_SEMANTICS_OPTIONS };
	CComboBox		m_cmbImageType;
	CxTargetButton	m_btOK;
	CxTargetButton	m_btOKNUS;
	CxTargetButton	m_btCancel;
	UINT			m_NumberOfCandidate;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGsemanticOptionsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON							m_hIcon;
	CAGsemanticOptionsTreeItem*		m_pSelectedItem;
	CAGsemanticOptionsTree			m_otTree;
	CAGimageSemanticTree			m_SemanticTree;

	aguint_id						m_ImageType;

	void UpdateImageType();

	// Generated message map functions
	//{{AFX_MSG(CCOptionTreeDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);


	LRESULT WM_ApplyButton(WPARAM wParam, LPARAM lParam);
	void OnTreeDeleteItem(NMHDR *pNotifyStruct, LRESULT *plResult);
	void OnTreeItemChanged(NMHDR* pNotifyStruct, LRESULT* plResult);
	void OnTreeContextMenu(NMHDR *pNotifyStruct, LRESULT *plResult);

	afx_msg void	OnInsertOptionsTreeItem();
	afx_msg void	OnDeleteOptionsTreeItem();
	afx_msg void	OnSelchangeImageType();
	afx_msg void	OnOkNUS();

	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	friend class CAGmagicISDemoMainFrame;
};

#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGsemanticCheckedTreeDlg************************************/
#if AGMAGIC_SUPPORT_MFC

class CAGsemanticCheckedTreeDlg : public CDialog
{
// Construction
public:
	CAGsemanticCheckedTreeDlg(CWnd* pParent = NULL);   // standard constructor
	
	void SetSemanticTree(CAGimageSemanticTree* pNoFreeSemanticTree);

// Dialog Data
	//{{AFX_DATA(CAGsemanticCheckedTreeDlg)
	enum { IDD = IDD_SEMANTIC_CHECKED_TREE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGsemanticCheckedTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CAGsemanticCheckedTree		m_SemanticCheckedTree;
	CAGimageSemanticTree*		m_pNoFreeSemanticTree;

	// Generated message map functions
	//{{AFX_MSG(CAGsemanticCheckedTreeDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	//#if AGMAGIC_SUPPORT_MFC
/*********************************class CAGmagicISDemoMainFrame************************************/

#if AGMAGIC_SUPPORT_MFC
#define AGMAGICISDEMO_LEO_MSG_BOX_LIBPATH		_T("..\\lib\\ui\\LeoMsgBox.dll")

#include <afxmt.h>
//#import "../../../../../../lib/ui/LeoMsgBox.dll" no_namespace

class CAGmagicISDemoDoc;
class CAGmagicISDemoMainFrame : public CAGmmMainFrame
{
	DECLARE_DYNAMIC(CAGmagicISDemoMainFrame)

	CAGmagicISDemoDoc*	GetDocument(aguint_id DocID);
public:
	CAGmagicISDemoMainFrame();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoMainFrame)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT OnReceivedOutputNotice(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISDemoMainFrame();
	virtual void*	DBCnnAttach(agtchar szDBCnnStr[]);
	virtual void*	DBCnnDetach();//phai Release

	void	BeginProgress();
	void	EndProgress();
	void	SetAllDocBusy(agbool bBusy);

//Attributes
public:
	agbool								m_bSearchingBusy;
	agbool								m_bUpdatingSearchResults;
	CAGmagicISDemoDoc*					m_pSearchDoc;

	CMutex								m_Mutex;
	CEvent								m_Event;

	CAGmagicISDemoDoc*					m_pProgressDoc;
	aguint_id							m_ProgressTimerID;
	agint32								m_nProgress;

	agbool								m_bIsInsertDBIntel;//insert anh vao co so du lieu mot cach thong minh

	CAGmmTrainingSystemUIWinThread*		m_pAGmmTrainingSystem;
	CAGmmSearchingSystemUIWinThread*	m_pAGmmSearchingSystem;

public:  // control bar embedded members
	CToolBar							m_wndToolBar22;

	CAGmagicISDemoControlBar*			m_pISControlBar;
	CAGmagicISDemoServerDlg*			m_pServerDlg;
	CAGmagicISDemoOutputBar*			m_pOutputBar;
	CAGmagicISDemoSearchResultDlg*		m_pSearchResultDlg;

	//IMsgBoxPtr							m_pILeoMsgBox;
public:
	agtchar*							m_szServerNotice;
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISDemoMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg LRESULT OnReceivedSearchResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnListCtrlUpdateDocumentAlready(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRequireSendAccessFreqAgain(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	afx_msg void OnConfigServer();
	afx_msg void OnCreateDB();
	afx_msg void OnStartServer();
	afx_msg void OnStopServer();

	afx_msg void OnBrowse();
	afx_msg void OnSearch();
	afx_msg void OnFeedback();
	afx_msg void OnFeedbackAdvanced();
	afx_msg void OnSearchResultUserOpen();
	afx_msg void OnSearchResultUserOpenDialog();
	afx_msg void OnSearchResultUserProperties();

	afx_msg void OnMainframeShowServer();
	afx_msg void OnMainframeShowOutput();
	afx_msg void OnMainframeShowResult();

	afx_msg void OnUpdateConfigServer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateDB(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStartServer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStopServer(CCmdUI* pCmdUI);

	afx_msg void OnUpdateBrowse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeedback(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeedbackAdvanced(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchResultUserOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchResultUserOpenDialog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchResultUserProperties(CCmdUI* pCmdUI);

	afx_msg void OnUpdateMainframeShowServer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMainframeShowOutput(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMainframeShowResult(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	void AdjustChildWndLayout();
	void InitServer();
	void CleanupServer();
public:
};

#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoChildFrame************************************/
#if AGMAGIC_SUPPORT_MFC
class CAGmagicISDemoChildFrame : public CAGmagicIP_MDIChildFrame
{
	DECLARE_DYNCREATE(CAGmagicISDemoChildFrame)
public:
	CAGmagicISDemoChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoChildFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISDemoChildFrame();

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISDemoChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoDoc************************************/
#if AGMAGIC_SUPPORT_MFC
class CAGmagicISDemoDoc : public CAGmagicIPDoc
{
protected: // create from serialization only
	CAGmagicISDemoDoc();
	DECLARE_DYNCREATE(CAGmagicISDemoDoc)

// Attributes

// Operations
public:
	aguint_id								m_QueryImageID;
	aguint_id								m_QueryImageType;
	CAGimageSemanticTree*					m_pQuerySemanticTree;

	CAGobjPtrArray<CAGoutSimPtrArray>		m_SearchResults;
	CAGobjPtrArray<CAGinteractImagesMsg>	m_SearchResults2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoDoc)
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL DoSave(LPCTSTR pszPathName, BOOL bReplace =TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISDemoDoc();

	void SetQuerySemanticTree(CAGimageSemanticTree* pSemanticTree, agbool bIsCopy);

	afx_msg void OnDatabaseInsert();

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISDemoDoc)
	afx_msg void OnDatabaseUpdate();
	afx_msg void OnDatabaseDelete();
	afx_msg void OnDatabaseSelect();

	afx_msg void OnUpdateDatabaseInsert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabaseUpdate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabaseDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabaseSelect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoView************************************/

#if AGMAGIC_SUPPORT_MFC
class CAGmagicISDemoView : public CAGmagicIPView
{
protected: // create from serialization only
	CAGmagicISDemoView();
	DECLARE_DYNCREATE(CAGmagicISDemoView)

// Attributes
public:
	CAGmagicISDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoView)
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISDemoView();

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISDemoView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void OnHelpTestAGmagicIP();
};

#ifndef _DEBUG  // debug version in demoView.cpp
inline CAGmagicISDemoDoc* CAGmagicISDemoView::GetDocument()
   { return (CAGmagicISDemoDoc*)m_pDocument; }
#endif

#endif	//#if AGMAGIC_SUPPORT_MFC

/*********************************class CAGmagicISDemoApp************************************/

#if AGMAGIC_SUPPORT_MFC
class CAGmagicISDemoApp : public CAGmagicIPApp
{
public:
	CAGmagicISDemoApp();

	// Attributes

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Operations

// Implementation

	//{{AFX_MSG(CAGmagicISDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	//#if AGMAGIC_SUPPORT_MFC


#endif // !defined(AGMAGICISDEMOUI_H__202FE12C_E86C_4D6B_BE71_2CD33244D1AF__INCLUDED_)
