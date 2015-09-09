#pragma once
#include "SelectBox.h"

void SelectBox::Create()
{
	this->controlHandler = CreateWindow(WC_COMBOBOX, TEXT(""),
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		this->positionLeft, this->positionTop, this->width, this->height, View::Window::GetWindowHandler(), NULL, View::Window::GetMainInstance(),
		NULL);
}

void SelectBox::AddItem(std::string item)
{
	std::wstring comboBoxItem = this->ConvertToWstring(item);
	SendMessage(this->controlHandler, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(comboBoxItem.c_str()));
	SendMessage(this->controlHandler, CB_SETCURSEL, 0, 0);
	this->items.push_back(item);
}

void SelectBox::AddItems(std::vector<std::string> items)
{
	std::vector<std::string>::iterator it;
	for (it = items.begin(); it != items.end(); ++it)
	{
		std::wstring itemName = ConvertToWstring(*it);
		this->items.push_back(*it);
		SendMessage(this->controlHandler, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(itemName.c_str()));
	}
	SendMessage(this->controlHandler, CB_SETCURSEL, 0, 0);
}

std::string SelectBox::GetSelectedItem()
{
	int ItemIndex = SendMessage(this->controlHandler, static_cast<UINT>(CB_GETCURSEL),
	                            static_cast<WPARAM>(0), static_cast<LPARAM>(0));

	TCHAR ListItem[256];
	static_cast<TCHAR>(SendMessage(this->controlHandler, static_cast<UINT>(CB_GETLBTEXT),
	                               static_cast<WPARAM>(ItemIndex), reinterpret_cast<LPARAM>(ListItem)));
	std::wstring tmpString(ListItem);
	return std::string(tmpString.begin(), tmpString.end());
}

void SelectBox::Clear()
{
	this->items.clear();
	SendMessage(this->controlHandler, CB_RESETCONTENT, 0, 0);

}