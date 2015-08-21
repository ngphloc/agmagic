; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgToolStatusBarDlg
LastTemplate=CStatusBarCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DlgToolStatusBar.h"

ClassCount=8
Class1=CDlgToolStatusBarApp
Class2=CDlgToolStatusBarDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MENU1
Resource4=IDD_DLGTOOLSTATUSBAR_DIALOG
Class4=CMyToolBar
Class5=CMyStatusBar
Class6=CToolBarControl
Class7=CStatusBarControl
Class8=CStatusControl
Resource5=IDM_TOOLBAR

[CLS:CDlgToolStatusBarApp]
Type=0
HeaderFile=DlgToolStatusBar.h
ImplementationFile=DlgToolStatusBar.cpp
Filter=N

[CLS:CDlgToolStatusBarDlg]
Type=0
HeaderFile=DlgToolStatusBarDlg.h
ImplementationFile=DlgToolStatusBarDlg.cpp
Filter=D
LastObject=IDC_EXPLORER1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=DlgToolStatusBarDlg.h
ImplementationFile=DlgToolStatusBarDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_DLGTOOLSTATUSBAR_DIALOG]
Type=1
Class=CDlgToolStatusBarDlg
ControlCount=0

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_EXIT
Command2=ID_FLAT_TOOLBAR1
Command3=ID_STANDARD_TOOLBAR1
Command4=ID_VIEWSORT_TOOLBAR1
Command5=IDD_ABOUTBOX
CommandCount=5

[TB:IDM_TOOLBAR]
Type=1
Class=?
Command1=ID_BUTTON32773
CommandCount=1

[CLS:CMyToolBar]
Type=0
HeaderFile=MyToolBar.h
ImplementationFile=MyToolBar.cpp
BaseClass=CToolBarCtrl
Filter=W

[CLS:CMyStatusBar]
Type=0
HeaderFile=MyStatusBar.h
ImplementationFile=MyStatusBar.cpp
BaseClass=CStatusBarCtrl
Filter=W
VirtualFilter=WC
LastObject=CMyStatusBar

[CLS:CToolBarControl]
Type=0
HeaderFile=ToolBarControl.h
ImplementationFile=ToolBarControl.cpp
BaseClass=CToolBarCtrl
Filter=W

[CLS:CStatusBarControl]
Type=0
HeaderFile=StatusBarControl.h
ImplementationFile=StatusBarControl.cpp
BaseClass=CStatusBarCtrl
Filter=W

[CLS:CStatusControl]
Type=0
HeaderFile=StatusControl.h
ImplementationFile=StatusControl.cpp
BaseClass=CStatusBarCtrl
Filter=W
LastObject=CStatusControl

