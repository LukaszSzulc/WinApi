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
		void CreateNewItem(ListViewItem*& item, std::wstring containerId, std::wstring containerName, std::wstring image, std::wstring date, std::wstring status);
		void AddItem(ListViewItem *item);

		void AddItems(std::vector<ListViewItem*> items);

		void Create() override;

		int GetSelectedIndex();

		std::string GetContainerId();

		void Refresh();

		void DeleteItem(int index);

		void UpdateItem(int index, std::string status);

		int ItemsCount();

		void Clear();

	private:
		std::vector<ListViewColumn*> columns;
		
		std::vector<ListViewItem*> items;

		void AddItemsToListView();

		void CreateItem(std::wstring containerId, std::wstring containerName, std::wstring containerImage, std::wstring containerStatus, std::wstring date, int index = -1);
	};
}