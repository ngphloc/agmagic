#if !defined(AFX_MYVIEW_H__AB5EEB71_8583_11D3_A194_0050040557FE__INCLUDED_)
#define AFX_MYVIEW_H__AB5EEB71_8583_11D3_A194_0050040557FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyView view

class CMyView : public CView
{
protected:
	CMyView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYVIEW_H__AB5EEB71_8583_11D3_A194_0050040557FE__INCLUDED_)
