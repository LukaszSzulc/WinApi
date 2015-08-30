#pragma once
#include "Control.h"
#include "Window.h"

class Button : public Control
{
public:
	Button(std::string controlId, int positionTop, int positionLeft, int width, int height, std::string content) :Control(controlId, positionTop, positionLeft, width, height)
	{
		this->content = content;
	}

	void Create() override;

private:
	std::string content;
};