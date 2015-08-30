#pragma once
#include <windows.h>
#include "Control.h"
#include <tchar.h>
#include <vector>
#include <iostream>


class Window
{
	
private:
	static HWND windowHandler;
	int width;
	int height;
	int nCmdShow;
	static HINSTANCE mainInstance;
	std::vector<Control*> controls;
public:
	Window(int width, int height,HINSTANCE hinstance,int nCmdShow)
	{
		this->width = width;
		this->height = height;
		this->mainInstance = hinstance;
		this->nCmdShow = nCmdShow;
	}
	static HINSTANCE GetMainInstance();

	static HWND GetWindowHandler();

	void CreateApplicationWindow();

	void HandleMessages();

	void AddControl(Control* control);

	void InitializeControls();

};