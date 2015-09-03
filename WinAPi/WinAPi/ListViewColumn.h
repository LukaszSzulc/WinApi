#pragma once
#include <string>
namespace View
{
	class ListViewColumn
	{
	public:
		ListViewColumn(int orderId, std::string headerText, int width)
		{
			this->orderId = orderId;
			this->width = width;
			this->headerText = headerText;
		}

		int GetOrderId()
		{
			return this->orderId;
		}

		std::string GetHeaderText()
		{
			return this->headerText;
		}

		int GetWidth()
		{
			return this->width;
		}
	private:
		int orderId;
		std::string headerText;
		int width;
	};
}