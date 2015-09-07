#pragma once

#include "DockerContainerSketch.h"

namespace Docker {
	namespace Model {
		void ContainerSketch::setCommand(std::string command) {
			this->Command = command;
		}

		void ContainerSketch::setImage(std::string imageName) {
			this->ImageName = imageName;
		}

		void ContainerSketch::setImage(Image image) {
			this->ImageName = image.Name;
		}

		std::string ContainerSketch::getCommand() {
			return this->Command;
		}

		std::string ContainerSketch::getImageName() {
			return this->ImageName;
		}
	}
}