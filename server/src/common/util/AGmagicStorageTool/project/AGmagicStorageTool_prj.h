
#if !defined(AGMAGICSTORAGETOOL_PRJ_H__D8D66CEE_2868_416B_965A_BFE6C577D996__INCLUDED_)
#define AGMAGICSTORAGETOOL_PRJ_H__D8D66CEE_2868_416B_965A_BFE6C577D996__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

/*************************************Define chung-bat buoc phai co*********************/

#include "../../../../common/include/AGmagicDefs.h"
#define	AGMAGICSTORAGETOOL_BINARY_SERIAL_KEY		_T("")

/*************************************Dinh nghia cac thu vien*********************/

#if(AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS)
//Preprocessor difinitions: WIN32,_DEBUG,_CONSOLE,_MBCS,_AFXDLL
//bat buoc phai define truoc
#pragma message(_T("Automatically linking with AGmagicUtil library"))
#pragma comment(lib, _T( "../../../../../lib/agutil/output/AGmagicUtil.lib"))

#else	//#if(AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS)
#error _T("Implement not yet")
#endif	//#if(AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS)


#endif // !defined(AGMAGICSTORAGETOOL_PRJ_H__D8D66CEE_2868_416B_965A_BFE6C577D996__INCLUDED_)
