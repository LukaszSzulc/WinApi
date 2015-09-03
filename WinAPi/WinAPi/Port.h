#pragma once
#include <string>

namespace Docker
{
	namespace Model
	{
		class Port
		{
		public:
			long PrivatePort;
			long PublicPort;
			std::string Type;
		};
	}
}