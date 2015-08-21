// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "BCMenu.h"

#if !defined(AFX_MAINFRM_H__3BAD4108_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_)
#define AFX_MAINFRM_H__3BAD4108_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
public:
	BOOL disable_flag,zoomflag,menu2flag,testflag,toolsflag;
	HMENU NewMenu();
	HMENU NewMyMenu();
	HMENU NewDefaultMenu();

	BCMenu m_menu,m_mymenu,m_default,m_test;
protected:
    BOOL BuildToolsMenu(HMENU hMenu);

	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnZoom();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnDefault();
	afx_msg void OnUpdateDefault(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnHomepage();
	afx_msg void OnEnable();
	afx_msg void OnUpdateEnable(CCmdUI* pCmdUI);
	afx_msg void OnDisable();
	afx_msg void OnUpdateDisable(CCmdUI* pCmdUI);
	afx_msg void OnAddMenuOptions();
	afx_msg void OnUpdateAddMenuOptions(CCmdUI* pCmdUI);
	afx_msg void OnRemoveZoom();
	afx_msg void OnMenu2();
	afx_msg void OnUpdateMenu2(CCmdUI* pCmdUI);
	afx_msg void OnZooms();
	afx_msg void OnNew();
	afx_msg void OnTile();
	afx_msg void OnJunk();
	afx_msg void OnNet();
	afx_msg void OnNewDocTemplate();
	afx_msg void OnColoredsquare();
	afx_msg void OnHatchedsquare();
	afx_msg void OnSmallcoloredsquare();
	afx_msg void OnAddtestmenu();
	afx_msg void OnUpdateAddtestmenu(CCmdUI* pCmdUI);
	afx_msg void OnAddtoolsmenu();
	afx_msg void OnUpdateAddtoolsmenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void On3dbitmaps();
	afx_msg void OnUpdate3dbitmaps(CCmdUI* pCmdUI);
	afx_msg void OnPickdisabled();
	afx_msg void OnUpdatePickdisabled(CCmdUI* pCmdUI);
	afx_msg void OnFindpopup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3BAD4108_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_)
