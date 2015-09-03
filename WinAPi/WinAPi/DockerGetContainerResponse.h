#pragma once
#include <string>
#include <vector>
#include "Port.h"

namespace Docker
{
	namespace Model
	{
		class DockerGetContainerResponse
		{
			public:
				std::string ContainerId;
				std::vector<std::string> Names;
				std::string Image;
				std::string Commad;
				std::string Status;
				std::vector<Docker::Model::Port> Ports;
				long SizeRow;
				long SizeRootFs;
		};

	}
}