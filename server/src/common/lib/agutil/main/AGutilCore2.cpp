#include "AGutilCore2.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/*******************************class CTwain*******************************/

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
#if AGMAGIC_SUPPORT_MFC
#include "../../sys/Twain/TwainCpp.cpp"
#endif
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
