// AboutDlg.cpp : Implementation of CAboutDlg
#include "stdafx.h"
#include "AboutDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg

CAboutDlg::CAboutDlg()
{
}

CAboutDlg::~CAboutDlg()
{
}

LRESULT CAboutDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CenterWindow();
	HWND hWnd = GetDlgItem(IDC_TYPE);
	if (hWnd)
	{
		m_wndType.SubclassWindow(hWnd);
		if (m_wndType.Load(MAKEINTRESOURCE(IDR_TYPE),_T("GIF")))
			m_wndType.Draw();
	};

	hWnd = GetDlgItem(IDC_EYES);
	if (hWnd)
	{
		m_wndEyes.SubclassWindow(hWnd);
		if (m_wndEyes.Load(MAKEINTRESOURCE(IDR_EYES),_T("GIF")))
			m_wndEyes.Draw();
	};

	return 1;  // Let the system set the focus
}

LRESULT CAboutDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

