1) Cach thay doi thu vien CxImage
- Trong project AGmagicIP, vao file AGimageDefs.h thay doi macro AGMAGIC_CXIMAGE_VER ve dung phien ban cua CxImage.

- Trong project AGmagicIPUI, vao file AGimageRC.h them mot dong include den demo/resource.h cua CxImage, vi du : #include "../lib/cximage/599a/windows/msvc/demo/resource.h". Dong thoi cung lam tuong tu cho file AGimageRC.rc, vi du: #include "../lib/cximage/599a/windows/msvc/demo/demo.rc". Ghi chu: chung ta nen include dung phien ban cua CxImage.

- Chep tat ca cac file tai nguyen (.bmp, .ico, .jpg,...) tu demo/res cua CxImage vao trong main/res cua project AGmagicIPUI.

- Vao file AGimageUI2.h, AGimageUI2.cpp trong project AGmagicIPUI de include cac file .h, .cpp trong project demo cua CxImage. That ra duong dan cac file .h, .cpp nay da duoc dinh nghia thanh cac macro trong AGimageDefs.h trong project AGmagicIP.

- Trong tat ca cac file .h, .cpp cua CxImage, sua tat cac cac dong lenh sau :
#include "ximage.h"
#include "ximajpg.h"
#include "ximagif.h"
#include "ximatif.h"
#include "xfile.h"
 thanh:
#include "../CxImage/ximage.h"
#include "../CxImage/ximajpg.h"
#include "../CxImage/ximagif.h"
#include "../CxImage/ximatif.h"
#include "../CxImage/xfile.h"

- Vao cac file demo.h, demoView.h, demoDoc.h, MainFrm.h, child
#ifndef AGMAGIC_DECL
class CDemoApp : public CWinApp
#else
class AGMAGIC_DECL CDemoApp : public CWinApp
#endif	//AGMAGIC_DECL
#ifndef AGMAGIC_DECL
class CDemoDoc : public CDocument
#else
class AGMAGIC_DECL CDemoDoc : public CDocument
#endif	//AGMAGIC_DECL
#ifndef AGMAGIC_DECL
class CDemoView : public CScrollView
#else
class AGMAGIC_DECL CDemoView : public CScrollView
#endif	//AGMAGIC_DECL
#ifndef AGMAGIC_DECL
class CMainFrame : public CMDIFrameWnd, public CTwain
#else
class AGMAGIC_DECL CMainFrame : public CMDIFrameWnd, public CTwain
#endif	//AGMAGIC_DECL


- Vao file AGimageUI2.cpp trong project AGmagicIPUI them cac dong lenh sau:
#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
#define AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif	//AGMAGICUI2_ALREADY_DEFINED_THIS_FILE

- Vao tat ca cac file .cpp trong project demo cua CxImage, them cac dong sau:
//this is AGmagic code
#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif 

- Vao file demo/demo.cpp cua CxImage sua dong lenh sau:
CDemoApp theApp;
 thanh:
//this is AGmagic code
#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
CDemoApp theApp;
#endif //#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE

- Vao file demo/demo.cpp cua CxImage sua dong lenh sau:
extern CDemoApp theApp;
 thanh:
#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE
extern CDemoApp theApp;
#endif //#ifndef AGMAGICUI2_ALREADY_DEFINED_THIS_FILE

- Vao 3 file MainFrm.cpp, demoDoc.cpp, demoView.cpp trong demo cua CxImage, sua tat ca cac bien theApp thanh pTheApp voi:
CDemoApp* pTheApp=(CDemoApp*)AfxGetApp();

- Vao file MainFrm.h trong demo cua CxImage sua dong lenh sau :
HMENU NewMenu();
HMENU NewDefaultMenu();
 thanh :
virtual HMENU NewMenu();
virtual HMENU NewDefaultMenu();

- Vao file MainFrm.h trong demo cua CxImage them 2 dong lenh sau :
inline CProgressCtrl& GetProgressBar() { return m_wndProgressBar; }
CProgressCtrl m_wndProgressBar;

- Trong ham OnCreate cua MainFrm.cpp cua CxImage/demo them cac dong lenh sau:
if (!m_wndProgressBar.Create(WS_CHILD,CRect(200,2,262,18),&m_wndStatusBar,ID_INDICATOR1))
{
	TRACE0("Failed to create progress bar\n");
	return -1;      // fail to create
}
m_wndProgressBar.ShowWindow(SW_SHOW);
m_wndProgressBar.SetRange(0,100);
Dong thoi vao file demo.rc cua CxImage/demo sua nhu sau:
STRINGTABLE DISCARDABLE 
BEGIN
    ID_INDICATOR_EXT        "EXT"
    ID_INDICATOR_CAPS       "CAP"
    ID_INDICATOR_NUM        "NUM"
    ID_INDICATOR_SCRL       "SCRL"
    ID_INDICATOR_OVR        "OVR"
    ID_INDICATOR_REC        "REC"
    ID_INDICATOR1           "                            "
    ID_INDICATOR2           "                            "
    ID_INDICATOR3           "        "
    ID_INDICATOR4           "                            "
END


- Trong ham OnNewProgress cua demoView.cpp cua CxImage/demo them cac dong lenh sau:
CProgressCtrl& progressBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetProgressBar();
progressBar.SetPos((int)wParam);
progressBar.Invalidate(1);


- Viet them 2 ham sau trong demoDoc.h cua CxImage/demo
virtual CxImage* newMyImage(CxImage* pImage=NULL, bool copypixels = true, bool copyselection = true, bool copyalpha = true) 
{
	if(pImage==NULL)
		return new CxImage();
	else
	{
		CxImage* pImageReturn=new CxImage();
		pImageReturn->Copy(pImage,copypixels,copyselection,copyalpha);
		return pImageReturn;
	}
};
va 2 ham sau trong AGimageUI2.h cua project AGmagicIPUI
virtual CxImage* newMyImage(CxImage* pImage=NULL, bool copypixels = true, bool copyselection = true, bool copyalpha = true) 
{
	if(pImage==NULL)
		return new CAGimage();
	else
	{
		CAGimage* pImageReturn=new CAGimage();
		pImageReturn->Copy((CAGimage*)pImage,copypixels,copyselection,copyalpha);
		return pImageReturn;
	}
};
virtual CxImage* newMyImage(aguint32 dwWidth, aguint32 dwHeight, aguint32 wBpp, aguint32 imagetype=0)
{
	return new CAGimage(dwWidth,dwHeight,wBpp,imagetype);
}

- Vao mot so ham sau cua MainFrm.cpp cua CxImage/demo sua nhu sau:
void CMainFrame::OnEditPaste()
{
	//....
	CxImage *newima = NewDoc->newMyImage();
	//....
}
void CAGmagicIP_MDIMainFrame::SetImage(HANDLE hBitmap,TW_IMAGEINFO& info)
{
	//....
	CxImage *newima = NewDoc->newMyImage();
	//....
}

- Sua tat ca cac len "new CxImage" thanh ham newImage trong demoDoc.cpp cua CxImage/demo thanh "newMyImage"

- Trong cac ham :
	afx_msg void OnImageFromBitmap();
	afx_msg void OnCximageLoadjpegresource();
	afx_msg void OnCximageLoadiconresource();
	afx_msg void OnCximageLoadgifresource();
	afx_msg void OnCximageLoadpngresource();
	afx_msg void OnCximageLoadtifresource();
	afx_msg void OnCximageDemocreatefromarray();
  cua demo.cpp cua CxImage/demo, sua cac dong lenh sau:
	CxImage* newImage=new CxImage();
        ....
	doc->image = newImage;
  thanh:
	CxImage newImage;
        ....
	doc->image = doc->newMyImage(&newImage);

- Trong ham void CDemoApp::OnCximageDownloadfromurl() sua tat cac cac "new CxImage" thanh "doc->newMyImage()"

- Trong CDemoApp them bien m_nDocInc duoc khoi gan la 1. Trong CDemoDoc them bien m_DocID duoc khoi gan la 0. Xem xet toan bo file demo.cpp va demoDoc.cpp, bat cu khi nao phat sinh document moi thi m_DocID=m_nDocInc ++. Dong thoi sua tat ca cac bien private cua CDemoView trong CxImage/demo/demoView.h thanh protected

- Vao file logomdi.cpp trong CxImage/demo sua bien sLogoString = "CxImage " thanh sLogoString = "AGmagic "

- Vao file demo.rc trong CxImage/demo sua nhu sau:
VS_VERSION_INFO VERSIONINFO
 FILEVERSION 1,0,0,0
 PRODUCTVERSION 1,0,0,0
 FILEFLAGSMASK 0x3fL
#ifdef _DEBUG
 FILEFLAGS 0x29L
#else
 FILEFLAGS 0x28L
#endif
 FILEOS 0x4L
 FILETYPE 0x1L
 FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904b0"
        BEGIN
            VALUE "Comments", " \0"
            VALUE "CompanyName", "www.agu.edu.vn\0"
            VALUE "FileDescription", "AGmagicIPUI Library\0"
            VALUE "FileVersion", "1, 0, 0, 0\0"
            VALUE "InternalName", "AGmagicIPUI\0"
            VALUE "LegalCopyright", " © Nguyen Phuoc Loc 2004-2005\0"
            VALUE "LegalTrademarks", "Freeware\0"
            VALUE "OriginalFilename", "AGmagicIPUI.DLL\0"
            VALUE "PrivateBuild", "5\0"
            VALUE "ProductName", "AGmagicIPUI\0"
            VALUE "ProductVersion", "1, 0, 0, 0\0"
            VALUE "SpecialBuild", "0\0"
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x409, 1200
    END
END

- Sua ham CDemoApp::InitInstance() trong file demo.cpp nhu sau:
#if _MFC_VER < 0x0700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL //khong can thiet nua doi voi VC 7.0
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically //khong can thiet nua doi voi VC 7.0
#endif
#endif	//#if _MFC_VER < 0x0700

- Cuoi cung sua cac file resource AGimageRC.h va AGimageRC.rc trong project AGmagicIPUI cho phu hop voi nhung thay doi moi cua cac phien ban CxImage