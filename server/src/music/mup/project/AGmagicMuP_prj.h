// AGmagicMuP.h : main header file for the AGmagicMuP DLL
//

#if !defined(AGMAGICMUP_PRJ_H__3FA06185_B909_4DA7_BB59_B306B8D3E8B1__INCLUDED_)
#define AGMAGICMUP_PRJ_H__3FA06185_B909_4DA7_BB59_B306B8D3E8B1__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

/*************************************Define chung-bat buoc phai co*********************/
#include "../../../common/include/AGmagicDefs.h"
#define	AGMAGICMUP_LIBRARY_SERIAL_KEY		_T("")

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
// CAGmagicMuPDllApp
// See AGmagicMuP.cpp for the implementation of this class
//

class CAGmagicMuPDllApp : public CWinApp
{
public:
	CAGmagicMuPDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmagicMuPDllApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAGmagicMuPDllApp)
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

#endif // !defined(AGMAGICMUP_PRJ_H__3FA06185_B909_4DA7_BB59_B306B8D3E8B1__INCLUDED_)
