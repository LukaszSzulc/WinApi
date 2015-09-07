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
	SendMessage(this->controlHandler, CB_ADDSTRING, 0, (LPARAM)(comboBoxItem.c_str()));
	this->items.push_back(item);
}

void SelectBox::Refresh()
{
}

std::string SelectBox::GetSelectedItem()
{
	int ItemIndex = SendMessage(this->controlHandler, (UINT)CB_GETCURSEL,
		(WPARAM)0, (LPARAM)0);

	TCHAR  ListItem[256];
	(TCHAR)SendMessage(this->controlHandler, (UINT)CB_GETLBTEXT,
		(WPARAM)ItemIndex, (LPARAM)ListItem);
	std::wstring tmpString(ListItem);
	return std::string(tmpString.begin(), tmpString.end());
}