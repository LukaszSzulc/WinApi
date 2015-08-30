#pragma once

#include "Control.h"

class TextBox : public Control
{
public:
	TextBox(std::string controlId, int positionTop, int positionLeft, int width, int height):Control(controlId,positionTop,positionLeft,width,height)
	{
	}
	
	std::string GetText();
	
	void Create() override;
};