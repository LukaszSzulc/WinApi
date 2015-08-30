#include "Label.h"
#include "Window.h"

void Label::Create()
{
	std::wstring str = std::wstring(text.begin(), text.end());
	LPCWSTR controlText = str.c_str();
	this->controlHandler = CreateWindowEx(0, _T("Static"), NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, positionLeft, positionTop, width, height, Window::GetWindowHandler(), NULL, Window::GetMainInstance(), NULL);
	this->SetSystemStyle();
	SetWindowText(this->controlHandler, controlText);
}
