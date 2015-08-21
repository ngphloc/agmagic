// AGmagicISUI.h : main header file for the AGmagicISUI DLL
//

#if !defined(AGMAGICISUI_PRJ_H__796650BC_8192_4293_B249_09170736870C__INCLUDED_)
#define AGMAGICISUI_PRJ_H__796650BC_8192_4293_B249_09170736870C__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

/*************************************Define va import chung-bat buoc phai co*********************/
#include "../../../common/include/AGmagicDefs.h"
#define	AGMAGICISUI_LIBRARY_SERIAL_KEY		_T("")

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
#pragma message(_T("Automatically linking with AGmagicUtil library"))
#pragma comment(lib, _T( "../../../../../common/lib/agutil/output/AGmagicUtil.lib"))

#pragma message(_T("Automatically linking with AGmagicUtilUI library"))
#pragma comment(lib, _T( "../../../../../common/lib/agutilui/output/AGmagicUtilUI.lib"))

#pragma message(_T("Automatically linking with AGmagicIP library"))
#pragma comment(lib, _T( "../../../../ip/output/AGmagicIP.lib"))

#pragma message(_T("Automatically linking with AGmagicIPUI library"))
#pragma comment(lib, _T( "../../../../ipui/output/AGmagicIPUI.lib"))

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
// CAGmagicISUIDllApp
// See AGmagicISUI.cpp for the implementation of this class
//

class CAGmagicISUIDllApp : public CWinApp
{
public:
	CAGmagicISUIDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicISUIDllApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAGmagicISUIDllApp)
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

#endif // !defined(AGMAGICISUI_PRJ_H__796650BC_8192_4293_B249_09170736870C__INCLUDED_)
