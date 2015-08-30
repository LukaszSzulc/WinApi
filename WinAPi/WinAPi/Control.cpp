#include "Control.h"

void Control::SetSystemStyle()
{
	HFONT defaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->controlHandler, WM_SETFONT, WPARAM(defaultFont), TRUE);
}
