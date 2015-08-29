#pragma once
#include <windows.h>
#include "Control.h"
#include <tchar.h>
#include <vector>


class Window
{
	
private:
	HWND windowHandler;
	int width;
	int height;
	int nCmdShow;
	HINSTANCE mainInstance;
	std::vector<Control> controls;
public:
	Window(int width, int height,HINSTANCE hinstance,int nCmdShow)
	{
		this->width = width;
		this->height = height;
		this->mainInstance = hinstance;
		this->nCmdShow = nCmdShow;
	}
	HINSTANCE GetMainInstance();

	HWND GetWindowHandler();

	void CreateApplicationWindow();

	void HandleMessages();

	void AddControl(const Control &control);
};