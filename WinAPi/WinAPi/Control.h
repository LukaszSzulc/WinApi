#pragma once
#include "Windows.h"
#include <string>

class Control
{
protected:
	std::string controlId;
	int positionLeft;
	int positionTop;
	int width;
	int height;
	HWND controlHandler;
public:
	Control(std::string controlId,int positionTop, int positionLeft, int width, int height)
	{
		this->width = width;
		this->height = height;
		this->controlId = controlId;
		this->positionTop = positionTop;
		this->positionLeft = positionLeft;
	}

	void virtual Create() = 0;

	void SetSystemStyle();
};