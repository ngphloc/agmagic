#if !defined(AFX_CHILDFRM_H__40806ABB_8526_41AE_97BE_391F5574CD28__INCLUDED_)
#define AFX_CHILDFRM_H__40806ABB_8526_41AE_97BE_391F5574CD28__INCLUDED_

// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef AGMAGIC_DECL
class CChildFrame : public CMDIChildWnd
#else
class AGMAGIC_DECL CChildFrame : public CMDIChildWnd
#endif	//AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_CHILDFRM_H__40806ABB_8526_41AE_97BE_391F5574CD28__INCLUDED_)
