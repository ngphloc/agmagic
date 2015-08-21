#if !defined(AGIMAGEUI2_H__A5F376D1_E909_4387_974D_0D6308150179__INCLUDED_)
#define AGIMAGEUI2_H__A5F376D1_E909_4387_974D_0D6308150179__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "../../ip/main/AGimage.h"
#include "AGimageUI.h"

#if AGMAGIC_SUPPORT_MFC
#include "AGimageRC.h"
#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
//#include "../../../common/lib/agutilui/main/AGmagicUI.h"	//chua BCMenu, CxTargetButton
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
#define AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
#endif	//AGMAGICUI2_ALREADY_DEFINED_THIS_FILE

#if AGMAGIC_CXIMAGE_VER==5991

/*******************************class CQuantizer*******************************/
#include AG_INCLUDE_QUANTIZE_H
/**************************DlgCapture dialog************************************************/
#include AG_INCLUDE_DLGCAPTURE_H
/**************************DlgColorize dialog************************************************/
#include AG_INCLUDE_DLGCOLORIZE_H
/**************************DlgCombine dialog************************************************/
#include AG_INCLUDE_DLGCOMBINE_H
/**************************DlgDecBpp dialog************************************************/
#include AG_INCLUDE_DLGDECBPP_H
/**************************DlgDither dialog************************************************/
#include AG_INCLUDE_DLGDITHER_H
/**************************DlgFFT dialog************************************************/
#include AG_INCLUDE_DLGFFT_H
/**************************DlgGamma dialog************************************************/
#include AG_INCLUDE_DLGGAMMA_H
/**************************DlgHisto dialog************************************************/
#include AG_INCLUDE_DLGHISTO_H
/**************************DlgIncBpp dialog************************************************/
#include AG_INCLUDE_DLGINCBPP_H
/**************************DlgMix dialog************************************************/
#include AG_INCLUDE_DLGMIX_H
/**************************DlgOpacity dialog************************************************/
#include AG_INCLUDE_DLGOPACITY_H
/**************************DlgOptions dialog************************************************/
#include AG_INCLUDE_DLGOPTIONS_H
/**************************DlgPalette dialog************************************************/
#include AG_INCLUDE_DLGPALETTE_H
/**************************DlgRepair dialog************************************************/
#include AG_INCLUDE_DLGREPAIR_H
/**************************DlgResample dialog************************************************/
#include AG_INCLUDE_DLGRESAMPLE_H
/**************************DlgRotate dialog************************************************/
#include AG_INCLUDE_DLGROTATE_H
/**************************DlgText dialog************************************************/
#include AG_INCLUDE_DLGTEXT_H
/**************************DlgThreshold dialog************************************************/
#include AG_INCLUDE_DLGTHRESHOLD_H
/**************************DlgURL dialog************************************************/
#include AG_INCLUDE_DLGURL_H
/**************************class CLogoMdi************************************************/
#include AG_INCLUDE_LOGOMDI_H

#elif AGMAGIC_CXIMAGE_VER==5993 //AGMAGIC_CXIMAGE_VER

/*******************************class CQuantizer*******************************/
#include AG_INCLUDE_QUANTIZE_H
/**************************DlgCapture dialog************************************************/
#include AG_INCLUDE_DLGCAPTURE_H
/**************************DlgColorize dialog************************************************/
#include AG_INCLUDE_DLGCOLORIZE_H
/**************************DlgCombine dialog************************************************/
#include AG_INCLUDE_DLGCOMBINE_H
/**************************DlgDecBpp dialog************************************************/
#include AG_INCLUDE_DLGDECBPP_H
/**************************DlgDither dialog************************************************/
#include AG_INCLUDE_DLGDITHER_H
/**************************DlgFFT dialog************************************************/
#include AG_INCLUDE_DLGFFT_H
/**************************DlgGamma dialog************************************************/
#include AG_INCLUDE_DLGGAMMA_H
/**************************DlgHisto dialog************************************************/
#include AG_INCLUDE_DLGHISTO_H
/**************************DlgIncBpp dialog************************************************/
#include AG_INCLUDE_DLGINCBPP_H
/**************************DlgJpeg dialog************************************************/
#include AG_INCLUDE_DLGJPEG_H
/**************************DlgMix dialog************************************************/
#include AG_INCLUDE_DLGMIX_H
/**************************DlgOpacity dialog************************************************/
#include AG_INCLUDE_DLGOPACITY_H
/**************************DlgOptions dialog************************************************/
#include AG_INCLUDE_DLGOPTIONS_H
/**************************DlgPalette dialog************************************************/
#include AG_INCLUDE_DLGPALETTE_H
/**************************DlgRepair dialog************************************************/
#include AG_INCLUDE_DLGREPAIR_H
/**************************DlgResample dialog************************************************/
#include AG_INCLUDE_DLGRESAMPLE_H
/**************************DlgRotate dialog************************************************/
#include AG_INCLUDE_DLGROTATE_H
/**************************DlgSkew dialog************************************************/
#include AG_INCLUDE_DLGSKEW_H
/**************************DlgText dialog************************************************/
#include AG_INCLUDE_DLGTEXT_H
/**************************DlgThreshold dialog************************************************/
#include AG_INCLUDE_DLGTHRESHOLD_H
/**************************DlgURL dialog************************************************/
#include AG_INCLUDE_DLGURL_H
/**************************class CLogoMdi************************************************/
#include AG_INCLUDE_LOGOMDI_H

#else //AGMAGIC_CXIMAGE_VER
#error _T("Implement not yet")
#endif //AGMAGIC_CXIMAGE_VER


/**************************class CMainFrame************************************************/
#include AG_INCLUDE_MAINFRM_H
/*
class AGMAGIC_DECL CAGmagicIP_MDIMainFrame : public CMDIFrameWnd, public CTwain
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGmagicIP_MDIMainFrame : public CMainFrame, public CAGmagicDBOrg
{
	DECLARE_DYNAMIC(CAGmagicIP_MDIMainFrame)
public:
	CAGmagicIP_MDIMainFrame();

	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO
	virtual void*	DBCnnAttach(agtchar szDBCnnStr[]);
	virtual void*	DBCnnDetach();//phai Release

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicIP_MDIMainFrame)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicIP_MDIMainFrame();
#ifdef _DEBUG
#endif
	virtual HMENU NewMenu();
	virtual HMENU NewDefaultMenu();

protected:  // control bar embedded members
 
// Generated message map functions
protected:
	protected:
	//{{AFX_MSG(CAGmagicIP_MDIMainFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/**************************class CChildFrame************************************************/
#include AG_INCLUDE_CHILDFRM_H
/*
class AGMAGIC_DECL CAGmagicIP_MDIChildFrame : public CMDIChildWnd
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGmagicIP_MDIChildFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CAGmagicIP_MDIChildFrame)
public:
	CAGmagicIP_MDIChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicIP_MDIChildFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicIP_MDIChildFrame();
#ifdef _DEBUG
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicIP_MDIChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/**************************class CDemoDoc************************************************/
#include AG_INCLUDE_DEMODOC_H

#include "../../ip/main/AGimageSeg.h"
/*
class AGMAGIC_DECL CAGmagicIPDoc : public CDocument
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGmagicIPDoc : public CDemoDoc
{
protected: // create from serialization only
	CAGmagicIPDoc();
	DECLARE_DYNCREATE(CAGmagicIPDoc)

// Attributes
public:

//viet them
	AGMAGICIP_DEFAULT_SEGS_CLASS	m_segs;
	HEURISTIC_SEG_PARAM				m_HSegParam;
	CAGimageGrayScale				m_SegAGimage;
	aguint_id						m_DocID;
	agbool							m_bBusy;

	virtual CxImage* newMyImage(CxImage* pImage=NULL, bool copypixels = true, bool copyselection = true, bool copyalpha = true) 
	{
		if(pImage==NULL)
			return new CAGimage();
		else
		{
			CAGimage* pImageReturn=new CAGimage();
			pImageReturn->Copy(pImage,copypixels,copyselection,copyalpha);
			return pImageReturn;
		}
	};
	virtual CxImage* newMyImage(DWORD dwWidth, DWORD dwHeight, DWORD wBpp, DWORD imagetype=0)
	{
		return new CAGimage(dwWidth,dwHeight,wBpp,imagetype);
	}
	CAGimage* GetImage() {return (CAGimage*)image;}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicIPDoc)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmagicIPDoc();
#ifdef _DEBUG
#endif

protected:

// Generated message map functions
protected:

	//{{AFX_MSG(CAGmagicIPDoc)
	afx_msg void OnSegmentationSegment();
	afx_msg void OnSegmentationSegmentIntel();
	afx_msg void OnSegmentationSegmentInverse();
	afx_msg void OnSegmentationSegmentLoad();
	afx_msg void OnSegmentationShow();
	afx_msg void OnSegmentationOption();

////////////////////////////////////////////////////////////////////////////

	afx_msg void OnUpdateSegmentationSegment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSegmentationSegmentIntel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSegmentationSegmentInverse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSegmentationSegmentLoad(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSegmentationShow(CCmdUI* pCmdUI);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend UINT SegmentationSegmentThread(LPVOID lParam);
	friend UINT SegmentationSegmentThreadIntel(LPVOID lParam);
	friend UINT SegmentationSegmentThreadInverse(LPVOID lParam);
};

/**************************class CDemoView************************************************/
#include AG_INCLUDE_DEMOVIEW_H
class AGMAGIC_DECL CAGmagicIPView : public CDemoView
{
protected: // create from serialization only
	CAGmagicIPView();
	DECLARE_DYNCREATE(CAGmagicIPView)

// Attributes
public:
	CAGmagicIPDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicIPView)
	public:
	protected:
	//}}AFX_VIRTUAL
	virtual void OnHelpTestAGmagicIP();

// Implementation
public:
	virtual ~CAGmagicIPView();

#ifdef _DEBUG
#endif

#if AGMAGICIP_DEMO_SELECT
#endif
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmagicIPView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in demoView.cpp
inline CAGmagicIPDoc* CAGmagicIPView::GetDocument()
   { return (CAGmagicIPDoc*)m_pDocument; }
#endif

/**************************class CDemoApp************************************************/
#include AG_INCLUDE_DEMO_H
/*
class AGMAGIC_DECL CAGmagicIPApp : public CWinApp
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGmagicIPApp : public CDemoApp
{
public:
	CAGmagicIPApp();

	// Attributes

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicIPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Operations

// Implementation

	//{{AFX_MSG(CAGmagicIPApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIPAboutDlg dialog used for App About
class CAGmagicIPAboutDlg : public CDialog
{
public:
	CAGmagicIPAboutDlg();
// Dialog Data
	//{{AFX_DATA(CAGmagicIPAboutDlg)
	enum { IDD = IDD_AGMAGICIPABOUTBOX };
	CxTargetButton	m_ok;
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicIPAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	//{{AFX_MSG(CAGmagicIPAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	//#if AGMAGIC_SUPPORT_MFC
#endif // !defined(AGIMAGEUI2_H__A5F376D1_E909_4387_974D_0D6308150179__INCLUDED_)
