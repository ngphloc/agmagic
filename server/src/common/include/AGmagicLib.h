#if !defined(AGMAGIC_LIB_H__84245237_A336_11D2_84B1_00C0DFF84685__INCLUDED_)
#define AGMAGIC_LIB_H__84245237_A336_11D2_84B1_00C0DFF84685__INCLUDED_

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

#if AGMAGIC_SUPPORT_MFC

#if AGMAGIC_MFC_VER < 0x0700

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxtempl.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#if !AGMAGIC_SUPPORT_ADO
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT
	
#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT
#endif

#else	//AGMAGIC_MFC_VER >= 0x0700

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#include "AGmagicOSVer.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#include <afxsock.h>		// MFC socket extensions
#include <afxtempl.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#if !AGMAGIC_SUPPORT_ADO
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT
#endif	//#if !AGMAGIC_SUPPORT_ADO

#endif	//#if AGMAGIC_MFC_VER <= 0x0600

#else	//#if AGMAGIC_SUPPORT_MFC
	
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shlwapi.lib")
//#pragma comment(lib, "ole32.lib")
//#pragma comment(lib, "oleaut32.lib")
//#pragma comment(lib, "uuid.lib")
//#pragma comment(lib, "odbc32.lib")
//#pragma comment(lib, "odbccp32.lib")

#if AGMAGIC_MFC_VER != _MFC_VER
#error "AGMAGIC_MFC_VER != _MFC_VER"
#endif //AGMAGIC_MFC_VER != _MFC_VER

#endif	//#if AGMAGIC_SUPPORT_MFC

#if (defined(_MSC_VER)) && (AGMAGIC_DEV_ENV_VER != _MSC_VER)
#undef AGMAGIC_DEV_ENV_VER
#define AGMAGIC_DEV_ENV_VER		_MSC_VER
#endif
	
//ho tro com
#include <comdef.h>
#elif AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
	#error _T("Implement not yet")
#elif AGMAGIC_OS_TYPE==AGMAGIC_UNIX_OS
	#error _T("Implement not yet")
#elif AGMAGIC_OS_TYPE==AGMAGIC_LINUX_OS
	#error _T("Implement not yet")
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	
#endif // !defined(AGMAGIC_LIB_H__84245237_A336_11D2_84B1_00C0DFF84685__INCLUDED_)
