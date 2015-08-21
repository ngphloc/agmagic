#include "AGmagicUI2.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/******************************class CPPToolTip************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../ui/PPTooltip/PPTooltip.cpp"
#include "../../ui/PPTooltip/PPHtmlDrawer.cpp"
#include "../../ui/PPTooltip/PPDrawManager.cpp"
#include "../../ui/PPTooltip/CeXDib.cpp"
#endif	//#if AGMAGIC_SUPPORT_MFC
