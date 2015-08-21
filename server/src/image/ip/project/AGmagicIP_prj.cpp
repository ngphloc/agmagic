// AGmagicIP.cpp : Defines the initialization routines for the DLL.
//
#include "AGmagicIP_prj.h"
#include "../main/AGimageUtil.h"

#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			AGMAGIC_LOG(_T("AGmagicIP.dll"), _T("AGmagicIP.DLL Initializing!\n"));
			AGMAGIC_LOG(_T("AGmagicIP.dll"), _T("Call  CAGmagicIPConfUtil::Init() in AGmagicIP.dll"));
			CAGmagicIPConfUtil::Init();
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

/****************************Regular MFC DLL (using shared and static DLL)*********************************/

//Regular MFC DLL (using shared and static DLL)
#elif (AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_REGULAR_STATIC_MFC_DLL || AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_REGULAR_SHARED_MFC_DLL)	//#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CAGmagicIPDllApp

BEGIN_MESSAGE_MAP(CAGmagicIPDllApp, CWinApp)
	//{{AFX_MSG_MAP(CAGmagicIPDllApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmagicIPDllApp construction

CAGmagicIPDllApp::CAGmagicIPDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAGmagicIPDllApp object
CAGmagicIPDllApp theApp;

BOOL CAGmagicIPDllApp::InitInstance()
{
	BOOL bResult = CWinApp::InitInstance();
	if(bResult)
	{
		AGMAGIC_LOG(_T("AGmagicIP.dll"), _T("Call CAGmagicConfUtil::Init() in AGmagicIP.dll"));
		TRACE0(_T("AGmagicIP.dll : Call CAGmagicIPConfUtil::Init() in AGmagicIP.dll"));
		CAGmagicIPConfUtil::Init();
	}	
	return bResult;
}

/***********************************Extension MFC DLL (using shared DLL)*********************************/

//Extension MFC DLL (using shared DLL)
#elif (AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_EXTENSION_MFC_DLL)	//#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE AGmagicIPDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
	
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0(_T("AGmagicIP.DLL Initializing!\n"));
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(AGmagicIPDLL, hInstance))
			return 0;
		
		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(AGmagicIPDLL);
		//CAGmagicIPDllSerialDlg	dllSerialDlg;
		//if(dllSerialDlg.DoModal()!=IDOK)
		//{
		//	AfxTermExtensionModule(AGmagicIPDLL);
		//	return 0;
		//}

		AGMAGIC_LOG(_T("AGmagicIP.dll"), _T("Call CAGmagicIPConfUtil::Init() in AGmagicIP.dll"));
		TRACE0(_T("AGmagicIP.dll : Call CAGmagicIPConfUtil::Init() in AGmagicIP.dll"));
		CAGmagicIPConfUtil::Init();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0(_T("AGmagicIP.DLL Terminating!\n"));
		// Terminate the library before destructors are called
		AfxTermExtensionModule(AGmagicIPDLL);

		//if(_tcslen(AGMAGICIP_LIBRARY_SERIAL_KEY)>0)
		//	AfxMessageBox(_T("Thank for use AGmagicIP DLL"),MB_OK | MB_ICONINFORMATION,0);
	}
	return 1;   // ok
}

#endif	//#if(AGMAGIC_LIBRARY_TYPE==AGMAGIC_WINDOWS_DLL)