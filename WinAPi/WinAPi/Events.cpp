#include "Events.h"
#include "DockerContainer.h"
#include <iostream>
#include "DockerClient.h"
using namespace View;

void Events::HandleListContainersEvent()
{
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	TextBox *port = Window::GetControl<TextBox>("DockerPort");
	ListView *listView = Window::GetControl<ListView>("ListView");
	SelectBox *selectBox = Window::GetControl<SelectBox>("SelectBox");
	std::string dockerUrl = url->GetText();
	if (dockerUrl == "" || port->GetText()=="")
	{
		MessageBox(NULL, TEXT("DockerUrl and port is required"), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}
	else
	{
		selectBox->Clear();
		listView->Clear();
		Docker::Client client;
		try
		{
			client.setHost(dockerUrl);
			client.setPort(atoi(port->GetText().c_str()));
			client.setHttps(false);
			std::vector<Docker::Model::Image> images = client.getImages();
			std::vector<Docker::Model::Container> containers = client.getContainers();
			listView->AddItems(containers);
			selectBox->AddItems(images);
		}
		catch (http_exception e)
		{
			std::string message = e.what();
			MessageBox(NULL, reinterpret_cast<LPCWSTR>(message.c_str()), TEXT("Error"), MB_ICONSTOP | MB_OK);
		}
	
	}
}

void Events::HandleDeleteContainerEvent()
{
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	TextBox *port = Window::GetControl<TextBox>("DockerPort");
	ListView *listView = Window::GetControl<ListView>("ListView");
	int selectedIndex = listView->GetSelectedIndex();

	if (listView->ItemsCount() != 0 && selectedIndex != -1 && url->GetText() != "" && port->GetText() != "")
	{

		Docker::Client client;
		client.setHost(url->GetText());
		client.setPort(atoi(port->GetText().c_str()));
		client.setHttps(false);
		try
		{
			std::string containerId = listView->GetContainerId();
			client.stopContainer(containerId);
			listView->DeleteItem(selectedIndex);
		}
		catch (http_exception e)
		{
			std::string message = e.what();
			MessageBox(NULL, reinterpret_cast<LPCWSTR>(message.c_str()), TEXT("Error"), MB_ICONSTOP | MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, TEXT("Your container list looks sad :(, becouse it does not contain any elements, add new container or list containers again."), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}
}

void Events::HandleRestartContainerEvent()
{
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	TextBox *port = Window::GetControl<TextBox>("DockerPort");
	ListView *listView = Window::GetControl<ListView>("ListView");
	int selectedIndex = listView->GetSelectedIndex();

	if (listView->ItemsCount() != 0 && selectedIndex != -1 && url->GetText() != "" && port->GetText() != "")
	{
		Docker::Client client;
		client.setHost(url->GetText());
		client.setPort(atoi(port->GetText().c_str()));
		client.setHttps(false);
		try
		{
			std::string containerId = listView->GetContainerId();
			client.restartContainer(containerId);
			std::vector<Docker::Model::Container> containers = client.getContainers();
			listView->Clear();
			listView->AddItems(containers);
		}
		catch (http_exception e)
		{
			std::string message = e.what();
			MessageBox(NULL, reinterpret_cast<LPCWSTR>(message.c_str()), TEXT("Error"), MB_ICONSTOP | MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, TEXT("Your container list looks sad :(, becouse does not contain any elements, add new container or list containers again."), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}

}

void Events::HandleCreateNewContainerEvent()
{
	ListView *listView = Window::GetControl<ListView>("ListView");
	TextBox *port = Window::GetControl<TextBox>("DockerPort");
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	SelectBox *selectBox = Window::GetControl<SelectBox>("SelectBox");
	TextBox *commands = Window::GetControl<TextBox>("Commands");
	std::string image = selectBox->GetSelectedItem();
	std::string command = commands->GetText();
	std::string dockerUrl = url->GetText();
	if(image == "" && command != "" && dockerUrl != "" && port->GetText() != "")
	{
		MessageBox(NULL, TEXT("WINDOWS 10 knows evrything about you,but we don't plese fill required fields image, commands and docker url"), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}
	else
	{
		Docker::Client client;
		client.setHost("winapidocker.cloudapp.net");
		client.setPort(atoi(port->GetText().c_str()));
		client.setHttps(false);
		try
		{
			Docker::Model::ContainerSketch sketch;
			sketch.setCommand(command);
			sketch.setImage(image);
			client.createContainer(sketch);
			std::vector<Docker::Model::Container> containers = client.getContainers();
			listView->Clear();
			listView->AddItems(containers);

		}
		catch (http_exception e)
		{
			std::string message = e.what();
			MessageBox(NULL, reinterpret_cast<LPCWSTR>(message.c_str()), TEXT("Error"), MB_ICONSTOP | MB_OK);
		}
	}
}

void Events::HandleKillContainerEvent()
{
	TextBox *url = Window::GetControl<TextBox>("DockerUrl");
	TextBox *port = Window::GetControl<TextBox>("DockerPort");
	ListView *listView = Window::GetControl<ListView>("ListView");
	int selectedIndex = listView->GetSelectedIndex();

	if (listView->ItemsCount() != 0 && selectedIndex != -1 && url->GetText() != "")
	{

		Docker::Client client;
		client.setHost(url->GetText());
		client.setPort(atoi(port->GetText().c_str()));
		client.setHttps(false);
		try
		{
			std::string containerId = listView->GetContainerId();
			client.killContainer(containerId);
			listView->DeleteItem(selectedIndex);
		}
		catch (http_exception e)
		{
			std::string message = e.what();
			MessageBox(NULL, reinterpret_cast<LPCWSTR>(message.c_str()), TEXT("Error"), MB_ICONSTOP | MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, TEXT("Your container list looks sad :(, becouse it does not contain any elements, add new container or list containers again."), TEXT("Error"), MB_ICONSTOP | MB_OK);
	}
}
