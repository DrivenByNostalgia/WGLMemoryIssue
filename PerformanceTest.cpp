#include "stdafx.h"
#include "windows.h"
#include <chrono>
#include <iostream>

// Code inspired by MSGalg, https://forums.geforce.com/default/topic/993265/activated-driver-slows-down-application/
void SetupWindow()
{
	HWND hWnd = CreateWindow(L"PerformanceTest", L"Test",
		WS_CAPTION | WS_BORDER | WS_SIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		0,
		0,
		10,
		10,
		NULL,
		NULL,
		nullptr,
		NULL);

	HDC hDC = GetDC(hWnd);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	ChoosePixelFormat(hDC, &pfd);

	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);
}

int main(int argc, char* argv[])
{
	int numRuns = 3;
	int testLength = 100000000;

	std::cout << "Before Window Creation\n";

	for (int i = 0; i < numRuns; i++)
	{
		std::cout << "Testing memory allocation performance " << (i + 1) << " / " << numRuns << ": ";

		auto start = std::chrono::system_clock::now();

		for (long i = 0; i < testLength; i++)
		{
			void* p = new char[1];

			delete[] p;
		}

		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		std::cout << elapsed.count() << " seconds" << std::endl;
	}

	SetupWindow();

	std::cout << "\nAfter Window Creation\n";

	for (int i = 0; i < numRuns; i++)
	{
		std::cout << "Testing memory allocation performance " << (i + 1) << " / " << numRuns << ": ";

		auto start = std::chrono::system_clock::now();

		for (long i = 0; i < testLength; i++)
		{
			void* p = new char[1];

			delete[] p;
		}

		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		std::cout << elapsed.count() << " seconds" << std::endl;
	}

	system("pause");

	return 0;
}