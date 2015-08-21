#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
#if		AGMAGIC_WINDOWS_OS_VER==AGMAGIC_WINDOWS_OS_95
	#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
	#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif

	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define _WIN32_WINNT 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif						

	#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define _WIN32_WINDOWS 0x0400 // Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
	#define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
	#endif
#elif	AGMAGIC_WINDOWS_OS_VER==AGMAGIC_WINDOWS_OS_98
	#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
	#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif

	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define _WIN32_WINNT 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif						

	#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
	#define _WIN32_IE 0x0401	// Change this to the appropriate value to target IE 5.0 or later.
	#endif
#elif	AGMAGIC_WINDOWS_OS_VER==AGMAGIC_WINDOWS_OS_NT40
	#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
	#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif

	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define _WIN32_WINNT 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif						

	#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
	#define _WIN32_IE 0x0401	// Change this to the appropriate value to target IE 5.0 or later.
	#endif
#elif	AGMAGIC_WINDOWS_OS_VER==AGMAGIC_WINDOWS_OS_ME
	#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
	#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif

	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define _WIN32_WINNT 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif						

	#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define _WIN32_WINDOWS 0x0490 // Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
	#define _WIN32_IE 0x0500	// Change this to the appropriate value to target IE 5.0 or later.
	#endif
#elif	AGMAGIC_WINDOWS_OS_VER==AGMAGIC_WINDOWS_OS_2000
	#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
	#define WINVER 0x0500		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif

	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define _WIN32_WINNT 0x0500		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif						

	#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define _WIN32_WINDOWS 0x0490 // Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
	#define _WIN32_IE 0x0501	// Change this to the appropriate value to target IE 5.0 or later.
	#endif
#elif	AGMAGIC_WINDOWS_OS_VER==AGMAGIC_WINDOWS_OS_XP
	#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
	#define WINVER 0x0501		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif

	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define _WIN32_WINNT 0x0501		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif						

	#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define _WIN32_WINDOWS 0x0490 // Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
	#define _WIN32_IE 0x0560	// Change this to the appropriate value to target IE 5.0 or later.
	#endif
#elif	AGMAGIC_WINDOWS_OS_VER==AGMAGIC_WINDOWS_OS_DOTNET_SERVER
	#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
	#define WINVER 0x0501		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif

	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define _WIN32_WINNT 0x0501		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif						

	#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define _WIN32_WINDOWS 0x0500 // Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
	#define _WIN32_IE 0x0560	// Change this to the appropriate value to target IE 5.0 or later.
	#endif
#endif	//AGMAGIC_WINDOWS_OS_VER==AGMAGIC_WINDOWS_OS_95
#else	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	#error	_T("Implement not yet")
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
 