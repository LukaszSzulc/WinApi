#include "Button.h"

void Button::Create()
{
	std::wstring str = this->ConvertToWstring(this->content);
	LPCWSTR buttonText = str.c_str();
	this->controlHandler = CreateWindowEx(WS_EX_CLIENTEDGE, _T("BUTTON"), buttonText, ES_PASSWORD | WS_CHILD | WS_VISIBLE | WS_BORDER,
		this->positionLeft, this->positionTop, this->width, this->height, Window::GetWindowHandler() , (HMENU)Window::GetHexControlId(this->controlId), Window::GetMainInstance(), NULL);
	this->SetSystemStyle();
}
