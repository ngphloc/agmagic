// CxSkinButtonDemoDlg.h : header file
//

#if !defined(AFX_CXSKINBUTTONDEMODLG_H__87819726_1CAB_11D5_B6BF_00E07D8144D0__INCLUDED_)
#define AFX_CXSKINBUTTONDEMODLG_H__87819726_1CAB_11D5_B6BF_00E07D8144D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xSkinButton.h"
#include "xStaticText.h"

/////////////////////////////////////////////////////////////////////////////
// CCxSkinButtonDemoDlg dialog

class CCxSkinButtonDemoDlg : public CDialog
{
// Construction
public:
	CCxSkinButtonDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCxSkinButtonDemoDlg)
	enum { IDD = IDD_CXSKINBUTTONDEMO_DIALOG };
	CxSkinButton	m_check3;
	CxSkinButton	m_check2;
	CxSkinButton	m_check1;
	CxSkinButton	m_radio3;
	CxSkinButton	m_radio2;
	CxSkinButton	m_radio1;
	CxSkinButton	m_btn5;
	CxStaticText	m_stx1;
	CxSkinButton	m_btn4;
	CxSkinButton	m_btn2;
	CxSkinButton	m_btn1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCxSkinButtonDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCxSkinButtonDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton7();
	afx_msg void OnButton5();
	afx_msg void OnButton4();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXSKINBUTTONDEMODLG_H__87819726_1CAB_11D5_B6BF_00E07D8144D0__INCLUDED_)
