// MainDlg.h : header file
//

#if !defined(AFX_MAINDLG_H__6F25FADE_3D19_4371_A550_B74561E7B764__INCLUDED_)
#define AFX_MAINDLG_H__6F25FADE_3D19_4371_A550_B74561E7B764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PageNotAvailable.h"
#include "PageTabWindow.h"
#include "PageTabContainers.h"
#include "PageButtons.h"
#include "PagePopupMenus.h"
#include "PageStatusBar.h"
#include "PageToolbars.h"
#include "PageCalendar.h"

#include "IconListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CExtResizableDialog
{
	bool m_bDialogInitComplete;

	// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_PROFUIS_CONTROLS_DIALOG };
	CExtLabel	m_labelUILook;
	CExtButton	m_btnBack;
	CExtButton	m_btnNext;
	CExtComboBox	m_UILook;
	CExtButton	m_btnOk;
	//}}AFX_DATA
	CIconListBox m_wndList;
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	class CMyToolControlBar: public CExtToolControlBar 
	{     
	public:
		virtual CExtBarContentExpandButton * OnCreateBarRightBtn(){ 
			return NULL; 
		}
	}; // CMyToolControlBar
	
	CExtMenuControlBar m_wndMenuBar;
	CMyToolControlBar m_wndToolBar;

// Implementation
protected:
	HICON m_hIcon;

	CPageNotAvailable *m_pPageNotAvailable;
#if (!defined __EXT_MFC_NO_TAB_CTRL)
	CPageTabWindow *m_pPageTabWindows;
#endif // (!defined __EXT_MFC_NO_TAB_CTRL)
#if (!defined __EXT_MFC_NO_TAB_PAGECONTAINER_CTRL && !defined __EXT_MFC_NO_TAB_PAGECONTAINER_FLAT_CTRL )
	CPageTabContainers *m_pPageTabContainers;
#endif // #if (!defined __EXT_MFC_NO_TAB_PAGECONTAINER_CTRL && !defined __EXT_MFC_NO_TAB_PAGECONTAINER_FLAT_CTRL )
	CPageButtons *m_pPageButtons;
	CPagePopupMenus *m_pPagePopupMenus;
	CPageStatusBar *m_pPageStatusBar;
	CPageToolbars *m_pPageToolbars;
#if (!defined __EXT_MFC_NO_DATE_PICKER)
	CPageCalendar *m_pPageCalendar;
#endif // #if (!defined __EXT_MFC_NO_DATE_PICKER)	

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAppAbout();
	afx_msg void OnLook2003();
	afx_msg void OnUpdateLook2003(CCmdUI* pCmdUI);
	afx_msg void OnLook2k();
	afx_msg void OnUpdateLook2k(CCmdUI* pCmdUI);
	afx_msg void OnLookXp();
	afx_msg void OnUpdateLookXp(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelendokComboUiLook();
	afx_msg void OnSelchangeList();
	afx_msg void OnBack();
	afx_msg void OnNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__6F25FADE_3D19_4371_A550_B74561E7B764__INCLUDED_)
