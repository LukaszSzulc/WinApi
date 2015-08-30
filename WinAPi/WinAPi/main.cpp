#include <windows.h>
#include "Window.h"

// Global variables

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Window window(700, 450, hInstance, nCmdShow);
	window.Initialize();

	return 0;
}
