#include "PasswordBox.h"
#include "Window.h"

void PasswordBox::Create()
{
	this->controlHandler = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL, ES_PASSWORD | WS_CHILD | WS_VISIBLE | WS_BORDER,
		positionLeft, positionTop, width, height, Window::GetWindowHandler(), NULL, Window::GetMainInstance(), NULL);
	this->SetSystemStyle();
}