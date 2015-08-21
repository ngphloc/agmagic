// AGmagicISClientUI.h: interface for the AGmagicISClientUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AGMAGICISCLIENTUI2_H__7E14F6E1_C09C_11D2_84B2_00C0DFF84685__INCLUDED_)
#define AGMAGICISCLIENTUI2_H__7E14F6E1_C09C_11D2_84B2_00C0DFF84685__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "../../../../../common/include/AGmagicDefs.h"

#if AGMAGIC_SUPPORT_MFC_UI
#if (!defined __PROF_UIS_H)
	#include "../../../../../common/lib/Prof-UIS/Include/Prof-UIS.h"
#endif // (!defined __PROF_UIS_H)
#endif	//#if AGMAGIC_SUPPORT_MFC_UI

#include "AGmagicISClientUI2RC.h"

/*******************class CResizableSampleDlg***************************/

#if AGMAGIC_SUPPORT_MFC_UI

class CResizableSampleDlg : public CExtResizableDialog
{
// Construction
public:
	CResizableSampleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResizableSampleDlg)
	enum { IDD = IDD_RESIZABLE_SAMPLE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResizableSampleDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC_UI

/*******************class CAGmagicISClientMainFrame***************************/

#if AGMAGIC_SUPPORT_MFC_UI

#if !defined(__EXT_TEMPL_H)
	#include <ExtTempl.h>
#endif
class CResizableSampleDlg;
class CAGmagicISClientMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CAGmagicISClientMainFrame();
	DECLARE_DYNCREATE(CAGmagicISClientMainFrame)

// Attributes
protected:
	WINDOWPLACEMENT m_dataFrameWP;

public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISClientMainFrame)
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void ActivateFrame(int nCmdShow = -1);
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISClientMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CExtMenuControlBar    m_wndMenuBar;
	CExtStatusControlBar  m_wndStatusBar;
	CExtToolControlBar    m_wndToolBar;
	
	CExtControlBar					m_wndSearchControlBar;
	CExtWRB< CExtResizableDialog >	m_wndSearchControlDlg;
	CExtWRB< CExtEdit >				m_wndEditInDockedDlg;

	CExtControlBar						m_ResizableSampleBar;
	CExtWRB< CResizableSampleDlg >		m_ResizableSampleDlg;

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISClientMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC_UI

/*******************class CAGmagicISClientDoc***************************/

#if AGMAGIC_SUPPORT_MFC_UI

class CAGmagicISClientDoc : public CDocument
{
protected: // create from serialization only
	CAGmagicISClientDoc();
	DECLARE_DYNCREATE(CAGmagicISClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISClientDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC_UI

/*******************class CAGmagicISClientView***************************/

#if AGMAGIC_SUPPORT_MFC_UI

class CAGmagicISClientView : public CView
{
protected: // create from serialization only
	CAGmagicISClientView();
	DECLARE_DYNCREATE(CAGmagicISClientView)

// Attributes
public:
	CAGmagicISClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISClientView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicISClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicISClientView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SDIDOCVIEWView.cpp
inline CAGmagicISClientDoc* CAGmagicISClientView::GetDocument()
   { return (CAGmagicISClientDoc*)m_pDocument; }
#endif

#endif	#if AGMAGIC_SUPPORT_MFC_UI

/*******************class CAGmagicISClientApp***************************/

#if AGMAGIC_SUPPORT_MFC_UI
#include "resource.h"       // main symbols

class CAGmagicISClientApp : public CWinApp
{
public:
	CAGmagicISClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//
	// Prof-UIS advanced options
    //
	void SetupUiAdvancedOptions();

	//{{AFX_MSG(CAGmagicISClientApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC_UI


#endif // !defined(AGMAGICISCLIENTUI_H__7E14F6E1_C09C_11D2_84B2_00C0DFF84685__INCLUDED_)
