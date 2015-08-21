#if !defined(AGIMAGEUI_H__CD3F8461_1647_4D35_BF59_B0D4B79CDB84__INCLUDED_)
#define AGIMAGEUI_H__CD3F8461_1647_4D35_BF59_B0D4B79CDB84__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "../../ip/main/AGimageDefs.h"

#if AGMAGIC_SUPPORT_MFC

/**************************CAGimageDlg dialog************************************************/

#include "../../ip/main/AGimage.h"
/*
class AGMAGIC_DECL CAGimageDlg : public CDialog
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageDlg : public CDialog
{
//
protected:
	agbool		m_bDeleteAGimage;
	CAGimage*	m_pAGimage;

	CAGimage*	SelectAGimage(CAGimage* pAGimage, agbool bDeleteAGimage=agfalse, agbool bCopyAGimage=agfalse);

// Construction
public:
	CAGimageDlg(aguint32 nIDTemplate, CAGimage* pAGimage, const agtchar* szTitle=NULL, agbool bDeleteAGimage=agfalse, agbool bCopyAGimage=agfalse, CWnd* pParent=NULL);

	static CAGimageDlg* ShowAGimageDlg(aguint32 nIDTemplate, CAGimage* pAGimage, const agtchar* szTitle=NULL);
// Dialog Data
	//{{AFX_DATA(CAGimageDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGimageDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/**************************CAGimageModalDlg dialog************************************************/

#include "../../ip/main/AGimage.h"
/*
class AGMAGIC_DECL CAGimageModalDlg : public CDialog
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageModalDlg : public CDialog
{
protected:
	agbool		m_bDeleteAGimage;
	CAGimage*	m_pAGimage;
	CBrush		m_bkBrush;

// Construction
public:
	CAGimageModalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, const agtchar* szTitle=NULL, agbool bDeleteAGimage=agfalse, agbool bCopyAGimage=agfalse, CWnd* pParent=NULL);
	CAGimage*		SelectAGimage(CAGimage* pAGimage, agbool bDeleteAGimage=agfalse, agbool bCopyAGimage=agfalse);

	static agint32 ShowAGimageDlg(aguint32 nIDTemplate, CAGimage* pAGimage, const agtchar* szTitle=NULL);
// Dialog Data
	//{{AFX_DATA(CAGimageModalDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageModalDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGimageModalDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/**************************CAGimageADlg dialog************************************************/
#include "../../ip/main/AGimage.h"

#define		AGMAGICIP_MFC_UI_DEFAULT_NUMCOLS	5
#define		AGMAGICIP_MFC_UI_DEFAULT_HINGEW		5
#define		AGMAGICIP_MFC_UI_DEFAULT_HINGEH		5

/*
class AGMAGIC_DECL CAGimageADlg : public CDialog
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageADlg : public CDialog
{
//
protected:
	agbool		m_bDeleteAGimageA;
	aguint32		m_nCols;
	CAGptrArray*	m_pAGimageA;
	CPoint		m_pos;
// Construction
public:
	CAGimageADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageA, aguint32 nCols=AGMAGICIP_MFC_UI_DEFAULT_NUMCOLS, agbool bDeleteAGimageA=agfalse, agbool bCopyAGimageA=agfalse, CWnd* pParent=NULL);

	static CAGimageADlg*	ShowAGimageADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageA, aguint32 nCols=AGMAGICIP_MFC_UI_DEFAULT_NUMCOLS);
// Dialog Data
	//{{AFX_DATA(CAGimageADlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageADlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGimageADlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/**************************CAGimageAModalDlg dialog************************************************/

#include "../../ip/main/AGimage.h"
/*
class AGMAGIC_DECL CAGimageAModalDlg : public CDialog
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageAModalDlg : public CDialog
{
//
protected:
	agbool		m_bDeleteAGimageA;
	aguint32	m_nCols;
	CAGptrArray*	m_pAGimageA;
	CPoint		m_pos;

	CBrush		m_bkBrush;
// Construction
public:
	CAGimageAModalDlg(aguint32 nIDTemplate, CAGptrArray* pAGimageA, aguint32 nCols=AGMAGICIP_MFC_UI_DEFAULT_NUMCOLS, agbool bDeleteAGimageA=agfalse, agbool bCopyAGimageA=agfalse, CWnd* pParent=NULL);
	static agint32 ShowAGimageADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageA, aguint32 nCols=AGMAGICIP_MFC_UI_DEFAULT_NUMCOLS);

// Dialog Data
	//{{AFX_DATA(CAGimageAModalDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageAModalDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGimageAModalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/**************************CAGimageAAbuDlg dialog************************************************/

#include "../../ip/main/AGimage.h"

/*
class AGMAGIC_DECL CAGimageAAbuDlg : public CDialog
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageAAbuDlg : public CDialog
{
//
protected:
	agbool		m_bDeleteAGimageAA;
	CAGptrArray*	m_pAGimageAA;
	CPoint		m_pos;
// Construction
public:
	CAGimageAAbuDlg(aguint32 nIDTemplate, CAGptrArray* pAGimageAA, agbool m_bDeleteAGimageAA=agfalse, agbool bCopyAGimageAA=agfalse, CWnd* pParent=NULL);
	static CAGimageAAbuDlg* ShowAGimageAADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageAA);

// Dialog Data
	//{{AFX_DATA(CAGimageAAbuDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageAAbuDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGimageAAbuDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/**************************CAGimageAAbuModalDlg dialog************************************************/

#include "../../ip/main/AGimage.h"

/*
class AGMAGIC_DECL CAGimageAAbuModalDlg : public CDialog
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageAAbuModalDlg : public CDialog
{
//
	agbool		m_bDeleteAGimageAA;
	CAGptrArray*	m_pAGimageAA;
	CPoint		m_pos;
// Construction
public:
	CAGimageAAbuModalDlg(aguint32 nIDTemplate, CAGptrArray* pAGimageAA, agbool bDeleteAGimageAA=agfalse, agbool bCopyAGimageAA=agfalse, CWnd* pParent=NULL);
	static agint32 ShowAGimageAADlg(aguint32 nIDTemplate, CAGptrArray* pAGimageAA);

// Dialog Data
	//{{AFX_DATA(CAGimageAAbuModalDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageAAbuModalDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGimageAAbuModalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/***************************class CAGimageFrame*********************************/

/*
class AGMAGIC_DECL CAGimageFrame : public CFrameWnd
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CAGimageFrame();
	DECLARE_DYNCREATE(CAGimageFrame)

// Attributes
public:
	static CFrameWnd*	CreateFrameWnd(CDocTemplate* pDocTemplate, agtchar* szTitle=NULL);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGimageFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CAGimageFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/***************************class CAGimageSplitFrame*********************************/

/*
class AGMAGIC_DECL CAGimageSplitFrame : public CFrameWnd
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageSplitFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CAGimageSplitFrame)
protected:
	CAGimageSplitFrame();           // protected constructor used by dynamic creation

// Attributes
protected:
	CSplitterWnd	m_wndSplitter;
public:
	CSplitterWnd*	GetSplitWnd(){return &m_wndSplitter;};	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageSplitFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAGimageSplitFrame();

	// Generated message map functions
	//{{AFX_MSG(CAGimageSplitFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/***************************class CAGimageMDIFrame*********************************/

/*
class AGMAGIC_DECL CAGimageMDIFrame : public CMDIFrameWnd
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageMDIFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CAGimageMDIFrame)
public:
	CAGimageMDIFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageMDIFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGimageMDIFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CAGimageMDIFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/***************************class CAGimageMDIChildFrame*********************************/

/*
class AGMAGIC_DECL CAGimageMDIChildFrame : public CMDIChildWnd
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageMDIChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CAGimageMDIChildFrame)
public:
	CAGimageMDIChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageMDIChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGimageMDIChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CAGimageMDIChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/***************************class CAGimageSplitMDIChildFrame*******************************/

/*
class AGMAGIC_DECL CAGimageSplitMDIChildFrame : public CMDIChildWnd
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageSplitMDIChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CAGimageSplitMDIChildFrame)
protected:
	CAGimageSplitMDIChildFrame();           // protected constructor used by dynamic creation

// Attributes
protected:
	CSplitterWnd	m_wndSplitter;
public:
	CSplitterWnd*	GetSplitWnd(){return &m_wndSplitter;};	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageSplitMDIChildFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAGimageSplitMDIChildFrame();

	// Generated message map functions
	//{{AFX_MSG(CAGimageSplitMDIChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/***************************class CAGimageDoc*******************************/

#include "../../ip/main/AGimage.h"
/*
class AGMAGIC_DECL CAGimageDoc : public CDocument
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageDoc : public CDocument
{
protected:
	CAGimageDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAGimageDoc)
	CAGimage*		m_pAGimage;

// Attributes
public:

// Operations
public:
	virtual CAGimage*	CreateAGimage()					{return new CAGimage();};
	CAGimage*			GetAGimage()					{ return (CAGimage*)m_pAGimage;}
	void				SetAGimage(CAGimage* pAGimage)	{ delete m_pAGimage ; m_pAGimage=(CAGimage*)pAGimage;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGimageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGimageDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/***************************class CAGimageView*******************************/

#include "../../ip/main/AGimage.h"

#if defined(IDC_GRAB_CUR) && defined(IDC_FLAT_CUR)
#define INIT_GRAB_FLAT_CUR \
{ \
	m_hGrabCur=AfxGetApp()->LoadCursor(IDC_GRAB_CUR); \
	m_hFlatCur=AfxGetApp()->LoadCursor(IDC_FLAT_CUR); \
}
#else
#define INIT_GRAB_FLAT_CUR \
{ \
	m_hGrabCur=NULL; \
	m_hFlatCur=NULL; \
}
#endif

/*
class AGMAGIC_DECL CAGimageView : public CScrollView
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageView : public CScrollView
{
protected:
	CAGimage*	m_pAGimage;
	agbool		m_bDeleteAGimage;
	CSize		m_docSize;
	CSize		m_pageSize;
	CSize		m_lineSize;

	HCURSOR		m_hGrabCur;
	HCURSOR		m_hFlatCur;

	agbool	m_bMouseDown;
	CPoint	m_ptCursorCurPos;
	CPoint	m_ptCursorOldPos;
	agbool	m_bScroll;

	CPoint	m_pos;

	void		UpdateScrollSize();
	CAGimage*	SelectAGimageProtect(CAGimage* pAGimage, agbool bDeleteAGimage=agfalse, agbool bCopyAGimage=agfalse);

public:
	CAGimage*	SelectAGimage(CAGimage* pAGimage, agbool bDeleteAGimage=agfalse, agbool bCopyAGimage=agfalse);
	HCURSOR		SetGrabCur(HCURSOR hGrabCur);
	HCURSOR		SetFlatCur(HCURSOR hFlatCur);
	void		SwitchScroll();

protected:
	CAGimageView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAGimageView)

// Attributes
public:
	CAGimageDoc*	GetDocument(); // non-debug version is inline

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAGimageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAGimageView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*******************************class CAGimageAView*******************************/

#include "../../ip/main/AGimage.h"

/*
class AGMAGIC_DECL CAGimageAView : public CScrollView
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageAView : public CScrollView
{
protected:
	CAGimageAView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAGimageAView)

	CAGptrArray*	m_pAGimageA;
	agbool		m_bDeleteAGimageA;
	CPoint		m_pos;
public:
	aguint32		m_nCols;

// Attributes
public:
	CAGptrArray*	SelectAGimageA(CAGptrArray* pAGimageA, aguint32 nCols=AGMAGICIP_MFC_UI_DEFAULT_NUMCOLS, agbool bDeleteImageExA=agfalse, agbool bCopyAGimageA=agfalse);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageAView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAGimageAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAGimageAView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*******************************class CAGimageAAbuView*******************************/

#include "../../ip/main/AGimage.h"

/*
class AGMAGIC_DECL CAGimageAAbuView : public CScrollView
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageAAbuView : public CScrollView
{
protected:
	CAGimageAAbuView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAGimageAAbuView)
	
	CAGptrArray*	m_pAGimageAA;
	agbool		m_bDeleteAGimageAA;
	CPoint		m_pos;

// Attributes
public:
	CAGptrArray*	SelectAGimageAA(CAGptrArray* pAGimageAA, agbool bDeleteAGimageAA=agfalse, agbool bCopyAGimageAA=agfalse);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageAAbuView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAGimageAAbuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAGimageAAbuView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/*******************************class CAGimageListCtrl*******************************/

#include "../../ip/main/AGimage.h"

#define AGMAGICIP_LVS_DEFAULTTYPE   (WS_VISIBLE|WS_CHILD|WS_BORDER|LVS_EDITLABELS)

#define INIT_AGMAGICIP_LISTINFO(ListCtrl) \
{ \
	ListCtrl.pAGimageA=NULL; \
	ListCtrl.paTextItem=NULL; \
	ListCtrl.pParentWnd=NULL; \
	ListCtrl.nID=-1; \
	ListCtrl.uType=LVS_ICON; \
	ListCtrl.prc=NULL; \
	ListCtrl.bCopyAGimageA=agtrue; \
	ListCtrl.nIDTemplate=-1; \
}

#define INIT_AGMAGICIP_LISTINFOPTR(pListCtrl) \
{ \
	pListCtrl->pAGimageA=NULL; \
	pListCtrl->paTextItem=NULL; \
	pListCtrl->pParentWnd=NULL; \
	pListCtrl->nID=-1; \
	pListCtrl->uType=LVS_ICON; \
	pListCtrl->prc=NULL; \
	pListCtrl->bCopyAGimageA=agtrue; \
	pListCtrl->nIDTemplate=-1; \
}

typedef struct tagAGMAGICIP_LISTINFO
{
	CAGptrArray*	pAGimageA; 
	CString			sColumn;
	CStringArray*	paTextItem;
	CWnd*			pParentWnd;
	aguint32		nID;
	aguint32		uType;
	RECT*			prc;
	agbool			bCopyAGimageA;
	aguint32		nIDTemplate;//template cua dialog hien thi tung anh
} AGMAGICIP_LISTINFO;

/*
class AGMAGIC_DECL CAGimageListCtrl : public CListCtrl
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageListCtrl : public CListCtrl
{
// Construction
public:
	aguint32	m_nIDTemplate;
	agbool		m_bShowAll;

	CAGimageListCtrl();
	void	DeleteAllAGimageData();
	void	ShowAllAGimageData();

	static	CAGimageListCtrl*	CreateAGimageListCtrl(AGMAGICIP_LISTINFO* pListInfo, CSize* psizeListLarge, CSize* psizeListSmall, COLORREF* pcrMask=NULL);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageListCtrl)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGimageListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGimageListCtrl)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/*******************************class CAGimageListCtrlEx*******************************/

#define	AGIMAGE_LISTCTRLEX_ITEM_WIDTH			100
#define	AGIMAGE_LISTCTRLEX_ITEM_HEIGHT			90
#define AGIMAGE_LISTCTRLEX_DEFAULTTYPE			(WS_VISIBLE|WS_CHILD|LVS_ICON)

class	CAGlvItemArray;
class	CAGimageListCtrlEx;
class	CAGmagicISDemoSearchResultDlg;
class	CAGmagicISDemoProp;
class	CAGmagicISDemoMainFrame;
UINT	ReceiveNewImages_ThreadProc(LPVOID param);

class AGMAGIC_DECL CAGimageLVItemExt
{
protected:

	CAGimage*			m_pAGimage;
	CAGmagicElement*	m_pAGmagicElement;
	aguint_id			m_ID;
	agint32				m_idx;//thu tu cua muc trong cac lvitem cua ListCtrl

	void Cleanup()
	{
		if(m_pAGimage)			delete m_pAGimage;			m_pAGimage=NULL;
		if(m_pAGmagicElement)	delete m_pAGmagicElement;	m_pAGmagicElement=NULL;
		m_ID=0;
		m_idx=-1;
	}

public:
	CAGimageLVItemExt()
	{
		m_pAGimage=NULL;
		m_pAGmagicElement=NULL;
		m_ID=0;
		m_idx=-1;
	}
	virtual ~CAGimageLVItemExt()
	{
		Cleanup();
	}
	friend class CAGlvItemArray;
	friend class CAGimageListCtrlEx;
	friend UINT ReceiveNewImages_ThreadProc(LPVOID param);
	friend class CAGmagicISDemoSearchResultDlg;
	friend class CAGmagicISDemoProp;
	friend class CAGmagicISDemoMainFrame;
};

class AGMAGIC_DECL CAGlvItemArray : public CAGobjPtrArray<CAGimageLVItemExt>
{
protected:
	agbool		m_bIsDeleteImages;

public:
	CAGlvItemArray();
	virtual ~CAGlvItemArray();

	virtual void RemoveAll();
	friend class CAGimageListCtrlEx;
};

#include <afxmt.h>//su dung critical section, mutex
class BCMenu;
class AGMAGIC_DECL CAGimageListCtrlEx : public CListCtrl
{
// Construction
public:
	CAGimageListCtrlEx();

// Attributes
public:
	CMutex				m_Mutex;
	agbool				m_bIsCreateAGimage;

	BCMenu*				m_pOutsideContextMenu;//ContextMenu cho ListCtrl duoc truyen tu ben ngoai

	CImageList			m_ImageList;
	CAGlvItemArray		m_AGlvItems;

	virtual CAGimage*	CreateAGimage()		{return new CAGimage();};

// Operations
public:
	void	GetAllSelectedIdxs(CAGint32Array* idxs);
	void	GetAllSelectedIDs(CAGidArray* IDs);
	void	SetOutsideContextMenu(aguint_id OutsideContextMenuID, aguint_id ToolbarIDforOutsideContextMenu=0);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageListCtrlEx)
	protected:
	virtual void PostNcDestroy();
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGimageListCtrlEx();
	BOOL DeleteAllItems();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGimageListCtrlEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg LRESULT OnReceivedNewImages(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend UINT ReceiveNewImages_ThreadProc(LPVOID param);
};

/*******************************class CAGimageListCtrlExBar*******************************/
#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutilui/main/AGmagicUI.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

#ifndef baseAGimageListCtrlExBar
#define baseAGimageListCtrlExBar	CSizingControlBarCF
#endif

#define		IDC_LISCTRLEX		311
class AGMAGIC_DECL CAGimageListCtrlExBar : public baseAGimageListCtrlExBar
{
// Construction
public:
	CAGimageListCtrlExBar();
	CAGimageListCtrlExBar(CFrameWnd* pFrameWnd, UINT ID);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageListCtrlExBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGimageListCtrlExBar();

protected:
	CAGimageListCtrlEx	m_ListCtrlEx;

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGimageListCtrlExBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*******************************class CAGimageListView*******************************/
#include "../../ip/main/AGimage.h"
#include <afxcview.h>

/*
class AGMAGIC_DECL CAGimageListView : public CListView
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageListView : public CListView
{
protected:
	CAGimageListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAGimageListView)

	AGMAGICIP_LISTINFO	m_ListInfo;
	agbool				m_bShowAll;

// Attributes
public:
	AGMAGICIP_LISTINFO SelectListInfo(AGMAGICIP_LISTINFO* pListInfo, CSize* psizeListLarge, CSize* psizeListSmall, COLORREF* pcrMask=NULL);
	void DeleteAllAGimageData();
	void ShowAllAGimageData();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimageListView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAGimageListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGimageListView)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*******************************class CAGimagePalDlg*******************************/

#include "../../ip/main/AGimage.h"

#define	AGMAGICIP_MFC_UI_PAL_SQUARE_X			16
#define	AGMAGICIP_MFC_UI_PAL_SQUARE_Y			16
#define	AGMAGICIP_MFC_UI_PAL_NUM_COLS			16
#define	AGMAGICIP_MFC_UI_PAL_SQUARE_HINGEX	4
#define	AGMAGICIP_MFC_UI_PAL_SQUARE_HINGEY	4

/*
class AGMAGIC_DECL CAGimagePalDlg : public CDialog
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimagePalDlg : public CDialog
{
protected:
	agbool		m_bDeleteAGimage;
	CAGimage*	m_pAGimage;
	agbool		m_bRainbow;			//co ve bang mau thanh vet dai hay khong
	
	CSize	m_squareXY;
	CSize	m_sizeHinge;
	aguint32	m_nCols;

// Construction
public:
	CAGimagePalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, agbool bDeleteAGimage=agfalse, CWnd* pParent=NULL);
	static CAGimagePalDlg*	ShowPalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, agbool bDeleteAGimage=agtrue);

// Dialog Data
	//{{AFX_DATA(CAGimagePalDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimagePalDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGimagePalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*******************************class CAGimagePalModalDlg*******************************/

#include "../../ip/main/AGimage.h"

/*
class AGMAGIC_DECL CAGimagePalModalDlg : public CDialog
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimagePalModalDlg : public CDialog
{
protected:
	agbool		m_bDeleteAGimage;
	CAGimage*	m_pAGimage;
	agbool		m_bRainbow;			//co ve bang mau thanh vet dai hay khong
	
	CSize	m_squareXY;
	CSize	m_sizeHinge;
	aguint32	m_nCols;

// Construction
public:
	CAGimagePalModalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, agbool bDeleteAGimage=agfalse, CWnd* pParent=NULL);

	static agint32 ShowPalDlg(aguint32 nIDTemplate, CAGimage* pAGimage, agbool bDeleteAGimage=agtrue);

// Dialog Data
	//{{AFX_DATA(CAGimagePalModalDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGimagePalModalDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAGimagePalModalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/***********************class CAGsemanticOptionsTree****************************/
#include "../../ip/main/AGsemantic.h"
class AGMAGIC_DECL CAGsemanticOptionsTreeItem : public COptionTreeItemEdit, public CAGmagicDBOrg
{
public:
	CAGimageSemantic* m_pSemantic;

	CAGsemanticOptionsTreeItem();
	virtual ~CAGsemanticOptionsTreeItem();

	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO
	virtual void*	DBCnnDetach();//khong Release

	void	Import(CAGimageSemantic* pSemantic);
	void	Export(CAGimageSemantic* pSemantic);
};

class AGMAGIC_DECL CAGsemanticOptionsTree : public COptionTree, public CAGmagicDBOrg
{
protected:
	void InsertFromNode(CAGimageSemanticNode* pNode, CAGsemanticOptionsTreeItem* pParentItem);
	void InsertToNode(CAGsemanticOptionsTreeItem* pItem, CAGimageSemanticNode*& pParentNode);

public:
	CAGsemanticOptionsTree();
	virtual ~CAGsemanticOptionsTree();

	void Import(CAGimageSemanticTree* pImageTree);
	void Export(CAGimageSemanticTree* pImageTree);

	CAGsemanticOptionsTreeItem* InsertItemEx(agtchar* Name, agtchar* Descs, CAGsemanticOptionsTreeItem* pParentItem, agbool bIsDBInsert=agtrue);

	friend class CAGimageSemanticTree;
};

/***********************class CAGsemanticCheckedTree****************************/

class AGMAGIC_DECL CAGsemanticCheckedTree : public CAGcheckedTree
{
// Construction
public:
	CAGsemanticCheckedTree();
	void Import(CAGimageSemanticTree* pImageTree);

	CAGimageSemanticNode* GetSemanticNode(HTREEITEM hItem);
	void UpdateSemanticWeight();

// Attributes
public:

protected:
	void InsertFromNode(CAGimageSemanticNode* pNode, HTREEITEM hParentItem);//pParentItem=NULL: Root item ;
	void UpdateSemanticWeight(HTREEITEM hItem, agreal64 level);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGsemanticCheckedTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGsemanticCheckedTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAGsemanticCheckedTree)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif	//#if AGMAGIC_SUPPORT_MFC

/*******************************class CAGimageUIUtil*******************************/
class CAGimageSeg;
class AGMAGIC_DECL CAGimageUIUtil
{
public:
	static void Show(CAGimageObjPtrbuMatrix* me, agbool bIsModal=agtrue);
	static void Show(CAGimageObjPtrtdMatrix* me, agbool bIsModal=agtrue);
	static void Show(CAGimageObjPtrVec* me, agbool bIsModal=agtrue);
	static void Show(CAGimageSeg* me, agbool bIsModal=agtrue);
	static void Show(CAGimageSegs* me, agbool bIsModal=agtrue);
};


#endif // !defined(AGIMAGEUI_H__CD3F8461_1647_4D35_BF59_B0D4B79CDB84__INCLUDED_)
