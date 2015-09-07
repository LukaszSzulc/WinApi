#include "Window.h"

using namespace View;

HINSTANCE Window::mainInstance = NULL;

HWND Window::windowHandler = NULL;

int Window::nCmdShow = 0;

std::map<std::string, Control*> Window::controls;

std::map<int, std::string> Window::mapHexToString;

int Window::controlCount = 0x0;

void Window::HandleButtonClick(WORD word)
{
	std::string controlId = GetHexIdByStringName(word);

	if (controlId == "ListContainers")
	{
		Events::HandleListContainersEvent();
	}
	if (controlId == "StartContainer")
	{
		Events::HandleStartContainerEvent();
	}
	if (controlId == "StopContainer")
	{
		Events::HandleStopContainerEvent();
	}
	if (controlId == "CreateContainer")
	{
		Events::HandleCreateNewContainerEvent();
	}
	if (controlId == "DeleteContainer")
	{
		Events::HandleDeleteContainerEvent();
	}
}


LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");

	switch (message)
	{
	case WM_COMMAND:
		HandleButtonClick(LOWORD(wParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void Window::CreateApplicationWindow()
{
	WNDCLASSEX wcex;
	auto className = _T("DockerClient");
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = this->WndProc;
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
	this->AddMapStringToHex(controlCount++, control->GetControlId());
	this->controls[control->GetControlId()] = control;;
}

void Window::InitializeControls()
{
	std::map<std::string, Control*>::iterator it;
	for (it = this->controls.begin(); it != this->controls.end(); ++it)
	{
		it->second->Create();
	}
}

void Window::CreateControls()
{
	Label* dockerUrlLabel = new Label("", 0, 0, 150, 20, "Docker Url");

	Button* listContainers = new Button("ListContainers", 40, 0, 150, 50, "ListContainers");
	Button* startContainerButton = new Button("StartContainer", 350, 150, 100, 40, "Start");
	Button* stopContainerButton = new Button("StopContainer", 350, 250, 100, 40, "Stop");
	Button* createContainerButton = new Button("CreateContainer", 350, 350, 100, 40, "Create");
	Button* deleteContainerButton = new Button("DeleteContainer", 350, 450, 100, 40, "Delete");

	TextBox* dockerUrl = new TextBox("DockerUrl", 20, 0, 150, 20);

	ListView* listView = new ListView("ListView", 0, 150, 550, 350);
	ListViewColumn* containerId = new ListViewColumn(0, "ContainerId", 150);
	ListViewColumn* name = new ListViewColumn(1, "Name", 100);
	ListViewColumn* image = new ListViewColumn(2, "Image", 100);
	ListViewColumn* status = new ListViewColumn(3, "Status", 100);
	ListViewColumn* created = new ListViewColumn(4, "Created", 100);
	listView->AddColumn(containerId);
	listView->AddColumn(name);
	listView->AddColumn(image);
	listView->AddColumn(status);
	listView->AddColumn(created);
	this->AddControl(listView);
	this->AddControl(listContainers);
	this->AddControl(dockerUrl);
	this->AddControl(startContainerButton);
	this->AddControl(createContainerButton);
	this->AddControl(deleteContainerButton);
	this->AddControl(stopContainerButton);
	this->AddControl(dockerUrlLabel);
}

void Window::Initialize()
{
	CreateApplicationWindow();
	CreateControls();
	InitializeControls();
	HandleMessages();
}


void Window::AddMapStringToHex(int hexId, std::string stringId)
{
	mapHexToString[hexId] = stringId;
}

std::string Window::GetHexIdByStringName(int hexId)
{
	return mapHexToString[hexId];
}

int Window::GetHexControlId(std::string controlId)
{
	std::map<int, std::string>::iterator it;
	for (it = mapHexToString.begin(); it != mapHexToString.end(); ++it)
	{
		if (it->second == controlId)
		{
			return it->first;
		}
	}
	return -1;
}
