// Experiment3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Experiment3.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//my stuff
HBITMAP imageBase;
HBITMAP imageMask;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EXPERIMENT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXPERIMENT3));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXPERIMENT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1); //(HBRUSH)GetStockObject(HOLLOW_BRUSH); //(HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EXPERIMENT3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	//new ones below, courtesy of thank you https://stackoverflow.com/questions/4052940/how-to-make-an-opengl-rendering-context-with-transparent-background
	////wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   int w = 200;
   int h = 168;

   imageBase = (HBITMAP)LoadImage(
	   NULL,
	   L"piplup5.bmp",////\\GameResources
	   IMAGE_BITMAP,
	   0,
	   0,
	   LR_LOADFROMFILE
   );
   imageMask = (HBITMAP)LoadImage(
	   NULL,
	   L"piplup5mask.bmp",////\\GameResources
	   IMAGE_BITMAP,
	   0,
	   0,
	   LR_LOADFROMFILE
   );


   //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_EX_LAYERED | WS_EX_APPWINDOW | WS_EX_TOPMOST | WS_EX_TRANSPARENT,//WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   //thank you Song Zhu and Greg https://stackoverflow.com/questions/65286495/make-a-win32-window-transparent-to-messages-click-touch-keyboard
   HWND hWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_APPWINDOW | WS_EX_TOPMOST, szTitle, szWindowClass,//WS_OVERLAPPEDWINDOW,    WS_EX_TRANSPARENT
	   WS_VISIBLE | WS_POPUP, 500, 150, w, h, NULL, NULL, hInstance, NULL);

   HWND hWnd2 = CreateWindowEx(WS_EX_LAYERED | WS_EX_APPWINDOW | WS_EX_TOPMOST | WS_EX_TRANSPARENT, szTitle, szWindowClass,//WS_OVERLAPPEDWINDOW,    WS_EX_TRANSPARENT
	   WS_VISIBLE | WS_POPUP, 800, 150, w, h, NULL, NULL, hInstance, NULL);

   if (!hWnd || !hWnd2)
   {
      return FALSE;
   }
   //SetCapture(hWnd);
   //ReleaseCapture();
   SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
   //thank you! https://newbedev.com/creating-a-transparent-window-in-c-win32
   SetLayeredWindowAttributes(hWnd, RGB(124, 254, 124), 0, LWA_COLORKEY);//previously transparent color was RGB(255, 255, 255) white  RGB(124, 254, 124) lime for v6

   //thank you! https://stackoverflow.com/questions/7724000/how-to-hide-collapse-main-menu-in-a-win32-mfc-application
   //Raymond Chen is the man
   SetMenu(hWnd, NULL); /* remove the menu */

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);


   /*
   SetLayeredWindowAttributes(hWnd2, 0, 255, LWA_ALPHA);
   SetLayeredWindowAttributes(hWnd2, RGB(255, 255, 255), 0, LWA_COLORKEY);
   SetMenu(hWnd2, NULL);
   ShowWindow(hWnd2, nCmdShow);
   UpdateWindow(hWnd2);*/

   return TRUE;
}


//static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
//	// List visible windows with a non-empty title
//	//PostMessage(hWnd, WM_LBUTTONDOWN, 1, lparam);
//	POINT atp = POINT();
//	atp.x = 500;
//	atp.y = 150;
//	HWND target = ChildWindowFromPoint(hWnd,
//		atp
//	);
//	PostMessage(target, WM_LBUTTONDOWN, 1, lparam);
//	return TRUE;
//}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_TIMER) {
		return 0;
	}
    switch (message)
    {
	case WM_CREATE:
		SetTimer(hWnd, 1, 0, NULL);//120 good for demo
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			HDC hDC_Main = GetDC(hWnd);
			HDC memoryDC = CreateCompatibleDC(hDC_Main);
			HDC tempDC = CreateCompatibleDC(memoryDC);
			HDC tempDC2 = CreateCompatibleDC(memoryDC);


			HBITMAP memoryBMP = (HBITMAP)CreateCompatibleBitmap(hDC_Main, 200, 200);
			HBITMAP selectedBMP = (HBITMAP)SelectObject(memoryDC, memoryBMP);


			HBITMAP temp2BMP = (HBITMAP)CreateCompatibleBitmap(hDC_Main, 200, 200);
			HBITMAP oldtemp2BMP = (HBITMAP)SelectObject(tempDC2, temp2BMP);
			
			RECT rect = { 0, 0, 200, 200 };
			HBRUSH limeBrush = CreateSolidBrush(RGB(124, 254, 124));
			//FillRect(tempDC2, &rect, WHITE_BRUSH);
			FillRect(memoryDC, &rect, limeBrush);//WHITE_BRUSH


			HBITMAP oldtempBMP = (HBITMAP)SelectObject(tempDC, imageMask);
			BitBlt(tempDC2, 0, 0, 200, 200, tempDC, 0 * 189, 0, SRCCOPY);
			BitBlt(tempDC, 0, 0, 200, 200, tempDC, 0 * 189, 0, NOTSRCCOPY);
			BitBlt(memoryDC, 0, 0, 200, 200, tempDC, 0 * 189, 0, SRCAND);
			DeleteObject(oldtempBMP);

			oldtempBMP = (HBITMAP)SelectObject(tempDC, imageBase);
			BitBlt(tempDC2, 0, 0, 200, 200, tempDC, 0 * 189, 0, SRCAND);


			BitBlt(memoryDC, 0, 0, 200, 200, tempDC2, 0 * 189, 0, SRCPAINT);

			BitBlt(hDC_Main, 0, 0, 200, 200, memoryDC, 0, 0, SRCCOPY);

			DeleteObject(oldtempBMP);
			DeleteObject(oldtemp2BMP);
			DeleteObject(temp2BMP);
			DeleteObject(selectedBMP);
			DeleteObject(memoryBMP);
			DeleteObject(tempDC2);
			DeleteObject(tempDC);
			DeleteObject(memoryDC);

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
	{
		int x = 1;
		x += 1;
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			HDC hDC_Main = GetDC(hWnd);
			HDC memoryDC = CreateCompatibleDC(hDC_Main);
			HDC tempDC = CreateCompatibleDC(memoryDC);


			HBITMAP memoryBMP = (HBITMAP)CreateCompatibleBitmap(hDC_Main, 200, 200);
			HBITMAP selectedBMP = (HBITMAP)SelectObject(memoryDC, memoryBMP);

			RECT rect = { 0, 0, 200, 200 };
			HBRUSH limeBrush = CreateSolidBrush(RGB(124, 254, 124));
			FillRect(memoryDC, &rect, limeBrush);

			HBITMAP oldtempBMP = (HBITMAP)SelectObject(tempDC, imageBase);
			BitBlt(memoryDC, 0, 0, 200, 200, tempDC, 0 * 189, 0, SRCCOPY);

			BitBlt(hDC_Main, 0, 0, 200, 200, memoryDC, 0, 0, SRCCOPY);

			DeleteObject(oldtempBMP);
			DeleteObject(selectedBMP);
			DeleteObject(memoryBMP);
			DeleteObject(tempDC);
			DeleteObject(memoryDC);

			EndPaint(hWnd, &ps);
		}
		break;
	}
	////case WM_MOUSEMOVE:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		break;
	case WM_LBUTTONDOWN:
	{
		int x = 1;
		x += 1;

		SetWindowPos(hWnd, NULL, -300, 150, 200, 168, 0);

		//EnumWindows(enumWindowCallback, lParam);
		//PostMessage(GetDesktopWindow(), message, wParam, lParam);
		break;
	}
	case WM_CANCELMODE:
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
