// AboutDlg.h : Declaration of the CAboutDlg

#ifndef __ABOUTDLG_H_
#define __ABOUTDLG_H_

#include "PictureExWnd.h"	// Added by ClassView
#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg
class CAboutDlg : 
	public CAxDialogImpl<CAboutDlg>
{
public:
	CAboutDlg();
	~CAboutDlg();

	enum { IDD = IDD_ABOUTDLG };

BEGIN_MSG_MAP(CAboutDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
protected:
	CPictureExWnd m_wndEyes;
	CPictureExWnd m_wndType;
};

#endif //__ABOUTDLG_H_
