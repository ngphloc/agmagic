#include "stdafx.h"
#include "resource.h"

// Note the WINVER and _WINNT_WIN32 declarations in stdafx.h

INT_PTR CALLBACK DialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
  ) 
{
   RECT rcDesktop;
   RECT rcMe;

   UINT uResult;
   BYTE bTranslucency;

   const DWORD ANIMATION_MILLIS = 200;
   const BYTE TRANSLUCENCY = 192;
   const BYTE TRANSLUCENCY_STEP = 16;
   const DWORD TRANSLUCENCY_TIMEOUT = TRANSLUCENCY_STEP * ANIMATION_MILLIS / TRANSLUCENCY;

   switch (uMsg) {
   case WM_INITDIALOG:
      // Make the window appear centered.
      ::GetWindowRect(GetDesktopWindow(), &rcDesktop);
      ::GetWindowRect(hwndDlg, &rcMe);
      ::MoveWindow(hwndDlg, (rcDesktop.right - (rcMe.right - rcMe.left)) / 2,
         (rcDesktop.bottom - (rcMe.bottom - rcMe.top)) / 2,
         rcMe.right - rcMe.left, rcMe.bottom - rcMe.top, FALSE);

      // Ask the user if he want a flickering window
      uResult = ::MessageBox(hwndDlg, "Do you want it smooth?",
         "SmoothAlpha", MB_YESNO | MB_ICONQUESTION);

      switch (uResult) {
      case IDNO: // Do the usual :-|
         ::AnimateWindow(hwndDlg, ANIMATION_MILLIS, AW_BLEND);
         break;

      case IDYES: // Do it smooth ;-)
         // Make it a layered window.
         ::SetWindowLong(hwndDlg, GWL_EXSTYLE,
            ::GetWindowLong(hwndDlg, GWL_EXSTYLE) | WS_EX_LAYERED);

         // Completely transparent window - note the third parameter
         ::SetLayeredWindowAttributes(hwndDlg, 0, 0, LWA_ALPHA);

         // Show it _first_
         ::ShowWindow(hwndDlg, SW_SHOW);

         // Redraw contents NOW - no flickering since the window's not visible
         ::RedrawWindow(hwndDlg, NULL, NULL, RDW_UPDATENOW); 

         // Normally, you would use a timer here...
         for (bTranslucency = 0; bTranslucency < TRANSLUCENCY;
         bTranslucency+=TRANSLUCENCY_STEP) {
            // Adjust the translucency
            ::SetLayeredWindowAttributes(hwndDlg, 0, bTranslucency, LWA_ALPHA);

            // Wait
            ::Sleep(TRANSLUCENCY_TIMEOUT);
         }

         // Set the final translucency
         ::SetLayeredWindowAttributes(hwndDlg, 0, bTranslucency, LWA_ALPHA);
      }

      break;

   case WM_COMMAND:
      switch (LOWORD(wParam)) {
      case IDOK:
         ::EndDialog(hwndDlg, 1);
         break;

      case IDCANCEL:
         ::EndDialog(hwndDlg, 0);
         break;
      }
   }

   return 0;
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
   InitCommonControls(); // for ListView
   ::DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc, 0);
   return 0;
}



