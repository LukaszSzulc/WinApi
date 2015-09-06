#pragma once


#include <string>


namespace Docker {
	namespace Model {
		class Container {
		public:
			std::string Id;
			std::string Image;
			std::string Command;
			unsigned int Created;
			std::string Status;
			std::string Name;
			Container();
		};
	}
}