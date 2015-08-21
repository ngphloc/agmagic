// PictureExDlg.cpp : Implementation of CPictureExDlg
#include "stdafx.h"
#include "PictureExDlg.h"
#include "AboutDlg.h"
#include "shellapi.h"  // for ShellExecute

/////////////////////////////////////////////////////////////////////////////
// CPictureExDlg

CPictureExDlg::CPictureExDlg() : m_hCursor(NULL)
{

}

CPictureExDlg::~CPictureExDlg()
{

}

LRESULT CPictureExDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CPictureExDlg::OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CPictureExDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Set application icon
	HICON hIcon = LoadIcon(_Module.GetResourceInstance(),
		MAKEINTRESOURCE(IDI_PICTUREEXDEMO));
	SetIcon(hIcon);
	CenterWindow();

	m_hCursor = LoadCursor(_Module.GetResourceInstance(),MAKEINTRESOURCE(IDC_HAND));

	HWND hWnd = GetDlgItem(IDC_BANNER);
	if (hWnd)
	{
		m_wndBanner.SubclassWindow(hWnd);
		if (m_wndBanner.Load(MAKEINTRESOURCE(IDR_BANNER),_T("GIF")))
			m_wndBanner.Draw();
	};

	return 1;  // Let the system set the focus
}

LRESULT CPictureExDlg::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RECT rect;
	::GetWindowRect(m_wndBanner.m_hWnd,&rect);

	POINT point;
	GetCursorPos(&point);

	if (PtInRect(&rect,point))
	{
		if (m_hCursor) SetCursor(m_hCursor);
		bHandled = TRUE;
		return S_OK;
	};

	bHandled = FALSE;
	return S_OK;
}

LRESULT CPictureExDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RECT rect;
	::GetWindowRect(m_wndBanner.m_hWnd,&rect);

	POINT point;
	GetCursorPos(&point);

	if (PtInRect(&rect,point))
	{
		ShellExecute(m_hWnd,_T("open"),_T("http://www.rsdn.ru"),_T(""),NULL,0);
	};

	return S_OK;
}
