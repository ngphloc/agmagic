// SkinDialog_DemoDlg.h : header file
//

#if !defined(AFX_SKINDIALOG_DEMODLG_H__7D93D5A5_B5CD_4792_9F75_8FF63EEC093A__INCLUDED_)
#define AFX_SKINDIALOG_DEMODLG_H__7D93D5A5_B5CD_4792_9F75_8FF63EEC093A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSkinDialog_DemoDlg dialog
#include "CDialogSK.h"

class CSkinDialog_DemoDlg : public CDialogSK
{
// Construction
public:
	CSkinDialog_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSkinDialog_DemoDlg)
	enum { IDD = IDD_SKINDIALOG_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinDialog_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSkinDialog_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINDIALOG_DEMODLG_H__7D93D5A5_B5CD_4792_9F75_8FF63EEC093A__INCLUDED_)
