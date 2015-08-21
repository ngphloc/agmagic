# Microsoft Developer Studio Project File - Name="COptionTree" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=COptionTree - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "COptionTree.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "COptionTree.mak" CFG="COptionTree - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "COptionTree - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "COptionTree - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "COptionTree - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /I "..\COptionTree" /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\COptionTree" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "COptionTree - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\COptionTree" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\COptionTree" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "COptionTree - Win32 Release"
# Name "COptionTree - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\COptionTree.cpp
# End Source File
# Begin Source File

SOURCE=.\COptionTree.def
# End Source File
# Begin Source File

SOURCE=.\COptionTree.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\COptionTree.rc2
# End Source File
# End Group
# Begin Group "COptionTree"

# PROP Default_Filter ""
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\COptionTree\OptionTree.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeCheckButton.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeColorPopUp.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSel.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSelColorButton.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSelFontCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSelGlobals.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSelSizeCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeImagePopUp.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeIPAddressEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemCheckBox.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemColor.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemDate.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemFile.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemFont.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemHyperLink.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemImage.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemIPAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemRadio.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemSpinner.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeList.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeRadioButton.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeSpinnerButton.cpp
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeSpinnerEdit.cpp
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\COptionTree\CommonRes.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTree.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeCheckButton.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeColorPopUp.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeDef.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFileDlg.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSel.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSelColorButton.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSelFontCombo.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSelGlobals.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeFontSelSizeCombo.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeImagePopUp.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeInfo.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeIPAddressEdit.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItem.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemCheckBox.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemColor.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemComboBox.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemDate.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemEdit.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemFile.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemFont.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemHyperLink.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemImage.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemIPAddress.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemRadio.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemSpinner.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeItemStatic.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeList.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeRadioButton.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeSpinnerButton.h
# End Source File
# Begin Source File

SOURCE=..\COptionTree\OptionTreeSpinnerEdit.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
