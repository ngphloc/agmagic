// mainfrm.h : interface of the CMainFrame class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

class CMainFrame
	: public CMDIFrameWnd
#if (!defined __EXT_MFC_NO_CUSTOMIZE)
	, public CExtCustomizeSite
#endif // (!defined __EXT_MFC_NO_CUSTOMIZE)
{
	DECLARE_DYNAMIC(CMainFrame)
		
public:
#if (defined __EXT_MFC_NO_CUSTOMIZE)
	CExtBarColorButton * m_pBtnColorFill, * m_pBtnColorOutline;
#endif // (defined __EXT_MFC_NO_CUSTOMIZE)

	CMainFrame();

#if (defined _AFXDLL && !defined __STATPROFUIS_WITH_DLLMFC__)
	
	class CMyMdiWindowsListDlg : public CExtMdiWindowsListDlg
	{
	public:
		CMyMdiWindowsListDlg::CMyMdiWindowsListDlg(CMDIFrameWnd* pMDIFrameWnd, CWnd* pParent=NULL)
			: CExtMdiWindowsListDlg(pMDIFrameWnd, pParent)
		{
		}
	protected:
		virtual void OnUpdateButtons()
		{
			CExtMdiWindowsListDlg::OnUpdateButtons();
			
			CMainFrame *pFrame = static_cast<CMainFrame *>(m_pMDIFrameWnd);
			if ( !pFrame->m_wndMenuBar.IsDisplayMdiDocumentButtons() )
			{
				m_btnCascade.ShowWindow(SW_HIDE);
				m_btnTileVert.ShowWindow(SW_HIDE);
				m_btnTileHorz.ShowWindow(SW_HIDE);
				m_btnMinimize.ShowWindow(SW_HIDE);
			}
			else
			{
				m_btnCascade.ShowWindow(SW_SHOW);
				m_btnTileVert.ShowWindow(SW_SHOW);
				m_btnTileHorz.ShowWindow(SW_SHOW);
				m_btnMinimize.ShowWindow(SW_SHOW);
			}
		}
	}; // class CMyMdiWindowsListDlg : public CExtMdiWindowsListDlg

#endif // #if (defined _AFXDLL && !defined __STATPROFUIS_WITH_DLLMFC__)

// Attributes
public:

	// window placement persistence
	WINDOWPLACEMENT m_dataFrameWP;

// Operations
public:

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

#if (!defined __EXT_MFC_NO_CUSTOMIZE)
	CExtBarButton *  OnCreateToolbarButton(
		CExtToolControlBar * pBar,
		CExtCustomizeCmdTreeNode * pNodeI,
		CExtCustomizeCmdTreeNode * pNodeC
		);
#endif // (!defined __EXT_MFC_NO_CUSTOMIZE)

public:
	// control bar embedded members
	CExtMenuControlBar		m_wndMenuBar;
	CExtStatusControlBar	m_wndStatusBar;
	CExtToolControlBar		m_wndToolBarStandard;
	CExtToolControlBar		m_wndToolBarCustom;
	CExtToolControlBar		m_wndPalette;

#if (!defined __EXT_MFC_NO_TABMDI_CTRL)
	CExtTabMdiWnd			m_wndMdiTabs;
#endif // (!defined __EXT_MFC_NO_TABMDI_CTRL)

#if (!defined __EXT_MFC_NO_CUSTOMIZE)
	virtual HICON OnColorItemGenerateIcon(
		CExtBarColorButton * pTBB,
		CExtCustomizeCmdTreeNode * pNode,
		COLORREF clr
		);
	virtual bool OnColorItemValueGet(
		CExtBarColorButton * pTBB,
		CExtCustomizeCmdTreeNode * pNode,
		COLORREF & clr,
		bool bSelected
		);
	virtual bool OnColorItemValueSet(
		CExtBarColorButton * pTBB,
		CExtCustomizeCmdTreeNode * pNode,
		COLORREF & clr,
		bool bSelected
		);
#endif // (!defined __EXT_MFC_NO_CUSTOMIZE)

public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	virtual void ActivateFrame(int nCmdShow = -1);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL
	
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMditabsTop();
	afx_msg void OnUpdateMditabsTop(CCmdUI* pCmdUI);
	afx_msg void OnMditabsBottom();
	afx_msg void OnUpdateMditabsBottom(CCmdUI* pCmdUI);
	afx_msg void OnMditabsLeft();
	afx_msg void OnUpdateMditabsLeft(CCmdUI* pCmdUI);
	afx_msg void OnMditabsRight();
	afx_msg void OnUpdateMditabsRight(CCmdUI* pCmdUI);
	afx_msg void OnMditabsShowClose();
	afx_msg void OnUpdateMditabsShowClose(CCmdUI* pCmdUI);
	afx_msg void OnMditabsShowCtxHelp();
	afx_msg void OnUpdateMditabsShowCtxHelp(CCmdUI* pCmdUI);
	afx_msg void OnUistyle2000();
	afx_msg void OnUpdateUistyle2000(CCmdUI* pCmdUI);
	afx_msg void OnUistyleXp();
	afx_msg void OnUpdateUistyleXp(CCmdUI* pCmdUI);
	afx_msg void OnViewLikeOffice2003();
	afx_msg void OnUpdateViewLikeOffice2003(CCmdUI* pCmdUI);
	afx_msg void OnContextHelp();
	afx_msg void OnUpdateContextHelp(CCmdUI* pCmdUI);
	afx_msg void OnCustomize();
	afx_msg void OnUpdateCustomize(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnExtMenuPrepare(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawPopupMenuItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorChangedFinally(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorSelectCustom(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
