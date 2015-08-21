// CxSkinButtonDemo.h : main header file for the CXSKINBUTTONDEMO application
//

#if !defined(AFX_CXSKINBUTTONDEMO_H__87819724_1CAB_11D5_B6BF_00E07D8144D0__INCLUDED_)
#define AFX_CXSKINBUTTONDEMO_H__87819724_1CAB_11D5_B6BF_00E07D8144D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCxSkinButtonDemoApp:
// See CxSkinButtonDemo.cpp for the implementation of this class
//

class CCxSkinButtonDemoApp : public CWinApp
{
public:
	CCxSkinButtonDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCxSkinButtonDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCxSkinButtonDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXSKINBUTTONDEMO_H__87819724_1CAB_11D5_B6BF_00E07D8144D0__INCLUDED_)
