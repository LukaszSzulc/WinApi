#pragma once

#include "Control.h"
namespace View
{
	class PasswordBox : public Control
	{
	public:
		PasswordBox(std::string controlId, int positionTop, int positionLeft, int width, int height) :Control(controlId, positionTop, positionLeft, width, height)
		{
		}

		std::string GetPassword();

		void Create() override;
	};
}