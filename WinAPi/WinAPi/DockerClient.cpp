#pragma once


#include "DockerClient.h"


namespace Docker {
	Client::Client() {}
	
	Client::Client(std::string host) {
		this->setHost(host);
	}

	Client::Client(std::string host, bool https) {
		this->setHost(host);
		this->setHttps(https);
	}

	void Client::setHost(std::string host) {
		this->host = host;
	}

	void Client::setPort(int port) {
		this->port = port;
	}

	void Client::setHttps(bool https) {
		this->https = https;
	}

	std::wstring Client::getBaseUrl() {
		std::string ret = "";
		if (this->https) ret += "https://";
		else ret += "http://";

		ret += this->host;

		ret += ":";
		ret += std::to_string(this->port);
		ret += "/";

		std::wstring return_value = std::wstring(ret.begin(), ret.end());
		return return_value;
	}

	std::string Client::wstringToString(std::wstring wstr) {
		return std::string(wstr.begin(), wstr.end());
	}

	std::vector<Docker::Model::Image> Client::getImages() {
		http_client client(this->getBaseUrl() + L"images/json?all=0");
		std::vector<Docker::Model::Image> images;

		client.request(methods::GET).then([=](http_response response){
			return response.extract_json();
		}).then([&](pplx::task<json::value> previousTask) {
			json::value const & v = previousTask.get();

			for (int i = 0; i < v.size(); ++i) {
				json::value val = v.at(i);

				std::wstring W_Id = val[U("Id")].as_string();
				std::wstring W_ParentId = val[U("ParentId")].as_string();
				std::wstring W_Name = val[U("RepoTags")].as_array()[0].as_string();

				std::string Id = std::string(W_Id.begin(), W_Id.end());
				std::string ParentId = std::string(W_ParentId.begin(), W_ParentId.end());
				std::string Name = std::string(W_Name.begin(), W_Name.end());

				Docker::Model::Image image;
				image.Id = Id;
				image.ParentId = ParentId;
				image.Name = Name;


				images.push_back(image);
			}
		}).wait();

		return images;

	}

	std::vector<Docker::Model::Container> Client::getContainers() {
		http_client client(this->getBaseUrl() + L"containers/json");
		std::vector<Docker::Model::Container> containers;

		client.request(methods::GET).then([=](http_response response){
			return response.extract_json();
		}).then([&](pplx::task<json::value> previousTask) {
			json::value const & v = previousTask.get();

			for (int i = 0; i < v.size(); ++i) {
				json::value val = v.at(i);

				std::wstring W_Id = val[U("Id")].as_string();
				std::wstring W_Image = val[U("Image")].as_string();
				std::wstring W_Name = val[U("Names")].as_array()[0].as_string();
				std::wstring W_Status = val[U("Status")].as_string();
				std::wstring W_Command = val[U("Command")].as_string();
				unsigned int Created = val[U("Created")].as_integer();

				std::string Id = wstringToString(W_Id);
				std::string Image = wstringToString(W_Image);
				std::string Name = wstringToString(W_Name);
				std::string Status = wstringToString(W_Status);
				std::string Command = wstringToString(W_Command);

				Docker::Model::Container container;
				container.Id = Id;
				container.Image = Image;
				container.Name = Name;
				container.Created = Created;
				container.Status = Status;
				container.Command = Command;

				containers.push_back(container);
			}
		}).wait();

		return containers;

	}

	void Client::createContainer(Docker::Model::ContainerSketch containerSketch) {
		std::string command = containerSketch.getCommand();
		std::string imageName = containerSketch.getImageName();

		std::wstring W_Command = std::wstring(command.begin(), command.end());
		std::wstring W_Image = std::wstring(imageName.begin(), imageName.end());
		std::wstring W_Id;

		json::value jsonObj;
		// jsonObj[U("Cmd")] = json::value::array();
		jsonObj[U("Cmd")] = json::value::string(W_Command);
		jsonObj[U("Image")] = json::value::string(W_Image);
		//jsonObj[U("VolumesFrom")] = json::value::array();
		//jsonObj[U("VolumesFrom")][0] = json::value::string(U("parent"));
		//jsonObj[U("VolumesFrom")][1] = json::value::string(U("other:ro"));
		jsonObj[U("Tty")] = json::value::boolean(true);

		http_client client(this->getBaseUrl() + L"containers/create");
		client.request(methods::POST, L"", jsonObj.to_string().c_str(), L"application/json").then([](http_response response) {
			return response.extract_json();
			//auto body = response.extract_string();
			//std::wcout << L"Added new Id: " << body.get().c_str() << std::endl;
		}).then([&](pplx::task<json::value> previousTask) {
			json::value v = previousTask.get();
			W_Id = v[U("Id")].as_string();
		}).wait();
		startContainer(W_Id);
	}

	void Client::startContainer(std::string Id) {
		std::wstring W_Id = std::wstring(Id.begin(), Id.end());
		this->startContainer(W_Id);
	}

	void Client::startContainer(std::wstring W_Id) {
		http_client client2(this->getBaseUrl() + L"containers/" + W_Id + L"/start");
		client2.request(methods::POST, L"", L"", L"").wait();
	}

	void Client::stopContainer(std::string Id) {
		std::wstring W_Id = std::wstring(Id.begin(), Id.end());
		this->stopContainer(W_Id);
	}

	void Client::stopContainer(std::wstring W_Id) {
		http_client client2(this->getBaseUrl() + L"containers/" + W_Id + L"/stop?t=5");
		client2.request(methods::POST, L"", L"", L"").wait();
	}

	void Client::restartContainer(std::string Id) {
		std::wstring W_Id = std::wstring(Id.begin(), Id.end());
		this->restartContainer(W_Id);
	}

	void Client::restartContainer(std::wstring W_Id) {
		http_client client2(this->getBaseUrl() + L"containers/" + W_Id + L"/restart?t=5");
		client2.request(methods::POST, L"", L"", L"").wait();
	}

	void Client::killContainer(std::string Id) {
		std::wstring W_Id = std::wstring(Id.begin(), Id.end());
		this->killContainer(W_Id);
	}

	void Client::killContainer(std::wstring W_Id) {
		http_client client2(this->getBaseUrl() + L"containers/" + W_Id + L"/kill");
		client2.request(methods::POST, L"", L"", L"").wait();
	}
}