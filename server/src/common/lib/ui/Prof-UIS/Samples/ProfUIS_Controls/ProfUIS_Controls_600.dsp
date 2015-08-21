# Microsoft Developer Studio Project File - Name="ProfUIS_Controls" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ProfUIS_Controls - Win32 MBCS Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProfUIS_Controls_600.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProfUIS_Controls_600.mak" CFG="ProfUIS_Controls - Win32 MBCS Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProfUIS_Controls - Win32 ANSI Release" (based on "Win32 (x86) Application")
!MESSAGE "ProfUIS_Controls - Win32 ANSI Debug" (based on "Win32 (x86) Application")
!MESSAGE "ProfUIS_Controls - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "ProfUIS_Controls - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "ProfUIS_Controls - Win32 MBCS Debug" (based on "Win32 (x86) Application")
!MESSAGE "ProfUIS_Controls - Win32 MBCS Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProfUIS_Controls - Win32 ANSI Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\AnsiRelease\ProfUIS_Controls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/ProfUIS_Controls-n.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "ProfUIS_Controls - Win32 ANSI Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\AnsiDebug\ProfUIS_Controls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/ProfUIS_Controls-nd.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "ProfUIS_Controls - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ProfUIS_Controls___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "ProfUIS_Controls___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\UnicodeDebug\ProfUIS_Controls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_UNICODE" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/ProfUIS_Controls-d.exe" /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/ProfUIS_Controls-ud.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "ProfUIS_Controls - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ProfUIS_Controls___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "ProfUIS_Controls___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\UnicodeRelease\ProfUIS_Controls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_UNICODE" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"..\..\Bin_600/ProfUIS_Controls-u.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "ProfUIS_Controls - Win32 MBCS Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ProfUIS_Controls___Win32_MBCS_Debug"
# PROP BASE Intermediate_Dir "ProfUIS_Controls___Win32_MBCS_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\MbcsDebug\ProfUIS_Controls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/ProfUIS_Controls-d.exe" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/ProfUIS_Controls-md.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "ProfUIS_Controls - Win32 MBCS Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ProfUIS_Controls___Win32_MBCS_Release"
# PROP BASE Intermediate_Dir "ProfUIS_Controls___Win32_MBCS_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\MbcsRelease\ProfUIS_Controls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/ProfUIS_Controls-m.exe" /libpath:"..\..\Bin_600"

!ENDIF 

# Begin Target

# Name "ProfUIS_Controls - Win32 ANSI Release"
# Name "ProfUIS_Controls - Win32 ANSI Debug"
# Name "ProfUIS_Controls - Win32 Unicode Debug"
# Name "ProfUIS_Controls - Win32 Unicode Release"
# Name "ProfUIS_Controls - Win32 MBCS Debug"
# Name "ProfUIS_Controls - Win32 MBCS Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\IconListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PageButtons.cpp
# End Source File
# Begin Source File

SOURCE=.\PageCalendar.cpp
# End Source File
# Begin Source File

SOURCE=.\PageNotAvailable.cpp
# End Source File
# Begin Source File

SOURCE=.\PagePopupMenus.cpp
# End Source File
# Begin Source File

SOURCE=.\PageStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTabContainers.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTabWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\PageToolbars.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfUIS_Controls.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfUIS_Controls.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\IconListBox.h
# End Source File
# Begin Source File

SOURCE=.\MainDlg.h
# End Source File
# Begin Source File

SOURCE=.\PageBase.h
# End Source File
# Begin Source File

SOURCE=.\PageButtons.h
# End Source File
# Begin Source File

SOURCE=.\PageCalendar.h
# End Source File
# Begin Source File

SOURCE=.\PageNotAvailable.h
# End Source File
# Begin Source File

SOURCE=.\PagePopupMenus.h
# End Source File
# Begin Source File

SOURCE=.\PageStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\PageTabContainers.h
# End Source File
# Begin Source File

SOURCE=.\PageTabWindow.h
# End Source File
# Begin Source File

SOURCE=.\PageToolbars.h
# End Source File
# Begin Source File

SOURCE=.\ProfUIS_Controls.h
# End Source File
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

SOURCE=.\res\checkbox_cross.bmp
# End Source File
# Begin Source File

SOURCE=.\res\checkbox_xp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\checkbox_xp_blue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\colorctrl.ico
# End Source File
# Begin Source File

SOURCE=.\res\download.avi
# End Source File
# Begin Source File

SOURCE=.\res\edit.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\IconForPopupMenu.ico
# End Source File
# Begin Source File

SOURCE=.\res\IconIn.ico
# End Source File
# Begin Source File

SOURCE=.\res\IconOut.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDI_BUTTONS.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDI_CALENDAR.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDI_MENU.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDI_MENU_TOOLBAR.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDI_STATUS_BAR.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDI_TAB_CONTAINER.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDI_TAB_WINDOW.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDR_EDIT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDR_MAIN_TOOLBAR.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDR_TOOLBAR_PALETTE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LedOff.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedOn.ico
# End Source File
# Begin Source File

SOURCE=.\res\Notepad.ico
# End Source File
# Begin Source File

SOURCE=.\res\ProfUIS_Controls.ico
# End Source File
# Begin Source File

SOURCE=.\res\ProfUIS_Controls.rc2
# End Source File
# Begin Source File

SOURCE=.\res\radiobox_xp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\radiobox_xp_blue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\radiobox_xp_cross.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tab_imag.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TOOLBAR_2_16bit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree.ico
# End Source File
# Begin Source File

SOURCE=.\res\xptheme.bin
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\manifest.xml
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
