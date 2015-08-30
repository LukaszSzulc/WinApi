#pragma once
#include "Control.h"

class Label : public Control
{
public:
	Label(std::string controlId, int positionTop, int positionLeft, int width, int height, std::string text) :Control(controlId, positionTop, positionLeft, width, height)
	{
		this->text = text;
	}

	void Create() override;
private:
	std::string text;
};