// ATLPictureExDemo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PictureExDlg.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()


#ifdef _DEBUG
#pragma comment(linker,"/defaultlib:libcmtd.lib")
#endif

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	lpCmdLine = GetCommandLine();
    HRESULT hRes = CoInitialize(NULL);
    _ASSERTE(SUCCEEDED(hRes));
    _Module.Init(NULL, hInstance, NULL);

	CPictureExDlg dlg;
	dlg.DoModal();

	_Module.Term();
    CoUninitialize();
	return 0;
}
