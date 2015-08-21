#include "AGmagicStorageTool_prj.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

#include "../main/AGsTool.h"
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

#if AGMAGIC_SUPPORT_MFC
CWinApp theApp;
#endif

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
#if AGMAGIC_SUPPORT_MFC
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
		return 1;
#endif
	AGsTool(argc,argv);
	return 0;
}
