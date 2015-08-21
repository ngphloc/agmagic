// DlgToolStatusBar.h : main header file for the DLGTOOLSTATUSBAR application
//

#if !defined(AFX_DLGTOOLSTATUSBAR_H__6E24C645_53B8_11D6_9693_B4C16A843021__INCLUDED_)
#define AFX_DLGTOOLSTATUSBAR_H__6E24C645_53B8_11D6_9693_B4C16A843021__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgToolStatusBarApp:
// See DlgToolStatusBar.cpp for the implementation of this class
//

class CDlgToolStatusBarApp : public CWinApp
{
public:
	CDlgToolStatusBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgToolStatusBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgToolStatusBarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTOOLSTATUSBAR_H__6E24C645_53B8_11D6_9693_B4C16A843021__INCLUDED_)
