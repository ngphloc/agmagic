#if !defined(AGMAGIC_DEFS_H)
#define AGMAGIC_DEFS_H

/************************cac define mac dinh*******************************************/
	
/////////////Dinh nghia he dieu hanh/////////////////////////////
#define		AGMAGIC_WINDOWS_OS			1
#define		AGMAGIC_WINCE_OS			2
#define		AGMAGIC_UNIX_OS				3
#define		AGMAGIC_LINUX_OS			4

#define	AGMAGIC_OS_TYPE			AGMAGIC_WINDOWS_OS

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	#define AGMAGIC_WINDOWS_OS_95					1
	#define AGMAGIC_WINDOWS_OS_98					2
	#define AGMAGIC_WINDOWS_OS_NT40					3
	#define AGMAGIC_WINDOWS_OS_ME					4
	#define AGMAGIC_WINDOWS_OS_2000					5
	#define AGMAGIC_WINDOWS_OS_XP					6
	#define AGMAGIC_WINDOWS_OS_DOTNET_SERVER		7
	#define AGMAGIC_WINDOWS_OS_2003					AGMAGIC_WINDOWS_OS_DOTNET_SERVER

	//#define	AGMAGIC_WINDOWS_OS_VER				AGMAGIC_WINDOWS_OS_2003
	#define	AGMAGIC_WINDOWS_OS_VER					AGMAGIC_WINDOWS_OS_XP
#endif

//dinh nghia moi truong phat trien
#define AGMAGIC_MSVC			1
#define AGMAGIC_BORLANDC		2
#define AGMAGIC_CBULIDER		3
#define AGMAGIC_DEVC			4
//Moi truong phat trien mac dinh la Microsoft VC
#define AGMAGIC_DEV_ENV			AGMAGIC_MSVC
//Phien ban cua moi truong phat trien neu la MSVC se theo macro _MSC_VER
//_MSC_VER Defines the major and minor versions of the compiler. 
//For example, 1300 for Microsoft Visual C++ .NET. 1300 represents version 13 
//and no point release. This represents the fact that there have been a total of 
//13 releases of the compiler. 
//If you type cl /? at the command line, you will see the full version for 
//the compiler you are using.
#define AGMAGIC_DEV_ENV_VER		1300

//////////Dinh nghia support MFC/////////
#define AGMAGIC_SUPPORT_MFC					1
#define AGMAGIC_SUPPORT_ADO					1
//dinh nghia AGMAGIC_MFC_VER tuong duong _MFC_VER cua he thong
//Visual Studio 6
#define	AGMAGIC_MFC_VER		0x0600
//Visual Studio .NET Beta (2001)
//#define	AGMAGIC_MFC_VER		0x0700
//Visual Studio 2003
//#define	AGMAGIC_MFC_VER		0x0710
//Visual Studio 2005
//#define	AGMAGIC_MFC_VER		0x0800
	
//////////Dinh nghia cac kieu thu vien/////////
#define AGMAGIC_WINDOWS_DLL								1
#define AGMAGIC_WINDOWS_REGULAR_STATIC_MFC_DLL			2
#define AGMAGIC_WINDOWS_REGULAR_SHARED_MFC_DLL			4
#define AGMAGIC_WINDOWS_EXTENSION_MFC_DLL				8

/////////Dinh nghia them//////////
#define VATI_EXTENSIONS

#ifndef THIS_PART_USE_AGMAGIC_LIBRARY
	#define AGMAGIC_DECL			__declspec(dllexport)
#else
	#define AGMAGIC_DECL			__declspec(dllimport)
#endif

/************************dieu chinh lai cac define*******************************************/

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

//dieu chinh lai _CRT_SECURE_NO_DEPRECATE
#if AGMAGIC_MFC_VER >= 0x0800

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif //_CRT_SECURE_NO_DEPRECATE

#ifdef _CRT_SECURE_NO_DEPRECATE
#ifdef  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#undef  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#endif //_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif //_CRT_SECURE_NO_DEPRECATE

#endif //AGMAGIC_MFC_VER
	
#else //AGMAGIC_OS_TYPE

#if AGMAGIC_DEV_ENV==AGMAGIC_MSVC || AGMAGIC_DEV_ENV==AGMAGIC_BORLANDC || AGMAGIC_DEV_ENV==AGMAGIC_CBULIDER
#error _T("Choose wrong developing environment")
#endif
	
//AGMAGIC_SUPPORT_MFC va AGMAGIC_SUPPORT_ADO phu thuoc vao AGMAGIC_OS_TYPE co bang AGMAGIC_WINDOWS_OS khong ?
#undef	AGMAGIC_SUPPORT_MFC
#define AGMAGIC_SUPPORT_MFC			0
#undef	AGMAGIC_SUPPORT_ADO
#define AGMAGIC_SUPPORT_ADO			0

#endif //AGMAGIC_OS_TYPE

#if !AGMAGIC_SUPPORT_MFC
#undef	AGMAGIC_MFC_VER
#define AGMAGIC_MFC_VER				0
#endif	//#if !AGMAGIC_SUPPORT_MFC

//Dinh nghia kieu thu vien
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	#if AGMAGIC_SUPPORT_MFC
		#define	AGMAGIC_LIBRARY_TYPE			AGMAGIC_WINDOWS_EXTENSION_MFC_DLL
	#else
		#define	AGMAGIC_LIBRARY_TYPE			AGMAGIC_WINDOWS_DLL
	#endif
#elif AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
	#error _T("Implement not yet")
#elif AGMAGIC_OS_TYPE==AGMAGIC_UNIX_OS
	#error _T("Implement not yet")
#elif AGMAGIC_OS_TYPE==AGMAGIC_LINUX_OS
	#error _T("Implement not yet")
#endif

/************************cac include ho tro*******************************************/
#ifndef AGMAGIC_USE_DEFS_BRIEFLY
#define AGMAGIC_LOG(szDllName,szInfo) ;

//ho tro cho thu vien
#include "AGmagicLib.h"

//Cac kieu du lieu
#include "AGmagicType.h"

//ho tro database
#include "AGmagicDB.h"
#endif	//AGMAGIC_USED_FOR_RESOURCE

#endif // !defined(AGMAGIC_DEFS_H)
