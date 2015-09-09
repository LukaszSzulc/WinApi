#pragma once
#include "Windows.h"
#include <string>
#include <map>
namespace View
{
	class Control
	{

	protected:
		std::string controlId;

		int positionLeft;

		int positionTop;

		int width;

		int height;

		HWND controlHandler;

		void SetSystemStyle();

		std::wstring ConvertToWstring(std::string itemToConvert);

		void SetFont();

	public:
		Control(std::string controlId, int positionTop, int positionLeft, int width, int height)
		{
			this->width = width;
			this->height = height;
			this->controlId = controlId;
			this->positionTop = positionTop;
			this->positionLeft = positionLeft;
		}

		~Control()
		{
			SendMessage(this->controlHandler, WM_CLOSE, 0, 0);
		}

		std::string GetControlId();

		HWND GetControlHandler();

		void virtual Create() = 0;
	};
}