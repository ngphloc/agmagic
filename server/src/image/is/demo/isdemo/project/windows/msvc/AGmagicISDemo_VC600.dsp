# Microsoft Developer Studio Project File - Name="AGmagicISDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AGmagicISDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AGmagicISDemo_VC600.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AGmagicISDemo_VC600.mak" CFG="AGmagicISDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AGmagicISDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AGmagicISDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AGmagicISDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../output"
# PROP Intermediate_Dir "../../../output"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../../../../../../../../bin/AGmagicISDemo.exe"

!ELSEIF  "$(CFG)" == "AGmagicISDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../output"
# PROP Intermediate_Dir "../../../output"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../../../../../../../../bin/AGmagicISDemo.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AGmagicISDemo - Win32 Release"
# Name "AGmagicISDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\AGmagicISDemo_prj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\AGmagicISDemoSE.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\AGmagicISDemoUI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\AGmagicISDemoUIRC.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\AGmagicISDemo_prj.h
# End Source File
# Begin Source File

SOURCE=..\..\..\main\AGmagicISDemoSE.h
# End Source File
# Begin Source File

SOURCE=..\..\..\main\AGmagicISDemoUI.h
# End Source File
# Begin Source File

SOURCE=..\..\..\main\AGmagicISDemoUIRC.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\..\main\res\searchcontrolbar\bg2.jpg
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\browse_down.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\browse_gray.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\browse_mask.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\browse_norm.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\browse_over.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\dialogsk\clk.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\clockst\ClockST_big.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\clockst\ClockST_pane.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\clockst\ClockST_small.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\xinfotip\default_tip.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\eyeblue.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\eyeclosed.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\eyeclosed_focus.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\eyegray.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\eyegreen.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\eyemask.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\eyered.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\pictureex\eyes.gif
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\feedback_down.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\feedback_gray.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\feedback_mask.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\feedback_norm.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\feedback_over.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchcontrolbar\hand_p.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\xinfotip\info_tip.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\isdemo_main.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\ldown.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\lgray.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\lmask.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\lnorm.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\lover.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\move_number.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\movefirst.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\movelast.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\movenext.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\moveprevious.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number01.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number02.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number03.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number04.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number05.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number06.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number07.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number08.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number09.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\searchresulttoolbar\number10.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\xinfotip\question_tip.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\rdown.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\rgray.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\rmask.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\rnorm.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\main\res\skinbutton\rover.bmp
# End Source File
# End Group
# End Target
# End Project
