#include "Events.h"
using namespace View;

void Events::HandleListContainersEvent()
{
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	
	std::string dockerUrl = url->GetText();
}

void Events::HandleStopContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	if (listView->ItemsCount() != 0)
	{
		int selectedIndex = listView->GetSelectedIndex();
		std::string containerId = listView->GetContainerId();
		listView->UpdateItem(selectedIndex, "Stoped");
	}
	else
	{
		MessageBox(NULL, TEXT("Your container list looks sad :(, becouse it does not contain any elements, add new container or list containers again."), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}
}

void Events::HandleStartContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	if (listView->ItemsCount() != 0)
	{
		int selectedIndex = listView->GetSelectedIndex();
		std::string containerId = listView->GetContainerId();
		listView->UpdateItem(selectedIndex, "Running");
	}
	else
	{
		MessageBox(NULL, TEXT("Your container list looks sad :(, becouse does not contain any elements, add new container or list containers again."), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}

}

void Events::HandleDeleteContainerEvent()
{
	
	ListView *listView = Window::GetControl<ListView>("ListView");
	if(listView->ItemsCount() != 0)
	{
		int selectedIndex = listView->GetSelectedIndex();
		std::string containerId = listView->GetContainerId();
		listView->DeleteItem(selectedIndex);
		listView->Refresh();
	}
	else
	{
		MessageBox(NULL, TEXT("Your container list looks sad :(, becouse does not contain any elements, add new container or list containers again."), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}
}

void Events::HandleCreateNewContainerEvent()
{
	Window window(700, 450, Window::GetMainInstance(), Window::nCmdShow);
	window.Initialize();
	srand(time(NULL));
	int id = rand() % 100000 + 50000;
	ListView *listView = Window::GetControl<ListView>("ListView");
	ListViewItem *item = new ListViewItem(std::to_string(id), "Bruce Wayne", "ubuntu", "Running", "123456789");
	listView->AddItem(item);
}

