// This is part of the Professional User Interface Suite library.
// Copyright (C) 2001-2004 FOSS Software, Inc.
// All rights reserved.
//
// http://www.prof-uis.com
// http://www.fossware.com
// mailto:support@fossware.com
//
// This source code can be used, modified and redistributed
// under the terms of the license agreement that is included
// in the Professional User Interface Suite package.
//
// Warranties and Disclaimers:
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND
// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
// IN NO EVENT WILL FOSS SOFTWARE INC. BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES,
// INCLUDING DAMAGES FOR LOSS OF PROFITS, LOSS OR INACCURACY OF DATA,
// INCURRED BY ANY PERSON FROM SUCH PERSON'S USAGE OF THIS SOFTWARE
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

#if (!defined __EXT_GROUPBOX_H)
#define __EXT_GROUPBOX_H

#if (!defined __EXT_MFC_DEF_H)
	#include <ExtMfcDef.h>
#endif // __EXT_MFC_DEF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExtGroupBox window

class __PROF_UIS_API CExtGroupBox : public CButton
{
// Construction
public:
	DECLARE_DYNAMIC( CExtGroupBox );
	CExtGroupBox();

// Attributes
public:

// Operations
public:

	enum e_style_t
	{
		STYLE_ETCHED	= 0,
		STYLE_ROUNDED	= 1,
		STYLE_FLAT		= 2,
	};

	void SetStyle( e_style_t eStyle )
	{
		ASSERT_VALID( this );
		m_eStyle = eStyle;
	}
	e_style_t GetStyle() const
	{
		ASSERT_VALID( this );
		return m_eStyle;
	}
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtGroupBox)
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtGroupBox();

private:
	e_style_t m_eStyle;
	
protected:

	virtual CRect OnDrawLabelText(
		CDC & dc,
		const RECT & rcText,
		__EXT_MFC_SAFE_LPCTSTR strText,
		DWORD dwDrawTextFlags,
		bool bEnabled
		);

	virtual void OnDrawFrameRect(
		CDC & dc,
		const RECT & rcClient
		);
		
	// Generated message map functions
protected:
	//{{AFX_MSG(CExtGroupBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __EXT_GROUPBOX_H
