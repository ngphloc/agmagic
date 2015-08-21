// AGmagicSP.h : main header file for the AGmagicSP DLL
//

#if !defined(AGMAGICSP_PRJ_H__306BF842_1E97_4C2F_AA46_4A31A5E242DF__INCLUDED_)
#define AGMAGICSP_PRJ_H__306BF842_1E97_4C2F_AA46_4A31A5E242DF__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

/*************************************Define chung-bat buoc phai co*********************/
#include "../../../common/include/AGmagicDefs.h"
#define	AGMAGICSP_LIBRARY_SERIAL_KEY		_T("")

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
// CAGmagicSPDllApp
// See AGmagicSP.cpp for the implementation of this class
//

class CAGmagicSPDllApp : public CWinApp
{
public:
	CAGmagicSPDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicSPDllApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAGmagicSPDllApp)
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

#endif // !defined(AGMAGICSP_PRJ_H__306BF842_1E97_4C2F_AA46_4A31A5E242DF__INCLUDED_)
