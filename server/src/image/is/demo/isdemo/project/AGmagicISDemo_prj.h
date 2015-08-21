// AGmagicISDemo.h : main header file for the AGMAGICISDEMO application
//

#if !defined(AGMAGICISDEMO_PRJ_H__5C7EBF63_BD41_11D2_84B2_00C0DFF84685__INCLUDED_)
#define AGMAGICISDEMO_PRJ_H__5C7EBF63_BD41_11D2_84B2_00C0DFF84685__INCLUDED_

#include "../../../../../common/include/AGmagicDefs.h"

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

/*************************************Define va import chung-bat buoc phai co*********************/

#define	AGMAGICISDEMO_EXCUTABLE_SERIAL_KEY		_T("")

/********************************************************************/

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
#if AGMAGIC_SUPPORT_MFC
//Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_AFXDLL,_MBCS
//bat buoc phai define truoc
#if AGMAGIC_MFC_VER <= 0x0710
#pragma message(_T("Automatically linking with AGmagicUtil library"))
#pragma comment(lib, _T( "../../../../../../../common/lib/agutil/output/AGmagicUtil.lib"))
#pragma message(_T("Automatically linking with AGmagicUtilUI library"))
#pragma comment(lib, _T( "../../../../../../../common/lib/agutilui/output/AGmagicUtilUI.lib"))

#pragma message(_T("Automatically linking with AGmagicIP library"))
#pragma comment(lib, _T( "../../../../../../ip/output/AGmagicIP.lib"))
#pragma message(_T("Automatically linking with AGmagicIPUI library"))
#pragma comment(lib, _T( "../../../../../../ipui/output/AGmagicIPUI.lib"))

#pragma message(_T("Automatically linking with AGmagicIS library"))
#pragma comment(lib, _T( "../../../../../../is/output/AGmagicIS.lib"))
#pragma message(_T("Automatically linking with AGmagicISUI library"))
#pragma comment(lib, _T( "../../../../../../isui/output/AGmagicISUI.lib"))
#else //AGMAGIC_MFC_VER
#pragma message(_T("Automatically linking with AGmagicUtil library"))
#pragma comment(lib, _T( "../../../../../../../common/lib/agutil/output/AGmagicUtil.lib"))

#pragma message(_T("Automatically linking with AGmagicIP library"))
#pragma comment(lib, _T( "../../../../../../ip/output/AGmagicIP.lib"))

#pragma message(_T("Automatically linking with AGmagicIS library"))
#pragma comment(lib, _T( "../../../../../../is/output/AGmagicIS.lib"))

#endif //AGMAGIC_MFC_VER

#else //AGMAGIC_SUPPORT_MFC
//Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_MBCS
//bat buoc phai define truoc
	#error _T("Implement not yet")
#endif //AGMAGIC_SUPPORT_MFC

#elif AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
	#error _T("Implement not yet")
#elif AGMAGIC_OS_TYPE==AGMAGIC_LINUX_OS
	#error _T("Implement not yet")
#elif AGMAGIC_OS_TYPE==AGMAGIC_UNIX_OS
	#error _T("Implement not yet")
#else
	#error _T("Implement not yet")
#endif

#endif // !defined(AGMAGICISDEMO_PRJ_H__5C7EBF63_BD41_11D2_84B2_00C0DFF84685__INCLUDED_)
