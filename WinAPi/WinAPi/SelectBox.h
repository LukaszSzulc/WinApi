#pragma once
#include "Control.h"
#include <vector>
#include "Window.h"

class SelectBox : public View::Control
{
public:
	SelectBox(std::string controlId ,int positionLeft, int positionTop, int width, int height) : Control(controlId, positionTop, positionLeft, width, height)
	{
	}

	void Create() override;
	
	void AddItem(std::string item);

	void Refresh();

	std::string GetSelectedItem();
private:
	std::vector<std::string> items;
};