// DlgToolStatusBarDlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_DLGTOOLSTATUSBARDLG_H__6E24C647_53B8_11D6_9693_B4C16A843021__INCLUDED_)
#define AFX_DLGTOOLSTATUSBARDLG_H__6E24C647_53B8_11D6_9693_B4C16A843021__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NUMIMAGES       3 
#define IMAGEWIDTH      16 
#define IMAGEHEIGHT     16 
#define BUTTONWIDTH     16
#define BUTTONHEIGHT    16 

#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CDlgToolStatusBarDlg dialog

class CDlgToolStatusBarDlg : public CDialog
{
// Construction
public:
	void DestroyToolBars();
	HWND CreateToolBar(HWND hWnd, int numButtons, BOOL bStandard);

	void CreateStatusBar();
	void CreateFlatToolBar();
	BOOL SetupImages(CImageList* mImageList);
	CDlgToolStatusBarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgToolStatusBarDlg)
	enum { IDD = IDD_DLGTOOLSTATUSBAR_DIALOG };
	HWND  hWndStatusbar;  
	HWND    hWndToolbar;  
	HWND m_CompIcon;
	CStatusBarCtrl m_StatusBar;
	CToolBarCtrl m_ToolBar;
	CImageList m_pImageList;
	CWebBrowser2	m_Browser;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgToolStatusBarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgToolStatusBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();
	afx_msg void OnBold();
	afx_msg void OnDrawing();
	afx_msg void OnStrikeOut();
	afx_msg void OnDestroy();
	afx_msg void OnAboutbox();
	afx_msg void OnToolbar(UINT nID);
	afx_msg void OnViewSortToolbar(UINT nID);
	afx_msg void OnSelectToolbar(UINT nID);
	afx_msg void OnUpdateToolbarStyle(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTOOLSTATUSBARDLG_H__6E24C647_53B8_11D6_9693_B4C16A843021__INCLUDED_)
