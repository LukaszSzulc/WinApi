#pragma once
#include <windows.h>
#include "Control.h"
#include <tchar.h>
#include <map>
#include "Label.h"
#include "Button.h"
#include "TextBox.h"
#include "PasswordBox.h"
#include "ListView.h"
#include "Events.h"

namespace View
{
	class Window
	{

	public:
		Window(int width, int height, HINSTANCE hinstance, int nCmdShow)
		{
			this->width = width;
			this->height = height;
			this->mainInstance = hinstance;
			this->nCmdShow = nCmdShow;
		}

		~Window()
		{
			delete this->mainInstance;
			delete this->windowHandler;
		}
		static HINSTANCE GetMainInstance();

		static HWND GetWindowHandler();


		static int GetHexControlId(std::string controlId);

		template<typename ControlType>
		static ControlType* GetControl(std::string controlId);

		void Initialize();

	private:
		static HINSTANCE mainInstance;
		static int controlCount;
		static void HandleButtonClick(WORD l_param);
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static HWND windowHandler;
		static std::map<std::string, Control*> controls;
		static std::map<int, std::string> mapHexToString;
		int width;
		int height;
		int nCmdShow;

		static std::string GetHexIdByStringName(int hexId);
		void CreateApplicationWindow();
		void InitializeControls();
		void AddControl(Control* control);
		void HandleMessages();
		void CreateControls();
		void AddMapStringToHex(int hexId, std::string stringId);



	};

	template <typename ControlType>
	ControlType* Window::GetControl(std::string controlId)
	{
		ControlType* control = dynamic_cast<ControlType*>(controls[controlId]);
		return control;

	}
}