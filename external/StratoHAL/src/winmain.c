/* -*- coding: utf-8; indent-tabs-mode: t; tab-width: 4; c-basic-offset: 4; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Windows Main
 */

/* HAL */
#include "stratohal/c89compat.h"
#include "stratohal/platform.h"
#include "d3drender.h"
#include "dsound.h"
#include "dsvideo.h"
#include "digamepad.h"
#include "stdfile.h"

/* Windows */
#include <windows.h>
#include <shlobj.h>			/* SHGetFolderPath() */
#include "resource.h"

/* Standard C */
#include <stdio.h>
#include <assert.h>
#include <signal.h>

/* msvcrt  */
#include <io.h>				/* _access() */
#include <locale.h>			/* setlocale() */

/* A macro to check whether a file exists. */
#define FILE_EXISTS(fname)	(_access(fname, 0) != -1)

/*
 * Constants
 */

/* A message to disable "Aero Snap" */
#define WM_RESTOREORIGINALSTYLE	(WM_USER + 1)

/* Buffer size for the window title. */
#define TITLE_BUF_SIZE	(1024)

/* Size of a log line. */
#define LOG_BUF_SIZE	(4096)

/* Frame per second. */
#define FPS				(30)

/* Millisecond of a frame. */
#define FRAME_MILLI		(16)

/* Millisecond to sleep once. */
#define SLEEP_MILLI		(5)

/* Buffer size of UTF-8/UTF-16 conversion. */
#define CONV_MESSAGE_SIZE	(65536)

/* Window class name. */
static const wchar_t wszWindowClassMain[] = L"AppMain";

/* i18n messages. */
enum {
	UIMSG_YES,
	UIMSG_NO,
	UIMSG_INFO,
	UIMSG_WARN,
	UIMSG_ERROR,
	UIMSG_CANNOT_OPEN_LOG,
	UIMSG_EXIT,
	UIMSG_TITLE,
	UIMSG_DELETE,
	UIMSG_OVERWRITE,
	UIMSG_DEFAULT,
	UIMSG_NO_SOUND_DEVICE,
	UIMSG_NO_GAME_FILES,
	UIMSG_WIN32_NO_DIRECT3D,
	UIMSG_WIN32_SMALL_DISPLAY,
};

/*
 * Variables
 */

/* Window title. (UTF-16) */
static wchar_t wszTitle[TITLE_BUF_SIZE];

/* Windows object. */
static HWND hWndMain;

/* Frame start time. */
static DWORD dwStartTime;

/* Running? */
static BOOL bRunning;

/* Force D3D9? */
static BOOL bForceD3D9;

/* Is full screen mode? */
static BOOL bFullScreen;

/* Move to the full screen mode? */
static BOOL bNeedFullScreen;

/* Move to the windowed mode? */
static BOOL bNeedWindowed;

/* Window style for the windowed mode. */
static DWORD dwStyle;

/* Position and size for the windowed mode. */
static RECT rcWindow;

/* RunFrame() allows rendering? */
static BOOL bRunFrameAllow;

/* Viewport. */
static int nViewportOffsetX;
static int nViewportOffsetY;
static int nViewportWidth;
static int nViewportHeight;

/* Scale factor for mouse coordinates. */
static float fMouseScale;

/* Is video playing? */
static BOOL bDShowMode;

/* Is video skippable by a click? */
static BOOL bDShowSkippable;

/* Log file. */
static FILE *pLogFile;
static wchar_t *pwszLogFilePath;

/*
 * Init Info
 */
static char *pszWindowTitle;
static int nWindowWidth;
static int nWindowHeight;

/*
 * Forward Declaration
 */

/* static */
static void SIGSEGV_Handler(int n);
static BOOL InitApp(HINSTANCE hInstance, int nCmdShow);
static void CleanupApp(void);
static BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
static void GameLoop(void);
static BOOL RunFrame(void);
static BOOL SyncEvents(void);
static BOOL WaitForNextFrame(void);
static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static int ConvertKeyCode(int nVK);
static void OnPaint(HWND hWnd);
static void OnCommand(WPARAM wParam, LPARAM lParam);
static void OnSizing(int edge, LPRECT lpRect);
static void OnSize(void);
static void UpdateScreenOffsetAndScale(int nClientWidth, int nClientHeight);
static BOOL OpenLogFile(void);
static void ShowLogFile(void);

/*
 * cpuid.c
 */
void check_cpuid(void);

/*
 * For a libraried version.
 */
#ifdef WINMAIN2
#define wWinMain wWinMain2
#endif

/*
 * WinMain
 */
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpszCmd,
	int nCmdShow)
{
	int nRet = 1;

	UNUSED_PARAMETER(hPrevInstance);
	UNUSED_PARAMETER(lpszCmd);

	signal(SIGABRT, SIGSEGV_Handler);

	do {
		/* Do the lower layer initialization. */
		if (!InitApp(hInstance, nCmdShow))
			break;

		/* Do a start call. */
		if (!on_event_start())
			break;

		/* Run the main loop. */
		GameLoop();

		/* Do a stop call.. */
		on_event_stop();

		nRet = 0;
	} while (0);

	/* Do the lower layer cleanup. */
	CleanupApp();

	ShowLogFile();

	return nRet;
}

static void SIGSEGV_Handler(int n)
{
	UNUSED_PARAMETER(n);

	log_error("Crashed.\n");

	exit(1);
}

/* Initialize the app. */
static BOOL InitApp(HINSTANCE hInstance, int nCmdShow)
{
	BOOL bFileOK;
	RECT rcClient;
	HRESULT hResult;

	setlocale(LC_NUMERIC, "C");

	/* Initialize COM. */
	hResult = CoInitialize(0);
	if (FAILED(hResult))
		return FALSE;

	/* Check SSE. */
#if defined(USE_SSE_DISPATCH)
	check_cpuid();
#endif

#if 0
	/* Check files. */
	bFileOK = FALSE;
	if (FILE_EXISTS(STARTUP_FILE))
		bFileOK = TRUE;
	else if (FILE_EXISTS(PACKAGE_FILE))
		bFileOK = TRUE;
	if (!bFileOK)
	{
		log_error(S_TR("No startup file."));
		return FALSE;
	}
#endif

	/* Initialize the file HAL. */
	if (!init_file())
		return FALSE;

	/* Do a boot callback. */
	if (!on_event_boot(&pszWindowTitle, &nWindowWidth, &nWindowHeight))
		return FALSE;

	/* Create a window. */
	if (!InitWindow(hInstance, nCmdShow))
		return FALSE;

	/* Initialize the graphics HAL. */
	if (!D3DInitialize(hWndMain, nWindowWidth, nWindowHeight, bForceD3D9))
	{
		log_info(S_TR("Failed to initialize the graphics."));
		return FALSE;
	}

	/* Correct the aspect ratio. */
	GetClientRect(hWndMain, &rcClient);
	if (rcClient.right != nWindowWidth || rcClient.bottom != nWindowHeight)
		UpdateScreenOffsetAndScale(rcClient.right, rcClient.bottom);

	/* Initialize the sound HAL. */
	if (!DSInitialize(hWndMain))
	{
		log_error(S_TR("Failed to initialize sound."));

		/* Fall-thru. */
	}

	/* Initialize the joystick HAL. */
	DInputInitialize(hInstance, hWndMain);

	return TRUE;
}

/* Cleanup the app. */
static void CleanupApp(void)
{
	/* Cleanup the joystick HAL. */
    DInputCleanup();

	/* Cleanup the graphics HAL. */
	D3DCleanup();

	/* Cleanup the sound HAL. */
	DSCleanup();

	/* Close the log file if opened. */
	if(pLogFile != NULL)
		fclose(pLogFile);
}

/* Create a window. */
static BOOL InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEXW wcex;
	RECT rc;
	int nVirtualScreenWidth, nVirtualScreenHeight;
	int nFrameAddWidth, nFrameAddHeight;
	int nMonitors;
	int nGameWidth, nGameHeight;
	int nWinWidth, nWinHeight;
	int nPosX, nPosY;
	int i;
	BOOL bInitialFullScreen;

	/* Register a window class. */
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize			= sizeof(WNDCLASSEXW);
	wcex.lpfnWndProc    = WndProc;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor        = LoadCursor(NULL, MAKEINTRESOURCE((WORD)(intptr_t)IDC_ARROW));
	wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszClassName  = wszWindowClassMain;
	wcex.hIconSm		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	if (!RegisterClassExW(&wcex))
		return FALSE;

	/* Select window styles. */
#if !defined(USE_EDITOR)
	dwStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_OVERLAPPED;
#else
	dwStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_OVERLAPPED | WS_THICKFRAME;
#endif

	/* Get a frame size. */
	nFrameAddWidth = GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	nFrameAddHeight = GetSystemMetrics(SM_CYCAPTION) +
					  GetSystemMetrics(SM_CYMENU) +
					  GetSystemMetrics(SM_CYFIXEDFRAME) * 2;

	/* Convert a window title from utf-8 to utf-16. */
	MultiByteToWideChar(CP_UTF8, 0, pszWindowTitle, -1, wszTitle, TITLE_BUF_SIZE - 1);

	/* Get a monitor count. */
	nMonitors = GetSystemMetrics(SM_CMONITORS);

	/* Start calclulation from this window size. */
	nGameWidth = nWindowWidth;
	nGameHeight = nWindowHeight;

	/* Get a display size. */
	nVirtualScreenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	nVirtualScreenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	nWinWidth = nGameWidth + nFrameAddWidth;
	nWinHeight = nGameHeight + nFrameAddHeight;

	/* If the display size is not enough. */
	bInitialFullScreen = FALSE;
	if (nVirtualScreenWidth < nWinWidth ||
		nVirtualScreenHeight < nWinHeight)
	{
		/* Scale down. */
		nWinWidth = nVirtualScreenWidth - 50;
		nWinHeight = nVirtualScreenHeight - 50;
		bInitialFullScreen = TRUE;
		bForceD3D9 = TRUE;
	}

	/* Center the window if not multiple monitors. */
	if (nMonitors == 1)
	{
		nPosX = (nVirtualScreenWidth - nWinWidth) / 2;
		nPosY = (nVirtualScreenHeight - nWinHeight) / 2;
	}
	else
	{
		nPosX = CW_USEDEFAULT;
		nPosY = CW_USEDEFAULT;
	}

	/* Create the main window. */
	hWndMain = CreateWindowExW(0, wszWindowClassMain, wszTitle, dwStyle,
							   nPosX, nPosY, nWinWidth, nWinHeight,
							   NULL, NULL, hInstance, NULL);
	if (hWndMain == NULL)
	{
		log_error("CreateWindowEx() failed.");
		return FALSE;
	}

	/* Adjust the window size. */
	SetRectEmpty(&rc);
	rc.right = nGameWidth;
	rc.bottom = nGameHeight;
	AdjustWindowRectEx(&rc, dwStyle, FALSE, (DWORD)GetWindowLong(hWndMain, GWL_EXSTYLE));
	SetWindowPos(hWndMain, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
	GetWindowRect(hWndMain, &rcWindow);

	/* Show the window. */
	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain);

	/* Process initial events. */
	dwStartTime = GetTickCount();
	for(i = 0; i < FPS / 10; i++)
		WaitForNextFrame();

	/* Enter the full screen mode if needed. */
	if (bInitialFullScreen)
	{
		bNeedFullScreen = TRUE;
		SendMessage(hWndMain, WM_SIZE, 0, 0);
	}

	return TRUE;
}

/* Run the game loop. */
static void GameLoop(void)
{
	BOOL bBreak;

	/* Set the running flag. */
	bRunning = TRUE;

	/* Allow redraw on WM_PAINT. */
	bRunFrameAllow = TRUE;

	/* Game Loop: */
	bBreak = FALSE;
	while (!bBreak)
	{
		/* Process events. */
		if (!SyncEvents())
			break;	/* "Close" pressed. */

		/* Sleep until a next frame. */
		if (!WaitForNextFrame())
			break;	/* "Close" pressed. */

		/* Get a frame start time. */
		dwStartTime = GetTickCount();

		/* Run a frame. */
		if (!RunFrame())
			bBreak = TRUE;
	}

	/* Clear the running flag. */
	bRunning = TRUE;
}

/* Run a frame. */
static BOOL RunFrame(void)
{
	BOOL bRet;

	/* If not ready. */
	if (!bRunFrameAllow)
		return TRUE;

	/* If a video is showing. */
	if(bDShowMode)
	{
		/* Process events. */
		if(!SyncEvents())
			return FALSE;

		/* Do a frame callback. */
		if(!on_event_frame())
			return FALSE;

		return TRUE;
	}

	/* Update DirectInput. */
	DInputUpdate();

	/* Start rendering. */
	D3DStartFrame();

	/* Do a frame callback. */
	bRet = TRUE;
	if(!on_event_frame())
	{
		/* Reached an exit. */
		bRet = FALSE;
		bRunFrameAllow = FALSE;
	}

	/* End rendering. */
	D3DEndFrame();

	return bRet;
}

/* Process events on the queue. */
static BOOL SyncEvents(void)
{
	/* DWORD dwStopWatchPauseStart; */
	MSG msg;

	/* Process events. */
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return FALSE;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return TRUE;
}

/* Sleep until a next frame. */
static BOOL WaitForNextFrame(void)
{
	DWORD end, lap, wait, span;

	/* If Direct3D is using. */
	if (!D3DIsSoftRendering())
	{
		/* Lower the CPU usage. */
		Sleep(1);
		return TRUE;
	}

	/* Our target frame rateis 60 fps. */
	span = FRAME_MILLI;

	/* Process events and sleep until a next frame time. */
	do {
		/* Process events if exit. */
		if(!SyncEvents())
			return FALSE;

		/* Get a lap time. */
		end = GetTickCount();
		lap = end - dwStartTime;

		/* Break if reached a next frame time. */
		if(lap >= span) {
			dwStartTime = end;
			break;
		}

		/* Decide a time to sleep. */
		wait = (span - lap > SLEEP_MILLI) ? SLEEP_MILLI : span - lap;

		/* Sleep. */
		Sleep(wait);
	} while(wait > 0);

	return TRUE;
}

/* Window procedure. */
static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int kc;

	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SYSKEYDOWN:	/* Alt + Key */
		/* Alt + Enter on D3D9. */
		if (wParam == VK_RETURN && (HIWORD(lParam) & KF_ALTDOWN))
		{
			if (!D3DIsSoftRendering())
			{
				if (!bFullScreen)
					bNeedFullScreen = TRUE;
				else
					bNeedWindowed = TRUE;
				SendMessage(hWndMain, WM_SIZE, 0, 0);
				return 0;
			}
		}

		/* Alt + F4 */
		if(wParam == VK_F4)
		{
#if 0
			if (MessageBox(hWnd,
						   win32_utf8_to_utf16("Are you sure you want to exit?"),
						   wszTitle, MB_OKCANCEL) == IDOK)
			{
#endif
				DestroyWindow(hWnd);
				return 0;
#if 0
			}
#endif
		}
		break;
	case WM_CLOSE:
#if 0
		if (MessageBox(hWnd,
					   win32_utf8_to_utf16("Are you sure you want to exit?"),
					   wszTitle,
					   MB_OKCANCEL) == IDOK)
#endif
			DestroyWindow(hWnd);
		return 0;
	case WM_LBUTTONDOWN:
		if (bRunning)
		{
			on_event_mouse_press(MOUSE_LEFT,
								 (int)((float)(LOWORD(lParam) - nViewportOffsetX) / fMouseScale),
								 (int)((float)(HIWORD(lParam) - nViewportOffsetY) / fMouseScale));
		}
		return 0;
	case WM_LBUTTONUP:
		if (bRunning)
		{
			on_event_mouse_release(MOUSE_LEFT,
								   (int)((float)(LOWORD(lParam) - nViewportOffsetX) / fMouseScale),
								   (int)((float)(HIWORD(lParam) - nViewportOffsetY) / fMouseScale));
		}
		return 0;
	case WM_RBUTTONDOWN:
		if (bRunning)
		{
			on_event_mouse_press(MOUSE_RIGHT,
								 (int)((float)(LOWORD(lParam) - nViewportOffsetX) / fMouseScale),
								 (int)((float)(HIWORD(lParam) - nViewportOffsetY) / fMouseScale));
		}
		return 0;
	case WM_RBUTTONUP:
		if (bRunning)
		{
			on_event_mouse_release(MOUSE_RIGHT,
								   (int)((float)(LOWORD(lParam) - nViewportOffsetX) / fMouseScale),
								   (int)((float)(HIWORD(lParam) - nViewportOffsetY) / fMouseScale));
		}
		return 0;
	case WM_KEYDOWN:
		/* Exclude auto repeat cases. */
		if((HIWORD(lParam) & 0x4000) != 0)
			return 0;

		/* If ESC is pressed in the full screen mode. */
		if((int)wParam == VK_ESCAPE && bFullScreen)
		{
			/* Change to the windowed mode. */
			bNeedWindowed = TRUE;
			SendMessage(hWndMain, WM_SIZE, 0, 0);
			return 0;
		}

		/* Other keys. */
		if (bRunning)
		{
			kc = ConvertKeyCode((int)wParam);
			if(kc != -1)
				on_event_key_press(kc);
		}
		return 0;
	case WM_KEYUP:
		if (bRunning)
		{
			kc = ConvertKeyCode((int)wParam);
			if(kc != -1)
				on_event_key_release(kc);
		}
		return 0;
	case WM_MOUSEMOVE:
		if (bRunning)
		{
			on_event_mouse_move((int)((float)(LOWORD(lParam) - nViewportOffsetX) / fMouseScale),
								(int)((float)(HIWORD(lParam) - nViewportOffsetY) / fMouseScale));
		}
		return 0;
	case WM_MOUSEWHEEL:
		if (bRunning)
		{
			if((int)(short)HIWORD(wParam) > 0)
			{
				on_event_key_press(KEY_UP);
				on_event_key_release(KEY_UP);
			}
			else if((int)(short)HIWORD(wParam) < 0)
			{
				on_event_key_press(KEY_DOWN);
				on_event_key_release(KEY_DOWN);
			}
		}
		return 0;
	case WM_KILLFOCUS:
		if (bRunning)
		{
			on_event_key_release(KEY_CONTROL);
		}
		return 0;
	case WM_PAINT:
		OnPaint(hWnd);
		return 0;
	case WM_COMMAND:
		OnCommand(wParam, lParam);
		return 0;
	case WM_GRAPHNOTIFY:
		if(!DShowProcessEvent())
			bDShowMode = FALSE;
		break;
	case WM_SIZING:
		OnSizing((int)wParam, (LPRECT)lParam);
		return TRUE;
	case WM_SIZE:
		OnSize();
		return 0;
	case WM_SYSCOMMAND:
		/* Hook maximize and enter full screen mode on D3D9. */
		if (wParam == SC_MAXIMIZE)
		{
			if (!D3DIsSoftRendering())
			{
				bNeedFullScreen = TRUE;
				SendMessage(hWndMain, WM_SIZE, 0, 0);
				return 0;
			}
		}

		/*
		 * Cancel Aero Snap:
		 *  - https://stackoverflow.com/questions/19661126/win32-prevent-window-snap
		 */
		if (wParam == (SC_MOVE | 2))
			wParam = SC_SIZE | 9;
		if ((wParam & 0xFFE0) == SC_SIZE && (wParam & 0x000F))
		{
			DWORD oldStyle = (DWORD)GetWindowLong(hWndMain, GWL_STYLE);
			PostMessage(hWndMain, WM_RESTOREORIGINALSTYLE, (WPARAM)GWL_STYLE, (LPARAM)oldStyle);
			SetWindowLong(hWndMain, GWL_STYLE, (LONG)(oldStyle & 0xFEFEFFFF));
			DefWindowProc(hWndMain, WM_SYSCOMMAND, wParam, lParam);
			return 0;
		}
		break;
	case WM_RESTOREORIGINALSTYLE:
		/* Restore Aero Snap. */
		if ((LONG)wParam == GWL_STYLE)
			SetWindowLong(hWndMain, GWL_STYLE, (LONG)lParam);
		return 0;
	case WM_NCLBUTTONDBLCLK:
		/* If the title bar is double-clicked. */
		if (wParam == HTCAPTION)
		{
			/* Change to the full screen mode. */
			if (!D3DIsSoftRendering())
			{
				bNeedFullScreen = TRUE;
				SendMessage(hWndMain, WM_SIZE, 0, 0);
				return 0;
			}
		}
		break;
	default:
		break;
	}

	/* Chain the system WndProc. */
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/* Convert a key code. */
static int ConvertKeyCode(int nVK)
{
	switch(nVK)
	{
	case VK_CONTROL:
		return KEY_CONTROL;
	case VK_SPACE:
		return KEY_SPACE;
	case VK_RETURN:
		return KEY_RETURN;
	case VK_UP:
		return KEY_UP;
	case VK_DOWN:
		return KEY_DOWN;
	case VK_LEFT:
		return KEY_LEFT;
	case VK_RIGHT:
		return KEY_RIGHT;
	case VK_ESCAPE:
		return KEY_ESCAPE;
	case 'S':
		return KEY_S;
	case 'L':
		return KEY_L;
	case 'H':
		return KEY_H;
	default:
		break;
	}
	return -1;
}

/* WM_PAINT */
static void OnPaint(HWND hWnd)
{
	HDC hDC;
	PAINTSTRUCT ps;

	hDC = BeginPaint(hWnd, &ps);
	RunFrame();
	EndPaint(hWnd, &ps);

	UNUSED_PARAMETER(hDC);
}

/* WM_COMMAND */
static void OnCommand(WPARAM wParam, LPARAM lParam)
{
	UINT nID;

	UNUSED_PARAMETER(lParam);

	nID = LOWORD(wParam);
#if 0
	switch(nID)
	{
	case ID_QUIT:
		PostMessage(hWndMain, WM_CLOSE, 0, 0);
		break;
	case ID_FULLSCREEN:
		SendMessage(hWndMain, WM_SYSCOMMAND, (WPARAM)SC_MAXIMIZE, (LPARAM)0);
		break;
	default:
		break;
	}
#endif
}

/* WM_SIZING */
static void OnSizing(int edge, LPRECT lpRect)
{
	RECT rcClient;
	float fPadX, fPadY, fWidth, fHeight, fAspect;
	int nOrigWidth, nOrigHeight;

	/* Get the rects before a size change. */
	GetWindowRect(hWndMain, &rcWindow);
	GetClientRect(hWndMain, &rcClient);

	/* Save the original window size. */
	nOrigWidth = rcWindow.right - rcWindow.left + 1;
	nOrigHeight = rcWindow.bottom - rcWindow.top + 1;

	/* Calc the paddings. */
	fPadX = (float)((rcWindow.right - rcWindow.left) -
					(rcClient.right - rcClient.left));
	fPadY = (float)((rcWindow.bottom - rcWindow.top) -
					(rcClient.bottom - rcClient.top));

	/* Calc the client size. */
	fWidth = (float)(lpRect->right - lpRect->left + 1) - fPadX;
	fHeight = (float)(lpRect->bottom - lpRect->top + 1) - fPadY;

	/* Adjust the window edges. */
	fAspect = (float)nWindowHeight / (float)nWindowWidth;
	switch (edge)
	{
	case WMSZ_TOP:
		fWidth = fHeight / fAspect;
		lpRect->top = lpRect->bottom - (int)(fHeight + fPadY + 0.5);
		lpRect->right = lpRect->left + (int)(fWidth + fPadX + 0.5);
		break;
	case WMSZ_TOPLEFT:
		fHeight = fWidth * fAspect;
		lpRect->top = lpRect->bottom - (int)(fHeight + fPadY + 0.5);
		lpRect->left = lpRect->right - (int)(fWidth + fPadX + 0.5);
		break;
	case WMSZ_TOPRIGHT:
		fHeight = fWidth * fAspect;
		lpRect->top = lpRect->bottom - (int)(fHeight + fPadY + 0.5);
		lpRect->right = lpRect->left + (int)(fWidth + fPadX + 0.5);
		break;
	case WMSZ_BOTTOM:
		fWidth = fHeight / fAspect;
		lpRect->bottom = lpRect->top + (int)(fHeight + fPadY + 0.5);
		lpRect->right = lpRect->left + (int)(fWidth + fPadX + 0.5);
		break;
	case WMSZ_BOTTOMRIGHT:
		fHeight = fWidth * fAspect;
		lpRect->bottom = lpRect->top + (int)(fHeight + fPadY + 0.5);
		lpRect->right = lpRect->left + (int)(fWidth + fPadX + 0.5);
		break;
	case WMSZ_BOTTOMLEFT:
		fHeight = fWidth * fAspect;
		lpRect->bottom = lpRect->top + (int)(fHeight + fPadY + 0.5);
		lpRect->left = lpRect->right - (int)(fWidth + fPadX + 0.5);
		break;
	case WMSZ_LEFT:
		fHeight = fWidth * fAspect;
		lpRect->left = lpRect->right - (int)(fWidth + fPadX + 0.5);
		lpRect->bottom = lpRect->top + (int)(fHeight + fPadY + 0.5);
		break;
	case WMSZ_RIGHT:
		fHeight = fWidth * fAspect;
		lpRect->right = lpRect->left + (int)(fWidth + fPadX + 0.5);
		lpRect->bottom = lpRect->top + (int)(fHeight + fPadY + 0.5);
		break;
	default:
		/* Aero Snap? */
		fHeight = fWidth * fAspect;
		lpRect->bottom = lpRect->top + (int)(fHeight + fPadY + 0.5);
		lpRect->right = lpRect->left + (int)(fWidth + fPadX + 0.5);
		break;
	}

	/* If there's a size change, update the viewport size. */
	if (nOrigWidth != lpRect->right - lpRect->left + 1 ||
		nOrigHeight != lpRect->bottom - lpRect->top + 1)
	{
		UpdateScreenOffsetAndScale((int)(fWidth + 0.5f), (int)(fHeight + 0.5f));
	}
}

/* WM_SIZE */
static void OnSize(void)
{
	RECT rc;

	if(bNeedFullScreen)
	{
		HMONITOR monitor;
		MONITORINFOEX minfo;

		bNeedFullScreen = FALSE;
		bNeedWindowed = FALSE;
		bFullScreen = TRUE;

		monitor = MonitorFromWindow(hWndMain, MONITOR_DEFAULTTONEAREST);
		minfo.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(monitor, (LPMONITORINFO)&minfo);
		rc = minfo.rcMonitor;

		dwStyle = (DWORD)GetWindowLong(hWndMain, GWL_STYLE);

		SetMenu(hWndMain, NULL);
		SetWindowLong(hWndMain, GWL_STYLE, (LONG)(WS_POPUP | WS_VISIBLE));
		SetWindowLong(hWndMain, GWL_EXSTYLE, WS_EX_TOPMOST);
		SetWindowPos(hWndMain, NULL, 0, 0, 0, 0,
					 SWP_NOMOVE | SWP_NOSIZE |
					 SWP_NOZORDER | SWP_FRAMECHANGED);
		MoveWindow(hWndMain, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
		InvalidateRect(hWndMain, NULL, TRUE);
	}
	else if (bNeedWindowed)
	{
		bNeedWindowed = FALSE;
		bNeedFullScreen = FALSE;
		bFullScreen = FALSE;

		SetWindowLong(hWndMain, GWL_STYLE, (LONG)dwStyle);
		SetWindowLong(hWndMain, GWL_EXSTYLE, 0);
		SetWindowPos(hWndMain, NULL, 0, 0, 0, 0,
					 SWP_NOMOVE | SWP_NOSIZE |
					 SWP_NOZORDER | SWP_FRAMECHANGED);
		MoveWindow(hWndMain, rcWindow.left, rcWindow.top,
				   rcWindow.right - rcWindow.left,
				   rcWindow.bottom - rcWindow.top, TRUE);
		InvalidateRect(hWndMain, NULL, TRUE);

		GetClientRect(hWndMain, &rc);
	}
	else
	{
		GetClientRect(hWndMain, &rc);
	}

	/* Update the screen offset and scale. */
	UpdateScreenOffsetAndScale(rc.right - rc.left, rc.bottom - rc.top);
}

/* Calculate screen offsets and scales. */
static void UpdateScreenOffsetAndScale(int nClientWidth, int nClientHeight)
{
	float fAspect, fUseWidth, fUseHeight;

	if (D3DIsSoftRendering())
	{
		nViewportWidth = nWindowWidth;
		nViewportHeight = nWindowHeight;
		nViewportOffsetX = 0;
		nViewportOffsetY = 0;
		fMouseScale = 1.0f;
		return;
	}

	/* Calc the aspect ratio of the game. */
	fAspect = (float)nWindowHeight / (float)nWindowWidth;

	/* Set the height temporarily with "width-first". */
    fUseWidth = (float)nClientWidth;
    fUseHeight = fUseWidth * fAspect;
    fMouseScale = (float)nClientWidth / (float)nWindowWidth;

	/* If height is not enough, determine width with "height-first". */
    if(fUseHeight > (float)nClientHeight)
	{
        fUseHeight = (float)nClientHeight;
        fUseWidth = (float)nClientHeight / fAspect;
        fMouseScale = (float)nClientHeight / (float)nWindowHeight;
    }

	/* Calc the viewport origin. */
	nViewportOffsetX = (int)((((float)nClientWidth - fUseWidth) / 2.0f) + 0.5);
	nViewportOffsetY = (int)((((float)nClientHeight - fUseHeight) / 2.0f) + 0.5);

	/* Save the viewport size. */
	nViewportWidth = (int)fUseWidth;
	nViewportHeight = (int)fUseHeight;

	/* Update the screen offset and scale for drawing subsystem. */
	D3DResizeWindow(nClientWidth, nClientHeight, nViewportOffsetX, nViewportOffsetY, nViewportWidth, nViewportHeight, fMouseScale);
}

/*
 * HAL
 */

/*
 * Show an INFO log.
 */
bool log_info(const char *s, ...)
{
	char buf[LOG_BUF_SIZE];
	va_list ap;

	OpenLogFile();

	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	if(pLogFile != NULL)
	{
		fprintf(pLogFile, "%s\n", buf);
		fflush(pLogFile);
		if(ferror(pLogFile))
			return false;
	}
	printf("%s\n", buf);

	return true;
}

/*
 * Show a WARN log.
 */
bool log_warn(const char *s, ...)
{
	char buf[LOG_BUF_SIZE];
	va_list ap;

	OpenLogFile();

	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	//MessageBoxW(hWndMain, win32_utf8_to_utf16(buf), wszTitle, MB_OK | MB_ICONWARNING);

	if(pLogFile != NULL)
	{
		fprintf(pLogFile, "%s\n", buf);
		fflush(pLogFile);
		if(ferror(pLogFile))
			return false;
	}
	printf("%s\n", buf);

	return true;
}

/*
 * Show an ERROR log.
 */
bool log_error(const char *s, ...)
{
	char buf[LOG_BUF_SIZE];
	va_list ap;

	OpenLogFile();

	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	//MessageBoxW(hWndMain, win32_utf8_to_utf16(buf), wszTitle, MB_OK | MB_ICONERROR);

	if(pLogFile != NULL)
	{
		fprintf(pLogFile, "%s\n", buf);
		fflush(pLogFile);
		if(ferror(pLogFile))
			return false;
	}
	printf("%s\n", buf);

	return true;
}

/*
 * Show an Out-of-memory error.
 */
bool log_out_of_memory(void)
{
	log_error("Out of memory.");
	return true;
}

/* Open the log file. */
static BOOL OpenLogFile(void)
{
	wchar_t path[MAX_PATH] = {0};

	/* If already open. */
	if(pLogFile != NULL)
		return TRUE;

	/* Create in the game directory. */
	pwszLogFilePath = wcsdup(L"log.txt");
	pLogFile = _wfopen(L"log.txt", L"w");
	if (pLogFile == NULL)
		return FALSE;

#if 0
	/* Create in AppData. */
	SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, path);
	wcsncat(path, L"\\", MAX_PATH - 1);
	wcsncat(path, win32_utf8_to_utf16(pszWindowTitle), MAX_PATH - 1);
	wcsncat(path, L"\\", MAX_PATH - 1);
	wcsncat(path, L"log.txt", MAX_PATH - 1);
	pwszLogFilePath = wcsdup(path);
	pLogFile = _wfopen(path, L"w");
	if (pLogFile == NULL)
		return FALSE;
#endif

	return TRUE;
}

/* Show the log file. */
static void ShowLogFile(void)
{
	if (pwszLogFilePath == NULL)
		return;

	ShellExecute(
		NULL,				// Parent window.
		L"open",			// Behavior.
        pwszLogFilePath,	// 開きたいファイルやURL
        NULL,				// Arguments.
        NULL,               // Working directory.
        SW_SHOWNORMAL);		// ShowWindow() status.
}

/*
 * Convert a utf-8 string to a utf-17 string.
 */
const wchar_t *win32_utf8_to_utf16(const char *utf8_message)
{
	static wchar_t wszMessage[CONV_MESSAGE_SIZE];

	const uint8_t *s;
	uint16_t *d;

	if (utf8_message == NULL)
		return L"";

	/* Don't use MultiByteToWideChar() as Windows 2000 doesn't support CP_UTF8. */
	s = (const uint8_t *)utf8_message;
	d = (uint16_t *)wszMessage;
	while (*s) {
		if (((*s) & 0x80) == 0) {
			/* 1-byte */
			*d++ = (uint16_t)((*s) & 0x7f);
			s += 1;
		} else if (((*s) & 0xe0) == 0xc0) {
			/* 2-byte */
			*d++ = (uint16_t)(
					  (((*(s + 0)) & 0x1f) << 6) |
					  (((*(s + 1)) & 0x3f) << 0)
				   );
			s += 2;
		} else if (((*s) & 0xf0) == 0xe0) {
			/* 3-byte */
			*d++ = (uint16_t)(
					  (((*(s + 0)) & 0x0f) << 12) |
					  (((*(s + 1)) & 0x3f) << 6) |
					  (((*(s + 2)) & 0x3f) << 0)
				   );
			s += 3;
		} else if (((*s) & 0xf8) == 0xf0) {
			/* 4-byte */
			uint32_t cp, hi, lo;
			cp = (uint32_t)(
					(((*(s + 0)) & 0x07) << 18) |
					(((*(s + 1)) & 0x3f) << 12) |
					(((*(s + 2)) & 0x3f) << 6) |
					(((*(s + 3)) & 0x3f) << 0)
				 );
			cp -= 0x10000;
			hi = 0xd800 + (uint32_t)((cp >> 10) & 0x3ff);
			lo = 0xdc00 + (uint32_t)((cp & 0x3ff));
			*d++ = (uint16_t)hi;
			*d++ = (uint16_t)lo;
			s += 4;
		} else {
			/* error */
			return L"";
		}
	}

	*d = L'\0';

#if 0
	MultiByteToWideChar(CP_UTF8, 0, utf8_message, -1, wszMessage, CONV_MESSAGE_SIZE - 1);
#endif

	return wszMessage;
}

/*
 * Convert a utf-16 string to a utf-8 string.
 */
const char *win32_utf16_to_utf8(const wchar_t *utf16_message)
{
	static char szMessage[CONV_MESSAGE_SIZE];

	const uint16_t *s;
	uint8_t *d;

	if (utf16_message == NULL)
		return "";

	/* Don't use MultiByteToWideChar() as Windows 2000 doesn't support CP_UTF8. */
	s = (const uint16_t *)utf16_message;
	d = (uint8_t *)szMessage;
	while (*s) {
		uint32_t cp;

		/* FIXME: support surrogate-pair */
		cp = *s++;

		if (cp <= 0x7f) {
			/* 1-byte */
			*d++ = cp & 0x7f;
		} else if (cp <= 0x7ff) {
			/* 2-byte */
			*d++ = (uint8_t)(0xc0 | ((cp >> 6) & 0x1f));
			*d++ = (uint8_t)(0x80 | ((cp >> 0) & 0x3f));
		} else if (cp <= 0xffff) {
			/* 3-byte */
			*d++ = (uint8_t)(0xe0 | ((cp >> 12) & 0x0f));
			*d++ = (uint8_t)(0x80 | ((cp >> 6) & 0x3f));
			*d++ = (uint8_t)(0x80 | ((cp >> 0) & 0x3f));
		} else if (cp <= 0x1fffff) {
			/* 4-byte */
			*d++ = (uint8_t)(0xf0 | ((cp >> 18) & 0x07));
			*d++ = (uint8_t)(0x80 | ((cp >> 12) & 0x3f));
			*d++ = (uint8_t)(0x80 | ((cp >> 6) & 0x3f));
			*d++ = (uint8_t)(0x80 | ((cp >> 0) & 0x3f));
		} else {
			/* error */
			return "";
		}
	}

	*d = '\0';

#if 0
	WideCharToMultiByte(CP_UTF8, 0, utf16_message, -1, szMessage, CONV_MESSAGE_SIZE - 1, NULL, NULL);
#endif

	return szMessage;
}

/*
 * Create a save directory.
 */
bool make_save_directory(void)
{
#if 0
	if (0) {
		/* Create in AppData. */
		wchar_t path[MAX_PATH] = {0};
		SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path);
		wcsncat(path, L"\\", MAX_PATH - 1);
		wcsncat(path, conv_utf8_to_utf16(conf_game_title), MAX_PATH - 1);
		CreateDirectory(path, NULL);
	} else {
#endif
		/* Create in the game directory. */
		CreateDirectoryW(L"save", NULL);
#if 0
	}
#endif

	return true;
}

/*
 * Get a real path of a file.
 */
char *make_real_path(const char *fname)
{
	wchar_t *buf;
	const char *result;
	size_t len;

#if 0
	if (0) {
		if (strncmp(fname, "save/", 5) == 0) {
			/* AppData */
			wchar_t path[MAX_PATH] = {0};
			SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path);
			wcsncat(path, L"\\", MAX_PATH - 1);
			wcsncat(path, conv_utf8_to_utf16(conf_game_title), MAX_PATH - 1);
			wcsncat(path, L"\\", MAX_PATH - 1);
			wcsncat(path, conv_utf8_to_utf16(fname), MAX_PATH - 1);
			return strdup(conv_utf16_to_utf8(path));
		}
	}
#endif

	/* TODO: absolute path. */

	/* Allocate a path buffer. */
	len = strlen(fname) + 1;
	buf = malloc(sizeof(wchar_t) * len);
	if (buf == NULL)
		return NULL;

	/* Create a path. */
	wcscpy(buf, win32_utf8_to_utf16(fname));

	result = win32_utf16_to_utf8(buf);
	free(buf);
	return strdup(result);
}

/*
 * Reset a lap timer.
 */
void reset_lap_timer(uint64_t *origin)
{
	*origin = GetTickCount();
}

/*
 * Get a timer lap.
 */
uint64_t get_lap_timer_millisec(uint64_t *origin)
{
	DWORD dwCur = GetTickCount();
	return (uint64_t)(dwCur - *origin);
}

/*
 * Play a video.
 */
bool play_video(const char *fname, bool is_skippable)
{
	char *path;

	path = make_real_path(fname);

	/* Set the event loop DirectShow mode. */
	bDShowMode = TRUE;

	/* Set a skippable flag. */
	bDShowSkippable = is_skippable;

	/* Start a playback. */
	BOOL ret = DShowPlayVideo(hWndMain, path, nViewportOffsetX, nViewportOffsetY, nViewportWidth, nViewportHeight);
	if(!ret)
		bDShowMode = FALSE;

	free(path);
	return ret;
}

/*
 * Stop a video.
 */
void stop_video(void)
{
	DShowStopVideo();
	bDShowMode = FALSE;
}

/*
 * Check if a video is playing back.
 */
bool is_video_playing(void)
{
	return bDShowMode;
}

/*
 * Check if the full screen mode is supported.
 */
bool is_full_screen_supported()
{
	return true;
}

/*
 * Check if in the full screen mode.
 */
bool is_full_screen_mode(void)
{
	return bFullScreen ? true : false;
}

/*
 * Enter the full screen mode.
 */
void enter_full_screen_mode(void)
{
	if (!bFullScreen)
	{
		bNeedFullScreen = TRUE;
		SendMessage(hWndMain, WM_SIZE, 0, 0);
	}
}

/*
 * Leave the full screen mode.
 */
void leave_full_screen_mode(void)
{
	if (bFullScreen)
	{
		bNeedWindowed = TRUE;
		SendMessage(hWndMain, WM_SIZE, 0, 0);
	}
}

/*
 * Get a system language.
 */
const char *get_system_language(void)
{
	DWORD dwLang = GetUserDefaultLCID() & 0x3ff;
	switch (dwLang) {
	case LANG_ENGLISH:
		return "en";
	case LANG_FRENCH:
		return "fr";
	case LANG_GERMAN:
		return "de";
	case LANG_SPANISH:
		return "es";
	case LANG_ITALIAN:
		return "it";
	case LANG_GREEK:
		return "el";
	case LANG_RUSSIAN:
		return "ru";
	case LANG_CHINESE_SIMPLIFIED:
		return "zh";
	case LANG_CHINESE_TRADITIONAL:
		return "tw";
	case LANG_JAPANESE:
		return "ja";
	default:
		break;
	}
	return "en";
}

/* Not used in Windows. */
void set_continuous_swipe_enabled(bool is_enabled)
{
	UNUSED_PARAMETER(is_enabled);
}
