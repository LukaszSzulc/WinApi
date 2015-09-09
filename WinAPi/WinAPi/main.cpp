#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "Window.h"

// Global variables
using namespace View;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Window window(1150, 450, hInstance, nCmdShow);
	window.Initialize();

	return 0;
}

//#include <iostream>
//#include "DockerClient.h"
//
//
//using namespace std;
//using namespace Docker;
//using namespace Docker::Model;
//
//
//int main() {
//	Client client;
//	client.setHost("127.0.0.1");
//	client.setPort(2375);
//	client.setHttps(false);
//
//	Docker::Model::ContainerSketch sketch;
//	sketch.setCommand("/bin/sh");
//	sketch.setImage("ubuntu:14.04");
//	// Mo¿esz te¿ tak:
//	// Docker::Model::Image image = client.getImages().at(0);
//	// sketch.setImage(image);
//	client.createContainer(sketch);
//
//	vector<Container> containers = client.getContainers();
//	std::cout << "Running containers: " << containers.size() << "\n";
//	for (int i = 0; i < containers.size(); ++i) {
//		Container c = containers.at(i);
//		std::cout << c.Name << "\n";
//	}
//
//	system("PAUSE");
//}