// CheckedTreeDlg.h : Header-Datei
//

#if !defined(AFX_CHECKEDTREEDLG_H__9AAC9897_A17B_11D3_853E_006097B7EE40__INCLUDED_)
#define AFX_CHECKEDTREEDLG_H__9AAC9897_A17B_11D3_853E_006097B7EE40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CheckedTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckedTreeDlg Dialogfeld

class CCheckedTreeDlg : public CDialog
{
// Konstruktion
public:
	CCheckedTreeDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CCheckedTreeDlg)
	enum { IDD = IDD_CHECKEDTREE_DIALOG };
		// HINWEIS: der Klassenassistent fügt an dieser Stelle Datenelemente (Members) ein
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CCheckedTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CCheckedTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	// create the control
	void
	createTreeControl();

	// fill the elements
	void
	fillTreeControl();


	CCheckedTreeCtrl		m_MyTreeControl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_CHECKEDTREEDLG_H__9AAC9897_A17B_11D3_853E_006097B7EE40__INCLUDED_)
