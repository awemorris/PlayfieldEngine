#include <Windows.h>

int WINAPI wWinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpszCmd, int nCmdShow);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpszCmd, int nCmdShow)
{
	return wWinMain2(hInstance, hPrevInstance, lpszCmd, nCmdShow);
}
