// AGmagicUtilUI.h : main header file for the AGmagicUtilUI DLL
//

#if !defined(AGMAGICUTILUI_PRJ_H__2CE70461_E004_4004_B6B0_9157096CA75F__INCLUDED_)
#define AGMAGICUTILUI_PRJ_H__2CE70461_E004_4004_B6B0_9157096CA75F__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

/*************************************Define chung-bat buoc phai co*********************/

#include "../../../include/AGmagicDefs.h"
#define	AGMAGICUTILUI_LIBRARY_SERIAL_KEY		_T("")

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

#pragma message(_T("Automatically linking with AGmagicUtilUI library"))
#pragma comment(lib, _T( "../../../../agutil/output/AGmagicUtil.lib"))

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
// CAGmagicUtilUIDllApp
// See AGmagicUtilUI.cpp for the implementation of this class
//
class CAGmagicUtilUIDllApp : public CWinApp
{
public:
	CAGmagicUtilUIDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicUtilUIDllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAGmagicUtilUIDllApp)
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

#endif // !defined(AGMAGICUTILUI_PRJ_H__2CE70461_E004_4004_B6B0_9157096CA75F__INCLUDED_)
