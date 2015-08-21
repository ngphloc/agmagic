#include "AGmagicISUI.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif //AGMAGIC_SUPPORT_MFC

/***********************************class CAGmmMainFrame**********************/

#if AGMAGIC_SUPPORT_MFC
IMPLEMENT_DYNAMIC(CAGmmMainFrame, CAGmagicIP_MDIMainFrame)

BEGIN_MESSAGE_MAP(CAGmmMainFrame, CAGmagicIP_MDIMainFrame)
	//{{AFX_MSG_MAP(CAGmmMainFrame)
	ON_MESSAGE(AGMAGICIP_WM_RECEIVED_OUTPUT_NOTICE, OnReceivedOutputNotice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CAGmagicIP_MDIMainFrame construction/destruction
CAGmmMainFrame::CAGmmMainFrame() : CAGmagicIP_MDIMainFrame()
{
}
CAGmmMainFrame::~CAGmmMainFrame()
{
}
LRESULT CAGmmMainFrame::OnReceivedOutputNotice(WPARAM wParam, LPARAM lParam)
{
	agtchar*					szOutputNotice=(agtchar*)lParam;
	if(szOutputNotice!=NULL)	free(szOutputNotice);
	return 0;
}
#endif //AGMAGIC_SUPPORT_MFC
