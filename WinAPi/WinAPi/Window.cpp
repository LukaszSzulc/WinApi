#include "Window.h"
#include "Label.h"
#include "Button.h"
#include "TextBox.h"
#include "PasswordBox.h"
#include "ListView.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");

	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HINSTANCE Window::mainInstance = NULL;

HWND Window::windowHandler = NULL;

void Window::CreateApplicationWindow()
{
	WNDCLASSEX wcex;
	auto className = _T("DockerClient");
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mainInstance;
	wcex.hIcon = LoadIcon(mainInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);
	}

	this->windowHandler = CreateWindow(
		className,
		className,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		mainInstance,
		NULL
		);
	ShowWindow(this->windowHandler,
		this->nCmdShow);
	UpdateWindow(this->windowHandler);
}

HWND Window::GetWindowHandler()
{
	return windowHandler;
}

HINSTANCE Window::GetMainInstance()
{
	return mainInstance;
}

void Window::HandleMessages()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::AddControl(Control* control)
{
	this->controls.push_back(control);
}

void Window::InitializeControls()
{
	std::vector<Control*>::iterator it;
	for (it = this->controls.begin(); it != this->controls.end(); ++it)
	{
		(*it)->Create();
	}
}

void Window::CreateControls()
{
	Label *dockerUrlLabel = new Label("", 0, 0, 150, 20, "Docker Url");
	Label *loginLabel = new Label("", 40, 0, 150, 20, "Login");
	Label *passwordLabel = new Label("", 80, 0, 150, 20, "Password");

	Button *loginButton = new Button("LoginButton", 140, 0, 150, 50, "Login");
	Button *startContainerButton = new Button("StartContainer", 350, 150, 100, 40, "Start");
	Button *stopContainerButton = new Button("StopContainer", 350, 250, 100, 40, "Stop");
	Button *createContainerButton = new Button("CreateContainer", 350, 350, 100, 40, "Create");
	Button *deleteContainerButton = new Button("DeleteContainer", 350, 450, 100, 40, "Delete");

	TextBox *dockerUrl = new TextBox("DockerUrl", 20, 0, 150, 20);
	TextBox *login = new TextBox("Login", 60, 0, 150, 20);
	PasswordBox *passwordBox = new PasswordBox("Password", 100, 0, 150, 20);

	ListView *listView = new ListView("ListView", 0, 150, 550, 350);
	ListViewItem *containerId = new ListViewItem(0, "ContainerId", 150);
	ListViewItem *name = new ListViewItem(1, "Name", 100);
	ListViewItem *image = new ListViewItem(2, "Image", 100);
	ListViewItem *status = new ListViewItem(3, "Status", 100);
	ListViewItem *created = new ListViewItem(4, "Created", 100);
	listView->AddItem(containerId);
	listView->AddItem(name);
	listView->AddItem(image);
	listView->AddItem(status);
	listView->AddItem(created);
	this->AddControl(listView);
	this->AddControl(loginButton);
	this->AddControl(dockerUrl);
	this->AddControl(startContainerButton);
	this->AddControl(createContainerButton);
	this->AddControl(deleteContainerButton);
	this->AddControl(stopContainerButton);
	this->AddControl(passwordBox);
	this->AddControl(dockerUrlLabel);
	this->AddControl(loginLabel);
	this->AddControl(passwordLabel);
	this->AddControl(login);

}
void Window::Initialize()
{
	CreateApplicationWindow();
	CreateControls();
	InitializeControls();
	HandleMessages();
}

