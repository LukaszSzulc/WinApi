#include "Events.h"
using namespace View;

void Events::HandleListContainersEvent()
{
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	ListView *listView = Window::GetControl<ListView>("ListView");
	SelectBox *selectBox = Window::GetControl<SelectBox>("SelectBox");
	std::string dockerUrl = url->GetText();
	if(dockerUrl == "")
	{
		MessageBox(NULL, TEXT("DockerUrl is required"), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}
	else
	{
		selectBox->Clear();
		listView->Clear();
	}
}

void Events::HandleStopContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	int selectedIndex = listView->GetSelectedIndex();

	if (listView->ItemsCount() != 0 && selectedIndex != -1)
	{
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
	int selectedIndex = listView->GetSelectedIndex();

	if (listView->ItemsCount() != 0 && selectedIndex != -1)
	{
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
	int selectedIndex = listView->GetSelectedIndex();

	if(listView->ItemsCount() != 0 && selectedIndex != -1)
	{
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
	ListView *listView = Window::GetControl<ListView>("ListView");
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	SelectBox *selectBox = Window::GetControl<SelectBox>("SelectBox");
	TextBox *commands = Window::GetControl<TextBox>("Commands");
	std::string image = selectBox->GetSelectedItem();
	std::string command = commands->GetText();
	std::string dockerUrl = url->GetText();
	if(image == "" || command == "" || dockerUrl == "")
	{
		MessageBox(NULL, TEXT("WINDOWS 10 knows evrything about you,but we don't plese fill required fields image, commands and docker url"), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}
	else
	{
		srand(time(NULL));
		int id = rand() % 100000 + 50000;
		ListViewItem *item = new ListViewItem(std::to_string(id), "Bruce Wayne", "ubuntu", "Running", "123456789");
		listView->AddItem(item);
	}
	
}

