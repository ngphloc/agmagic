# Microsoft Developer Studio Project File - Name="MDI_InnerOuterBars" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MDI_InnerOuterBars - Win32 Static MBCS Debug with MFC DLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MDI_InnerOuterBars_600.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MDI_InnerOuterBars_600.mak" CFG="MDI_InnerOuterBars - Win32 Static MBCS Debug with MFC DLL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MDI_InnerOuterBars - Win32 ANSI Release" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 ANSI Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 MBCS Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 MBCS Release" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static ANSI Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static ANSI Release" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static MBCS Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static MBCS Release" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static ANSI Debug with MFC DLL" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static ANSI Release with MFC DLL" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static Unicode Debug with MFC DLL" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static Unicode Release with MFC DLL" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static MBCS Debug with MFC DLL" (based on "Win32 (x86) Application")
!MESSAGE "MDI_InnerOuterBars - Win32 Static MBCS Release with MFC DLL" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MDI_InnerOuterBars - Win32 ANSI Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\AnsiRelease\MDI_InnerOuterBars"
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-n.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 ANSI Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\AnsiDebug\MDI_InnerOuterBars"
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
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-nd.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\UnicodeDebug\MDI_InnerOuterBars"
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
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-d.exe" /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-ud.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\UnicodeRelease\MDI_InnerOuterBars"
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
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-u.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 MBCS Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_MBCS_Debug"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_MBCS_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\MbcsDebug\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-d.exe" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-md.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 MBCS Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_MBCS_Release"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_MBCS_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\MbcsRelease\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-m.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static ANSI Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_Debug"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticAnsiDebug\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-d.exe" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-snd.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static ANSI Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_Release"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticAnsiRelease\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-sn.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static Unicode Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_Unicode_Debug"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticUnicodeDebug\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-sd.exe" /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-sud.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static Unicode Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_Unicode_Release"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticUnicodeRelease\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-s.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-su.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static MBCS Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_MBCS_Debug"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_MBCS_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticMbcsDebug\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-sd.exe" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-smd.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static MBCS Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_MBCS_Release"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_MBCS_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticMbcsRelease\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-s.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-sm.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static ANSI Debug with MFC DLL"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_Debug_with_MFC_DLL"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_Debug_with_MFC_DLL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticAnsiDebugWithMfcDll\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "__STATPROFUIS_WITH_DLLMFC__" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-snd.exe" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-ynd.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static ANSI Release with MFC DLL"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_Release_with_MFC_DLL"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_Release_with_MFC_DLL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticAnsiReleaseWithMfcDll\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "__STATPROFUIS_WITH_DLLMFC__" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-sn.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-yn.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static Unicode Debug with MFC DLL"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_Unicode_Debug_with_MFC_DLL"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_Unicode_Debug_with_MFC_DLL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticUnicodeDebugWithMfcDll\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_UNICODE" /D "__STATPROFUIS_WITH_DLLMFC__" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-sud.exe" /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-yud.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static Unicode Release with MFC DLL"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_Unicode_Release_with_MFC_DLL"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_Unicode_Release_with_MFC_DLL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticUnicodeReleaseWithMfcDll\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_UNICODE" /D "__STATPROFUIS_WITH_DLLMFC__" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-su.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-yu.exe" /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static MBCS Debug with MFC DLL"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_MBCS_Debug_with_MFC_DLL"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_MBCS_Debug_with_MFC_DLL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticMbcsDebugWithMfcDll\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "__STATPROFUIS_WITH_DLLMFC__" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-smd.exe" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-ymd.exe" /pdbtype:sept /libpath:"..\..\Bin_600"

!ELSEIF  "$(CFG)" == "MDI_InnerOuterBars - Win32 Static MBCS Release with MFC DLL"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MDI_InnerOuterBars___Win32_Static_MBCS_Release_with_MFC_DLL"
# PROP BASE Intermediate_Dir "MDI_InnerOuterBars___Win32_Static_MBCS_Release_with_MFC_DLL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin_600"
# PROP Intermediate_Dir "..\..\Bin_600\StaticMbcsReleaseWithMfcDll\MDI_InnerOuterBars"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "__STATPROFUIS_WITH_DLLMFC__" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D _WIN32_IE=0x0400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-sm.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin_600/MDI_InnerOuterBars-ym.exe" /libpath:"..\..\Bin_600"

!ENDIF 

# Begin Target

# Name "MDI_InnerOuterBars - Win32 ANSI Release"
# Name "MDI_InnerOuterBars - Win32 ANSI Debug"
# Name "MDI_InnerOuterBars - Win32 Unicode Debug"
# Name "MDI_InnerOuterBars - Win32 Unicode Release"
# Name "MDI_InnerOuterBars - Win32 MBCS Debug"
# Name "MDI_InnerOuterBars - Win32 MBCS Release"
# Name "MDI_InnerOuterBars - Win32 Static ANSI Debug"
# Name "MDI_InnerOuterBars - Win32 Static ANSI Release"
# Name "MDI_InnerOuterBars - Win32 Static Unicode Debug"
# Name "MDI_InnerOuterBars - Win32 Static Unicode Release"
# Name "MDI_InnerOuterBars - Win32 Static MBCS Debug"
# Name "MDI_InnerOuterBars - Win32 Static MBCS Release"
# Name "MDI_InnerOuterBars - Win32 Static ANSI Debug with MFC DLL"
# Name "MDI_InnerOuterBars - Win32 Static ANSI Release with MFC DLL"
# Name "MDI_InnerOuterBars - Win32 Static Unicode Debug with MFC DLL"
# Name "MDI_InnerOuterBars - Win32 Static Unicode Release with MFC DLL"
# Name "MDI_InnerOuterBars - Win32 Static MBCS Debug with MFC DLL"
# Name "MDI_InnerOuterBars - Win32 Static MBCS Release with MFC DLL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MDI_InnerOuterBars.cpp
# End Source File
# Begin Source File

SOURCE=.\MDI_InnerOuterBars.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MDI_InnerOuterBars.h
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

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_MDI_InnerOuterBarst.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_mdit.ico
# End Source File
# Begin Source File

SOURCE=.\res\MDI_InnerOuterBars.ico
# End Source File
# Begin Source File

SOURCE=.\res\MDI_InnerOuterBars.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
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
