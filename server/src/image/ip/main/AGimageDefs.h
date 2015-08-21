/*
Cau hinh tao thu vien (DLL) trong VC6++: 4 cau hinh
1) Windows DLL (khong dung MFC) : Truoc tien ta phai #define AGMAGIC_SUPPORT_MFC 0 
   a) Phien ban Debug
		Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_USRDLL,_MBCS,JAS_WIN_MSVC_BUILD
		Link: wininet.lib lib/CxImage/j2k/Debug/j2k.lib lib/CxImage/jasper/Debug/jasper.lib lib/CxImage/jbig/Debug/jbig.lib lib/CxImage/jpeg/Debug/jpeg.lib lib/CxImage/mng/Debug/mng.lib lib/CxImage/png/Debug/png.lib lib/CxImage/tiff/Debug/tiff.lib lib/CxImage/zlib/Debug/zlib.lib 
		Output: AGmagicIP.dll va AGmagicIP.lib
   b) Phien ban Release
		Preprocessor difinitions: WIN32,NDEBUG,_WINDOWS,_USRDLL,_MBCS,JAS_WIN_MSVC_BUILD
		Link: wininet.lib lib/CxImage/j2k/Debug/j2k.lib lib/CxImage/jasper/Debug/jasper.lib lib/CxImage/jbig/Debug/jbig.lib lib/CxImage/jpeg/Debug/jpeg.lib lib/CxImage/mng/Debug/mng.lib lib/CxImage/png/Debug/png.lib lib/CxImage/tiff/Debug/tiff.lib lib/CxImage/zlib/Debug/zlib.lib 
		Output: AGmagicIP.dll va AGmagicIP.lib
   c) Cau truc thu vien : Xem vi du

2) Regular MFC DLL (using static DLL) : Truoc tien ta phai #define AGMAGIC_SUPPORT_MFC 1
	DLL nay su dung MFC nhung khong cho phep trao doi con tro cac doi tuong MFC trong DLL voi ung dung
	DLL nay su dung MFC DLL tinh
   Cau hinh nay co 2 phien ban
   a) Phien ban Debug
		Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_WINDLL,_USRDLL,_MBCS,JAS_WIN_MSVC_BUILD
		Link: wininet.lib lib/CxImage/j2k/Debug/j2k.lib lib/CxImage/jasper/Debug/jasper.lib lib/CxImage/jbig/Debug/jbig.lib lib/CxImage/jpeg/Debug/jpeg.lib lib/CxImage/mng/Debug/mng.lib lib/CxImage/png/Debug/png.lib lib/CxImage/tiff/Debug/tiff.lib lib/CxImage/zlib/Debug/zlib.lib 
		Output: AGmagicIP.dll va AGmagicIP.lib
   b) Phien ban Release
		Preprocessor difinitions: WIN32,NDEBUG,_WINDOWS,_WINDLL,_USRDLL,_MBCS,JAS_WIN_MSVC_BUILD
		Link: wininet.lib lib/CxImage/j2k/Debug/j2k.lib lib/CxImage/jasper/Debug/jasper.lib lib/CxImage/jbig/Debug/jbig.lib lib/CxImage/jpeg/Debug/jpeg.lib lib/CxImage/mng/Debug/mng.lib lib/CxImage/png/Debug/png.lib lib/CxImage/tiff/Debug/tiff.lib lib/CxImage/zlib/Debug/zlib.lib 
		Output: AGmagicIP.dll va AGmagicIP.lib
   c) Cau truc thu vien : Xem vi du

3) Regular MFC DLL (using shared DLL) : Truoc tien ta phai #define AGMAGIC_SUPPORT_MFC 1
	DLL nay su dung MFC nhung khong cho phep trao doi con tro cac doi tuong MFC trong DLL voi ung dung
	DLL nay su dung MFC DLL dong
   Cau hinh nay co 2 phien ban
   a) Phien ban Debug
		Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_WINDLL,_AFXDLL,_MBCS,JAS_WIN_MSVC_BUILD
		Link: wininet.lib lib/CxImage/j2k/Debug/j2k.lib lib/CxImage/jasper/Debug/jasper.lib lib/CxImage/jbig/Debug/jbig.lib lib/CxImage/jpeg/Debug/jpeg.lib lib/CxImage/mng/Debug/mng.lib lib/CxImage/png/Debug/png.lib lib/CxImage/tiff/Debug/tiff.lib lib/CxImage/zlib/Debug/zlib.lib 
		Output: AGmagicIP.dll va AGmagicIP.lib
   b) Phien ban Release
		Preprocessor difinitions: WIN32,NDEBUG,_WINDOWS,_WINDLL,_AFXDLL,_MBCS,JAS_WIN_MSVC_BUILD
		Link: wininet.lib lib/CxImage/j2k/Debug/j2k.lib lib/CxImage/jasper/Debug/jasper.lib lib/CxImage/jbig/Debug/jbig.lib lib/CxImage/jpeg/Debug/jpeg.lib lib/CxImage/mng/Debug/mng.lib lib/CxImage/png/Debug/png.lib lib/CxImage/tiff/Debug/tiff.lib lib/CxImage/zlib/Debug/zlib.lib 
		Output: AGmagicIP.dll va AGmagicIP.lib
   c) Cau truc thu vien : Xem vi du

4) Extension MFC DLL (using shared DLL):  Truoc tien ta phai #define AGMAGIC_SUPPORT_MFC 1
	DLL nay su dung MFC va cho phep trao doi con tro cac doi tuong MFC trong DLL voi ung dung
	DLL nay su dung MFC DLL dong
   Cau hinh nay co 2 phien ban
   a) Phien ban Debug
		Preprocessor difinitions: WIN32,_DEBUG,_WINDOWS,_WINDLL,_AFXDLL,_MBCS,JAS_WIN_MSVC_BUILD,_AFXEXT
		(khong can thiet phai define _AFXEXT)
		Link: wininet.lib lib/CxImage/j2k/Debug/j2k.lib lib/CxImage/jasper/Debug/jasper.lib lib/CxImage/jbig/Debug/jbig.lib lib/CxImage/jpeg/Debug/jpeg.lib lib/CxImage/mng/Debug/mng.lib lib/CxImage/png/Debug/png.lib lib/CxImage/tiff/Debug/tiff.lib lib/CxImage/zlib/Debug/zlib.lib 
		Output: AGmagicIP.dll va AGmagicIP.lib
   b) Phien ban Release
		Preprocessor difinitions: WIN32,NDEBUG,_WINDOWS,_WINDLL,_AFXDLL,_MBCS,JAS_WIN_MSVC_BUILD,_AFXEXT
		(khong can thiet phai define _AFXEXT)
		Link: wininet.lib lib/CxImage/j2k/Debug/j2k.lib lib/CxImage/jasper/Debug/jasper.lib lib/CxImage/jbig/Debug/jbig.lib lib/CxImage/jpeg/Debug/jpeg.lib lib/CxImage/mng/Debug/mng.lib lib/CxImage/png/Debug/png.lib lib/CxImage/tiff/Debug/tiff.lib lib/CxImage/zlib/Debug/zlib.lib 
		Output: AGmagicIP.dll va AGmagicIP.lib
   c) Cau truc thu vien : Xem vi du
*/


#if !defined(AGIMAGEDEFS_H)
#define AGIMAGEDEFS_H

/*******************Cac define va include bat buoc phai khai bao**********************************/
//5991 la 599a
//5992 la 599b
//5993 la 599c
#define AGMAGIC_CXIMAGE_VER  5991

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
#if AGMAGIC_CXIMAGE_VER==5991
#if AGMAGIC_DEV_ENV==AGMAGIC_MSVC
	//danh cho project AGmagicIP
	#define	AG_LIB_PATH_CXIMAGE _T("../../../lib/cximage/599a/windows/msvc/CxImage/Debug/cximage.lib")
	#define	AG_LIB_PATH_J2K		_T("../../../lib/cximage/599a/windows/msvc/j2k/Debug/j2k.lib")
	#define	AG_LIB_PATH_JASPER	_T("../../../lib/cximage/599a/windows/msvc/jasper/Debug/jasper.lib")
	#define	AG_LIB_PATH_JBIG	_T("../../../lib/cximage/599a/windows/msvc/jbig/Debug/jbig.lib")
	#define	AG_LIB_PATH_JPEG	_T("../../../lib/cximage/599a/windows/msvc/jpeg/Debug/Jpeg.lib")
	#define	AG_LIB_PATH_MNG		_T("../../../lib/cximage/599a/windows/msvc/mng/Debug/mng.lib")
	#define	AG_LIB_PATH_PNG		_T("../../../lib/cximage/599a/windows/msvc/png/Debug/png.lib")
	#define	AG_LIB_PATH_TIFF	_T("../../../lib/cximage/599a/windows/msvc/tiff/Debug/Tiff.lib")
	#define	AG_LIB_PATH_ZLIB	_T("../../../lib/cximage/599a/windows/msvc/zlib/Debug/zlib.lib")

	#define	AG_INCLUDE_XIMAGE_H				"../lib/cximage/599a/windows/msvc/CxImage/ximage.h"
	#define	AG_INCLUDE_XIMAJPG_H			"../lib/cximage/599a/windows/msvc/CxImage/ximajpg.h"
	#define	AG_INCLUDE_XIMAGIF_H			"../lib/cximage/599a/windows/msvc/CxImage/ximagif.h"
	#define	AG_INCLUDE_XIMATIF_H			"../lib/cximage/599a/windows/msvc/CxImage/ximatif.h"

	//danh cho project AGmagicIPUI
	#define	AG_INCLUDE_MEMDC_H				"../../ip/lib/cximage/599a/windows/msvc/demo/memdc.h"
	#define	AG_INCLUDE_BCMENU_H				"../../ip/lib/cximage/599a/windows/msvc/demo/BCMenu.h"
	#define	AG_INCLUDE_BCMENU_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/BCMenu.cpp"
	#define	AG_INCLUDE_QUANTIZE_H			"../../ip/lib/cximage/599a/windows/msvc/demo/Quantize.h"
	#define	AG_INCLUDE_QUANTIZE_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/Quantize.cpp"
	#define	AG_INCLUDE_TWAINCPP_H			"../../ip/lib/cximage/599a/windows/msvc/demo/TwainCpp.h"
	#define	AG_INCLUDE_TWAINCPP_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/TwainCpp.cpp"
	#define	AG_INCLUDE_XTARGETBUTTON_H		"../../ip/lib/cximage/599a/windows/msvc/demo/xTargetButton.h"
	#define	AG_INCLUDE_XTARGETBUTTON_CPP	"../../ip/lib/cximage/599a/windows/msvc/demo/xTargetButton.cpp"

	#define	AG_INCLUDE_DLGCAPTURE_H			"../../ip/lib/cximage/599a/windows/msvc/demo/dlgcapture.h"
	#define	AG_INCLUDE_DLGCAPTURE_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/dlgcapture.cpp"
	#define	AG_INCLUDE_DLGCOLORIZE_H		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgColorize.h"
	#define	AG_INCLUDE_DLGCOLORIZE_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgColorize.cpp"
	#define	AG_INCLUDE_DLGCOMBINE_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgCombine.h"
	#define	AG_INCLUDE_DLGCOMBINE_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgCombine.cpp"
	#define	AG_INCLUDE_DLGDECBPP_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgDecBpp.h"
	#define	AG_INCLUDE_DLGDECBPP_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgDecBpp.cpp"
	#define	AG_INCLUDE_DLGDITHER_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgDither.h"
	#define	AG_INCLUDE_DLGDITHER_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgDither.cpp"
	#define	AG_INCLUDE_DLGFFT_H				"../../ip/lib/cximage/599a/windows/msvc/demo/DlgFFT.h"
	#define	AG_INCLUDE_DLGFFT_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgFFT.cpp"
	#define	AG_INCLUDE_DLGGAMMA_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgGamma.h"
	#define	AG_INCLUDE_DLGGAMMA_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgGamma.cpp"
	#define	AG_INCLUDE_DLGHISTO_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgHisto.h"
	#define	AG_INCLUDE_DLGHISTO_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgHisto.cpp"
	#define	AG_INCLUDE_DLGINCBPP_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgIncBpp.h"
	#define	AG_INCLUDE_DLGINCBPP_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgIncBpp.cpp"
	#define	AG_INCLUDE_DLGMIX_H				"../../ip/lib/cximage/599a/windows/msvc/demo/DlgMix.h"
	#define	AG_INCLUDE_DLGMIX_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgMix.cpp"
	#define	AG_INCLUDE_DLGOPACITY_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgOpacity.h"
	#define	AG_INCLUDE_DLGOPACITY_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgOpacity.cpp"
	#define	AG_INCLUDE_DLGOPTIONS_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgOptions.h"
	#define	AG_INCLUDE_DLGOPTIONS_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgOptions.cpp"
	#define	AG_INCLUDE_DLGPALETTE_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgPalette.h"
	#define	AG_INCLUDE_DLGPALETTE_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgPalette.cpp"
	#define	AG_INCLUDE_DLGREPAIR_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgRepair.h"
	#define	AG_INCLUDE_DLGREPAIR_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgRepair.cpp"
	#define	AG_INCLUDE_DLGRESAMPLE_H		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgResample.h"
	#define	AG_INCLUDE_DLGRESAMPLE_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgResample.cpp"
	#define	AG_INCLUDE_DLGROTATE_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgRotate.h"
	#define	AG_INCLUDE_DLGROTATE_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgRotate.cpp"
	#define	AG_INCLUDE_DLGTEXT_H			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgText.h"
	#define	AG_INCLUDE_DLGTEXT_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgText.cpp"
	#define	AG_INCLUDE_DLGTHRESHOLD_H		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgThreshold.h"
	#define	AG_INCLUDE_DLGTHRESHOLD_CPP		"../../ip/lib/cximage/599a/windows/msvc/demo/DlgThreshold.cpp"
	#define	AG_INCLUDE_DLGURL_H				"../../ip/lib/cximage/599a/windows/msvc/demo/DlgURL.h"
	#define	AG_INCLUDE_DLGURL_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/DlgURL.cpp"
	#define	AG_INCLUDE_LOGOMDI_H			"../../ip/lib/cximage/599a/windows/msvc/demo/logomdi.h"
	#define	AG_INCLUDE_LOGOMDI_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/logomdi.cpp"
	#define	AG_INCLUDE_MAINFRM_H			"../../ip/lib/cximage/599a/windows/msvc/demo/MainFrm.h"
	#define	AG_INCLUDE_MAINFRM_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/MainFrm.cpp"
	#define	AG_INCLUDE_CHILDFRM_H			"../../ip/lib/cximage/599a/windows/msvc/demo/ChildFrm.h"
	#define	AG_INCLUDE_CHILDFRM_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/ChildFrm.cpp"
	#define	AG_INCLUDE_DEMODOC_H			"../../ip/lib/cximage/599a/windows/msvc/demo/demoDoc.h"
	#define	AG_INCLUDE_DEMODOC_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/demoDoc.cpp"
	#define	AG_INCLUDE_DEMOVIEW_H			"../../ip/lib/cximage/599a/windows/msvc/demo/demoView.h"
	#define	AG_INCLUDE_DEMOVIEW_CPP			"../../ip/lib/cximage/599a/windows/msvc/demo/demoView.cpp"
	#define	AG_INCLUDE_DEMO_H				"../../ip/lib/cximage/599a/windows/msvc/demo/demo.h"
	#define	AG_INCLUDE_DEMO_CPP				"../../ip/lib/cximage/599a/windows/msvc/demo/demo.cpp"

	#define	AG_INCLUDE_RESOURCE_H			"../../ip/lib/cximage/599a/windows/msvc/demo/resource.h"
	#define	AG_INCLUDE_DEMO_RC				"../../ip/lib/cximage/599a/windows/msvc/demo/demo.rc"
#else //AGMAGIC_DEV_ENV
	#error _T("Implement not yet")
#endif //AGMAGIC_DEV_ENV

#elif AGMAGIC_CXIMAGE_VER==5993
#if AGMAGIC_DEV_ENV==AGMAGIC_MSVC
	//danh cho project AGmagicIP
	#define	AG_LIB_PATH_CXIMAGE _T("../../../lib/cximage/599c/windows/msvc/CxImage/Debug/cximage.lib")
	#define	AG_LIB_PATH_J2K		_T("../../../lib/cximage/599c/windows/msvc/j2k/Debug/j2k.lib")
	#define	AG_LIB_PATH_JASPER	_T("../../../lib/cximage/599c/windows/msvc/jasper/Debug/jasper.lib")
	#define	AG_LIB_PATH_JBIG	_T("../../../lib/cximage/599c/windows/msvc/jbig/Debug/jbig.lib")
	#define	AG_LIB_PATH_JPEG	_T("../../../lib/cximage/599c/windows/msvc/jpeg/Debug/Jpeg.lib")
	#define	AG_LIB_PATH_MNG		_T("../../../lib/cximage/599c/windows/msvc/mng/Debug/mng.lib")
	#define	AG_LIB_PATH_PNG		_T("../../../lib/cximage/599c/windows/msvc/png/Debug/png.lib")
	#define	AG_LIB_PATH_TIFF	_T("../../../lib/cximage/599c/windows/msvc/tiff/Debug/Tiff.lib")
	#define	AG_LIB_PATH_ZLIB	_T("../../../lib/cximage/599c/windows/msvc/zlib/Debug/zlib.lib")

	#define	AG_INCLUDE_XIMAGE_H				"../lib/cximage/599c/windows/msvc/CxImage/ximage.h"
	#define	AG_INCLUDE_XIMAJPG_H			"../lib/cximage/599c/windows/msvc/CxImage/ximajpg.h"
	#define	AG_INCLUDE_XIMAGIF_H			"../lib/cximage/599c/windows/msvc/CxImage/ximagif.h"
	#define	AG_INCLUDE_XIMATIF_H			"../lib/cximage/599c/windows/msvc/CxImage/ximatif.h"

	//danh cho project AGmagicIPUI
	#define	AG_INCLUDE_MEMDC_H				"../../ip/lib/cximage/599c/windows/msvc/demo/memdc.h"
	#define	AG_INCLUDE_BCMENU_H				"../../ip/lib/cximage/599c/windows/msvc/demo/BCMenu.h"
	#define	AG_INCLUDE_BCMENU_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/BCMenu.cpp"
	#define	AG_INCLUDE_QUANTIZE_H			"../../ip/lib/cximage/599c/windows/msvc/demo/Quantize.h"
	#define	AG_INCLUDE_QUANTIZE_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/Quantize.cpp"
	#define	AG_INCLUDE_TWAINCPP_H			"../../ip/lib/cximage/599c/windows/msvc/demo/TwainCpp.h"
	#define	AG_INCLUDE_TWAINCPP_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/TwainCpp.cpp"
	#define	AG_INCLUDE_XTARGETBUTTON_H		"../../ip/lib/cximage/599c/windows/msvc/demo/xTargetButton.h"
	#define	AG_INCLUDE_XTARGETBUTTON_CPP	"../../ip/lib/cximage/599c/windows/msvc/demo/xTargetButton.cpp"

	#define	AG_INCLUDE_DLGCAPTURE_H			"../../ip/lib/cximage/599c/windows/msvc/demo/dlgcapture.h"
	#define	AG_INCLUDE_DLGCAPTURE_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/dlgcapture.cpp"
	#define	AG_INCLUDE_DLGCOLORIZE_H		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgColorize.h"
	#define	AG_INCLUDE_DLGCOLORIZE_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgColorize.cpp"
	#define	AG_INCLUDE_DLGCOMBINE_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgCombine.h"
	#define	AG_INCLUDE_DLGCOMBINE_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgCombine.cpp"
	#define	AG_INCLUDE_DLGDECBPP_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgDecBpp.h"
	#define	AG_INCLUDE_DLGDECBPP_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgDecBpp.cpp"
	#define	AG_INCLUDE_DLGDITHER_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgDither.h"
	#define	AG_INCLUDE_DLGDITHER_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgDither.cpp"
	#define	AG_INCLUDE_DLGFFT_H				"../../ip/lib/cximage/599c/windows/msvc/demo/DlgFFT.h"
	#define	AG_INCLUDE_DLGFFT_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgFFT.cpp"
	#define	AG_INCLUDE_DLGGAMMA_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgGamma.h"
	#define	AG_INCLUDE_DLGGAMMA_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgGamma.cpp"
	#define	AG_INCLUDE_DLGHISTO_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgHisto.h"
	#define	AG_INCLUDE_DLGHISTO_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgHisto.cpp"
	#define	AG_INCLUDE_DLGINCBPP_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgIncBpp.h"
	#define	AG_INCLUDE_DLGINCBPP_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgIncBpp.cpp"

	#define	AG_INCLUDE_DLGJPEG_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgIncBpp.h"
	#define	AG_INCLUDE_DLGJPEG_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgIncBpp.cpp"

	#define	AG_INCLUDE_DLGMIX_H				"../../ip/lib/cximage/599c/windows/msvc/demo/DlgMix.h"
	#define	AG_INCLUDE_DLGMIX_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgMix.cpp"
	#define	AG_INCLUDE_DLGOPACITY_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgOpacity.h"
	#define	AG_INCLUDE_DLGOPACITY_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgOpacity.cpp"
	#define	AG_INCLUDE_DLGOPTIONS_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgOptions.h"
	#define	AG_INCLUDE_DLGOPTIONS_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgOptions.cpp"
	#define	AG_INCLUDE_DLGPALETTE_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgPalette.h"
	#define	AG_INCLUDE_DLGPALETTE_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgPalette.cpp"
	#define	AG_INCLUDE_DLGREPAIR_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgRepair.h"
	#define	AG_INCLUDE_DLGREPAIR_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgRepair.cpp"
	#define	AG_INCLUDE_DLGRESAMPLE_H		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgResample.h"
	#define	AG_INCLUDE_DLGRESAMPLE_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgResample.cpp"
	#define	AG_INCLUDE_DLGROTATE_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgRotate.h"
	#define	AG_INCLUDE_DLGROTATE_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgRotate.cpp"

	#define	AG_INCLUDE_DLGSKEW_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgRotate.h"
	#define	AG_INCLUDE_DLGSKEW_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgRotate.cpp"

	#define	AG_INCLUDE_DLGTEXT_H			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgText.h"
	#define	AG_INCLUDE_DLGTEXT_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgText.cpp"
	#define	AG_INCLUDE_DLGTHRESHOLD_H		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgThreshold.h"
	#define	AG_INCLUDE_DLGTHRESHOLD_CPP		"../../ip/lib/cximage/599c/windows/msvc/demo/DlgThreshold.cpp"
	#define	AG_INCLUDE_DLGURL_H				"../../ip/lib/cximage/599c/windows/msvc/demo/DlgURL.h"
	#define	AG_INCLUDE_DLGURL_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/DlgURL.cpp"
	#define	AG_INCLUDE_LOGOMDI_H			"../../ip/lib/cximage/599c/windows/msvc/demo/logomdi.h"
	#define	AG_INCLUDE_LOGOMDI_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/logomdi.cpp"
	#define	AG_INCLUDE_MAINFRM_H			"../../ip/lib/cximage/599c/windows/msvc/demo/MainFrm.h"
	#define	AG_INCLUDE_MAINFRM_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/MainFrm.cpp"
	#define	AG_INCLUDE_CHILDFRM_H			"../../ip/lib/cximage/599c/windows/msvc/demo/ChildFrm.h"
	#define	AG_INCLUDE_CHILDFRM_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/ChildFrm.cpp"
	#define	AG_INCLUDE_DEMODOC_H			"../../ip/lib/cximage/599c/windows/msvc/demo/demoDoc.h"
	#define	AG_INCLUDE_DEMODOC_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/demoDoc.cpp"
	#define	AG_INCLUDE_DEMOVIEW_H			"../../ip/lib/cximage/599c/windows/msvc/demo/demoView.h"
	#define	AG_INCLUDE_DEMOVIEW_CPP			"../../ip/lib/cximage/599c/windows/msvc/demo/demoView.cpp"
	#define	AG_INCLUDE_DEMO_H				"../../ip/lib/cximage/599c/windows/msvc/demo/demo.h"
	#define	AG_INCLUDE_DEMO_CPP				"../../ip/lib/cximage/599c/windows/msvc/demo/demo.cpp"

	#define	AG_INCLUDE_RESOURCE_H			"../../ip/lib/cximage/599c/windows/msvc/demo/resource.h"
	#define	AG_INCLUDE_DEMO_RC				"../../ip/lib/cximage/599c/windows/msvc/demo/demo.rc"
#else //AGMAGIC_DEV_ENV
	#error _T("Implement not yet")
#endif //AGMAGIC_DEV_ENV
#else //AGMAGIC_CXIMAGE_VER
	#error _T("Implement not yet")
#endif //AGMAGIC_CXIMAGE_VER

#else	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	#error _T("Implement not yet")
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

#include "../../../common/include/AGmagicDefs.h"

#ifndef AGMAGIC_USE_DEFS_BRIEFLY
/**************************************************************************************/
#include AG_INCLUDE_XIMAGE_H

/*******************cac define va include cua rieng AGmagicIP**************************/

#define AGMAGICIP_UNKNOWN_FEATURE				0
#define AGMAGICIP_256CLR_FEATURE				1
#define AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE		2
#define AGMAGICIP_MULTICLR_FEATURE				3
#define AGMAGICIP_MULTIATT_FEATURE				4
#define AGMAGICIP_AFFINITY						5
#define AGMAGICIP_USER_ACCESS_PATTERN			6
#define AGMAGICIP_USER_ACCESS_FREQUENCY			7

#define	AGMAGICIP_MIN_NORM_FEAT_VALUE			((agfreal)0.000000001)

/*********************************mot so tien ich**************************/

#define DELETE_AGMAGICIP_ARRAY(Array) \
{ \
	agint32 n=Array.GetSize(); \
	for(agint32 i=0;i<n;i++) \
	{ \
		CAGimage* pAGimage=(CAGimage*)(Array.GetAt(i)); \
		delete pAGimage; \
	} \
	Array.RemoveAll(); \
}

#define DELETE_AGMAGICIP_ARRAYPTR(pArray,bDeleteMe) \
{ \
	if(pArray!=NULL) \
	{ \
		agint32 n=pArray->GetSize(); \
		for(agint32 i=0;i<n;i++) \
		{ \
			CAGimage* pAGimage=(CAGimage*)(pArray->GetAt(i)); \
			if(pAGimage!=NULL) \
				delete pAGimage; \
		} \
		pArray->RemoveAll(); \
		if(bDeleteMe) \
		{ \
			delete pArray; \
			pArray=NULL; \
		} \
	} \
}
#define DELETE_AGMAGICIP_ARRAYPTR_ARRAY(ArrayPtrArray) \
{ \
	agint32 n=ArrayPtrArray.GetSize(); \
	for(agint32 i=0;i<n;i++) \
	{ \
		CAGptrArray* pA=(CAGptrArray*)(ArrayPtrArray.GetAt(i)); \
		DELETE_AGMAGICIP_ARRAYPTR(pA,agtrue) \
	} \
	ArrayPtrArray.RemoveAll(); \
}
#define DELETE_AGMAGICIP_ARRAYPTR_ARRAY_ONLY_ROW(ArrayPtrArray) \
{ \
	agint32 n=ArrayPtrArray.GetSize(); \
	for(agint32 i=0;i<n;i++) \
	{ \
		CAGptrArray* pA=(CAGptrArray*)(ArrayPtrArray.GetAt(i)); \
		delete pA; \
	} \
	ArrayPtrArray.RemoveAll(); \
}

#define DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR(pArrayPtrArray,bDeleteMe) \
{ \
	if(pArrayPtrArray!=NULL) \
	{ \
		agint32 n=pArrayPtrArray->GetSize(); \
		for(agint32 i=0;i<n;i++) \
		{ \
			CAGptrArray* pA=(CAGptrArray*)(pArrayPtrArray->GetAt(i)); \
			DELETE_AGMAGICIP_ARRAYPTR(pA,agtrue) \
		} \
		pArrayPtrArray->RemoveAll(); \
		if(bDeleteMe) \
		{ \
			delete pArrayPtrArray; \
			pArrayPtrArray=NULL; \
		} \
	} \
}

#define DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR_ONLY_ROW(pArrayPtrArray,bDeleteMe) \
{ \
	if(pArrayPtrArray!=NULL) \
	{ \
		agint32 n=pArrayPtrArray->GetSize(); \
		for(agint32 i=0;i<n;i++) \
		{ \
			CAGptrArray* pA=(CAGptrArray*)(pArrayPtrArray->GetAt(i)); \
			delete pA; \
		} \
		pArrayPtrArray->RemoveAll(); \
		if(bDeleteMe) \
		{ \
			delete pArrayPtrArray; \
			pArrayPtrArray=NULL; \
		} \
	} \
}

//#if AGMAGIC_SUPPORT_MFC
//#define DELETE_AGMAGICIP_MFC_ARRAYPTR_ARRAY(ArrayPtrArray) \
//{ \
//	agint32 n=ArrayPtrArray.GetSize(); \
//	for(agint32 i=0;i<n;i++) \
//	{ \
//		CPtrArray* pA=(CPtrArray*)(ArrayPtrArray.GetAt(i)); \
//		DELETE_AGMAGICIP_ARRAYPTR(pA,agtrue) \
//	} \
//	ArrayPtrArray.RemoveAll(); \
//}
//
//#define DELETE_AGMAGICIP_MFC_ARRAYPTR_ARRAYPTR(pArrayPtrArray,bDeleteMe) \
//{ \
//	if(pArrayPtrArray!=NULL) \
//	{ \
//		agint32 n=pArrayPtrArray->GetSize(); \
//		for(agint32 i=0;i<n;i++) \
//		{ \
//			CPtrArray* pA=(CPtrArray*)(pArrayPtrArray->GetAt(i)); \
//			DELETE_AGMAGICIP_ARRAYPTR(pA,agtrue) \
//		} \
//		pArrayPtrArray->RemoveAll(); \
//		if(bDeleteMe) \
//		{ \
//			delete pArrayPtrArray; \
//			pArrayPtrArray=NULL; \
//		} \
//	} \
//}
//#endif	//#if AGMAGIC_SUPPORT_MFC

/**************************************************************************************/
#endif	//AGMAGIC_USED_FOR_RESOURCE

#endif // !defined(AGIMAGEDEFS_H__F249C9B4_93B8_47C0_B742_6289CCA0738A__INCLUDED_)
