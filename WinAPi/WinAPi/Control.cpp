#include "Control.h"

void Control::SetSystemStyle()
{
	HFONT defaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->controlHandler, WM_SETFONT, WPARAM(defaultFont), TRUE);
}

std::wstring Control::ConvertToWstring(std::string itemToConvert)
{
	std::wstring str = std::wstring(itemToConvert.begin(), itemToConvert.end());
	return str;
}

HWND Control::GetControlHandler()
{
	return this->controlHandler;
}


std::string Control::GetControlId()
{
	return this->controlId;
}
