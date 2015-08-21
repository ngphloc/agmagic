// CPPTooltip_demoView.cpp : implementation of the CPPTooltip_demoView class
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"

#include "CPPTooltip_demoDoc.h"
#include "CPPTooltip_demoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoView

IMPLEMENT_DYNCREATE(CPPTooltip_demoView, CScrollView)

BEGIN_MESSAGE_MAP(CPPTooltip_demoView, CScrollView)
	//{{AFX_MSG_MAP(CPPTooltip_demoView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
	ON_BN_CLICKED(IDC_BUTTON1, OnShowIconInTray)
	ON_BN_CLICKED(IDC_BUTTON2, OnRemoveIconFromTray)
	ON_BN_CLICKED(IDC_BUTTON3, OnShowHelpTooltip)
	ON_BN_CLICKED(IDC_BUTTON4, OnHideHelpTooltip)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoView construction/destruction

CPPTooltip_demoView::CPPTooltip_demoView()
{
	// TODO: add construction code here
	m_rect [0].SetRect(0, 200, 100, 300);
	m_rect [1].SetRect(100, 200, 200, 300);
	m_rect [2].SetRect(0, 300, 100, 400);
	m_rect [3].SetRect(100, 300, 200, 400);
	m_rect [4].SetRect(200, 0, 530, 355);

	//Creates map's hotareas
	AddCity(221, 257, 225, 261, "<h2>Brest</h2>");
	AddCity(229, 170, 233, 174, "<h2>Hrodna</h2>");
	AddCity(301, 259, 305, 263, "<h2>Pinsk</h2>");
	AddCity(410, 263, 414, 267, "<h2>Mazyr</h2>");
	AddCity(467, 240, 471, 244, "<h2>Homyel'</h2>");
	AddCity(302, 203, 306, 207, "<h2>Baranavichy</h2>");
	AddCity(408, 203, 412, 207, "<h2>Babruysk</h2>");
	AddCity(350, 158, 358, 166, "<h2>Minsk</h2><br>I'm living here ");
	AddCity(443, 159, 447, 163, "<h2>Mahilyov</h2>");
	AddCity(444, 125, 448, 129, "<h2>Orsha</h2>");
	AddCity(435, 88, 439, 92, "<h2>Vitsyebsk</h2>");
	AddCity(392, 73, 396, 77, "<h2>Polatsk</h2>");
}

void CPPTooltip_demoView::AddCity(int x1, int y1, int x2, int y2, CString strText)
{
	structCITY_RECT sr;
	sr.rect.SetRect(x1, y1, x2, y2);
	sr.strText = strText;
	m_Cities.push_back(sr);
}

CPPTooltip_demoView::~CPPTooltip_demoView()
{
}

BOOL CPPTooltip_demoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoView drawing

void CPPTooltip_demoView::OnDraw(CDC* pDC)
{
	CPPTooltip_demoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap * pOldBitmap = memDC.SelectObject(&m_map);
	pDC->BitBlt(m_rect [4].left, m_rect [4].top, 330, 355, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();

	pDC->FillSolidRect(m_rect [0], RGB(255, 0, 0));
	pDC->FillSolidRect(m_rect [1], RGB(0, 255, 0));
	pDC->FillSolidRect(m_rect [2], RGB(0, 0, 255));
	pDC->FillSolidRect(m_rect [3], RGB(0, 255, 255));

}

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoView printing

BOOL CPPTooltip_demoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPPTooltip_demoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPPTooltip_demoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoView diagnostics

#ifdef _DEBUG
void CPPTooltip_demoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPPTooltip_demoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPPTooltip_demoDoc* CPPTooltip_demoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPPTooltip_demoDoc)));
	return (CPPTooltip_demoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoView message handlers

void CPPTooltip_demoView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();

	m_map.LoadBitmap(IDB_MAP);
	
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 1000;
	sizeTotal.cy = 1000;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_traytip.Create(this);
	m_traytip.SetSize(CPPToolTip::PPTTSZ_MARGIN_CX, 4);
	m_traytip.SetSize(CPPToolTip::PPTTSZ_MARGIN_CY, 4);

	m_pButton1.Create("Show icon in tray", WS_CHILD|WS_VISIBLE, CRect(550, 0, 750, 30), this, IDC_BUTTON1);
	m_pButton2.Create("Remove icon from tray", WS_CHILD|WS_VISIBLE, CRect(550, 40, 750, 70), this, IDC_BUTTON2);
	m_pButton3.Create("Show help tooltip in tray", WS_CHILD|WS_VISIBLE, CRect(550, 80, 750, 110), this, IDC_BUTTON3);
	m_pButton4.Create("Hide help tooltip from tray", WS_CHILD|WS_VISIBLE, CRect(550, 120, 750, 150), this, IDC_BUTTON4);

	m_tooltip.Create(this);
	m_tooltip.SetNotify();
	
	m_tooltip.AddTool(&m_pButton1, _T("<center><h2>ToolTip in System Tray</h2><br><hr color=blue></center><br>Click a button to show application icon<br>in the system tray"));
	m_tooltip.AddTool(&m_pButton2, _T("<center><h2>ToolTip in System Tray</h2><br><hr color=blue></center><br>Click a button to remove application icon<br>from the system tray"));
	m_tooltip.AddTool(&m_pButton3, _T("<center><h2>ToolTip in System Tray</h2><br><hr color=blue></center><br>Click a button to show Help Tooltip on application icon<br>in tray<br=2><span class=cpp-comment>Thanks <a href=\"http://www.ireksoftware.com\">Irek Zielinski</a> for method of search an icon<br>in the system tray</span>"));
	m_tooltip.AddTool(&m_pButton4, _T("<center><h2>ToolTip in System Tray</h2><br><hr color=blue></center><br>Click a button to manual hide Help Tooltip"));
	
	m_tooltip.AddTool(this, _T("<center><h2>ToolTip in ScrollView</h2><br><hr color=blue></center><br>ToolTip for <font color=red>RED</font> rectangle in View"), m_rect [0]);
	m_tooltip.AddTool(this, _T("<center><h2>ToolTip in ScrollView</h2><br><hr color=blue></center><br>ToolTip for <font color=green>GREEN</font> rectangle in View"), m_rect [1]);
	m_tooltip.AddTool(this, _T("<center><h2>ToolTip in ScrollView</h2><br><hr color=blue></center><br>ToolTip for <font color=blue>BLUE</font> rectangle in View"), m_rect [2]);
	m_tooltip.AddTool(this, _T("<center><h2>ToolTip in ScrollView</h2><br><hr color=blue></center><br>ToolTip for <font color=cyan>CYAN</font> rectangle in View"), m_rect [3]);

	//Add tooltip to the Map
	PPTOOLTIP_INFO ti;
	ti.nBehaviour = PPTOOLTIP_MULTIPLE_SHOW;
	ti.nIDTool = IDB_MAP;
	ti.rectBounds = m_rect [4];
	ti.sTooltip = "";
	ti.nMask = PPTOOLTIP_MASK_BEHAVIOUR;
	m_tooltip.AddTool(this, ti);
}

BOOL CPPTooltip_demoView::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	m_traytip.RelayEvent(pMsg);
	
	return CScrollView::PreTranslateMessage(pMsg);
}

void CPPTooltip_demoView::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (pNotify->ti->nIDTool == IDB_MAP)
	{
		CPoint pt = *pNotify->pt;
		ScreenToClient(&pt);
		pt += GetScrollPosition();
		structCITY_RECT sr;
		for (int i = 0; i < (int)m_Cities.size(); i++)
		{
			sr = m_Cities [i];
			if (sr.rect.PtInRect(pt))
			{
				pNotify->ti->sTooltip = sr.strText;
				return;
			}
		}

		CString str;
		str.Format(_T("Map x=%d, y=%d"), pt.x, pt.y);
		pNotify->ti->sTooltip = str;
	} //if
} //End NotifyDisplayTooltip

void CPPTooltip_demoView::OnShowIconInTray()
{
	CPPTooltip_demoApp * pApp = (CPPTooltip_demoApp*)AfxGetApp();

	NOTIFYICONDATA nid; 
	nid.cbSize = sizeof(nid); 
	nid.hWnd = m_hWnd; 
	nid.uID = 1; 
	nid.uFlags = NIF_ICON|NIF_TIP; 
	strncpy(nid.szTip, "Our icon in tray :-D", 64);
	nid.hIcon = pApp->LoadIcon(IDR_MAINFRAME);
	Shell_NotifyIcon(NIM_ADD, &nid);

	//let's initialize tray icon position tracking
	//second argument it's ID of icon (nid.uID)
	m_tray_pos.InitializePositionTracking(m_hWnd,1);
}

void CPPTooltip_demoView::OnRemoveIconFromTray()
{
	NOTIFYICONDATA nid; 
	nid.cbSize = sizeof(nid); 
	nid.hWnd = m_hWnd; 
	nid.uID = 1; 
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

void CPPTooltip_demoView::OnShowHelpTooltip()
{
	TRACE("Show tray tooltip\n");
	CPoint ptIcon;
	BOOL bIconFound = m_tray_pos.GetTrayIconPosition(ptIcon);
	if (bIconFound == -1)
		return;

	m_tray_pos.RestoreTrayIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	CString str = _T("<table><tr><td><icon idres=128></td><td><right><a><icon idres=158 width=16 height=16 style=g hotstyle></a></right><br><center><h2>Tooltip in tray</h2><br><hr color=blue></center><br>");
	if(bIconFound)
	{
		CString str1;
		//we were able to find out icon on the screen
		str1.Format("We were able to find out position of the tray icon!<br>It's located at: <b>X:[%d] Y:[%d]</b>", ptIcon.x, ptIcon.y);
		str += str1;
	}
	else
	{
		CString str1;
		//we were not able to find out position of icon - but in 99% of times this function returns usefull data
		str1.Format("We were NOT ABLE to find out position of the tray icon!<br>Maybe we're under Windows XP and our icon is hidden ?<br>But the best place to display our balloon is:<br><b>X:[%d] Y:[%d]</b>", ptIcon.x, ptIcon.y);
		str += str1;
	}
	str += _T("</td></tr><tr><td colspan=2><span class=cpp-comment>Thanks <a href=\"http://www.ireksoftware.com\">Irek Zielinski</a> for his <a href=\"http://www.codeproject.com/shell/ctrayiconposition.asp\">CTrayIconPosition - where<br>is my tray icon?</a> article!!!</span></td></tr></table>");
	m_traytip.ShowHelpTooltip(&ptIcon, str);
}

void CPPTooltip_demoView::OnHideHelpTooltip()
{
	TRACE("Hide tray tooltip\n");
	m_tooltip.HideTooltip();
}

void CPPTooltip_demoView::OnDestroy() 
{
	OnHideHelpTooltip();
	OnRemoveIconFromTray();
	
	CScrollView::OnDestroy();
}
