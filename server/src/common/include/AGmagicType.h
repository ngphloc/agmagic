#if !defined(AGMAGIC_TYPE_H__84245236_A336_11D2_84B1_00C0DFF84685__INCLUDED_)
#define AGMAGIC_TYPE_H__84245236_A336_11D2_84B1_00C0DFF84685__INCLUDED_

#include <TCHAR.h>	// For UNICODE support

//kieu va hang
#define		agbool		bool
#define		agtrue		true
#define		agfalse		false

#define		agchar		char
#define		agwchar		WCHAR
#define		agtchar		TCHAR

#define		agint8			char
#define		aguint8			unsigned char
#define		agint16			short
#define		aguint16		unsigned short
#define		agint32			long
#define		aguint32		unsigned long
#define		agint_xcoord	agint32
#define		agint_bu_ycoord agint32
#define		agint_td_ycoord agint32

#define		agint64			__int64
#define		aguint64		unsigned __int64
#define		agint_highest	agint64
#define		aguint_highest	aguint64
#define		aguint_id		aguint_highest
#define		agint			int		
#define		aguint			unsigned int		
#define     agreal32		float
#define     agreal64		double
#define     agreal80		long double
#define		agfreal			agreal64

#define		aguint8_max		(255)
#define		aguint16_max	(65535)
#define		aguint32_max	(4294967295)
#define		aguint64_max	(18446744073709551615)
#define		aguint8_min		0
#define		aguint16_min	0
#define		aguint32_min	0
#define		aguint64_min	0

#define		agint8_max	(127)
#define		agint16_max	(32767)
#define		agint32_max	(2147483647)
#define		agint64_max	(9223372036854775807)
#define		agint_max	(2147483647)
#define		agreal32_max	(3.4E+38)
#define		agreal64_max	(1.7E+308)
#define		agreal80_max	(1.2E+4932)
#define		agint8_min	(-128)
#define		agint16_min	(-32768)
#define		agint32_min	(-2147483648)
#define		agint64_min	(-9223372036854775808)
#define		agint_min	(-2147483648)
#define		agreal32_min	(3.4E-38)
#define		agreal64_min	(1.7E-308)
#define		agreal80_min	(1.2E-4932)

#define		aguint8_hex_max	0xFF
#define		aguint16_hex_max	0xFFFF
#define		aguint32_hex_max	0xFFFFFFFF
#define		aguint64_hex_max	0xFFFFFFFFFFFFFFFF
#define		aguint8_hex_min	0x00
#define		aguint16_hex_min	0x0000
#define		aguint32_hex_min	0x00000000
#define		aguint64_hex_min	0x0000000000000000

#define		agint8_hex_max	0x7F
#define		agint16_hex_max	0x7FFF
#define		agint32_hex_max	0x7FFFFFFF
#define		agint64_hex_max	0x7FFFFFFFFFFFFFFF
#define		agint8_hex_min	0x80
#define		agint16_hex_min	0x8000
#define		agint32_hex_min	0x80000000
#define		agint64_hex_min	0x8000000000000000
#define		AGCLRQUAD	RGBQUAD

typedef int (* agcmpfunc)(const void*, const void*);

typedef struct tagAGTD_POINT
{
    agint_xcoord	x;
    agint_td_ycoord	y;
} AGTD_POINT;
typedef struct tagAGBU_POINT
{
    agint_xcoord	x;
    agint_bu_ycoord	y;
} AGBU_POINT;

typedef struct tagAGTD_RECT
{
    agint_xcoord	left;
    agint_td_ycoord	top;
    agint_xcoord	right;
    agint_td_ycoord	bottom;
} AGTD_RECT;
typedef struct tagAGBU_RECT
{
    agint_xcoord	left;
    agint_bu_ycoord	top;
    agint_xcoord	right;
    agint_bu_ycoord	bottom;
} AGBU_RECT;
#define COPY_RECT_TO_RECT(xxxDstRect,xxxSrcRect) \
{ \
    xxxDstRect.left=xxxSrcRect.left; \
    xxxDstRect.top=xxxSrcRect.top; \
    xxxDstRect.right=xxxSrcRect.right; \
    xxxDstRect.bottom=xxxSrcRect.bottom; \
}

#ifndef WIN32
typedef struct tagSIZE
{
    agint32        cx;
    agint32        cy;
} SIZE;
#endif

//dinh nghia cac tien ich
#define AGMAX(a,b)            (((a) > (b)) ? (a) : (b))

#define AGMIN(a,b)            (((a) < (b)) ? (a) : (b))

#define	AGMAKE_UINT16(lo,hi)    ((aguint16)(((aguint8)(lo)) | ((aguint16)((aguint8)(hi))) << 8))
#define AGMAKE_UINT32(lo,hi)    ((aguint32)(((aguint16)(lo)) | ((aguint32)((aguint16)(hi))) << 16))
#define AGLO_UINT16_OF(l)       ((aguint16)(l))
#define AGHI_UINT16_OF(l)       ((aguint16)(((aguint32)(l) >> 16) & 0xFFFF))
#define AGLO_UINT8_OF(w)        ((aguint8)(w))
#define AGHI_UINT8_OF(w)        ((aguint8)(((aguint16)(w) >> 8) & 0xFF))

//tri tuyet doi cua hieu hai so
#ifndef AGABS_OF_SUB
#define AGABS_OF_SUB(a,b)  (((a)>(b))?((a)-(b)):((b)-(a)))
#endif

//Mot so lam toan hoc
#define AG_EUC_DIS(aa,bb)				(sqrt((agreal64)(aa)*(aa) + (agreal64)(bb)*(bb)))
#define AG_EUC_DIS_2(aa,bb,cc)			(sqrt((agreal64)(aa)*(aa) + (agreal64)(bb)*(bb) + (agreal64)(cc)*(cc)))
#define AG_EUC_DIS_NOTSQRT(aa,bb)		((agreal64)(aa)*(aa) + (agreal64)(bb)*(bb))
#define AG_EUC_DIS_NOTSQRT_2(aa,bb,cc)	((agreal64)(aa)*(aa) + (agreal64)(bb)*(bb) + (agreal64)(cc)*(cc))

//Cac define phu
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS || AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
	#define AGMAGIC_DIR_SPLASH			_T('\\')
	#define AGMAGIC_DIR_SPLASH_STR		_T("\\")
#elif AGMAGIC_OS_TYPE==AGMAGIC_LINUX_OS || AGMAGIC_OS_TYPE==AGMAGIC_UNIX_OS
	#define AGMAGIC_DIR_SPLASH			_T('/')
	#define AGMAGIC_DIR_SPLASH_STR		_T("/")
#else
	#error _T("Implement not yet")
#endif
	
#define	AGMAGIC_MAX_PATH_LENGTH		4096
#define	AG_DAU_NHAY_CSDL				_T("\'")
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS || AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
#define	AGMAGIC_DIALOG_BKCOLOR							(RGB(192,192,192))
//#define	AGMAGIC_DIALOG_BKCOLOR_USED_FOR_SEGMENT_TRANS	AGMAGIC_DIALOG_BKCOLOR
#endif
	
//define cac message
#define	AGMAGICIP_WM_FIRST								(WM_USER + 170)

#define AGMAGICIP_WM_RECEIVED_NEW_IMAGES				(AGMAGICIP_WM_FIRST + 1)
#define AGMAGICIP_WM_RECEIVED_USER_ACCESS				(AGMAGICIP_WM_FIRST + 2)
#define AGMAGICIP_WM_SEARCH_REQUIRE						(AGMAGICIP_WM_FIRST + 3)
#define AGMAGICIP_WM_SEARCH_RESULT						(AGMAGICIP_WM_FIRST + 4)
#define AGMAGICIP_WM_REQUIRE_SEND_ACCESS_FREQ_AGAIN		(AGMAGICIP_WM_FIRST + 5)
#define AGMAGICIP_WM_LISTCTRL_UPDATE_DOCUMENT_ALREADY	(AGMAGICIP_WM_FIRST + 6)
#define AGMAGICIP_WM_RECEIVED_OUTPUT_NOTICE				(AGMAGICIP_WM_FIRST + 7)

#endif // !defined(AGMAGIC_TYPE_H__84245236_A336_11D2_84B1_00C0DFF84685__INCLUDED_)
