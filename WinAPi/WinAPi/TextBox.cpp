#include "TextBox.h"
#include "Window.h"

void TextBox::Create()
{
	this->controlHandler = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
		positionLeft, positionTop, width, height, Window::GetWindowHandler(), NULL, Window::GetMainInstance(), NULL);
	this->SetSystemStyle();
}

std::string TextBox::GetText()
{
	//TODO replace with control Text;
	return NULL;
}

