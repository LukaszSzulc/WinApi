#include "TextBox.h"
#include "Window.h"
using namespace View;

void TextBox::Create()
{
	this->controlHandler = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL, WS_CHILD | WS_VISIBLE,
		positionLeft, positionTop, width, height, Window::GetWindowHandler(), NULL, Window::GetMainInstance(), NULL);
	this->SetSystemStyle();
}

std::string TextBox::GetText()
{
	wchar_t *buffor = new wchar_t[1024];
	GetWindowText(this->controlHandler, buffor, 1024);
	std::wstring text(buffor);
	return std::string(text.begin(),text.end());
}

