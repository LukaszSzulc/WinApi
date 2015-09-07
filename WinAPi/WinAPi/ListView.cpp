#include "ListView.h"
#include "Window.h"

using namespace View;

void ListView::AddColumn(ListViewColumn *column)
{
	this->columns.push_back(column);
}
void ListView::AddItem(ListViewItem *item)
{
	std::wstring containerId = this->ConvertToWstring(item -> GetContainerId());
	std::wstring containerName = this->ConvertToWstring(item -> GetName());
	std::wstring containerImage = this->ConvertToWstring(item -> GetImage());
	std::wstring conteinerStatus = this->ConvertToWstring(item->GetStatus());
	std::wstring creationDate = this->ConvertToWstring(item->GetCreated());
	CreateItem(containerId, containerName, containerImage, conteinerStatus, creationDate);
	std::vector<ListViewItem*>::iterator it;
	it = this->items.begin();
	this->items.insert(it,item);
}

void ListView::Create()
{
	this->controlHandler = CreateWindowEx(0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_EDITLABELS,
		positionLeft, positionTop, width, height, Window::GetWindowHandler(), (HMENU)Window::GetHexControlId(this->controlId), Window::GetMainInstance() , NULL);

	std::vector<ListViewColumn*>::iterator it;
	for (it = this->columns.begin(); it != this->columns.end(); ++it)
	{
		std::string headerText = (*it)->GetHeaderText();
		std::wstring str = std::wstring(headerText.begin(), headerText.end());
		LPWSTR columnText = const_cast<LPWSTR>(str.c_str());
		LVCOLUMN column;
		column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		column.cx = (*it)->GetWidth();
		column.iSubItem = (*it)->GetOrderId();
		column.pszText = columnText;
		ListView_InsertColumn(this->controlHandler, this->columns.size(), &column);
	}
}

int ListView::GetSelectedIndex()
{
	int i = SendMessage(this->controlHandler, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
	return i;
}

std::string ListView::GetContainerId()
{
	wchar_t *buffer = new wchar_t[1024];
	int i = SendMessage(this->controlHandler, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
	ListView_GetItemText(this->controlHandler, i, 0, buffer, 1024);
	std::wstring str(buffer);
	return std::string(str.begin(), str.end());
}

void ListView::Refresh()
{
	ListView_DeleteAllItems(this->controlHandler);
	this->AddItemsToListView();
}

void ListView::CreateItem(std::wstring containerId, std::wstring containerName, std::wstring containerImage, std::wstring containerStatus, std::wstring date)
{
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	int currentItem = this->items.size();
	lvi.pszText = const_cast<LPWSTR>(containerId.c_str());
	lvi.iItem = 0;
	lvi.iSubItem = 0;

	ListView_InsertItem(this->controlHandler, &lvi);
	ListView_SetItemText(this->controlHandler, 0, 1, const_cast<LPWSTR>(containerName.c_str()));
	ListView_SetItemText(this->controlHandler, 0, 2, const_cast<LPWSTR>(containerImage.c_str()));
	ListView_SetItemText(this->controlHandler, 0, 3, const_cast<LPWSTR>(containerStatus.c_str()));
	ListView_SetItemText(this->controlHandler, 0, 4, const_cast<LPWSTR>(date.c_str()));
}

void ListView::AddItemsToListView()
{
	std::vector<ListViewItem*>::iterator it;
	for (it = this->items.begin(); it != this->items.end(); ++it)
	{
		std::wstring containerId = this->ConvertToWstring((*it)->GetContainerId());
		std::wstring containerName = this->ConvertToWstring((*it)->GetName());
		std::wstring containerImage = this->ConvertToWstring((*it)->GetImage());
		std::wstring conteinerStatus = this->ConvertToWstring((*it)->GetStatus());
		std::wstring creationDate = this->ConvertToWstring((*it)->GetCreated());
		CreateItem(containerId, containerName, containerImage, conteinerStatus, creationDate);
	}
}

void ListView::DeleteItem(int index)
{
	std::vector<ListViewItem*>::iterator it;
	this->items.erase(this->items.begin() + index);
	ListView_DeleteItem(this->controlHandler, index);
}

void ListView::UpdateItem(int index, std::string status)
{
	if(this->items[index]->GetStatus() != status)
	{
		this->items[index]->SetStatus(status);
		this->Refresh();
	}
	else
	{
		MessageBox(NULL, TEXT("You must select diffrent state, becouse contaianer current state is equal to requested new state."), TEXT("Warning"), MB_OK | MB_ICONEXCLAMATION);
	}
}

int ListView::ItemsCount()
{
	return this->items.size();
}