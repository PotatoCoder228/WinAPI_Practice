// WinAPIPractice.cpp: определяет точку входа для приложения.
//

#include <Windows.h>
#include <fcntl.h>
#include <cstdio>
#include <io.h>
#include <locale.h>
#include <iostream>
#include <vector>

//my headers
#include "GraphManager.h"

/**
* @param hwnd - a window descriptor
* @param uMsg - a message code
* @param wParam, @param lParam - addition parameters
*/

graphic_utils::GraphManager manager;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) 
	{
	case WM_PAINT:
	{
		manager.draw(hwnd, wParam, lParam);
		return 0;
	}
	case WM_SIZE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hinstExe,
	HINSTANCE hinstDepr,
	PWSTR pszCmdLine,
	int iCmdShow)
{
	//a stupid crutch for UTF-16 "Windows" input
	_setmode(_fileno(stdin), _O_U16TEXT);

	setlocale(LOCALE_ALL, "ru_RU.UTF-8");
	char szAppName[] = "GraphManagerTest";
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndClass;
	//the struct size for future WinAPI updates
	wndClass.cbSize = sizeof(wndClass);
	//the window class style
	//CS_HREDRAW - the horizontal redrawing
	//CS_VREDRAW - the vertical redrawing
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	//the callback of current window
	wndClass.lpfnWndProc = WndProc;
	//
	wndClass.cbClsExtra = 0;
	//
	wndClass.cbWndExtra = 0;
	//
	wndClass.hInstance = hinstExe;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = CreateSolidBrush(RGB(50, 50, 50));
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndClass);
	hwnd = CreateWindow(
		szAppName,
		"The GraphManager Program",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinstExe,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//app lifecycle
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


/*
#include <fcntl.h>
#include <io.h>

void console() {
	while (true) {
		wchar_t chars[255];
		std::wcin >> chars;
		std::wcout << chars << std::endl;
	}
}

int WINAPI wWinMain(HINSTANCE hinstExe, 
	HINSTANCE hinstDepr, 
	PWSTR pszCmdLine,
	int nCmdShow)
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	std::setlocale(LOCALE_ALL, "ru_RU.UTF-8");
	std::wcout << L"Привет" << std::endl;
	void win_alloc();
	win_alloc();
	std::flush(std::wcout);
	console();
	return 0;
}

void win_alloc() {
	//GMEM_ZEROINIT - инициализация нулями
	std::wcout << TEXT(L"Выделили память под следующие числа: ")<<std::endl;
	GLOBALHANDLE moveable_ptr = GlobalAlloc(GMEM_MOVEABLE, sizeof(int)*2);
	int* ptr = (int*)GlobalLock(moveable_ptr);
	ptr[0] = 11;
	ptr[1] = 12;
	std::wcout<<ptr[0]<<L" "<<ptr[1]<< std::endl;
	GlobalUnlock(moveable_ptr);
	GlobalFree(moveable_ptr);
}
*/
