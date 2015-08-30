#include <windows.h>
#include <tchar.h>
#include <string>
#include <commctrl.h>
#include "Window.h"
#include "Button.h"
#include "TextBox.h"
// Global variables

static TCHAR szWindowClass[] = _T("win32app");

static TCHAR szTitle[] = _T("Win32 Guided Tour Application");
static HWND mainWindow;
static HINSTANCE hInst;



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND CreateApplicationWindow(int width,int height)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);
		return NULL;
	}

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInst,
		NULL
		);
	return hWnd;
}

void SetSystemFont(HWND control)
{
	HFONT defaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(control, WM_SETFONT, WPARAM(defaultFont), TRUE);
}

HWND CreateLabel(int positionLeft,int positionTop,int width,int height,std::string text)
{
	std::wstring str = std::wstring(text.begin(), text.end());
	LPCWSTR controlText = str.c_str();
	HWND hStatic = CreateWindowEx(0, _T("Static"), NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, positionLeft, positionTop, width, height, mainWindow, NULL, hInst, NULL);
	SetSystemFont(hStatic);
	SetWindowText(hStatic, controlText);
	return hStatic;
}

HWND CreateTextBox(int positionLeft,int positionTop,int width,int height)
{
	HWND textHandler = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
		positionLeft, positionTop, width, height, mainWindow, NULL, hInst, NULL);
	SetSystemFont(textHandler);
	return textHandler;
}

HWND CreatePasswordBox(int positionLeft, int positionTop, int width, int height)
{
	HWND passwordHandler = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL, ES_PASSWORD|WS_CHILD | WS_VISIBLE | WS_BORDER,
		positionLeft, positionTop, width, height, mainWindow, NULL, hInst, NULL);
	SetSystemFont(passwordHandler);
	return passwordHandler;
}

HWND CreateButton(int positionLeft, int positionTop, int width, int height,std::string content)
{
	std::wstring str = std::wstring(content.begin(), content.end());
	LPCWSTR controlText = str.c_str();
	HWND buttonHandler = CreateWindowEx(WS_EX_CLIENTEDGE, WC_BUTTON, controlText, ES_PASSWORD | WS_CHILD | WS_VISIBLE | WS_BORDER,
		positionLeft, positionTop, width, height, mainWindow, NULL, hInst, NULL);
	SetSystemFont(buttonHandler);
	return buttonHandler;
}

HWND CreateListView(int positionLeft,int positionTop,int width,int height)
{
	HWND hListBox = CreateWindowEx(0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER|LVS_REPORT,
		positionLeft, positionTop, width, height, mainWindow, NULL, hInst, NULL);
	LVCOLUMN lvc;
	lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	return hListBox;
}

HWND CreateCheckBox(int positionLeft,int positionTop,int width,int height)
{
	HWND checkBoxHandler = CreateWindowEx(0, _T("BUTTON"), _T("Without login and password"), BS_CHECKBOX | WS_CHILD | WS_VISIBLE | WS_BORDER,
		positionLeft, positionTop, width, height, mainWindow, NULL, hInst, NULL);
	SetSystemFont(checkBoxHandler);
	return checkBoxHandler;
}

void ListViewInsertColumn(HWND listViewHandler,int orderId,int width,std::string text)
{
	std::wstring str = std::wstring(text.begin(), text.end());
	LPWSTR columnText = const_cast<LPWSTR>(str.c_str());
	LVCOLUMN column;
	column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	column.cx = width;
	column.iSubItem = orderId;
	column.pszText = columnText;
	ListView_InsertColumn(listViewHandler, 5, &column);
}

void HandleMessages(MSG& msg)
{

}


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Button *loginButton = new Button("LoginButton", 140, 0, 150, 50, "Login");
	Button *startContainerButton = new Button("StartContainer", 350, 150, 100, 40, "Start");
	Button *stopContainerButton = new Button("StopContainer", 350, 250, 100, 40, "Stop");
	Button *createContainerButton = new Button("CreateContainer", 350, 350, 100, 40, "Create");
	Button *deleteContainerButton = new Button("DeleteContainer", 350, 450, 100, 40, "Delete");
	TextBox *loginTextBox = new TextBox("Login", 20, 0, 150, 20);
	Window win(700, 450,hInstance,nCmdShow);
	win.CreateApplicationWindow();
	win.AddControl(loginButton);
	win.AddControl(loginTextBox);
	win.AddControl(startContainerButton);
	win.AddControl(createContainerButton);
	win.AddControl(deleteContainerButton);
	win.AddControl(stopContainerButton);
	win.InitializeControls();
	win.HandleMessages();

	//mainWindow = CreateApplicationWindow(700,450);
	//CreateLabel(0, 0, 150, 20, "Docker Url");
	//CreateTextBox(0, 20, 150, 20);
	//CreateLabel(0, 40, 150, 20, "Login");
	//CreateTextBox(0, 60, 150, 20);
	//CreateLabel(0, 80, 150, 20, "Password");
	//CreatePasswordBox(0, 100, 150, 20);
	//CreateButton(0, 140, 150, 50, "Login");
	//HWND listView = CreateListView(150, 0, 550, 350);
	//ListViewInsertColumn(listView, 0, 150, "ContainerID");
	//ListViewInsertColumn(listView, 1, 100, "Name");
	//ListViewInsertColumn(listView, 2, 100, "Image");
	//ListViewInsertColumn(listView, 3, 100, "Status");
	//ListViewInsertColumn(listView, 4, 100, "Created");
	//CreateButton(150, 350, 100, 40, "Start");
	//CreateButton(250, 350, 100, 40, "Stop");
	//CreateButton(350, 350, 100, 40, "Create");
	//CreateButton(450, 350, 100, 40, "Delete");

	

	//ShowWindow(mainWindow,
	//	nCmdShow);
	//UpdateWindow(mainWindow);

	//MSG msg;
	//HandleMessages(msg);
	return 0;
//	return (int)msg.wParam;
}


//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//	TCHAR greeting[] = _T("Hello, World!");
//
//	switch (message)
//	{	
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//
//	return 0;
//}