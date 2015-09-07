#include "Control.h"
using namespace View;

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

void Control::SetFont()
{
	HFONT hFont = CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma"));
	SendMessage(this->controlHandler, WM_SETFONT, WPARAM(hFont), TRUE);
}
