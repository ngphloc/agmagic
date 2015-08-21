// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "mymenu.h"
#include "MainFrm.h"
#include "MymenuDoc.h"
#include "MyFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int Undocheck=0;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
ON_WM_CREATE()
ON_COMMAND(ID_ZOOM, OnZoom)
ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
ON_WM_MEASUREITEM()
ON_WM_MENUCHAR()
ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
ON_COMMAND(ID_EDIT_CUT, OnEditCut)
ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
ON_COMMAND(ID_DEFAULT, OnDefault)
ON_UPDATE_COMMAND_UI(ID_DEFAULT, OnUpdateDefault)
ON_WM_INITMENUPOPUP()
ON_COMMAND(ID_HOMEPAGE, OnHomepage)
ON_COMMAND(ID_ENABLE, OnEnable)
ON_UPDATE_COMMAND_UI(ID_ENABLE, OnUpdateEnable)
ON_COMMAND(ID_DISABLE, OnDisable)
ON_UPDATE_COMMAND_UI(ID_DISABLE, OnUpdateDisable)
ON_COMMAND(ID_ADD_MENU_OPTIONS, OnAddMenuOptions)
ON_UPDATE_COMMAND_UI(ID_ADD_MENU_OPTIONS, OnUpdateAddMenuOptions)
ON_COMMAND(ID_REMOVE_ZOOM, OnRemoveZoom)
ON_COMMAND(ID_MENU2, OnMenu2)
ON_UPDATE_COMMAND_UI(ID_MENU2, OnUpdateMenu2)
ON_COMMAND(ID_ZOOMS, OnZooms)
ON_COMMAND(ID_NEW, OnNew)
ON_COMMAND(ID_TILE, OnTile)
ON_COMMAND(ID_JUNK, OnJunk)
ON_COMMAND(ID_NET, OnNet)
ON_COMMAND(ID_NEW_DOC_TEMPLATE, OnNewDocTemplate)
	ON_COMMAND(ID_COLOREDSQUARE, OnColoredsquare)
	ON_COMMAND(ID_HATCHEDSQUARE, OnHatchedsquare)
	ON_COMMAND(ID_SMALLCOLOREDSQUARE, OnSmallcoloredsquare)
	ON_COMMAND(ID_ADDTESTMENU, OnAddtestmenu)
	ON_UPDATE_COMMAND_UI(ID_ADDTESTMENU, OnUpdateAddtestmenu)
	ON_COMMAND(ID_ADDTOOLSMENU, OnAddtoolsmenu)
	ON_UPDATE_COMMAND_UI(ID_ADDTOOLSMENU, OnUpdateAddtoolsmenu)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
	ON_COMMAND(ID_3DBITMAPS, On3dbitmaps)
	ON_UPDATE_COMMAND_UI(ID_3DBITMAPS, OnUpdate3dbitmaps)
	ON_COMMAND(ID_PICKDISABLED, OnPickdisabled)
	ON_UPDATE_COMMAND_UI(ID_PICKDISABLED, OnUpdatePickdisabled)
	ON_COMMAND(ID_FINDPOPUP, OnFindpopup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	FILE *fp=fopen("BCMenu.startup","r");
	if(fp){
		int newstyle;
		if(fscanf(fp,"%d",&newstyle)==1){
			BCMenu::SetMenuDrawMode(newstyle);
		}
		fclose(fp);
	}
	zoomflag=TRUE;
	disable_flag=FALSE;
	menu2flag=FALSE;
	testflag=FALSE;
	toolsflag=FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_GRIPPER|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	CMenu *pSystemMenu=GetSystemMenu(FALSE);
	pSystemMenu->AppendMenu(MF_SEPARATOR);
	pSystemMenu->AppendMenu(MF_STRING,IDM_SYSMENU_ABOUT,_T("&About MyApp")); //SK modified for Unicode
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnZoom() 
{
	int newstyle;
	int style=BCMenu::GetMenuDrawMode();
	if(style==BCMENU_DRAWMODE_ORIGINAL)newstyle=BCMENU_DRAWMODE_XP;
	else newstyle=BCMENU_DRAWMODE_ORIGINAL;
	FILE *fp=fopen("BCMenu.startup","w");
	if(fp){
		fprintf(fp,"%d",newstyle);
		fclose(fp);
		MessageBox(_T("You must restart this application\nto see the different menu style"));
	}
}

void CMainFrame::OnEditUndo() 
{
	Undocheck=!Undocheck;	
}

HMENU CMainFrame::NewMenu()
{
	static UINT toolbars[]={
		IDR_MAINFRAME,
		IDR_TOOLBAR
	};
	
	// Load the menu from the resources
	m_menu.LoadMenu(IDR_MYMENUTYPE);
	
	// Use ModifyODMenu to add a bitmap to a menu options.The first parameter
	// is the menu option text string.If it's NULL, keep the current text
	// string.The second option is the ID of the menu option, or the menu
	// option text (use this for adding bitmaps to popup options) to change.
	// The third option is the resource ID of the bitmap.This can also be a
	// toolbar ID in which case the class searches the toolbar for the
	// appropriate bitmap.Only Bitmap and Toolbar resources are supported.
	m_menu.ModifyODMenu(NULL,ID_WINDOW_TILE_HORZ,IDB_WINDOW_TILE);
	m_menu.ModifyODMenu(NULL,ID_WINDOW_CASCADE,IDB_WINDOW_NEW);
	m_menu.ModifyODMenu(NULL,ID_JUNK1,IDB_WINDOW_TILE);
	m_menu.ModifyODMenu(NULL,ID_JUNK2,IDB_WINDOW_NEW);
	m_menu.ModifyODMenu(NULL,_T("&Rocscience on the Web"),IDB_NET);
	m_menu.ModifyODMenu(NULL,ID_MEDIA,IDB_HICOLORBITMAP);
	
	// Instead of a resource you can use a CBitmap object with ModifyODMenu
	
	HBITMAP hbmp=BCMenu::LoadSysColorBitmap(IDB_NET);
	if(hbmp){
		CBitmap bmp;
		bmp.Attach(hbmp);
		m_menu.ModifyODMenu(NULL,ID_NET,&bmp);
		bmp.Detach();
		DeleteObject(hbmp);
	}

	// attach a colored square bitmap to an ID
	// solid blue square with a red border
	m_menu.ModifyODMenu(NULL,ID_COLOREDSQUARE,RGB(0,0,255),RGB(255,0,0));
	// a diagonal cross hatched red square with a black border
	m_menu.ModifyODMenu(NULL,ID_HATCHEDSQUARE,RGB(255,0,0),RGB(0,0,0),HS_DIAGCROSS);
	// a smaller colored square
	CSize size(10,10);
	m_menu.ModifyODMenu(NULL,ID_SMALLCOLOREDSQUARE,RGB(0,0,255),RGB(255,0,0),-1,&size);

	// Instead of a resource you can use a CImageList object with ModifyODMenu
	CImageList temp;
	temp.Create(16,15,ILC_COLORDDB|ILC_MASK,1,1);
	temp.Add((HICON)AfxGetApp()->LoadIcon(IDI_256COLOR));
	m_menu.ModifyODMenu(NULL,ID_ZOOMS,&temp,0);
	
	// Another method for adding bitmaps to menu options is through the
	// LoadToolbars member function.This method allows you to add all
	// the bitmaps in a toolbar object to menu options (if they exist).
	// The first function parameter is an array of toolbar id's.
	// The second is the number of toolbar id's. There is also a
	// function called LoadToolbar that just takes an id.
	m_menu.LoadToolbars(toolbars,2);
	
	return(m_menu.Detach());
}

HMENU CMainFrame::NewMyMenu()
{
	static UINT toolbars[]={
		IDR_MAINFRAME,
			IDR_TOOLBAR
	};
	
	m_mymenu.LoadMenu(IDR_MYTYPE);
	m_mymenu.LoadToolbars(toolbars,2);
	
	return(m_mymenu.Detach());
}

HMENU CMainFrame::NewDefaultMenu()
{
	m_default.LoadMenu(IDR_MAINFRAME);
	m_default.LoadToolbar(IDR_MAINFRAME);
	return(m_default.Detach());
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(Undocheck);
}


void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	BOOL setflag=FALSE;
	if(lpMeasureItemStruct->CtlType==ODT_MENU){
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID)&&BCMenu::IsMenu((HMENU)lpMeasureItemStruct->itemID)){
			m_menu.MeasureItem(lpMeasureItemStruct);
			setflag=TRUE;
		}
	}
	if(!setflag)CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lresult;
	if(BCMenu::IsMenu(pMenu))
		lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
		lresult=CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
	return(lresult);
}

void CMainFrame::OnEditCopy() 
{
}

void CMainFrame::OnEditCut() 
{
}

void CMainFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDefault() 
{
	CMenu *menu = AfxGetMainWnd()->GetMenu()->GetSubMenu(2);
	if(::GetMenuDefaultItem(menu->m_hMenu,MF_BYPOSITION,0)==5)
		::SetMenuDefaultItem(menu->m_hMenu,(unsigned int)-1,MF_BYPOSITION);//SK: removed  warning C4245: 'argument' : conversion from 'const int' to 'unsigned int', signed/unsigned mismatch
	else
		::SetMenuDefaultItem(menu->m_hMenu,5,MF_BYPOSITION);
}

void CMainFrame::OnUpdateDefault(CCmdUI* pCmdUI) 
{
	CMenu *menu = AfxGetMainWnd()->GetMenu()->GetSubMenu(2);
	if(::GetMenuDefaultItem(menu->m_hMenu,MF_BYPOSITION,0)==5){
		pCmdUI->SetRadio(TRUE);
		pCmdUI->SetText(_T("Default ON"));//SK modified for Unicode
	}
	else{
		pCmdUI->SetRadio(FALSE);
		pCmdUI->SetText(_T("Default"));//SK modified for Unicode
	}
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	if(!bSysMenu){
		if(BCMenu::IsMenu(pPopupMenu)) BCMenu::UpdateMenu(pPopupMenu);
	}
}

void CMainFrame::OnHomepage() 
{
	ShellExecute(::GetDesktopWindow(),_T("open"),//SK modified for Unicode
		_T("http://www.rocscience.com/~corkum/BCMenu.html"),NULL,NULL,//SK modified for Unicode
		SW_MAXIMIZE);
}

void CMainFrame::OnEnable() 
{
	disable_flag=!disable_flag;
}

void CMainFrame::OnUpdateEnable(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!disable_flag);
	if(!disable_flag)pCmdUI->SetText(_T("&Enabled"));//SK modified for Unicode
	else pCmdUI->SetText(_T("&Disabled"));//SK modified for Unicode
}

void CMainFrame::OnDisable() 
{
	disable_flag=!disable_flag;
}

void CMainFrame::OnUpdateDisable(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(disable_flag);
	if(disable_flag)pCmdUI->SetText(_T("&Enabled"));//SK modified for Unicode
	else pCmdUI->SetText(_T("&Disabled"));//SK modified for Unicode
}

void CMainFrame::OnAddMenuOptions() 
{
	BCMenu *menu = (BCMenu *)AfxGetMainWnd()->GetMenu()->GetSubMenu(1);
	int numitems=menu->GetMenuItemCount();
	if((zoomflag&&numitems==10)||(!zoomflag&&numitems==7)){
		
		//  There are 2 ways of doing the dynamic popups
		
		//  This is method 1 (using AppendMenu with MF_POPUP)
		//    menu->AppendMenu(MF_STRING,ID_EDIT_CUT,_T("Cu&t\tCtrl+X"));
		//    BCMenu *popup1=new BCMenu; // deleted in BCMenu::RemoveMenu
		//    popup1->CreatePopupMenu();
		//    popup1->AppendMenu(MF_STRING,ID_EDIT_PASTE,_T("&Paste\tCtrl+V"));
		//    BCMenu *popup2=new BCMenu; // deleted in BCMenu::RemoveMenu
		//    popup2->CreatePopupMenu();
		//    popup2->AppendMenu(MF_STRING,ID_EDIT_COPY,_T("&Copy\tCtrl+C"));
		//    popup1->AppendMenu(MF_POPUP,(UINT)popup2->m_hMenu,_T("Pop&up2"));
		//    menu->AppendMenu(MF_POPUP,(UINT)popup1->m_hMenu,_T("P&opup1"));
		
		//  This is method 2 (using AppendODPopupMenu). AppendODPopupMenu
		//  has the added advantage of using the current BCMenu's properties.
		//  (i.e. check mark type etc.)
		menu->AppendMenu(MF_STRING,ID_EDIT_CUT,_T("Cu&t\tCtrl+X"));
		BCMenu *popup1=menu->AppendODPopupMenu(_T("P&opup1"));
		popup1->AppendMenu(MF_STRING,ID_EDIT_PASTE,_T("&Paste\tCtrl+V"));
		BCMenu *popup2=popup1->AppendODPopupMenu(_T("Pop&up2"));
		popup2->AppendMenu(MF_STRING,ID_EDIT_COPY,_T("&Copy\tCtrl+C"));
		
		//  Add the bitmaps to the new menu's
		menu->LoadToolbar(IDR_MAINFRAME); 
		menu->ModifyODMenu(NULL,_T("Pop&up2"),IDB_NET);
	}
	else{
		int count = zoomflag ? 10 : 7;
		// call BCMenu::RemoveMenu to remove the dynamic menu's. Note that
		// the function also delete's the BCMenu object so don't call delete.
		for(int i=numitems;i>=count;--i)menu->RemoveMenu(i,MF_BYPOSITION);
	}
}

void CMainFrame::OnUpdateAddMenuOptions(CCmdUI* pCmdUI) 
{
	CMenu *menu = AfxGetMainWnd()->GetMenu()->GetSubMenu(1);
	int numitems=menu->GetMenuItemCount();
	if((zoomflag&&numitems==7)||(!zoomflag&&numitems==4))pCmdUI->SetCheck(FALSE);
	else pCmdUI->SetCheck(TRUE);
}

void CMainFrame::OnRemoveZoom() 
{
	BCMenu *menu = (BCMenu *)AfxGetMainWnd()->GetMenu()->GetSubMenu(1);
	int numitems=menu->GetMenuItemCount();
	if(numitems==7||numitems==9){
		menu->DeleteMenu(0,MF_BYPOSITION);
		menu->DeleteMenu(0,MF_BYPOSITION);
		menu->DeleteMenu(0,MF_BYPOSITION);
		zoomflag=FALSE;
	}
	menu = (BCMenu *)AfxGetMainWnd()->GetMenu()->GetSubMenu(2);
	menu->DeleteMenu("&Popup",BCMENU_HEAD);
	menu->SetMenuText(ID_VIEW_TOOLBAR,"&Toggle Toolbar",MF_BYCOMMAND);
}

void CMainFrame::OnMenu2() 
{
	menu2flag=!menu2flag;
	BCMenu *pMenu = (BCMenu *)AfxGetMainWnd()->GetMenu()->GetSubMenu(3);
	int numitems=pMenu->GetMenuItemCount();
	for(int i=numitems-1;i>=0;--i)pMenu->DeleteMenu(i,MF_BYPOSITION);
	if(menu2flag){
		pMenu->AppendMenu(MF_STRING,ID_NEW,_T("New"));
		pMenu->AppendMenu(MF_STRING,ID_TILE,_T("Tile"));
		pMenu->AppendMenu(MF_SEPARATOR);
		BCMenu *popup1=pMenu->AppendODPopupMenu(_T("P&opup1"));
		popup1->AppendMenu(MF_STRING,ID_EDIT_PASTE,_T("&Paste\tCtrl+V"));
		pMenu->LoadToolbar(IDR_TOOLBAR);
		pMenu->LoadToolbar(IDR_MAINFRAME); 
	}
	else{
		pMenu->AppendMenu(MF_STRING,ID_ZOOMS,_T("Zoom"),IDB_ZOOM);
		
		CImageList temp;
		temp.Create(16,15,ILC_COLORDDB|ILC_MASK,1,1);
		pMenu->AddBitmapToImageList(&temp,IDB_NET);
		pMenu->InsertMenu(0,MF_STRING|MF_BYPOSITION,ID_NET,_T("Net"),&temp,0);
		pMenu->InsertMenu(ID_NET,MF_STRING,ID_TILE,_T("Tile"));
		pMenu->InsertMenu(1,MF_SEPARATOR|MF_BYPOSITION);
		pMenu->LoadToolbar(IDR_TOOLBAR);
	}
}

void CMainFrame::OnUpdateMenu2(CCmdUI* pCmdUI) 
{
	if(!menu2flag)pCmdUI->SetCheck(FALSE);
	else pCmdUI->SetCheck(TRUE);
}

void CMainFrame::OnZooms() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnNew() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnTile() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnJunk() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnNet() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnNewDocTemplate() 
{
	CMDIFrameWnd *pFrame=(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild=(CMDIChildWnd *)pFrame->GetActiveFrame();
	CMymenuDoc* pDoc = (CMymenuDoc *)pChild->GetActiveDocument();
	CMymenuApp *pApp  = (CMymenuApp *)AfxGetApp();
	CMultiDocTemplate *pTemplate=pApp->pMyTemplate;
	if(pDoc&&pApp&&pTemplate){
		CMyFrame *pNewFrame = (CMyFrame *)pTemplate->CreateNewFrame(pDoc,NULL);
		if(pNewFrame)pTemplate->InitialUpdateFrame(pNewFrame,pDoc);
	}
}

void CMainFrame::OnColoredsquare() 
{
}

void CMainFrame::OnHatchedsquare() 
{
}

void CMainFrame::OnSmallcoloredsquare() 
{
}

void CMainFrame::OnAddtestmenu() 
{
	if(!testflag){
		m_test.LoadMenu(IDR_RIGHT_CLICK);
		m_test.LoadToolbar(IDR_MAINFRAME);
		m_test.LoadToolbar(IDR_TOOLBAR);
		m_menu.Attach(GetMenu()->m_hMenu);
		m_menu.InsertMenu(4,MF_POPUP|MF_BYPOSITION,(UINT)m_test.GetSubMenu(0)->m_hMenu,_T("&Test"));
		m_menu.Detach();
		DrawMenuBar();
		testflag=TRUE;
	}
	else{
		m_menu.Attach(GetMenu()->m_hMenu);
		m_menu.DeleteMenu(4,MF_BYPOSITION);
		m_menu.Detach();
		DrawMenuBar();
		testflag=FALSE;
	}
}

void CMainFrame::OnUpdateAddtestmenu(CCmdUI* pCmdUI) 
{
	if(testflag)pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

BOOL CMainFrame::BuildToolsMenu(HMENU hMenu)
{
#ifdef UNICODE
    wchar_t szMenuText[256];
#else
    char szMenuText[256];
#endif
    int  nIdx;

	// this memory is cleaned up when when the menu is deleted (DeleteMenu)
	// or when the application is closed. Whichever happens first.
	BCMenu *pBCMenu = new BCMenu;

    pBCMenu->CreateMenu();

    // Append an Edit Tools item
    pBCMenu->AppendMenu(MF_STRING, ID_APP_ABOUT, _T("&Edit Tools..."));

    // Add a separator before the user-defined tools
    pBCMenu->AppendMenu(MF_SEPARATOR);

    // Append one menu item for each user-defined item
    for(nIdx = 0; nIdx < 10; nIdx++)
    {
#ifdef UNICODE
        wsprintf(szMenuText, _T("User Item #%d"), nIdx + 1);
#else
        sprintf(szMenuText, "User Item #%d", nIdx + 1);
#endif
        pBCMenu->AppendMenu(MF_STRING, ID_APP_ABOUT, szMenuText);
    }

    m_menu.Attach(hMenu);
    m_menu.InsertMenu(4, MF_BYPOSITION | MF_POPUP, (UINT)pBCMenu->m_hMenu, _T("&Tools"));
    m_menu.Detach();

    return TRUE;
}

void CMainFrame::OnAddtoolsmenu() 
{
    if(!toolsflag)
    {
        BuildToolsMenu(GetMenu()->m_hMenu);
        DrawMenuBar();
		toolsflag=TRUE;
    }
    else
    {
		m_menu.Attach(GetMenu()->m_hMenu);
		m_menu.DeleteMenu(4,MF_BYPOSITION);
		m_menu.Detach();
		DrawMenuBar();
		toolsflag=FALSE;
    }
}

void CMainFrame::OnUpdateAddtoolsmenu(CCmdUI* pCmdUI) 
{
	if(toolsflag)pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	if(BCMenu::GetMenuDrawMode()==BCMENU_DRAWMODE_XP){
		pCmdUI->SetText(_T("Change to Original Menu Style"));
		pCmdUI->SetCheck(1);
	}
	else{ 
		pCmdUI->SetText(_T("Change to XP Luna Menu Style"));
		pCmdUI->SetCheck(0);
	}

}

void CMainFrame::On3dbitmaps() 
{
	BOOL style=BCMenu::GetXPBitmap3D();
	BCMenu::SetXPBitmap3D(!style);
}

void CMainFrame::OnUpdate3dbitmaps(CCmdUI* pCmdUI) 
{
	if(BCMenu::GetMenuDrawMode()==BCMENU_DRAWMODE_XP){
		if(BCMenu::GetXPBitmap3D()==TRUE)pCmdUI->SetCheck(TRUE);
		else pCmdUI->SetCheck(FALSE);
	}
	else pCmdUI->Enable(FALSE);
}

void CMainFrame::OnPickdisabled() 
{
	BOOL style=BCMenu::GetSelectDisableMode();
	BCMenu::SetSelectDisableMode(!style);
}

void CMainFrame::OnUpdatePickdisabled(CCmdUI* pCmdUI) 
{
	if(BCMenu::GetSelectDisableMode())
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnFindpopup() 
{
	m_menu.Attach(GetMenu()->m_hMenu);
	BCMenu *pMenu = (BCMenu *)m_menu.GetSubBCMenu(_T("&Rocscience on the Web"));
	if(pMenu){
		pMenu->AppendMenu(MF_STRING,ID_WINDOW_TILE_HORZ,_T("&Tile"));
		pMenu->ModifyODMenu(NULL,ID_WINDOW_TILE_HORZ,IDB_WINDOW_TILE);
	}
	m_menu.Detach();
}
