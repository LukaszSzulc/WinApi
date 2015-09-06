#pragma once

#include <vector>
#include <string>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include "DockerImage.h"
#include "DockerContainer.h"


using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace web::json;

namespace Docker {
	class Client {
	private:
		std::string host;
		int port;
		bool https;

		std::wstring getBaseUrl();
		std::string Client::wstringToString(std::wstring wstr);

	public:
		Client();
		Client(std::string host);
		Client(std::string host, bool https);

		void setHost(std::string host);
		void setHttps(bool https);
		void setPort(int port);

		std::vector<Docker::Model::Image> getImages();
		std::vector<Docker::Model::Container> getContainers();
	};
}