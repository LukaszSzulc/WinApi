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

				std::string Id = std::string(W_Id.begin(), W_Id.end());
				std::string ParentId = std::string(W_ParentId.begin(), W_ParentId.end());

				Docker::Model::Image image;
				image.Id = Id;
				image.ParentId = ParentId;


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
}