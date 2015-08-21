#if !defined(AFX_DEMO_H__D15CC661_367E_43C3_8C82_009E7C01E5F0__INCLUDED_)
#define AFX_DEMO_H__D15CC661_367E_43C3_8C82_009E7C01E5F0__INCLUDED_
// demo.h : main header file for the DEMO application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#ifdef VATI_EXTENSIONS
// just for including CXTEXTINFO type declaration:
#include "../CxImage/ximage.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoApp:
// See demo.cpp for the implementation of this class
//

#ifndef AGMAGIC_DECL
class CDemoApp : public CWinApp
#else
class AGMAGIC_DECL CDemoApp : public CWinApp
#endif	//AGMAGIC_DECL
{
public:
	CDemoApp();

	// Attributes
	int m_nDocCount;	//number of documents
	CMultiDocTemplate *demoTemplate;
	
//viet them
	int m_nDocInc;//so document duoc tang dan mai

#ifdef VATI_EXTENSIONS
	int m_optJpegQuality;
    // for text placement
    CXTEXTINFO  m_text;
#endif

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Operations
	BOOL PromptForFileName(CString& fileName, UINT nIDSTitle, 
		DWORD dwFlags, BOOL bOpenFileDialog, int* pType=NULL);
	int GetIndexFromType(int nDocType, BOOL bOpenFileDialog);
	int GetTypeFromIndex(int nIndex, BOOL bOpenFileDialog);
	CString GetExtFromType(int nDocType);
	CString GetDescFromType(int nDocType);
	CString GetFileTypes(BOOL bOpenFileDialog);
	BOOL GetWritableType(int nDocType);

// Implementation

	//{{AFX_MSG(CDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnImageFromBitmap();
	afx_msg void OnCximageLoadjpegresource();
	afx_msg void OnCximageLoadiconresource();
	afx_msg void OnCximageLoadgifresource();
	afx_msg void OnCximageLoadpngresource();
	afx_msg void OnCximageLoadtifresource();
	afx_msg void OnWindowCloseall();
	afx_msg void OnCximageDemosavemultipagetiff();
	afx_msg void OnCximageDemosaveanimatedgif();
	afx_msg void OnCximageDownloadfromurl();
	afx_msg void OnCximageDemocreatefromarray();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
extern CDemoApp theApp;
#endif //#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE

struct DocType
{
public:
	int nID;
	BOOL bRead;
	BOOL bWrite;
	const char* description;
	const char* ext;
};


/////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_DEMO_H__D15CC661_367E_43C3_8C82_009E7C01E5F0__INCLUDED_)
