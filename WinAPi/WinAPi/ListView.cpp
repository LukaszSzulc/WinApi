#include "ListView.h"
#include "Window.h"

using namespace View;

void ListView::AddColumn(ListViewColumn *column)
{
	this->columns.push_back(column);
}

void ListView::CreateNewItem(ListViewItem*& item, std::wstring containerId, std::wstring containerName, std::wstring image, std::wstring date, std::wstring status)
{
	int currentsItemCount = this->items.size();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	lvi.pszText = const_cast<LPWSTR>(containerId.c_str());
	lvi.iItem = 0;
	lvi.iSubItem = 0;

	ListView_InsertItem(this->controlHandler, &lvi);
	ListView_SetItemText(this->controlHandler, 0, 1, const_cast<LPWSTR>(containerName.c_str()));
	ListView_SetItemText(this->controlHandler, 0, 2, const_cast<LPWSTR>(image.c_str()));
	ListView_SetItemText(this->controlHandler, 0, 3, const_cast<LPWSTR>(status.c_str()));
	ListView_SetItemText(this->controlHandler, 0, 4, const_cast<LPWSTR>(date.c_str()));
}

void ListView::AddItem(ListViewItem *item)
{
	std::wstring containerId = this->ConvertToWstring(item->GetContainerId());
	std::wstring containerName = this->ConvertToWstring(item->GetName());
	std::wstring image = this->ConvertToWstring(item->GetImage());
	std::wstring date = this->ConvertToWstring(item->GetCreated());
	std::wstring status = this->ConvertToWstring(item->GetStatus());
	CreateNewItem(item, containerId, containerName, image, date, status);
	this->items.push_back(item);
}

void ListView::Create()
{
	this->controlHandler = CreateWindowEx(0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_EDITLABELS,
		positionLeft, positionTop, width, height, Window::GetWindowHandler(), (HMENU)Window::GetHexControlId(this->controlId), Window::GetMainInstance() , NULL);

	std::vector<ListViewColumn*>::iterator it;
	int subItem = 0;
	for (it = this->columns.begin(); it != this->columns.end(); ++it, subItem++)
	{
		std::string headerText = (*it)->GetHeaderText();
		std::wstring str = std::wstring(headerText.begin(), headerText.end());
		LPWSTR columnText = const_cast<LPWSTR>(str.c_str());
		LVCOLUMN column;
		column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		column.cx = (*it)->GetWidth();
		column.iSubItem = (*it)->GetOrderId();
		column.pszText = columnText;
		column.iSubItem = subItem;
		ListView_InsertColumn(this->controlHandler, this->columns.size(), &column);
	}



//	lvi.mask = LVIF_TEXT;
//
//	lvi.pszText = _T("987654321");
//	lvi.iItem = 1;
//	lvi.iSubItem = 0;
//	ListView_InsertItem(this->controlHandler, &lvi);	
//	ListView_SetItemText(this->controlHandler, 1, 1, _T("Random name by docker"));
//	ListView_SetItemText(this->controlHandler, 1, 2, _T("ubuntu/lastest"));
//	ListView_SetItemText(this->controlHandler, 1, 3, _T("Running"));
//	ListView_SetItemText(this->controlHandler, 1, 4, _T("Epoch datetame"));

}

std::string ListView::GetContainerId()
{
	wchar_t *buffer = new wchar_t[1024];
	int i = SendMessage(this->controlHandler, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
	ListView_GetItemText(this->controlHandler, i, 0, buffer, 1024);
	std::wstring str(buffer);
	return std::string(str.begin(), str.end());
}

void ListView::Clear()
{
	ListView_DeleteAllItems(this->controlHandler);
}