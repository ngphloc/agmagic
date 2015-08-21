; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMymenuView
LastTemplate=CMDIChildWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mymenu.h"
LastPage=0

ClassCount=9
Class1=CChildFrame
Class2=CMainFrame
Class3=CMymenuApp
Class4=CAboutDlg
Class5=CMymenuDoc
Class6=CMymenuView
Class7=CToolBarEx

ResourceCount=13
Resource1=IDR_MYTYPE (English (U.S.))
Resource2=IDR_TOOLBAR
Resource3=IDR_MAINFRAME
Resource4=IDR_MYMENUTYPE
Resource5=IDR_TOOLBAR (English (U.S.))
Resource6=IDD_ABOUTBOX
Resource7=IDR_MYMENUTYPE (English (U.S.))
Resource8=IDR_MAINFRAME (English (U.S.))
Resource9=IDR_RIGHT_CLICK (English (U.S.))
Class8=CMyView
Class9=CMyFrame
Resource10=IDR_RIGHT_CLICK
Resource11=IDR_MYTYPE
Resource12=IDR_TOOLBAR1 (English (U.S.))
Resource13=IDD_ABOUTBOX (English (U.S.))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=ID_FINDPOPUP

[CLS:CMymenuApp]
Type=0
BaseClass=CWinApp
HeaderFile=mymenu.h
ImplementationFile=mymenu.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=mymenu.cpp
ImplementationFile=mymenu.cpp
LastObject=CAboutDlg

[CLS:CMymenuDoc]
Type=0
BaseClass=CDocument
HeaderFile=mymenuDoc.h
ImplementationFile=mymenuDoc.cpp

[CLS:CMymenuView]
Type=0
BaseClass=CView
HeaderFile=mymenuView.h
ImplementationFile=mymenuView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CMymenuView

[CLS:CToolBarEx]
Type=0
BaseClass=CToolBar
HeaderFile=ToolBarEx.h
ImplementationFile=ToolBarEx.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_ENABLE
Command10=ID_DISABLE
CommandCount=10

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=ID_HOMEPAGE
Command2=ID_WINDOW_NEW
Command3=ID_ZOOM
Command4=ID_NEW
Command5=ID_TILE
Command6=ID_JUNK
CommandCount=6

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MYMENUTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_ZOOM
Command12=ID_REMOVE_ZOOM
Command13=ID_ENABLE
Command14=ID_DISABLE
Command15=ID_ADD_MENU_OPTIONS
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_DEFAULT
Command21=ID_MENU2
Command22=ID_NEW_DOC_TEMPLATE
Command23=ID_ZOOMS
Command24=ID_NET
Command25=ID_ZOOMS
Command26=ID_MEDIA
Command27=ID_ADDTESTMENU
Command28=ID_ADDTOOLSMENU
Command29=ID_WINDOW_NEW
Command30=ID_WINDOW_CASCADE
Command31=ID_WINDOW_TILE_HORZ
Command32=ID_COLOREDSQUARE
Command33=ID_HATCHEDSQUARE
Command34=ID_SMALLCOLOREDSQUARE
Command35=ID_APP_ABOUT
Command36=ID_HOMEPAGE
CommandCount=36

[MNU:IDR_RIGHT_CLICK]
Type=1
Class=?
Command1=ID_ZOOM
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_HOMEPAGE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_ZOOM
CommandCount=14

[MNU:IDR_MYMENUTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_ZOOM
Command12=ID_REMOVE_ZOOM
Command13=ID_3DBITMAPS
Command14=ID_PICKDISABLED
Command15=ID_ENABLE
Command16=ID_DISABLE
Command17=ID_ADD_MENU_OPTIONS
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_DEFAULT
Command23=ID_MENU2
Command24=ID_NEW_DOC_TEMPLATE
Command25=ID_ZOOMS
Command26=ID_NET
Command27=ID_ZOOMS
Command28=ID_MEDIA
Command29=ID_ADDTESTMENU
Command30=ID_ADDTOOLSMENU
Command31=ID_JUNK1
Command32=ID_JUNK2
Command33=ID_WINDOW_NEW
Command34=ID_WINDOW_CASCADE
Command35=ID_WINDOW_TILE_HORZ
Command36=ID_COLOREDSQUARE
Command37=ID_HATCHEDSQUARE
Command38=ID_SMALLCOLOREDSQUARE
Command39=ID_APP_ABOUT
Command40=ID_HOMEPAGE
Command41=ID_FINDPOPUP
CommandCount=41

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_ENABLE
Command10=ID_DISABLE
CommandCount=10

[TB:IDR_TOOLBAR (English (U.S.))]
Type=1
Class=?
Command1=ID_HOMEPAGE
Command2=ID_WINDOW_NEW
Command3=ID_ZOOM
Command4=ID_NEW
Command5=ID_TILE
Command6=ID_JUNK
CommandCount=6

[MNU:IDR_RIGHT_CLICK (English (U.S.))]
Type=1
Class=?
Command1=ID_ZOOM
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_HOMEPAGE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
CommandCount=7

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_ZOOM
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CMyView]
Type=0
HeaderFile=MyView.h
ImplementationFile=MyView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CMyView

[CLS:CMyFrame]
Type=0
HeaderFile=MyFrame.h
ImplementationFile=MyFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC
LastObject=ID_NEW_DOC_TEMPLATE

[MNU:IDR_MYTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_FILE_SAVE_AS
Command12=ID_ZOOM
Command13=ID_REMOVE_ZOOM
Command14=ID_DEFAULT
Command15=ID_NEW_DOC_TEMPLATE
Command16=ID_WINDOW_NEW
Command17=ID_WINDOW_CASCADE
Command18=ID_WINDOW_TILE_HORZ
Command19=ID_APP_ABOUT
Command20=ID_HOMEPAGE
CommandCount=20

[MNU:IDR_MYTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_FILE_SAVE_AS
Command12=ID_ZOOM
Command13=ID_REMOVE_ZOOM
Command14=ID_DEFAULT
Command15=ID_NEW_DOC_TEMPLATE
Command16=ID_WINDOW_NEW
Command17=ID_WINDOW_CASCADE
Command18=ID_WINDOW_TILE_HORZ
Command19=ID_APP_ABOUT
Command20=ID_HOMEPAGE
CommandCount=20

[TB:IDR_TOOLBAR1 (English (U.S.))]
Type=1
Command1=ID_HOMEPAGE
Command2=ID_WINDOW_NEW
Command3=ID_ZOOM
Command4=ID_NEW
Command5=ID_TILE
Command6=ID_JUNK
Command7=ID_MEDIA
CommandCount=7

