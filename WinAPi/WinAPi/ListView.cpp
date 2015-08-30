#include "ListView.h"
#include "Window.h"


void ListView::AddColumn(ListViewColumn *column)
{
	this->columns.push_back(column);
}
void ListView::AddItem(ListViewItem *item)
{
	this->items.push_back(item);
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

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	lvi.pszText = _T("123456789");
	lvi.iItem = 0;
	lvi.iSubItem = 0;

	ListView_InsertItem(this->controlHandler, &lvi);
	ListView_SetItemText(this->controlHandler, 0, 1, _T("Random name by docker"));
	ListView_SetItemText(this->controlHandler, 0, 2, _T("ubuntu/lastest"));
	ListView_SetItemText(this->controlHandler, 0, 3, _T("Running"));
	ListView_SetItemText(this->controlHandler, 0, 4, _T("Epoch datetame"));


	lvi.mask = LVIF_TEXT;

	lvi.pszText = _T("987654321");
	lvi.iItem = 1;
	lvi.iSubItem = 0;
	ListView_InsertItem(this->controlHandler, &lvi);	
	ListView_SetItemText(this->controlHandler, 1, 1, _T("Random name by docker"));
	ListView_SetItemText(this->controlHandler, 1, 2, _T("ubuntu/lastest"));
	ListView_SetItemText(this->controlHandler, 1, 3, _T("Running"));
	ListView_SetItemText(this->controlHandler, 1, 4, _T("Epoch datetame"));

}

std::string ListView::GetContainerId()
{
	wchar_t *buffer = new wchar_t[1024];
	int i = SendMessage(this->controlHandler, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
	ListView_GetItemText(this->controlHandler, i, 0, buffer, 1024);
	std::wstring str(buffer);
	return std::string(str.begin(), str.end());
}
