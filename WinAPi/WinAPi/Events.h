#pragma once
#include <string>
#include "Window.h"
#include "TextBox.h"
#include "PasswordBox.h"
#include "stdlib.h"
#include "time.h"
#include "SelectBox.h"

namespace View
{
	class Events
	{
	public:
		static void HandleListContainersEvent();

		static void HandleRestartContainerEvent();

		static void HandleDeleteContainerEvent();

		static void HandleCreateNewContainerEvent();

		static void HandleKillContainerEvent();

	};
}