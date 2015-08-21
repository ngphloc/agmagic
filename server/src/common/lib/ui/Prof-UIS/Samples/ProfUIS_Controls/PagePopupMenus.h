#if !defined(AFX_PAGEPOPUPMENUS_H__37F8A029_132C_4EEF_8BA8_FC82B64EFCEC__INCLUDED_)
#define AFX_PAGEPOPUPMENUS_H__37F8A029_132C_4EEF_8BA8_FC82B64EFCEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PagePopupMenus.h : header file
//
#include "PageBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPagePopupMenus dialog

class CPagePopupMenus : public CPageBase
{
// Construction
public:
	CPagePopupMenus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPagePopupMenus)
	enum { IDD = IDD_PAGE_POPUP_MENUS };
	CExtLabel		m_Static1;
	CExtCheckBox	m_chkMenuWithShadows;
	CExtCheckBox	m_chkMenuAnimation;
	CExtGroupBox	m_StaticMenuAnimation;
	CExtComboBox	m_MenuAnimation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagePopupMenus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPagePopupMenus)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokMenuAnimation();
	afx_msg void OnCheckMenuAnimation();
	afx_msg void OnCheckMenuWithShadows();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnColorSelectCustom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorChangedFinally(WPARAM wParam, LPARAM lParam);
	LRESULT OnMsgSelectionNotification( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnDrawPopupMenuItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawPopupLeftArea(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPOPUPMENUS_H__37F8A029_132C_4EEF_8BA8_FC82B64EFCEC__INCLUDED_)
