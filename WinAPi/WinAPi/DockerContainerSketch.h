#pragma once


#include <string>
#include "DockerImage.h"

namespace Docker {
	namespace Model {
		class ContainerSketch {
		private:
			std::string Command;
			std::string ImageName;

		public:
			std::string getCommand();
			std::string getImageName();

			void setCommand(std::string command);
			void setImage(std::string imageName);
			void setImage(Docker::Model::Image image);
		};
	}
}