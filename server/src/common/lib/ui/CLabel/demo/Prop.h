#if !defined(AFX_PROP_H__E8A72AA2_6E56_11D2_84F8_0060970C2D45__INCLUDED_)
#define AFX_PROP_H__E8A72AA2_6E56_11D2_84F8_0060970C2D45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Prop.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProp dialog

class CProp : public CPropertyPage
{
	DECLARE_DYNCREATE(CProp)

// Construction
public:
	CProp();
	~CProp();

// Dialog Data
	//{{AFX_DATA(CProp)
	enum { IDD = IDD_PROPPAGE_MEDIUM };
	CLabel	m_stc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProp)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROP_H__E8A72AA2_6E56_11D2_84F8_0060970C2D45__INCLUDED_)
