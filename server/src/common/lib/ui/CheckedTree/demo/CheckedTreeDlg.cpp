// CheckedTreeDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CheckedTree.h"
#include "CheckedTreeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckedTreeDlg Dialogfeld

CCheckedTreeDlg::CCheckedTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckedTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckedTreeDlg)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCheckedTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckedTreeDlg)
		// HINWEIS: Der Klassenassistent fügt an dieser Stelle DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckedTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckedTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckedTreeDlg Nachrichten-Handler

BOOL CCheckedTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	createTreeControl();

	fillTreeControl();
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void 
CCheckedTreeDlg::createTreeControl()
{
	CRect FrameRect;

	// calculate the rectangle
	GetDlgItem(IDC_TREEFRAME)->GetWindowRect(FrameRect);
	ScreenToClient(FrameRect);
	FrameRect.InflateRect(-20,-20);

	// create the Treecontrol
	m_MyTreeControl.Create(
		WS_CHILD | 
		WS_VISIBLE |
		WS_BORDER |
		WS_TABSTOP |
		TVS_HASBUTTONS |
		TVS_HASLINES |
		TVS_LINESATROOT |
		TVS_SHOWSELALWAYS |
		TVS_CHECKBOXES |		// These style constant is needed !
		TVS_TRACKSELECT, 
		FrameRect, this, 1005
	);

	// !!! SET BITMAPS
	// !!! AFTER YOU CREATED THE CONTROL
	m_MyTreeControl.SetBitmaps(IDB_BITMAP_NORMAL,IDB_BITMAP_STATUS);
}

void CCheckedTreeDlg::fillTreeControl()
{
	// fill items
	TCHAR* FirstName = new TCHAR[255];
	TCHAR* SecndName= new TCHAR[255];

	strcpy(FirstName,"Item 1");
	strcpy(SecndName,"Item 2");

	TV_INSERTSTRUCT	First;
	memset (&First,0,sizeof(First));

	First.hParent = NULL;
	First.hInsertAfter = NULL;
	First.item.mask = TVIF_STATE | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	// !!! DO NOT USE Index 0 for Statusimage 
	First.item.state = INDEXTOSTATEIMAGEMASK (1);
	First.item.stateMask = TVIS_STATEIMAGEMASK;
	// !!! keep care when copying this string
	First.item.pszText = FirstName;
	First.item.cchTextMax = 255;
	
	First.item.iImage = 0;
	First.item.iSelectedImage = 0;
	m_MyTreeControl.InsertItem(&First);

	//zweites Element
	TV_INSERTSTRUCT	Secnd;
	memset (&Secnd,0,sizeof(Secnd));

	Secnd.hParent = m_MyTreeControl.GetRootItem();
	Secnd.hInsertAfter = TVI_FIRST ;
	Secnd.item.mask = TVIF_STATE | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	// !!! DO NOT USE Index 0 for Statusimage 
	Secnd.item.state = INDEXTOSTATEIMAGEMASK (2);
	Secnd.item.stateMask = TVIS_STATEIMAGEMASK;
	// !!! keep care when copying this string
	Secnd.item.pszText = SecndName;
	Secnd.item.cchTextMax = 255;

	Secnd.item.iImage = 1;
	Secnd.item.iSelectedImage = 1;

	m_MyTreeControl.InsertItem(&Secnd);
}

	
void CCheckedTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CCheckedTreeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CCheckedTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
