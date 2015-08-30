#pragma once
#include <windows.h>
#include "Control.h"
#include <tchar.h>
#include <vector>
#include <iostream>
#include <map>


class Window
{
	
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

	void Initialize();

	static int GetHexControlId(std::string controlId);

private:
	static HINSTANCE mainInstance;
	static int controlCount;
	static void HandleButtonClick(WORD l_param);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static HWND windowHandler;
	static Control* GetControl(std::string controlId);
	static std::map<std::string, Control*> controls;
	static std::map<int, std::string> mapHexToString;
	int width;
	int height;
	int nCmdShow;

	static std::string GetHexIdByStringName(int hexId);
	static std::string GetControlId();
	void CreateApplicationWindow();
	void InitializeControls();
	void AddControl(Control* control);
	void HandleMessages();
	void CreateControls();
	void AddMapStringToHex(int hexId,std::string stringId);



};