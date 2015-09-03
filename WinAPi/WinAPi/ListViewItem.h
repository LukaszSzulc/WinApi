#pragma once
namespace View
{
	class ListViewItem
	{
	public:
		ListViewItem(std::string containerId, std::string name, std::string image, std::string status, std::string created)
		{
			this->containerId = containerId;
			this->created = created;
			this->name = name;
			this->status = status;
			this->image = image;
		}

		std::string GetImage()
		{
			return this->image;
		}

		std::string GetContainerId()
		{
			return this->containerId;
		}

		std::string GetName()
		{
			return this->name;
		}

		std::string GetStatus()
		{
			return this->status;
		}

		std::string GetCreated()
		{
			return this->created;
		}
	private:
		std::string containerId;
		std::string name;
		std::string image;
		std::string status;
		std::string created;
	};
}