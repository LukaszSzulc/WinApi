#pragma once
#include <string>
#include <vector>

namespace Docker
{
	namespace Service
	{
		//TODO:: Replace void with Docker Models https://docs.docker.com/reference/api/docker_remote_api_v1.20/
		class DockerService
		{
			void virtual ListContainers() = 0;

			void virtual GetContainerById(std::string containerId) = 0;
			// TODO:: Add Create Container Model https://docs.docker.com/reference/api/docker_remote_api_v1.20/ as a input argument;
			void virtual CreateContainer();

			void virtual StartContainer(std::string containerId) = 0;

			void virtual StopContainer(std::string containerId) = 0;

			void virtual RestartContainer(std::string containerId) = 0;

			void virtual DeleteContainer(std::string containerId) = 0;
		};
	}
}
