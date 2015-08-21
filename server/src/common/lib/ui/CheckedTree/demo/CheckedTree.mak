# Microsoft Developer Studio Generated NMAKE File, Based on CheckedTree.dsp
!IF "$(CFG)" == ""
CFG=CheckedTree - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. CheckedTree - Win32 Debug wird als\
 Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "CheckedTree - Win32 Release" && "$(CFG)" !=\
 "CheckedTree - Win32 Debug"
!MESSAGE Ungültige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "CheckedTree.mak" CFG="CheckedTree - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "CheckedTree - Win32 Release" (basierend auf\
  "Win32 (x86) Application")
!MESSAGE "CheckedTree - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 
!ERROR Eine ungültige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CheckedTree - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CheckedTree.exe"

!ELSE 

ALL : "$(OUTDIR)\CheckedTree.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CheckedTree.obj"
	-@erase "$(INTDIR)\CheckedTree.pch"
	-@erase "$(INTDIR)\CheckedTree.res"
	-@erase "$(INTDIR)\CheckedTreeCtrl.obj"
	-@erase "$(INTDIR)\CheckedTreeDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CheckedTree.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\CheckedTree.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\CheckedTree.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CheckedTree.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\CheckedTree.pdb" /machine:I386 /out:"$(OUTDIR)\CheckedTree.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\CheckedTree.obj" \
	"$(INTDIR)\CheckedTree.res" \
	"$(INTDIR)\CheckedTreeCtrl.obj" \
	"$(INTDIR)\CheckedTreeDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CheckedTree.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CheckedTree - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CheckedTree.exe"

!ELSE 

ALL : "$(OUTDIR)\CheckedTree.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CheckedTree.obj"
	-@erase "$(INTDIR)\CheckedTree.pch"
	-@erase "$(INTDIR)\CheckedTree.res"
	-@erase "$(INTDIR)\CheckedTreeCtrl.obj"
	-@erase "$(INTDIR)\CheckedTreeDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CheckedTree.exe"
	-@erase "$(OUTDIR)\CheckedTree.ilk"
	-@erase "$(OUTDIR)\CheckedTree.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\CheckedTree.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\CheckedTree.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CheckedTree.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\CheckedTree.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\CheckedTree.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CheckedTree.obj" \
	"$(INTDIR)\CheckedTree.res" \
	"$(INTDIR)\CheckedTreeCtrl.obj" \
	"$(INTDIR)\CheckedTreeDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CheckedTree.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "CheckedTree - Win32 Release" || "$(CFG)" ==\
 "CheckedTree - Win32 Debug"
SOURCE=.\CheckedTree.cpp

!IF  "$(CFG)" == "CheckedTree - Win32 Release"

DEP_CPP_CHECK=\
	".\CheckedTree.h"\
	".\CheckedTreeCtrl.h"\
	".\CheckedTreeDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckedTree.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\CheckedTree.pch"


!ELSEIF  "$(CFG)" == "CheckedTree - Win32 Debug"

DEP_CPP_CHECK=\
	".\CheckedTree.h"\
	".\CheckedTreeCtrl.h"\
	".\CheckedTreeDlg.h"\
	

"$(INTDIR)\CheckedTree.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\CheckedTree.pch"


!ENDIF 

SOURCE=.\CheckedTree.rc
DEP_RSC_CHECKE=\
	".\res\bitmap_n.bmp"\
	".\res\bitmap_s.bmp"\
	".\res\CheckedTree.ico"\
	".\res\CheckedTree.rc2"\
	

"$(INTDIR)\CheckedTree.res" : $(SOURCE) $(DEP_RSC_CHECKE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CheckedTreeCtrl.cpp

!IF  "$(CFG)" == "CheckedTree - Win32 Release"

DEP_CPP_CHECKED=\
	".\CheckedTree.h"\
	".\CheckedTreeCtrl.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckedTreeCtrl.obj" : $(SOURCE) $(DEP_CPP_CHECKED) "$(INTDIR)"\
 "$(INTDIR)\CheckedTree.pch"


!ELSEIF  "$(CFG)" == "CheckedTree - Win32 Debug"

DEP_CPP_CHECKED=\
	".\CheckedTree.h"\
	".\CheckedTreeCtrl.h"\
	

"$(INTDIR)\CheckedTreeCtrl.obj" : $(SOURCE) $(DEP_CPP_CHECKED) "$(INTDIR)"\
 "$(INTDIR)\CheckedTree.pch"


!ENDIF 

SOURCE=.\CheckedTreeDlg.cpp

!IF  "$(CFG)" == "CheckedTree - Win32 Release"

DEP_CPP_CHECKEDT=\
	".\CheckedTree.h"\
	".\CheckedTreeCtrl.h"\
	".\CheckedTreeDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckedTreeDlg.obj" : $(SOURCE) $(DEP_CPP_CHECKEDT) "$(INTDIR)"\
 "$(INTDIR)\CheckedTree.pch"


!ELSEIF  "$(CFG)" == "CheckedTree - Win32 Debug"

DEP_CPP_CHECKEDT=\
	".\CheckedTree.h"\
	".\CheckedTreeCtrl.h"\
	".\CheckedTreeDlg.h"\
	

"$(INTDIR)\CheckedTreeDlg.obj" : $(SOURCE) $(DEP_CPP_CHECKEDT) "$(INTDIR)"\
 "$(INTDIR)\CheckedTree.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CheckedTree - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\CheckedTree.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CheckedTree.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CheckedTree - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\CheckedTree.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CheckedTree.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

