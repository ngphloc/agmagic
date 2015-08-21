#include "AGimageUI2.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif	//_DEBUG
#endif	//AGMAGIC_SUPPORT_MFC


#if AGMAGIC_SUPPORT_MFC
#if AGMAGIC_CXIMAGE_VER==5991

/*******************************class CQuantizer*******************************/
#include AG_INCLUDE_QUANTIZE_CPP
/**************************DlgCapture dialog************************************************/
#include AG_INCLUDE_DLGCAPTURE_CPP
/**************************DlgColorize dialog************************************************/
#include AG_INCLUDE_DLGCOLORIZE_CPP
/**************************DlgCombine dialog************************************************/
#include AG_INCLUDE_DLGCOMBINE_CPP
/**************************DlgDecBpp dialog************************************************/
#include AG_INCLUDE_DLGDECBPP_CPP
/**************************DlgDither dialog************************************************/
#include AG_INCLUDE_DLGDITHER_CPP
/**************************DlgFFT dialog************************************************/
#include AG_INCLUDE_DLGFFT_CPP
/**************************DlgGamma dialog************************************************/
#include AG_INCLUDE_DLGGAMMA_CPP
/**************************DlgHisto dialog************************************************/
#include AG_INCLUDE_DLGHISTO_CPP
/**************************DlgIncBpp dialog************************************************/
#include AG_INCLUDE_DLGINCBPP_CPP
/**************************DlgMix dialog************************************************/
#include AG_INCLUDE_DLGMIX_CPP
/**************************DlgOpacity dialog************************************************/
#include AG_INCLUDE_DLGOPACITY_CPP
/**************************DlgOptions dialog************************************************/
#include AG_INCLUDE_DLGOPTIONS_CPP
/**************************DlgPalette dialog************************************************/
#include AG_INCLUDE_DLGPALETTE_CPP
/**************************DlgRepair dialog************************************************/
#include AG_INCLUDE_DLGREPAIR_CPP
/**************************DlgResample dialog************************************************/
#include AG_INCLUDE_DLGRESAMPLE_CPP
/**************************DlgRotate dialog************************************************/
#include AG_INCLUDE_DLGROTATE_CPP
/**************************DlgText dialog************************************************/
#include AG_INCLUDE_DLGTEXT_CPP
/**************************DlgThreshold dialog************************************************/
#include AG_INCLUDE_DLGTHRESHOLD_CPP
/**************************DlgURL dialog************************************************/
#include AG_INCLUDE_DLGURL_CPP
/**************************CLogoMdi dialog************************************************/
#include AG_INCLUDE_LOGOMDI_CPP
/**************************class CMainFrame************************************************/
#include AG_INCLUDE_MAINFRM_CPP
/**************************class CChildFrame************************************************/
#include AG_INCLUDE_CHILDFRM_CPP
/**************************class CDemoDoc************************************************/
#include AG_INCLUDE_DEMODOC_CPP
/**************************class CDemoView************************************************/
#include AG_INCLUDE_DEMOVIEW_CPP
/**************************class CDemoApp************************************************/
#include AG_INCLUDE_DEMO_CPP

#elif AGMAGIC_CXIMAGE_VER==5993 //AGMAGIC_CXIMAGE_VER

/**************************DlgCapture dialog************************************************/
#include AG_INCLUDE_DLGCAPTURE_CPP
/**************************DlgColorize dialog************************************************/
#include AG_INCLUDE_DLGCOLORIZE_CPP
/**************************DlgCombine dialog************************************************/
#include AG_INCLUDE_DLGCOMBINE_CPP
/**************************DlgDecBpp dialog************************************************/
#include AG_INCLUDE_DLGDECBPP_CPP
/**************************DlgDither dialog************************************************/
#include AG_INCLUDE_DLGDITHER_CPP
/**************************DlgFFT dialog************************************************/
#include AG_INCLUDE_DLGFFT_CPP
/**************************DlgGamma dialog************************************************/
#include AG_INCLUDE_DLGGAMMA_CPP
/**************************DlgHisto dialog************************************************/
#include AG_INCLUDE_DLGHISTO_CPP
/**************************DlgIncBpp dialog************************************************/
#include AG_INCLUDE_DLGINCBPP_CPP
/**************************DlgJpeg dialog************************************************/
#include AG_INCLUDE_DLGJPEG_CPP
/**************************DlgMix dialog************************************************/
#include AG_INCLUDE_DLGMIX_CPP
/**************************DlgOpacity dialog************************************************/
#include AG_INCLUDE_DLGOPACITY_CPP
/**************************DlgOptions dialog************************************************/
#include AG_INCLUDE_DLGOPTIONS_CPP
/**************************DlgPalette dialog************************************************/
#include AG_INCLUDE_DLGPALETTE_CPP
/**************************DlgRepair dialog************************************************/
#include AG_INCLUDE_DLGREPAIR_CPP
/**************************DlgResample dialog************************************************/
#include AG_INCLUDE_DLGRESAMPLE_CPP
/**************************DlgRotate dialog************************************************/
#include AG_INCLUDE_DLGROTATE_CPP
/**************************DlgSkew dialog************************************************/
#include AG_INCLUDE_DLGSKEW_CPP
/**************************DlgText dialog************************************************/
#include AG_INCLUDE_DLGTEXT_CPP
/**************************DlgThreshold dialog************************************************/
#include AG_INCLUDE_DLGTHRESHOLD_CPP
/**************************DlgURL dialog************************************************/
#include AG_INCLUDE_DLGURL_CPP
/**************************CLogoMdi dialog************************************************/
#include AG_INCLUDE_LOGOMDI_CPP
/**************************class CMainFrame************************************************/
#include AG_INCLUDE_MAINFRM_CPP
/**************************class CChildFrame************************************************/
#include AG_INCLUDE_CHILDFRM_CPP
/**************************class CDemoDoc************************************************/
#include AG_INCLUDE_DEMODOC_CPP
/**************************class CDemoView************************************************/
#include AG_INCLUDE_DEMOVIEW_CPP
/**************************class CDemoApp************************************************/
#include AG_INCLUDE_DEMO_CPP

#else //AGMAGIC_CXIMAGE_VER
#error _T("Implement not yet")
#endif //AGMAGIC_CXIMAGE_VER

#endif //AGMAGIC_SUPPORT_MFC

/**************************class CAGmagicIP_MDIMainFrame****************************************/
IMPLEMENT_DYNAMIC(CAGmagicIP_MDIMainFrame, CMainFrame)

BEGIN_MESSAGE_MAP(CAGmagicIP_MDIMainFrame, CMainFrame)
	//{{AFX_MSG_MAP(CAGmagicIP_MDIMainFrame)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIP_MDIMainFrame construction/destruction
CAGmagicIP_MDIMainFrame::CAGmagicIP_MDIMainFrame() : CMainFrame(), CAGmagicDBOrg()
{
}
CAGmagicIP_MDIMainFrame::~CAGmagicIP_MDIMainFrame()
{
}
void* CAGmagicIP_MDIMainFrame::DBCnnAttach(void* pDBCnnI)//khong AddRef, tra ve Connection cu doi ADO
{
	throw _T("Not support this function");
}
void* CAGmagicIP_MDIMainFrame::DBCnnAttach(agtchar szDBCnnStr[])
{
	throw _T("You must define in devired class");
}
void* CAGmagicIP_MDIMainFrame::DBCnnDetach()//phai Release
{
	throw _T("You must define in devired class");
}

//////////////////////////////////////////////////////////////////////////////
HMENU CAGmagicIP_MDIMainFrame::NewMenu()
{
  static UINT toolbars[]={
    IDR_MAINFRAME,
	IDR_TOOLBAR1
  };

  // Load the menu from the resources
  // ****replace IDR_MENUTYPE with your menu ID****
  m_menu.LoadMenu(IDR_AGMAGICIPTYPE);  
  // One method for adding bitmaps to menu options is 
  // through the LoadToolbars member function.This method 
  // allows you to add all the bitmaps in a toolbar object 
  // to menu options (if they exist). The first function 
  // parameter is an array of toolbar id's. The second is 
  // the number of toolbar id's. There is also a function 
  // called LoadToolbar that just takes an id.
  m_menu.LoadToolbars(toolbars,2);

  return(m_menu.Detach());
}
//////////////////////////////////////////////////////////////////////////////
HMENU CAGmagicIP_MDIMainFrame::NewDefaultMenu()
{
  m_default.LoadMenu(IDR_AGMAGICIPMAINFRAME);
  m_default.LoadToolbar(IDR_MAINFRAME);
  return(m_default.Detach());
}
void CAGmagicIP_MDIMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMainFrame::OnSize(nType, cx, cy);
	CStatusBar&		statusBar=GetStatusBar();
	CProgressCtrl&	progressCtrl=GetProgressBar();

	CRect rc;
	statusBar.GetItemRect(1,&rc);
	progressCtrl.MoveWindow(&rc,TRUE);
	// TODO: Add your message handler code here
}

/**************************class CAGmagicIP_MDIChildFrame************************************************/
IMPLEMENT_DYNCREATE(CAGmagicIP_MDIChildFrame, CChildFrame)

BEGIN_MESSAGE_MAP(CAGmagicIP_MDIChildFrame, CChildFrame)
	//{{AFX_MSG_MAP(CAGmagicIP_MDIChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIP_MDIChildFrame construction/destruction
CAGmagicIP_MDIChildFrame::CAGmagicIP_MDIChildFrame() : CChildFrame()
{
	// TODO: add member initialization code here
}

CAGmagicIP_MDIChildFrame::~CAGmagicIP_MDIChildFrame()
{
}

/**************************class CAGmagicIPDoc****************************************/
#include "../../ip/main/AGimageUtil.h"

IMPLEMENT_DYNCREATE(CAGmagicIPDoc, CDemoDoc)

BEGIN_MESSAGE_MAP(CAGmagicIPDoc, CDemoDoc)
	//{{AFX_MSG_MAP(CAGmagicIPDoc)
	ON_UPDATE_COMMAND_UI(ID_SEGMENTATION_SEGMENT, OnUpdateSegmentationSegment)
	ON_UPDATE_COMMAND_UI(ID_SEGMENTATION_SEGMENT_INTEL, OnUpdateSegmentationSegmentIntel)
	ON_UPDATE_COMMAND_UI(ID_SEGMENTATION_SEGMENT_INVERSE, OnUpdateSegmentationSegmentInverse)
	ON_UPDATE_COMMAND_UI(ID_SEGMENTATION_SEGMENT_LOAD, OnUpdateSegmentationSegmentLoad)
	ON_UPDATE_COMMAND_UI(ID_SEGMENTATION_SHOW, OnUpdateSegmentationShow)

////////////////////////////////////////////////////////////////////////////

	ON_COMMAND(ID_SEGMENTATION_SEGMENT, OnSegmentationSegment)
	ON_COMMAND(ID_SEGMENTATION_SEGMENT_INTEL, OnSegmentationSegmentIntel)
	ON_COMMAND(ID_SEGMENTATION_SEGMENT_INVERSE, OnSegmentationSegmentInverse)
	ON_COMMAND(ID_SEGMENTATION_SEGMENT_LOAD, OnSegmentationSegmentLoad)
	ON_COMMAND(ID_SEGMENTATION_SHOW, OnSegmentationShow)
	ON_COMMAND(ID_SEGMENTATION_OPTION,  OnSegmentationOption)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAGmagicIPDoc::CAGmagicIPDoc() : CDemoDoc()
{
	//viet them
	INIT_HEURISTIC_SEG_PARAM(m_HSegParam)
	m_bBusy=agfalse;
}
//////////////////////////////////////////////////////////////////////////////
CAGmagicIPDoc::~CAGmagicIPDoc()
{
}
//////////////////////////////////////////////////////////////////////////////

void CAGmagicIPDoc::OnUpdateSegmentationSegment(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(hThread==0 && image  && image->IsValid() && !m_bBusy);
}
void CAGmagicIPDoc::OnUpdateSegmentationSegmentIntel(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(hThread==0 && image  && image->IsValid() && !m_bBusy);
}
void CAGmagicIPDoc::OnUpdateSegmentationSegmentInverse(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(hThread==0 && image  && image->IsValid() && !m_bBusy);
}
void CAGmagicIPDoc::OnUpdateSegmentationSegmentLoad(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(hThread==0 && image  && image->IsValid() && !m_bBusy);
}
void CAGmagicIPDoc::OnUpdateSegmentationShow(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(image  && image->IsValid() && m_segs.GetSize()>0 && !m_bBusy);
}

//////////////////////////////////////////////////////////////////////////////

void /*unsigned long _stdcall*/ RunSegmentProgressThread(void *lParam)
{
	CAGmagicIPDoc *pDoc = (CAGmagicIPDoc *)lParam;
	long n;
	POSITION pos;
	CView *pView;
	while((n=pDoc->m_SegAGimage.GetProgress())<100){
		Sleep(333);
		if(pDoc->m_SegAGimage.GetEscape()) break;
		pos = pDoc->GetFirstViewPosition();
		pView = pDoc->GetNextView(pos);
		if (pView) SendMessage(pView->m_hWnd, WM_USER_PROGRESS,n,0);
	}
	pos = pDoc->GetFirstViewPosition();
	pView = pDoc->GetNextView(pos);
	if (pView) SendMessage(pView->m_hWnd, WM_USER_PROGRESS,100,0);
	Sleep(111);
	pos = pDoc->GetFirstViewPosition();
	pView = pDoc->GetNextView(pos);
	if (pView) SendMessage(pView->m_hWnd, WM_USER_NEWIMAGE,0,0);
	pDoc->hProgress = 0;
	_endthread();
	return;
}
UINT SegmentationSegmentThread(LPVOID lParam)
{
	CAGmagicIPDoc*			pDoc = (CAGmagicIPDoc *)lParam;
	if (pDoc==NULL || pDoc->image==NULL)
	{
		pDoc->hThread=0;
		AfxEndThread(0,TRUE);
		return 0;
	}
	
	 //prepare for elaboration
	pDoc->m_SegAGimage.SetProgress(0);
	pDoc->m_SegAGimage.SetEscape(0);

	//pDoc->SubmitUndo();
	
	// auxilary thread for progress bar
	pDoc->hProgress = (HANDLE)_beginthread(RunSegmentProgressThread,0,pDoc);
	pDoc->Stopwatch(0);

	//phan chinh
	pDoc->m_SegAGimage.Copy(pDoc->GetImage());
	pDoc->m_segs.SegCreate(pDoc->GetImage(),NULL,&(pDoc->m_SegAGimage));

	pDoc->Stopwatch(1);
	pDoc->m_SegAGimage.SetProgress(100);

	//phan xem ket qua
	pDoc->OnSegmentationShow();

	pDoc->hThread=0;
	AfxEndThread(0,TRUE);
	return 0;
}
UINT SegmentationSegmentThreadIntel(LPVOID lParam)
{
	CAGmagicIPDoc*			pDoc = (CAGmagicIPDoc *)lParam;
	if (pDoc==NULL || pDoc->image==NULL)
	{
		pDoc->hThread=0;
		AfxEndThread(0,TRUE);
		return 0;
	}

	aguint_id	ImageType=0;
	if(!pDoc->GetPathName().IsEmpty())
	{
		agtchar*	szImageName=NULL;
		agtchar*	szBaseSampleDir=NULL;
		agtchar*	szDirTypeName=NULL;
		CString		szPathName=pDoc->GetPathName();
		CAGimageIOUtil::AnalyzeImagePathAndAlloc(szPathName.GetBuffer(0),szBaseSampleDir, szDirTypeName, szImageName);
		ImageType=CAGmagicConfUtil::GetTypeOfSampleImagesDirNames(szDirTypeName);
		if(szImageName)		free(szImageName);
		if(szBaseSampleDir) free(szBaseSampleDir);
		if(szDirTypeName)	free(szDirTypeName);
	}

	 //prepare for elaboration
	pDoc->m_SegAGimage.SetProgress(0);
	pDoc->m_SegAGimage.SetEscape(0);

	//pDoc->SubmitUndo();
	
	// auxilary thread for progress bar
	pDoc->hProgress = (HANDLE)_beginthread(RunSegmentProgressThread,0,pDoc);
	pDoc->Stopwatch(0);

	//phan chinh
	if(!CAGmagicConfUtil::IsNegativeImageWhenSegment(ImageType))
		pDoc->m_SegAGimage.Copy(pDoc->GetImage());
	else
	{
		CAGimage	NegativeImage;
		NegativeImage.Copy(pDoc->image);
		NegativeImage.Negative();
		pDoc->m_SegAGimage.Copy(&NegativeImage);
	}
	pDoc->m_segs.SegCreate(pDoc->GetImage(),NULL,&(pDoc->m_SegAGimage));

	pDoc->Stopwatch(1);
	pDoc->m_SegAGimage.SetProgress(100);

	//phan xem ket qua
	pDoc->OnSegmentationShow();

	pDoc->hThread=0;
	AfxEndThread(0,TRUE);
	return 0;
}
UINT SegmentationSegmentThreadInverse(LPVOID lParam)
{
	CAGmagicIPDoc*			pDoc = (CAGmagicIPDoc *)lParam;
	if (pDoc==NULL || pDoc->image==NULL)
	{
		pDoc->hThread=0;
		AfxEndThread(0,TRUE);
		return 0;
	}
	
	 //prepare for elaboration
	pDoc->m_SegAGimage.SetProgress(0);
	pDoc->m_SegAGimage.SetEscape(0);

	//pDoc->SubmitUndo();
	
	// auxilary thread for progress bar
	pDoc->hProgress = (HANDLE)_beginthread(RunSegmentProgressThread,0,pDoc);
	pDoc->Stopwatch(0);

	//phan chinh
	CAGimage	NegativeImage;
	NegativeImage.Copy(pDoc->image);
	NegativeImage.Negative();
	pDoc->m_SegAGimage.Copy(&NegativeImage);
	pDoc->m_segs.SegCreate(pDoc->GetImage(),NULL,&(pDoc->m_SegAGimage));

	pDoc->Stopwatch(1);
	pDoc->m_SegAGimage.SetProgress(100);

	//phan xem ket qua
	pDoc->OnSegmentationShow();

	pDoc->hThread=0;
	AfxEndThread(0,TRUE);
	return 0;
}
void CAGmagicIPDoc::OnSegmentationSegment()
{
	if(hThread!=0)	return;
	CWinThread* pWinThread=AfxBeginThread(SegmentationSegmentThread,this);
	hThread	= pWinThread->m_hThread;
}
void CAGmagicIPDoc::OnSegmentationSegmentIntel()
{
	if(hThread!=0)	return;
	CWinThread* pWinThread=AfxBeginThread(SegmentationSegmentThreadIntel,this);
	hThread	= pWinThread->m_hThread;
}
void CAGmagicIPDoc::OnSegmentationSegmentInverse()
{
	if(hThread!=0)	return;
	CWinThread* pWinThread=AfxBeginThread(SegmentationSegmentThreadInverse,this);
	hThread	= pWinThread->m_hThread;
}
void CAGmagicIPDoc::OnSegmentationSegmentLoad()
{
	CAGmagicIP_MDIMainFrame* pMainWnd=(CAGmagicIP_MDIMainFrame*)AfxGetMainWnd();
	if(pMainWnd->DBCnnGet())
	{
		aguint_id ImageID=GetImage()->m_ID;
		if(ImageID==0)
		{
			CString			szImagePath=GetPathName();
			CAGidTypeArray	ImageIDTypes;
			CAGimageDBUtil::FindImageIntel(pMainWnd->DBCnnGet(), szImagePath.GetBuffer(0), &ImageIDTypes);
			if(ImageIDTypes.GetSize()==1)
			{
				IMAGE_ID_TYPE	ImageIDType=ImageIDTypes.GetAt(0);
				ImageID=ImageIDType.ImageID;
			}
		}
		if(ImageID!=0)
		{
			m_segs.DBCnnAttach(pMainWnd->DBCnnGet());
			if(m_segs.DBRead(ImageID))
			{
				//phan xem ket qua
				OnSegmentationShow();
				return;
			}
		}
	}
	pMainWnd->MessageBox(_T("Image Segment not store In database"),_T("Error"),MB_OK|MB_ICONSTOP);
}
//////////////////////////////////////////////////////////////////////////////
void CAGmagicIPDoc::OnSegmentationShow()
{
	if(m_segs.GetSize()==0)
	{
		AfxMessageBox(_T("No segment to show or not do segmentation yet"),MB_OK|MB_ICONINFORMATION,0);
		return;
	}

	agtchar	szNotice[128];
	_stprintf(szNotice,_T("There are %lu segment(s)"),m_segs.GetSize());
	AfxMessageBox(szNotice,MB_OK|MB_ICONINFORMATION,0);
	CAGimageUIUtil::Show(&m_segs);
}

//////////////////////////////////////////////////////////////////////////////

void CAGmagicIPDoc::OnSegmentationOption()
{
}

/**************************class CAGmagicIPView****************************************/
IMPLEMENT_DYNCREATE(CAGmagicIPView, CDemoView)

BEGIN_MESSAGE_MAP(CAGmagicIPView, CDemoView)
	//{{AFX_MSG_MAP(CAGmagicIPView)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_HELP_TEST_AGMAGICIP, OnHelpTestAGmagicIP)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIPView construction/destruction
CAGmagicIPView::CAGmagicIPView() : CDemoView()
{
}
//////////////////////////////////////////////////////////////////////////////
CAGmagicIPView::~CAGmagicIPView()
{
}

#ifdef _DEBUG
CAGmagicIPDoc* CAGmagicIPView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAGmagicIPDoc)));
	return (CAGmagicIPDoc*)m_pDocument;
}
#endif //_DEBUG

void CAGmagicIPView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CAGmagicIPDoc* pDoc = GetDocument();
	if (pDoc && pDoc->m_tool==2) return;
#ifdef VATI_EXTENSIONS
	// suppress context menu if right-click function was called just now
	if ( m_suppressContextMenu == true )
		return;
#endif
	static UINT toolbars[]={
		IDR_MAINFRAME,
		IDR_TOOLBAR1,
	};
	BCMenu menu;
	menu.LoadMenu(IDM_AGMAGICIP_CONTEXT);
	menu.LoadToolbars(toolbars,2);
	CMenu *pContextMenu=menu.GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
}

void CAGmagicIPView::OnHelpTestAGmagicIP()
{
	CAGmagicIPDoc*	pDoc = GetDocument();
	CAGimage*		pAGimage=pDoc->GetImage();
	MessageBox(_T("Test"));
}

/**********************class CAGmagicIPApp, class CAGmagicIPAboutDlg****************************/
BEGIN_MESSAGE_MAP(CAGmagicIPApp, CDemoApp)
	//{{AFX_MSG_MAP(CAGmagicIPApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	// Standard print setup command
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIPApp construction
CAGmagicIPApp::CAGmagicIPApp() : CDemoApp()
{
}
//////////////////////////////////////////////////////////////////////////////
// The one and only CAGmagicIPApp object

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIPApp initialization
BOOL CAGmagicIPApp::InitInstance()
{
	// <dave> dump memory leaks
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	// Standard initialization
#if _MFC_VER < 0x0700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL //khong can thiet nua doi voi VC 7.0
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically //khong can thiet nua doi voi VC 7.0
#endif
#endif	//#if _MFC_VER < 0x0700
	LoadStdProfileSettings(9);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_AGMAGICIPTYPE,
		RUNTIME_CLASS(CAGmagicIPDoc),
		RUNTIME_CLASS(CAGmagicIP_MDIChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAGmagicIPView));
	demoTemplate = pDocTemplate;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CAGmagicIP_MDIMainFrame* pMainFrame = new CAGmagicIP_MDIMainFrame();
	if (!pMainFrame->LoadFrame(IDR_AGMAGICIPMAINFRAME)) return FALSE;
	m_pMainWnd = pMainFrame;

	// This code replaces the MFC created menus with 
	// the Ownerdrawn versions 
	pDocTemplate->m_hMenuShared=pMainFrame->NewMenu();
	pMainFrame->m_hMenuDefault=pMainFrame->NewDefaultMenu();
	// This simulates a window being opened if you don't have
	// a default window displayed at startup
	pMainFrame->OnUpdateFrameMenu(pMainFrame->m_hMenuDefault);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
    // Alter behaviour to not open window immediately
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo)) return FALSE;

#ifdef VATI_EXTENSIONS
    // init m_text by a temporary CxImage 
	CxImage *ima = new CxImage();
	ima->InitTextInfo( &m_text );
	delete ima;
    
	//recall last used font data for Text tool
    sprintf( m_text.lfont.lfFaceName, GetProfileString ( "TextTool", "lfFaceName", "Arial") );
	m_text.lfont.lfCharSet   = GetProfileInt ( "TextTool", "lfCharSet", EASTEUROPE_CHARSET ) ;
    m_text.lfont.lfWeight    = GetProfileInt ( "TextTool", "lfWeight", 0 );
    m_text.lfont.lfItalic    = GetProfileInt ( "TextTool", "lfItalic", 0 ); 
    m_text.lfont.lfUnderline = GetProfileInt ( "TextTool", "lfUnderline", 0 ); 
    m_text.fcolor = GetProfileInt ( "TextTool", "fcolor", RGB( 255,255,160 ));
    m_text.bcolor = GetProfileInt ( "TextTool", "bcolor", RGB( 32, 96, 0 ));
    m_text.opaque = GetProfileInt ( "TextTool", "opaque", 1);
    m_text.b_opacity = (float)(GetProfileInt( "TextTool", "opacity", 0 ))/(float)100.;  
    m_text.b_round   = GetProfileInt ( "TextTool", "roundradius", 25 );

	m_optJpegQuality = GetProfileInt("Options","JpegQuality",90);

	// recall if main window was maximized on last exit
    if ( GetProfileInt ( "Screen", "maximized", 0 ))
        m_nCmdShow|=SW_MAXIMIZE;
#endif;

	// The main window has been initialized, so show and update it.
    pMainFrame -> ShowWindow ( SW_MAXIMIZE ) ;
	pMainFrame->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable open from command line
	if (*m_lpCmdLine != 0)
		OpenDocumentFile(m_lpCmdLine);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////
// App command to run the dialog
void CAGmagicIPApp::OnAppAbout()
{
	CAGmagicIPAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAGmagicIPAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAGmagicIPAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////////////
CAGmagicIPAboutDlg::CAGmagicIPAboutDlg() : CDialog(CAGmagicIPAboutDlg::IDD)
{
}
//////////////////////////////////////////////////////////////////////////////
void CAGmagicIPAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCapture)
	DDX_Control(pDX, IDOK, m_ok);
	//}}AFX_DATA_MAP
}
//////////////////////////////////////////////////////////////////////////////
BOOL CAGmagicIPAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ok.SetIcon(IDI_AGMAGICIP_G,BS_LEFT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
