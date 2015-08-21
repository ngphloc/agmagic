// AGmagicIP.h : main header file for the AGmagicIP DLL
//

#if !defined(AGMAGICIP_PRJ_H__E98F71A6_B361_11D6_BB83_CAEE2E1CB77B__INCLUDED_)
#define AGMAGICIP_PRJ_H__E98F71A6_B361_11D6_BB83_CAEE2E1CB77B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*************************************Define va import chung-bat buoc phai co*********************/

#include "../../../common/include/AGmagicDefs.h"
#define	AGMAGICIP_LIBRARY_SERIAL_KEY		_T("")
#include "../main/AGimageDefs.h"

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

#pragma message(_T("Automatically linking with AGmagicUtil library"))
#pragma comment(lib, _T( "../../../../../common/lib/agutil/output/AGmagicUtil.lib"))

#pragma message(_T("Automatically linking with cximage library"))
#pragma comment(lib, AG_LIB_PATH_CXIMAGE)

#pragma message(_T("Automatically linking with j2k library"))
#pragma comment(lib, AG_LIB_PATH_J2K)

#pragma message(_T("Automatically linking with jasper library"))
#pragma comment(lib, AG_LIB_PATH_JASPER)

#pragma message(_T("Automatically linking with jbig library"))
#pragma comment(lib, AG_LIB_PATH_JBIG)

#pragma message(_T("Automatically linking with Jpeg library"))
#pragma comment(lib, AG_LIB_PATH_JPEG)

#pragma message(_T("Automatically linking with mng library"))
#pragma comment(lib, AG_LIB_PATH_MNG)

#pragma message(_T("Automatically linking with png library"))
#pragma comment(lib, AG_LIB_PATH_PNG)

#pragma message(_T("Automatically linking with Tiff library"))
#pragma comment(lib, AG_LIB_PATH_TIFF)

#pragma message(_T("Automatically linking with zlib library"))
#pragma comment(lib, AG_LIB_PATH_ZLIB)

#else	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
#error _T("Implement not yet")
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

/*************************************Dinh nghia cac thu vien*********************/

#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)
//Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_USRDLL,_MBCS,JAS_WIN_MSVC_BUILD
//bat buoc phai define truoc

// Insert your headers here

//Regular MFC DLL (using static DLL or shared DLL)
#elif (AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_REGULAR_STATIC_MFC_DLL || AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_REGULAR_SHARED_MFC_DLL)	//#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)

#if (AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_REGULAR_STATIC_MFC_DLL)
//Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_WINDLL,_USRDLL,_MBCS,JAS_WIN_MSVC_BUILD
//bat buoc phai define truoc
#endif	//#if (AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_REGULAR_STATIC_MFC_DLL)

#if (AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_REGULAR_SHARED_MFC_DLL)
//Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_WINDLL,_AFXDLL,_MBCS,JAS_WIN_MSVC_BUILD
//bat buoc phai define truoc
#endif	//#if (AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_REGULAR_SHARED_MFC_DLL)

/////////////////////////////////////////////////////////////////////////////
// CAGmagicIPDllApp
// See AGmagicIP.cpp for the implementation of this class
//
class CAGmagicIPDllApp : public CWinApp
{
public:
	CAGmagicIPDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicIPDllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAGmagicIPDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//Extension MFC DLL (using shared DLL)
#elif (AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_EXTENSION_MFC_DLL)	//#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)
//Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_WINDLL,_AFXDLL,_MBCS,JAS_WIN_MSVC_BUILD,_AFXEXT
//bat buoc phai define truoc


#else	//#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)
#error _T("Not support this dll type")
#endif	//#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AGMAGICIP_PRJ_H__E98F71A6_B361_11D6_BB83_CAEE2E1CB77B__INCLUDED_)
