#pragma once


#include <string>
#include <iostream>


namespace Docker {
	namespace Model {
		class Image {
		public:
			std::string Id;
			std::string ParentId;
			std::string RepoTags;
			unsigned int Created;
			unsigned int VirtualSize;
			
			std::ostream& operator<<(std::ostream& os);

			Image();

		};
	}
}