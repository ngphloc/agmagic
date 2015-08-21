#if !defined(AGMAGICISUI_H__90ABFC91_2623_4360_9E69_CC76712A9C5E__INCLUDED_)
#define AGMAGICISUI_H__90ABFC91_2623_4360_9E69_CC76712A9C5E__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "../../../common/include/AGmagicDefs.h"

/***********************************class CAGmmMainFrame**********************/

#if AGMAGIC_SUPPORT_MFC
#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../ipui/main/AGimageUI2.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"
class AGMAGIC_DECL CAGmmMainFrame : public CAGmagicIP_MDIMainFrame
{
	DECLARE_DYNAMIC(CAGmmMainFrame)

public:
	CAGmmMainFrame();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmmMainFrame)
	public:
	virtual LRESULT OnReceivedOutputNotice(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmmMainFrame();


//Attributes
public:

public:  // control bar embedded members

// Generated message map functions
protected:
	//{{AFX_MSG(CAGmmMainFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC

#endif // !defined(AGMAGICISUI_H__90ABFC91_2623_4360_9E69_CC76712A9C5E__INCLUDED_)

