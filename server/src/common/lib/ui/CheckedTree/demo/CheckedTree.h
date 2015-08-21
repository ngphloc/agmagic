// CheckedTree.h : Haupt-Header-Datei für die Anwendung CHECKEDTREE
//

#if !defined(AFX_CHECKEDTREE_H__9AAC9895_A17B_11D3_853E_006097B7EE40__INCLUDED_)
#define AFX_CHECKEDTREE_H__9AAC9895_A17B_11D3_853E_006097B7EE40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CCheckedTreeApp:
// Siehe CheckedTree.cpp für die Implementierung dieser Klasse
//

class CCheckedTreeApp : public CWinApp
{
public:
	CCheckedTreeApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CCheckedTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CCheckedTreeApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_CHECKEDTREE_H__9AAC9895_A17B_11D3_853E_006097B7EE40__INCLUDED_)
