#include "PasswordBox.h"
#include "Window.h"

void PasswordBox::Create()
{
	this->controlHandler = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL, ES_PASSWORD | WS_CHILD | WS_VISIBLE | WS_BORDER,
		positionLeft, positionTop, width, height, Window::GetWindowHandler(), NULL, Window::GetMainInstance(), NULL);
	this->SetSystemStyle();
}

std::string PasswordBox::GetPassword()
{
	wchar_t *buffor = new wchar_t[1024];
	GetWindowText(this->controlHandler, buffor, 1024);
	std::wstring text(buffor);
	return std::string(text.begin(), text.end());
}
