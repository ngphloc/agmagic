// PictureExDlg.h : Declaration of the CPictureExDlg

#ifndef __PICTUREEXDLG_H_
#define __PICTUREEXDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "PictureExWnd.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CPictureExDlg
class CPictureExDlg : 
	public CAxDialogImpl<CPictureExDlg>
{
public:
	CPictureExDlg();
	~CPictureExDlg();

	enum { IDD = IDD_PICTUREEXDLG };

BEGIN_MSG_MAP(CPictureExDlg)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	COMMAND_ID_HANDLER(IDC_ABOUT, OnAbout)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()

	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

protected:
	HCURSOR m_hCursor;
	CPictureExWnd m_wndBanner;
};

#endif //__PICTUREEXDLG_H_
