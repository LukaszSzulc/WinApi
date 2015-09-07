#pragma once
#include "Control.h"
#include <vector>
#include <commctrl.h>
#include "ListViewColumn.h"
#include "ListViewItem.h"
namespace View
{
	class ListView : public Control
	{
	public:
		ListView(std::string controlId, int positionTop, int positionLeft, int width, int height) :Control(controlId, positionTop, positionLeft, width, height)
		{
		}

		void AddColumn(ListViewColumn *column);
		void AddItem(ListViewItem *item);

		void Refresh();
		void Create() override;
		std::string GetContainerId();
		
	private:
		std::vector<ListViewColumn*> columns;
		std::vector<ListViewItem*> items;
		void Clear();
		void CreateNewItem(ListViewItem*& item, std::wstring containerId, std::wstring containerName, std::wstring image, std::wstring date, std::wstring status);

	};
}