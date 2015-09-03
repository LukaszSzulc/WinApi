#pragma once
#include <string>
#include "Window.h"
#include "TextBox.h"
#include "PasswordBox.h"
namespace View
{
	class Events
	{
	public:
		static void HandleLoginEvent();
		static void HandleStartContainerEvent();
		static void HandleStopContainerEvent();
		static void HandleCreateNewContainerEvent();
		static void HandleDeleteContainerEvent();
	};
}