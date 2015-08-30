#include "ListView.h"
#include "Window.h"


void ListView::AddItem(ListViewItem *item)
{
	this->items.push_back(item);
}

void ListView::Create()
{
	this->controlHandler = CreateWindowEx(0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT,
		positionLeft, positionTop, width, height, Window::GetWindowHandler(), NULL, Window::GetMainInstance() , NULL);

	std::vector<ListViewItem*>::iterator it;
	for (it = this->items.begin(); it != this->items.end(); ++it)
	{
		std::string headerText = (*it)->GetHeaderText();
		std::wstring str = std::wstring(headerText.begin(), headerText.end());
		LPWSTR columnText = const_cast<LPWSTR>(str.c_str());
		LVCOLUMN column;
		column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		column.cx = (*it)->GetWidth();
		column.iSubItem = (*it)->GetOrderId();
		column.pszText = columnText;
		ListView_InsertColumn(this->controlHandler, this->items.size(), &column);
	}
}
