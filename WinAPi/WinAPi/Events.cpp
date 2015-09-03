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
	std::string containerId = listView->GetContainerId();
}

void Events::HandleStartContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	std::string containerId = listView->GetContainerId();
}

void Events::HandleDeleteContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	std::string containerId = listView->GetContainerId();
}

void Events::HandleCreateNewContainerEvent()
{
	
}

