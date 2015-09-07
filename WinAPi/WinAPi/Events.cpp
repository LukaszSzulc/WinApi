#include "Events.h"
using namespace View;

void Events::HandleLoginEvent()
{
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	TextBox *login = Window::GetControl<TextBox>("Login");
	PasswordBox *password = Window::GetControl<PasswordBox>("Password");
	
	std::string dockerUrl = url->GetText();
	std::string dockerLogin = login->GetText();
	std::string dockerPassword = password->GetPassword();
}

void Events::HandleStopContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	int selectedIndex = listView->GetSelectedIndex();
	std::string containerId = listView->GetContainerId();
	listView->UpdateItem(selectedIndex, "Stoped");
}

void Events::HandleStartContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	int selectedIndex = listView->GetSelectedIndex();
	std::string containerId = listView->GetContainerId();
	listView->UpdateItem(selectedIndex, "Running");
}

void Events::HandleDeleteContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	int selectedIndex = listView->GetSelectedIndex();
	std::string containerId = listView->GetContainerId();
	listView->DeleteItem(selectedIndex);
	listView->Refresh();
}

void Events::HandleCreateNewContainerEvent()
{
	srand(time(NULL));
	int id = rand() % 100000 + 50000;
	ListView *listView = Window::GetControl<ListView>("ListView");
	ListViewItem *item = new ListViewItem(std::to_string(id), "Bruce Wayne", "ubuntu", "Running", "123456789");
	listView->AddItem(item);
}

